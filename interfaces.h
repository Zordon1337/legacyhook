#pragma once
#include <Windows.h>
#include "IVEngineClient.hpp"
#include "EntityList.h"
#include "ISurface.h"
#include "IVPanel.h"
#include "EngineVGUI.h"
#include "Globals.h"
#include "IEngineTrace.h"
#include "IPrediction.h"
namespace I {
	void Init();
	void* baseclient;
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
	void* Capture(const char* moduleName, const char* interfaceName) noexcept;

	template <typename Interface>
	Interface* Capture(const char* moduleName, const char* interfaceName) noexcept;
}