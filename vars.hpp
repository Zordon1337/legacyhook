#pragma once
#include "CEntity.h"
namespace vars {
	CEntity* localPlayer = nullptr;
	CVector ang;
	bool bToggleMenu = true;

}

namespace cfg {
	namespace aim {
		bool bIsEnabled = false;
		bool bUseAutofire = false;
		bool bAntiAim = false;
	}
	namespace movement {
		bool bBunnyHop = false;
		bool bAutoStrafe = false;
	}
}