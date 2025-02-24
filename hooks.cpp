#include "hooks.h"
#include "interfaces.h"
#include "minhook/MinHook.h"
#include <iostream>
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

		if (localPlayer)
		{
			if (!(localPlayer->getFlags() & CEntity::FL_ONGROUND)) {
				if (!(localPlayer->getFlags() & CEntity::FL_ONGROUND))
					cmd->buttons &= ~CUserCmd::IN_JUMP;
				else
					cmd->buttons |= CUserCmd::IN_JUMP;
			}
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
		if (I::engine->IsInGame())
		{
			for (int i = 1; i < 32; i++) {
				auto player = I::entitylist->GetEntityFromIndex(i);
				if (!player) continue;
				if (player->IsDormant()) continue;
				CMatrix3x4 bones[256];
				if (!player->SetupBones(bones, 128, 0x7FF00, I::globals->currentTime)) continue;
				CVector top;
				if (I::debugoverlay->ScreenPosition(bones[8].Origin() + CVector{ 0.f,0.f,11.f }, top)) continue;
				CVector bottom;
				if (I::debugoverlay->ScreenPosition(player->GetAbsOrigin(), bottom)) continue;
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