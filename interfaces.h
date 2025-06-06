#pragma once
#include <Windows.h>
#include "IVEngineClient.h"
#include "EntityList.h"
#include "ISurface.h"
#include "IVPanel.h"
#include "EngineVGUI.h"
#include "Globals.h"
#include "IEngineTrace.h"
#include "IPrediction.h"
#include "CInput.h"
#include "IVModelInfoClient.h"
#include "IBaseClientDLL.h"
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