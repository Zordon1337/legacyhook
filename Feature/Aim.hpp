#include "../vars.hpp"
#include "../interfaces.h"
#include "../SDK/CUserCmd.h"
#include <random>
#include "../SDK/meth.cpp"
namespace Features::Aim {
	float RandomFloat(float min, float max)
	{
		static auto oRandomFloat = reinterpret_cast<float(*)(float, float)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomFloat"));
		return oRandomFloat(min, max);
	}

	static void setRandomSeed(int seed) noexcept
	{
		using randomSeedFn = void(*)(int);
		static auto randomSeed{ reinterpret_cast<randomSeedFn>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed")) };
		randomSeed(seed);
	}

	float getRandom(float bottom, float top) noexcept
	{
		std::random_device rd{};
		std::mt19937 generator(rd());
		std::uniform_real_distribution<float> dis(bottom, top);
		return dis(generator);
	}
	bool hitChance(CEntity* localPlayer, CEntity* entity, CEntity* weaponData, const CVector& destination, const CUserCmd* cmd, const int hitChance) noexcept
	{
		if (!hitChance)
			return true;

		constexpr int maxSeed = 255; //256

		const CVector angles(destination + cmd->viewangles);

		int hits = 0;
		const int hitsNeed = static_cast<int>(static_cast<float>(maxSeed) * (static_cast<float>(hitChance) / 100.f));
		const auto weapSpread = weaponData->getSpread();
		const auto weapInaccuracy = weaponData->getInaccuracy();
		const auto localEyePosition = localPlayer->GetEyePosition();
		const auto range = weaponData->getWeaponDate()->range;
		cfg::aim::drawPos.clear();
		for (int i = 0; i < maxSeed; ++i)
		{
			setRandomSeed(i + 1);
			float inaccuracy = RandomFloat(0.f, 1.f);
			float spread = RandomFloat(0.f, 1.f);
			const float spreadX = RandomFloat(0.f, 2.f * static_cast<float>(3.14));
			const float spreadY = RandomFloat(0.f, 2.f * static_cast<float>(3.14));

			inaccuracy *= weapInaccuracy;
			spread *= weapSpread;

			CVector spreadView{ (cosf(spreadX) * inaccuracy) + (cosf(spreadY) * spread),
							   (sinf(spreadX) * inaccuracy) + (sinf(spreadY) * spread), 0.0f };
			CVector direction{ (angles.x + (angles.y * spreadView.x) + (angles.z * spreadView.y)) * range };

			static CTrace trace;
			CVector pos;
			I::debugoverlay->ScreenPosition(localEyePosition + direction, pos);
			cfg::aim::drawPos["Line"] = pos;
			I::engineTrace->TraceRay({ localEyePosition, localEyePosition + direction }, MASK_SHOT, { localPlayer }, trace);
			if (trace.entity == entity)
				++hits;

			if (hits >= hitsNeed)
				return true;

			if ((maxSeed - i + hits) < hitsNeed)
				return false;
		}
		return false;
	}

	void RunAimbot(CUserCmd* cmd) {
		if (!vars::localPlayer) {
			return;
		}
		if (!cfg::aim::bIsEnabled) {
			return;
		}
		CVector bestAngle{};
		float bestFov = cfg::aim::flAimbotFov;
		CEntity* bestTarget = nullptr;

		auto activeweapon = vars::localPlayer->getActiveWeapon();
		if (!activeweapon) {
			return;
		}
		auto wdata = activeweapon->getWeaponDate();

		for (int i = 1; i < 32; i++) {
			auto player = I::entitylist->GetEntityFromIndex(i);
			if (!player || player->IsDormant() || player == vars::localPlayer ||
				player->getTeam() == vars::localPlayer->getTeam() || !player->isAlive())
				continue;

			CMatrix3x4 bones[128];
			if (!player->SetupBones(bones, 128, 0x7FF00, I::globals->currentTime)) continue;

			CVector localEyePosition = vars::localPlayer->GetEyePosition();

			// todo, if not visible, shot only visible hitboxes
			CTrace trace;
			I::engineTrace->TraceRay(
				CRay{ localEyePosition, bones[10].Origin() },
				MASK_SHOT, { vars::localPlayer },
				trace
			);

			if (!trace.entity || trace.fraction < 0.97f) continue;

			CVector enemyAngle = (bones[10].Origin() - localEyePosition).ToAngle() - (cmd->viewangles);
			float fov = std::hypot(enemyAngle.x, enemyAngle.y);

			if (fov < bestFov) {
				bestFov = fov;
				bestAngle = enemyAngle;	
				bestTarget = player;
			}
		}
		bool clamped{ false };

		if (bestTarget && cfg::aim::bIsEnabled) {
			/*

		
			too big skill issue to implement

			int hits = 0;
			int totalShots = 150;

			QAngle ang = cmd->viewangles.ToQangle() + bestAngle.ToQangle();

			CVector forward, right, up;
			meth::AngleVectors(ang, forward, right, up);

			float spread = activeweapon->getSpread();
			float inaccuracy = activeweapon->getInaccuracy();

			auto VecScale = [](const CVector& vec, float scalar) -> CVector {
				return { vec.x * scalar, vec.y * scalar, vec.z * scalar };
				};

			auto VecNormalize = [](const CVector& vec) -> CVector {
				float len = std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
				return (len != 0.f) ? CVector{ vec.x / len, vec.y / len, vec.z / len } : CVector{};
				};

			for (int i = 0; i < totalShots; i++) {
				float rand1 = RandomFloat(0.f, 1.f);
				float rand2 = RandomFloat(0.f, 2.f * M_PI);

				float total_deviation = spread + inaccuracy;
				float spreadX = std::cos(rand2) * rand1 * total_deviation;
				float spreadY = std::sin(rand2) * rand1 * total_deviation;


				CVector shotDir = forward + VecScale(right, spreadX) + VecScale(up, spreadY);
				shotDir = VecNormalize(shotDir);

				CTrace trace;
				I::engineTrace->TraceRay(
					CRay{ vars::localPlayer->GetEyePosition(), vars::localPlayer->GetEyePosition() + VecScale(shotDir, wdata->range) },
					MASK_SHOT, { vars::localPlayer },
					trace
				);

				if (trace.entity == bestTarget)
					hits++;
			}
			
			float hitchance = (hits / static_cast<float>(totalShots)) * 100.f;
			*/
			float hitchance = 1 / activeweapon->getInaccuracy();
			std::cout << "Hitchance: " << hitchance << "%" << std::endl;

			if (hitchance < cfg::aim::flHitChance) {
				return; 
			}
			if (cfg::aim::bSilentAim) {
				cmd->viewangles = cmd->viewangles + bestAngle;
			}
			else {
				I::engine->SetViewAngles(cmd->viewangles + bestAngle);
			}

			if (cfg::aim::bUseAutofire && activeweapon->nextPrimaryAttack() <= I::globals->currentTime)
				cmd->buttons |= CUserCmd::IN_ATTACK;
		}




	}

	void RunAntiAim(CUserCmd* cmd) {
		if (!(cmd->buttons & CUserCmd::IN_ATTACK) && cfg::aim::bAntiAim) {

			if (cmd->viewangles.y > 180.f)
				cmd->viewangles.y = -180.f;
			cmd->viewangles.x = 89;
			cmd->viewangles.y = vars::ang.y + cfg::aim::iAntiAimSpeed;


		}
	}
}