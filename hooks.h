#pragma once
#include "SDK/CUserCmd.h"
#include "SDK/IVPanel.h"
enum client_frame_stage_t {
	FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,

	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};
namespace hk {
	void Init();

	using CreateMoveFn = bool(__thiscall*)(void*, float, CUserCmd*) noexcept;
	inline CreateMoveFn CreateMoveOriginal = nullptr;
	bool __stdcall CreateMove(float frameTime, CUserCmd* cmd) noexcept;

	using PaintTraverseFn = void(__thiscall*)(IVPanel*, std::uint32_t, bool, bool) noexcept;
	inline PaintTraverseFn PaintTraverseOriginal = nullptr;
	void __stdcall PaintTraverse(std::uint32_t panel, bool forceRepaint, bool allowForce) noexcept;

	void DrawString(int x, int y, int r, int g, int b, int a, bool bCenter, const char* pszText, unsigned long font);
	using framestagehook = void(__thiscall*)(void*, client_frame_stage_t);
	inline framestagehook FrameStageoriginal;
	void __stdcall FrameStage(client_frame_stage_t frame_stage);


	

}

