#include "CUserCmd.h"
namespace hk {
	void Init();

	using CreateMoveFn = bool(__thiscall*)(void*, float, CUserCmd*) noexcept;
	inline CreateMoveFn CreateMoveOriginal = nullptr;
	bool __stdcall CreateMove(float frameTime, CUserCmd* cmd) noexcept;
}

