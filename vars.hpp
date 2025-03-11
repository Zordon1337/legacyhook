#pragma once
#include "CEntity.h"
namespace vars {
	CEntity* localPlayer = nullptr;
	CVector ang;
	bool bToggleMenu = true;
	int iMenuIndex = 0;
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
}