#pragma once
#include <Windows.h>
#include "SDK/IVEngineClient.h"
#include "SDK/EntityList.h"
#include "SDK/ISurface.h"
#include "SDK/IVPanel.h"
#include "SDK/EngineVGUI.h"
#include "SDK/Globals.h"
#include "SDK/IEngineTrace.h"
#include "SDK/IPrediction.h"
#include "SDK/CInput.h"
#include "SDK/IVModelInfoClient.h"
#include "SDK/IBaseClientDLL.h"
namespace I {
	void Init();
	IBaseClientDLL* baseclient;
	void* clientmode;
	IVEngineClient* engine;
	IClientEntityList* entitylist;
	ISurface* surface;
	IVPanel* panel;
	IEngineVGui* enginevgui;
	IVDebugOverlay* debugoverlay;
	IGlobalVars* globals = nullptr;
	IEngineTrace* engineTrace = nullptr;
	IPrediction* prediction = nullptr;
	CInput* input = nullptr;
	IVModelInfoClient* modelinfo = nullptr;

	void* Capture(const char* moduleName, const char* interfaceName) noexcept;

	template <typename Interface>
	Interface* Capture(const char* moduleName, const char* interfaceName) noexcept;
}