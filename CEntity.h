#pragma once
#include "Structs.h"
class CEntity
{
public:
	enum EFlags : std::int32_t
	{
		FL_ONGROUND = (1 << 0),
		FL_DUCKING = (1 << 1),
		FL_ANIMDUCKING = (1 << 2),
		FL_WATERJUMP = (1 << 3),
		FL_ONTRAIN = (1 << 4),
		FL_INRAIN = (1 << 5),
		FL_FROZEN = (1 << 6),
		FL_ATCONTROLS = (1 << 7),
		FL_CLIENT = (1 << 8),
		FL_FAKECLIENT = (1 << 9),
		FL_INWATER = (1 << 10),
		FL_FLY = (1 << 11),
		FL_SWIM = (1 << 12),
		FL_CONVEYOR = (1 << 13),
		FL_NPC = (1 << 14),
		FL_GODMODE = (1 << 15),
		FL_NOTARGET = (1 << 16),
		FL_AIMTARGET = (1 << 17),
		FL_PARTIALGROUND = (1 << 18),
		FL_STATICPROP = (1 << 19),
		FL_GRAPHED = (1 << 20),
		FL_GRENADE = (1 << 21),
		FL_STEPMOVEMENT = (1 << 22),
		FL_DONTTOUCH = (1 << 23),
		FL_BASEVELOCITY = (1 << 24),
		FL_WORLDBRUSH = (1 << 25),
		FL_OBJECT = (1 << 26),
		FL_KILLME = (1 << 27),
		FL_ONFIRE = (1 << 28),
		FL_DISSOLVING = (1 << 29),
		FL_TRANSRAGDOLL = (1 << 30),
		FL_UNBLOCKABLE_BY_PLAYER = (1 << 31)
	};

	enum EWeaponType : int
	{
		WEAPONTYPE_KNIFE = 0,
		WEAPONTYPE_PISTOL = 1,
		WEAPONTYPE_SUBMACHINEGUN = 2,
		WEAPONTYPE_RIFLE = 3,
		WEAPONTYPE_SHOTGUN = 4,
		WEAPONTYPE_SNIPER = 5,
		WEAPONTYPE_MACHINEGUN = 6,
		WEAPONTYPE_C4 = 7,
		WEAPONTYPE_PLACEHOLDER = 8,
		WEAPONTYPE_GRENADE = 9,
		WEAPONTYPE_HEALTHSHOT = 11,
		WEAPONTYPE_FISTS = 12,
		WEAPONTYPE_BREACHCHARGE = 13,
		WEAPONTYPE_BUMPMINE = 14,
		WEAPONTYPE_TABLET = 15,
		WEAPONTYPE_MELEE = 16
	};

	enum MoveType_t
	{
		MOVETYPE_NONE = 0,
		MOVETYPE_ISOMETRIC,
		MOVETYPE_WALK,
		MOVETYPE_STEP,
		MOVETYPE_FLY,
		MOVETYPE_FLYGRAVITY,
		MOVETYPE_VPHYSICS,
		MOVETYPE_PUSH,
		MOVETYPE_NOCLIP,
		MOVETYPE_LADDER,
		MOVETYPE_OBSERVER,
		MOVETYPE_CUSTOM,
		MOVETYPE_LAST = MOVETYPE_CUSTOM,
		MOVETYPE_MAX_BITS = 4
	};


	inline int32_t getFlags() noexcept
	{
		return *reinterpret_cast<int32_t*>(reinterpret_cast<uintptr_t>(this) + 0x100); // m_fFlags
	}

	inline CVector getVelocity() noexcept
	{
		return *reinterpret_cast<CVector*>(reinterpret_cast<uintptr_t>(this) + 0x110); // m_vecVelocity
	}
	inline int getTeam() noexcept
	{
		return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0xF0); // m_iTeamNum
	}


	constexpr bool SetupBones(CMatrix3x4* out, std::int32_t max, std::int32_t mask, float currentTime) noexcept
	{
		return memory::Call<bool>(this + 0x4, 13, out, max, mask, currentTime);
	}

	constexpr bool IsDormant() noexcept
	{
		return memory::Call<bool>(this + 0x8, 9);
	}
	inline int tickBase() noexcept {

		return *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + 0x17C0);
	}
	constexpr const CVector& GetAbsOrigin() noexcept
	{
		return memory::Call<const CVector&>(this, 10);
	}
	inline int getHealth() noexcept {
		return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0xFC);
	}
	 bool isAlive() noexcept {
		return this->getHealth() > 0;
	}
	 inline CVector getVecView() noexcept
	 {
		 return *reinterpret_cast<CVector*>(reinterpret_cast<uintptr_t>(this) + 0x104);
	 }
	 inline CVector getVecOrgin() noexcept
	 {
		 return *reinterpret_cast<CVector*>(reinterpret_cast<uintptr_t>(this) + 0xAC);
	 }
	 CVector GetEyePosition() noexcept
	 {
		 CVector ViewOffset = this->getVecView();
		 return this->GetAbsOrigin() + ViewOffset;
	 }
	 inline BYTE getLifeState() {
		 return *reinterpret_cast<BYTE*>(reinterpret_cast<uintptr_t>(this) + 0x25B);
	 }
	 inline UINT* getWeapons() {
		 return (UINT*)((DWORD)this + 0x11C0);
	 }
	 inline UINT* getWeapon() {
		 return (UINT*)((DWORD)this + 0x0D78);
	 }
	 inline float getWeaponNextPrimaryAttack() {
		 return *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(getWeapon() + 0x159C));
	 }
	 int GetMoveType() {
		 return *(int*)((DWORD)this + 0x258);
	 }

	 inline int* getMusicKit() {
		 return (int*)((DWORD)this + 0x1D9C);
	 }


	 constexpr CEntity* getActiveWeapon() noexcept
	 {
		 return memory::Call<CEntity*>(this, 252);
	 }
	 constexpr float getInaccuracy() noexcept
	 {
		 return memory::Call<float>(this, 459);
	 }
	 inline float nextPrimaryAttack() noexcept {
		 return *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + 0x159C);
	 }
};

class CBaseAttributableItem : CEntity {
public:
	inline int* GetItemDefinitionIndex() {
		return (int*)((DWORD)this + 0x1148 + 0x40 + 0x194);
	}

	inline int* GetItemIDHigh() {
		return (int*)((DWORD)this + 0x1148 + 0x40 + 0x1A8);
	}

	inline int* GetEntityQuality() {
		return (int*)((DWORD)this + 0x1148 + 0x40 + 0x198);
	}

	inline char* GetCustomName() {
		return (char*)((DWORD)this + 0x1148 + 0x40 + 0x224);
	}

	inline int* GetOriginalOwnerXuidLow() {
		return (int*)((DWORD)this + 0x14F0);
	}

	inline int* GetOriginalOwnerXuidHigh() {
		return (int*)((DWORD)this + 0x14F4);
	}

	inline int* GetFallbackPaintKit() {
		return (int*)((DWORD)this + 0x14F8);
	}

	inline int* GetFallbackSeed() {
		return (int*)((DWORD)this + 0x3144);
	}

	inline float* GetFallbackWear() {
		return (float*)((DWORD)this + 0x14FC);
	}

	inline int* GetFallbackStatTrak() {
		return (int*)((DWORD)this + 0x1504);
	}
};