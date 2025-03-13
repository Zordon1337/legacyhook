#pragma once
#include "CEntity.h"
#include "Recv.h"
#include <unordered_map>
namespace vars {
	CEntity* localPlayer = nullptr;
	CVector ang;
	bool bToggleMenu = true;
	int iMenuIndex = 0;

	RecvVarProxyFn fnOriginalProxyFn = NULL;
}
enum ItemDefinitionIndex : int {
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516
};
const std::unordered_map<ItemDefinitionIndex, const char*> ItemDefNames = {
	{WEAPON_DEAGLE, "WEAPON_DEAGLE"},
	{WEAPON_ELITE, "WEAPON_ELITE"},
	{WEAPON_FIVESEVEN, "WEAPON_FIVESEVEN"},
	{WEAPON_GLOCK, "WEAPON_GLOCK"},
	{WEAPON_AK47, "WEAPON_AK47"},
	{WEAPON_AUG, "WEAPON_AUG"},
	{WEAPON_AWP, "WEAPON_AWP"},
	{WEAPON_FAMAS, "WEAPON_FAMAS"},
	{WEAPON_G3SG1, "WEAPON_G3SG1"},
	{WEAPON_GALILAR, "WEAPON_GALILAR"},
	{WEAPON_M249, "WEAPON_M249"},
	{WEAPON_M4A1, "WEAPON_M4A1"},
	{WEAPON_MAC10, "WEAPON_MAC10"},
	{WEAPON_P90, "WEAPON_P90"},
	{WEAPON_UMP45, "WEAPON_UMP45"},
	{WEAPON_XM1014, "WEAPON_XM1014"},
	{WEAPON_BIZON, "WEAPON_BIZON"},
	{WEAPON_MAG7, "WEAPON_MAG7"},
	{WEAPON_NEGEV, "WEAPON_NEGEV"},
	{WEAPON_SAWEDOFF, "WEAPON_SAWEDOFF"},
	{WEAPON_TEC9, "WEAPON_TEC9"},
	{WEAPON_TASER, "WEAPON_TASER"},
	{WEAPON_HKP2000, "WEAPON_HKP2000"},
	{WEAPON_MP7, "WEAPON_MP7"},
	{WEAPON_MP9, "WEAPON_MP9"},
	{WEAPON_NOVA, "WEAPON_NOVA"},
	{WEAPON_P250, "WEAPON_P250"},
	{WEAPON_SCAR20, "WEAPON_SCAR20"},
	{WEAPON_SG556, "WEAPON_SG556"},
	{WEAPON_SSG08, "WEAPON_SSG08"},
	{WEAPON_KNIFE, "WEAPON_KNIFE"},
	{WEAPON_KNIFE_T, "WEAPON_KNIFE_T"},
	{WEAPON_M4A1_SILENCER, "WEAPON_M4A1_SILENCER"},
	{WEAPON_USP_SILENCER, "WEAPON_USP_SILENCER"},
	{WEAPON_CZ75A, "WEAPON_CZ75A"},
	{WEAPON_REVOLVER, "WEAPON_REVOLVER"},
	{WEAPON_KNIFE_BAYONET, "WEAPON_KNIFE_BAYONET"},
	{WEAPON_KNIFE_FLIP, "WEAPON_KNIFE_FLIP"},
	{WEAPON_KNIFE_GUT, "WEAPON_KNIFE_GUT"},
	{WEAPON_KNIFE_KARAMBIT, "WEAPON_KNIFE_KARAMBIT"},
	{WEAPON_KNIFE_M9_BAYONET, "WEAPON_KNIFE_M9_BAYONET"},
	{WEAPON_KNIFE_TACTICAL, "WEAPON_KNIFE_TACTICAL"},
	{WEAPON_KNIFE_FALCHION, "WEAPON_KNIFE_FALCHION"},
	{WEAPON_KNIFE_BUTTERFLY, "WEAPON_KNIFE_BUTTERFLY"},
	{WEAPON_KNIFE_PUSH, "WEAPON_KNIFE_PUSH"}
};
#define skinnableitems_amount 38
const ItemDefinitionIndex skinnableitems[] = {
	WEAPON_DEAGLE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR,
	WEAPON_M249,
	WEAPON_M4A1,
	WEAPON_MAC10,
	WEAPON_P90,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_HKP2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SCAR20,
	WEAPON_SG556,
	WEAPON_SSG08,
	WEAPON_M4A1_SILENCER,
	WEAPON_USP_SILENCER,
	WEAPON_CZ75A, // i think revolver doesnt exist because there is no skins, but i am too lazy to check
	WEAPON_KNIFE_BAYONET,
	WEAPON_KNIFE_FLIP,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_BUTTERFLY,
};
const std::unordered_map<ItemDefinitionIndex, const char*> knifeModels = {
	{WEAPON_KNIFE_BAYONET, "models/weapons/v_knife_bayonet.mdl"},
	{WEAPON_KNIFE_FLIP, "models/weapons/v_knife_flip.mdl" },
	{WEAPON_KNIFE_GUT, "models/weapons/v_knife_gut.mdl"},
	{WEAPON_KNIFE_KARAMBIT, "models/weapons/v_knife_karam.mdl"},
	{WEAPON_KNIFE_M9_BAYONET, "models/weapons/v_knife_m9_bay.mdl"},
	{WEAPON_KNIFE_TACTICAL, "models/weapons/v_knife_tactical.mdl"},
	{WEAPON_KNIFE_BUTTERFLY, "models/weapons/v_knife_butterfly.mdl"}
};

const char* findKnifeModel(ItemDefinitionIndex idx) {
	if (knifeModels.find(idx) != knifeModels.end()) {
		return knifeModels.find(idx)->second;
	}
	else {
		return "";
	}
}
namespace cfg {
	namespace aim {
		bool bIsEnabled = false;
		bool bUseAutofire = false;
		bool bSilentAim = false;
		bool bAntiAim = false;
		int iAntiAimSpeed = 1;
		float flAimbotFov = 1;

	}
	namespace esp {
		bool bBoxEsp = false;
		bool bHealthBar = false;
		bool bThirdPerson = false;
		bool bDrawVelocity = false;
		int iVelocityYPos = 0;
	}
	namespace movement {
		bool bBunnyHop = false;
		bool bAutoStrafe = false;
	}
	namespace misc {
		bool bCustomCrosshair = false;
		int iCustomCrosshairSize = 1;
	}
	namespace skins {
		int iOrginalCtKnife = 0;
		int iOrginalTKnife = 0;
		int iCustomCtKnife = 0;
		int iCustomTKnife = 0;

		int iSkinsTabSelectedSkin = 0;
		int iWeaponTypesTab = 0;

	}
}