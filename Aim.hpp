#include "vars.hpp"
#include "interfaces.h"
#include "CUserCmd.h"
namespace Features::Aim {
	float RandomFloat(float min, float max)
	{
		static auto oRandomFloat = reinterpret_cast<float(*)(float, float)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomFloat"));
		return oRandomFloat(min, max);
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

			CVector enemyAngle = (bones[10].Origin() - localEyePosition).ToAngle() - cmd->viewangles;
			float fov = std::hypot(enemyAngle.x, enemyAngle.y);

			if (fov < bestFov) {
				bestFov = fov;
				bestAngle = enemyAngle;	
				bestTarget = player;
			}
		}
		bool clamped{ false };

		if (bestTarget && cfg::aim::bIsEnabled) {
			auto oldangle = cmd->viewangles;
			if (std::abs(bestAngle.x) > 255 || std::abs(bestAngle.y) > 255) {
				bestAngle.x = std::clamp(bestAngle.x, -255.f, 255.f);
				bestAngle.y = std::clamp(bestAngle.y, -255.f, 255.f);
				clamped = true;
			}
			if (cfg::aim::bSilentAim) {

				cmd->viewangles = cmd->viewangles + bestAngle;
			}
			else {

				I::engine->SetViewAngles(cmd->viewangles + bestAngle);
			}
			auto activeweapon = vars::localPlayer->getActiveWeapon();
			if (!activeweapon) {
				return;
			}
			auto wdata = activeweapon->getWeaponDate();
/*
			int hits = 0;
			int rays = 100;
			for (int i = 0; i < rays; i++)
			{
				auto spread = activeweapon->getInaccuracy() + activeweapon->getSpread();
				CVector randomizer = {
					RandomFloat(-(spread/2),spread/2),
					RandomFloat(-(spread / 2),spread / 2),
					RandomFloat(-(spread / 2),spread / 2)
				};
				auto randomized_forward = cmd->viewangles + randomizer;
				CTrace trace;
				I::engineTrace->TraceRay(
					CRay{ vars::localPlayer->GetEyePosition(),  vars::localPlayer->GetEyePosition() + randomized_forward * CVector{wdata->range,wdata->range,wdata->range} },
					MASK_SHOT, { bestTarget },
					trace
				);


				//std::cout << "spread: " << spread << std::endl;
				//std::cout << "randomizer: " << randomizer.x << ", " << randomizer.y << ", " << randomizer.z <<  std::endl;
				//std::cout << "randomized_forward: " << randomized_forward.x << ", " <<  randomized_forward.y << ", " <<  randomized_forward.z << std::endl;
				//std::cout << "is Trace an entity: " << (trace.entity == bestTarget) << std::endl;
				if (trace.entity && trace.entity == bestTarget) {
					hits++;
				}
			}
			std::cout << "hits: " << hits << std::endl;*/
			if (cfg::aim::bUseAutofire && activeweapon->nextPrimaryAttack() <= I::globals->currentTime && activeweapon->getInaccuracy() <= cfg::aim::flMaxInaccurracy && !clamped)
				cmd->buttons |= CUserCmd::IN_ATTACK;
			if(clamped)
				cmd->buttons &= ~CUserCmd::IN_ATTACK;
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