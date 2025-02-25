#include "hooks.h"
#include "interfaces.h"
#include "minhook/MinHook.h"
#include <iostream>
#include "vars.hpp"
#include <string>
#include "meth.h"
#include <thread>
#include <chrono>

HFont WatermarkFont;
HFont MediumFont;
void hk::Init() {

	if (MH_Initialize())
		throw std::runtime_error("Unable to initialize minhook");
	MH_CreateHook(
		memory::Get(I::clientmode, 24),
		&CreateMove,
		reinterpret_cast<void**>(&CreateMoveOriginal)
	);

	MH_CreateHook(
		memory::Get(I::panel, 41),
		&PaintTraverse,
		reinterpret_cast<void**>(&PaintTraverseOriginal)
	);
	MH_CreateHook(
		memory::Get(I::baseclient, 36),
		&FrameStage,
		reinterpret_cast<void**>(&FrameStageoriginal)
	);
	MH_EnableHook(MH_ALL_HOOKS);

	WatermarkFont = I::surface->CreateFont();
	MediumFont = I::surface->CreateFont();
	I::surface->SetFontGlyphSet(WatermarkFont, "Arial", 18, 400, 0, 0, 0x200);
	I::surface->SetFontGlyphSet(MediumFont, "Arial", 16, 400, 0, 0, 0x200);
}

bool __stdcall hk::CreateMove(float frameTime, CUserCmd* cmd) noexcept
{
	if (!cmd->command_number)
		return hk::CreateMoveOriginal(I::clientmode, frameTime,cmd);

	if (CreateMoveOriginal(I::clientmode, frameTime, cmd))
		I::engine->SetViewAngles(cmd->viewangles);

	if (I::engine->IsInGame())
	{
		auto localPlayer = I::entitylist->GetEntityFromIndex(I::engine->GetLocalPlayerIndex());
		vars::localPlayer = localPlayer;
		if (localPlayer)
		{
			if (!(localPlayer->getFlags() & CEntity::FL_ONGROUND)) {
				if (!(localPlayer->getFlags() & CEntity::FL_ONGROUND))
					cmd->buttons &= ~CUserCmd::IN_JUMP;
				else
					cmd->buttons |= CUserCmd::IN_JUMP;
			}

			if(!true) // reserved for autofire check
				if (!(cmd->buttons & CUserCmd::IN_ATTACK)) return false;

			CVector m_oldangle = cmd->viewangles;
			float m_oldforward = cmd->forwardmove;
			float m_oldsidemove = cmd->sidemove;

			CVector bestAngle{};
			float bestFov = 180.f;
			CEntity* bestTarget = nullptr;

			for (int i = 1; i < 32; i++) {
				auto player = I::entitylist->GetEntityFromIndex(i);
				if (!player || player->IsDormant() || player == vars::localPlayer ||
					player->getTeam() == vars::localPlayer->getTeam() || !player->isAlive())
					continue;

				CMatrix3x4 bones[128];
				if (!player->SetupBones(bones, 128, 0x7FF00, I::globals->currentTime)) continue;

				CVector localEyePosition = vars::localPlayer->GetEyePosition();

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

			if (bestTarget) {
				cmd->viewangles = cmd->viewangles + bestAngle;
				I::engine->SetViewAngles(cmd->viewangles); 
				cmd->buttons |= CUserCmd::IN_ATTACK; 
			}

			if (!(cmd->buttons & CUserCmd::IN_ATTACK)) {
				int rx = 0;
				cmd->viewangles.x = rx;
				int ry = std::rand() % 360;
				if (ry > 180) {
					ry /= 2;
					ry *= -1;
				}
				cmd->viewangles.y = ry;

				vars::ang = cmd->viewangles;
			}
			meth::CorrectMovement(m_oldangle, cmd, m_oldforward, m_oldsidemove);

		}

	}

	return false;
}

void __stdcall hk::PaintTraverse(std::uint32_t panel, bool forceRepaint, bool allowForce) noexcept
{
	if (panel == I::enginevgui->GetPanel(PANEL_TOOLS))
	{
		hk::DrawString(10, 10, 255, 255, 255, 255, false, "Legacyhook built on " __DATE__, WatermarkFont);
		hk::DrawString(10, 30, 255, 255, 255, 255, false, "https://github.com/Zordon1337/legacyhook", MediumFont);
		if (I::engine->IsInGame() && vars::localPlayer)
		{
			for (int i = 1; i < 32; i++) {
				auto player = I::entitylist->GetEntityFromIndex(i);
				if (!player) continue;
				if (player->IsDormant()) continue;
				// is local?
				if (player == vars::localPlayer) continue;
				// is teammate?
				if (player->getTeam() == vars::localPlayer->getTeam()) continue;
				// is dead?
				if (!player->isAlive()) continue;
				CMatrix3x4 bones[256];
				if (!player->SetupBones(bones, 128, 0x7FF00, I::globals->currentTime)) continue;
				CVector top;
				if (I::debugoverlay->ScreenPosition(bones[10].Origin() + CVector{ 0.f,0.f,16.f }, top)) continue;
				CVector bottom;
				if (I::debugoverlay->ScreenPosition(player->GetAbsOrigin(), bottom)) continue;
				CVector head;
				if (I::debugoverlay->ScreenPosition(bones[10].Origin(), head)) continue;
				const float h = bottom.y - top.y;
				const float w = h * 0.3f;
				const auto left = static_cast<int>(top.x - w);
				const auto right = static_cast<int>(top.x + w);
				I::surface->DrawSetColor(255, 255, 255, 255);
				I::surface->DrawOutlinedRect(left, top.y, right, bottom.y);
				

				
			}
		}
	}
	PaintTraverseOriginal(I::panel, panel, forceRepaint, allowForce);
}

void __stdcall hk::FrameStage(client_frame_stage_t stage) {
	CVector ang = CVector(89.f, 89.f, 0.f);
	std::cout << stage << std::endl;
	switch (stage) {
	case FRAME_UNDEFINED:                       break;
	case FRAME_START:

		break;
	case FRAME_NET_UPDATE_START:                break;
	case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
		break;
	case FRAME_NET_UPDATE_POSTDATAUPDATE_END:   break;
	case FRAME_NET_UPDATE_END:

		break;
	case FRAME_RENDER_START:
		if (I::engine->IsInGame() && vars::localPlayer)
		{
			I::prediction->SetLocalViewAngles(vars::ang);
		}
		break;
	case FRAME_RENDER_END:                      break;
	default:                                    break;
	}
	hk::FrameStageoriginal(I::baseclient, stage);
}

void hk::DrawString(int x, int y, int r, int g, int b, int a, bool bCenter, const char* pszText, unsigned long font)
{
	if (pszText == NULL)
	{
		return;
	}

	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };

	va_start(va_alist, pszText);
	vsprintf_s(szBuffer, pszText, va_alist);
	va_end(va_alist);

	wsprintfW(szString, L"%S", szBuffer);


	I::surface->DrawSetTextFont(font);
	I::surface->DrawSetTextPos(x, y);
	I::surface->DrawSetTextColor(r, g, b, a);
	I::surface->DrawPrintText(szString, wcslen(szString), 0);
}