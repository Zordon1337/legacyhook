#pragma once
#include <Windows.h>
#include "IVEngineClient.hpp"
#include "EntityList.h"
namespace I {
	void Init();
	void* baseclient;
	void* clientmode;
	IVEngineClient* engine;
	IClientEntityList* entitylist;
	void* Capture(const char* moduleName, const char* interfaceName) noexcept;

	template <typename Interface>
	Interface* Capture(const char* moduleName, const char* interfaceName) noexcept;
}