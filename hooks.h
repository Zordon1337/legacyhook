#pragma once
#include "CUserCmd.h"
#include "IVPanel.h"
namespace hk {
	void Init();

	using CreateMoveFn = bool(__thiscall*)(void*, float, CUserCmd*) noexcept;
	inline CreateMoveFn CreateMoveOriginal = nullptr;
	bool __stdcall CreateMove(float frameTime, CUserCmd* cmd) noexcept;

	using PaintTraverseFn = void(__thiscall*)(IVPanel*, std::uint32_t, bool, bool) noexcept;
	inline PaintTraverseFn PaintTraverseOriginal = nullptr;
	void __stdcall PaintTraverse(std::uint32_t panel, bool forceRepaint, bool allowForce) noexcept;

	void DrawString(int x, int y, int r, int g, int b, int a, bool bCenter, const char* pszText, unsigned long font);

	

}

