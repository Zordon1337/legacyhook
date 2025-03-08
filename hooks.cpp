#include "hooks.h"
#include "interfaces.h"
#include "minhook/MinHook.h"
#include <iostream>
#include "vars.hpp"
#include <string>
#include "meth.h"
#include <thread>
#include <chrono>
#include "cmenu.hpp"

#include "Aim.hpp"
#include "Movement.hpp"

HFont WatermarkFont;
HFont MediumFont;
HFont TitleFont;
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
	TitleFont = I::surface->CreateFont();
	I::surface->SetFontGlyphSet(WatermarkFont, "Arial", 18, 400, 0, 0, 0x200);
	I::surface->SetFontGlyphSet(MediumFont, "Arial", 16, 400, 0, 0, 0x200);
	I::surface->SetFontGlyphSet(TitleFont, "Tahoma", 12, 150, 0, 0, 0);
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
			

			

			CVector m_oldangle = cmd->viewangles;
			float m_oldforward = cmd->forwardmove;
			float m_oldsidemove = cmd->sidemove;

			
			
			Features::Aim::RunAimbot(cmd);

			Features::Aim::RunAntiAim(cmd);

			Features::Movement::RunBhop(cmd);
			
			Features::Movement::RunAutoStrafe(cmd);

			

			meth::CorrectMovement(m_oldangle, cmd, m_oldforward, m_oldsidemove);
		}

	}

	return false;
}

void __stdcall hk::PaintTraverse(std::uint32_t panel, bool forceRepaint, bool allowForce) noexcept
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
		vars::bToggleMenu = !vars::bToggleMenu;
	if (panel == I::enginevgui->GetPanel(PANEL_TOOLS))
	{
		hk::DrawString(10, 10, 255, 255, 255, 255, false, "Legacyhook built on " __DATE__, WatermarkFont);
		hk::DrawString(10, 30, 255, 255, 255, 255, false, "https://github.com/Zordon1337/legacyhook", MediumFont);
		if (vars::bToggleMenu)
			CMenu::Draw(TitleFont);
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
				
				if (cfg::esp::bBoxEsp)
				{
					I::surface->DrawSetColor(255, 255, 255, 255);
					I::surface->DrawOutlinedRect(left, top.y, right, bottom.y);

				}

				if (cfg::esp::bHealthBar) {
					I::surface->DrawSetColor(0, 0, 0, 255);
					I::surface->DrawOutlinedRect(left - 7, top.y - 2, left - 4, bottom.y + 2);
					const float health = player->getHealth() * 0.01f;
					I::surface->DrawSetColor(255 * (1.f - health), 255 * health, 0, 255);
					I::surface->DrawFilledRect(left - 5, top.y, left - 4, top.y + h * health);
				}
				
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
		if (I::engine->IsInGame() && vars::localPlayer && cfg::aim::bAntiAim)
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