#pragma once
#include "vars.hpp"
#include "SDK/CEntity.h"
#include "Windows.h"
#include "skins.hpp"
#include "interfaces.h"
namespace Features::Visuals {
	void DrawBox(int x, int y, int xx, int yy, int r, int g, int b, int a) {
		if (cfg::esp::bBoxEsp)
		{
			I::surface->DrawSetColor(r, g, b, a);
			I::surface->DrawOutlinedRect(x, y, xx, yy);
		}
	}
	void DrawHealthBar(CEntity* player, int left, CVector bottom, CVector top, int h) {
		if (cfg::esp::bHealthBar) {
			I::surface->DrawSetColor(0, 0, 0, 255);
			I::surface->DrawOutlinedRect(left - 4, top.y, left - 1, bottom.y);
			const float health = player->getHealth() * 0.01f;
			I::surface->DrawSetColor(255 * (1.f - health), 255 * health, 0, 255);
			I::surface->DrawFilledRect(left - 3, (bottom.y - h * health), left - 2, bottom.y);
		}
	}
	void ApplySkins() {
		if (!vars::localPlayer || vars::localPlayer->getLifeState() != 0) return;
		UINT* hWeapons = vars::localPlayer->getWeapons();

		if (!hWeapons) return;

		// TODO: ownership check

		for (int i = 0; hWeapons[i]; i++) {

			CBaseAttributableItem* Weapon = (CBaseAttributableItem*)I::entitylist->GetClientEntityFromHandle(hWeapons[i]);

			if (!Weapon) break;

			int WeaponIndex = *Weapon->GetItemDefinitionIndex();
			switch (WeaponIndex)
			{
			case WEAPON_KNIFE_T: {
				*Weapon->GetItemDefinitionIndex() = TKnife;
				if (skins.find(TKnife) != skins.end()) {
					*Weapon->GetFallbackPaintKit() = skins[TKnife].paintkit_id;
				}
				break;
			}
			case WEAPON_KNIFE: {
				*Weapon->GetItemDefinitionIndex() = CTKnife;
				if (skins.find(CTKnife) != skins.end()) {
					*Weapon->GetFallbackPaintKit() = skins[CTKnife].paintkit_id;
				}
				break;
			}
			default: {
				if (skins.find(WeaponIndex) != skins.end()) {
					*Weapon->GetFallbackPaintKit() = skins[WeaponIndex].paintkit_id;
				}
			}
			}
			*Weapon->GetItemIDHigh() = -1;
		}
	}
	void FixAngles() {
		if (I::engine->IsInGame() && vars::localPlayer && cfg::esp::bThirdPerson)
		{
			I::prediction->SetLocalViewAngles(vars::ang);
		}
	}
}