#include "hooks.h"
#include "interfaces.h"
#include "minhook/MinHook.h"
#include <iostream>
#include "vars.hpp"
#include <string>
#include "SDK/meth.h"
#include <thread>
#include <chrono>
#include "SDK/cmenu.hpp"

#include "Aim.hpp"
#include "Movement.hpp"
#include "SDK/IBaseClientDLL.h"
#include "skins.hpp"
#include "Visuals.hpp"
#define POW(x) ((x)*(x))

HFont WatermarkFont;
HFont MediumFont;
HFont TitleFont;
HFont VelocityFont;
HFont CheckboxFont;
void ViewModelIndexProxy(const CRecvProxyData* data, void* struc, void* Out) {
	auto dat = const_cast<CRecvProxyData*>(data);

	// TODO: ANIM FIX FOR SOME KNIFES

	cfg::skins::iCustomCtKnife = I::modelinfo->GetModelIndex(findKnifeModel(CTKnife));
	cfg::skins::iCustomTKnife = I::modelinfo->GetModelIndex(findKnifeModel(TKnife));
	cfg::skins::iOrginalCtKnife = I::modelinfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl");
	cfg::skins::iOrginalTKnife = I::modelinfo->GetModelIndex("models/weapons/v_knife_default_t.mdl");
	
	if (dat->m_Value.m_Int == cfg::skins::iOrginalCtKnife) {
		dat->m_Value.m_Int = cfg::skins::iCustomCtKnife;
	}
	if (dat->m_Value.m_Int == cfg::skins::iOrginalTKnife) {
		dat->m_Value.m_Int = cfg::skins::iCustomTKnife;
	}


	vars::fnOriginalProxyFn(data, struc, Out);
}

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
	VelocityFont = I::surface->CreateFont();
	CheckboxFont = I::surface->CreateFont();
	I::surface->SetFontGlyphSet(WatermarkFont, "Tahoma", 22, 400, 0, 0, 0x010);
	I::surface->SetFontGlyphSet(MediumFont, "Arial", 16, 400, 0, 0, 0x010);
	I::surface->SetFontGlyphSet(TitleFont, "Tahoma", 16, 900, 0, 0, 0x010);
	I::surface->SetFontGlyphSet(VelocityFont, "Tahoma", 32, 900, 0, 0, 0x010);
	I::surface->SetFontGlyphSet(CheckboxFont, "Arial", 16, 100, 0, 0, 0x010);
	for (int i = 1; i < 30; i++) {
		auto font = I::surface->CreateFont();
		I::surface->SetFontGlyphSet(font, "Tahoma", i, 400, 0, 0, 0x010);
		cfg::aim::fonts[i] = font;
	}
	for (ClientClass* cl = I::baseclient->GetAllClasses(); cl; cl = cl->m_pNext) {
		if (!strcmp(cl->m_pNetworkName, "CBaseViewModel")) {
			RecvTable* cltable = cl->m_pRecvTable;
			for (int nIndex = 0; nIndex < cltable->m_nProps; nIndex++) {
				RecvProp* prop = &cltable->m_pProps[nIndex];

				if (!prop || strcmp(prop->m_pVarName, "m_nModelIndex"))
					continue;

				vars::fnOriginalProxyFn = prop->m_ProxyFn;
				prop->m_ProxyFn = (RecvVarProxyFn)ViewModelIndexProxy;
			}
		}
	}
}
bool __stdcall hk::CreateMove(float frameTime, CUserCmd* cmd) noexcept
{
	if (!cmd->command_number)
		return hk::CreateMoveOriginal(I::clientmode, frameTime,cmd);

	if (CreateMoveOriginal(I::clientmode, frameTime, cmd))
		I::engine->SetViewAngles(cmd->viewangles);

	// i was on crack or smth? cmove is only when player is spawned lol
	if (I::engine->IsInGame())
	{
		auto localPlayer = I::entitylist->GetEntityFromIndex(I::engine->GetLocalPlayerIndex());
		vars::localPlayer = localPlayer;
		if (localPlayer)
		{
			I::globals->serverTime(cmd);
			



			CVector m_oldangle = cmd->viewangles;
			float m_oldforward = cmd->forwardmove;
			float m_oldsidemove = cmd->sidemove;

			
			
			Features::Aim::RunAimbot(cmd);

			Features::Aim::RunAntiAim(cmd);

			Features::Movement::RunBhop(cmd);

			Features::Movement::RunAutoStrafe(cmd);
			

			

			meth::CorrectMovement(m_oldangle, cmd, m_oldforward, m_oldsidemove);

			vars::ang = cmd->viewangles;
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
		{

			CMenu::Draw(TitleFont,CheckboxFont);
			CMenu::DrawSkinChanger(TitleFont);
		}
			
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
				
				Features::Visuals::DrawBox(left, top.y, right, bottom.y, 255, 255, 255, 255);
				Features::Visuals::DrawHealthBar(player, left, bottom, top, h);
				
				int textX = (left + right) / 2;

				int textY = static_cast<int>(top.y) - 2; 

				auto name = "[player]";
				auto fontSize = std::clamp(static_cast<int>(h * 0.15f), 4, 12);
				auto font = cfg::aim::fonts[fontSize];

				wchar_t wname[64];
				mbstowcs(wname, name, sizeof(wname) / sizeof(wchar_t));

				auto textsize = I::surface->getTextSize(name, font);

				textX -= textsize.x / 2;

				I::surface->DrawSetTextFont(font);
				I::surface->DrawSetTextColor(0, 0, 0, 255);
				I::surface->DrawSetTextPos(textX + 1, textY + 1);
				I::surface->DrawPrintText(wname, wcslen(wname), 0);

				I::surface->DrawSetTextColor(255, 255, 255, 255);
				I::surface->DrawSetTextPos(textX, textY);
				I::surface->DrawPrintText(wname, wcslen(wname), 0);

			}
		}
		// foreach in unordered_map cfg::aim::pos
		for (const auto& [key, value] : cfg::aim::drawPos) {
			if (value.x == 0 && value.y == 0) continue;

			I::surface->DrawOutlinedRect(value.x, value.y,value.x+15,value.y+15);
		}

		if (cfg::esp::bDrawVelocity && vars::localPlayer && vars::localPlayer->isAlive()) {
			int w, h;
			I::engine->GetScreenSize(w, h);


			auto vel = vars::localPlayer->getVelocity();
			auto text = std::to_string((int)(sqrt(POW(vel.x) + POW(vel.y))));

			auto textsize = I::surface->getTextSize(text.c_str(), VelocityFont);
			DrawString((w / 2) - (textsize.x / 2), h - cfg::esp::iVelocityYPos - (textsize.y / 2), 255, 255, 255, 255, false, text.c_str(), VelocityFont);
		}
		if (cfg::misc::bCustomCrosshair) {
			int w, h;
			I::engine->GetScreenSize(w, h);
			I::surface->DrawSetColor(255, 255, 255, 255);
			I::surface->DrawLine((w / 2) - (10 * cfg::misc::iCustomCrosshairSize), h / 2, (w / 2) + (10 * cfg::misc::iCustomCrosshairSize), h / 2);
			I::surface->DrawLine(w / 2, (h / 2) - (10 * cfg::misc::iCustomCrosshairSize), w / 2, (h / 2) + (10 * cfg::misc::iCustomCrosshairSize));
		}
	}
	PaintTraverseOriginal(I::panel, panel, forceRepaint, allowForce);
}

void __stdcall hk::FrameStage(client_frame_stage_t stage) {

	CVector vecAngles;
	I::engine->GetViewAngles(vecAngles);
	if (vars::localPlayer && cfg::esp::bThirdPerson) {
		if (!I::input->m_fCameraInThirdPerson) {
			I::input->m_fCameraInThirdPerson = true;
			I::input->m_vecCameraOffset = CVector(vecAngles.x, vecAngles.y, 300);
			auto engine = (DWORD)GetModuleHandleA("engine.dll");
			*reinterpret_cast<uintptr_t*>(engine + 0x514018) = 1;
		}
	}
	else {
		if (I::input->m_fCameraInThirdPerson) {
			I::input->m_fCameraInThirdPerson = false;
			I::input->m_vecCameraOffset = vecAngles;
			auto engine = (DWORD)GetModuleHandleA("engine.dll");
			*reinterpret_cast<uintptr_t*>(engine + 0x514018) = 0;
		}
	}
	switch (stage) {
	case FRAME_NET_UPDATE_POSTDATAUPDATE_START: Features::Visuals::ApplySkins(); break;
	case FRAME_RENDER_START: Features::Visuals::FixAngles(); break;
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
