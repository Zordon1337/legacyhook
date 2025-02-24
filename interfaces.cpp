
#include "interfaces.h"
#include <iostream>
#include "Globals.h"

void I::Init() {
	I::baseclient = I::Capture("client.dll", "VClient016");
	std::cout << "baseclient: " << I::baseclient << std::endl;
	I::clientmode = **reinterpret_cast<void***>((*reinterpret_cast<unsigned int**>(baseclient))[10] + 5);
	std::cout << "clientmode: " << I::clientmode << std::endl;
	I::engine = I::Capture<IVEngineClient>("engine.dll", "VEngineClient013");
	std::cout << "engine: " << I::engine << std::endl;
	I::entitylist = I::Capture<IClientEntityList>("client.dll", "VClientEntityList003");
	std::cout << "entitylist: " << I::entitylist << std::endl;
	I::panel = I::Capture<IVPanel>("vgui2.dll", "VGUI_Panel009");
	std::cout << "panel: " << I::panel << std::endl;
	I::surface = I::Capture<ISurface>("vguimatsurface.dll", "VGUI_Surface031");
	std::cout << "surface: " << I::surface << std::endl;
	I::enginevgui = I::Capture<IEngineVGui>("engine.dll", "VEngineVGui001");
	std::cout << "enginevgui: " << I::enginevgui << std::endl;
	I::debugoverlay = I::Capture<IVDebugOverlay>("engine.dll", "VDebugOverlay004");
	std::cout << "debugoverlay: " << I::debugoverlay << std::endl;
	I::globals = **reinterpret_cast<IGlobalVars***>((*reinterpret_cast<uintptr_t**>(baseclient))[11] + 10);
	std::cout << "globals: " << I::globals << std::endl;
}

void* I::Capture(const char* moduleName, const char* interfaceName) noexcept
{
	const HINSTANCE handle = GetModuleHandle(moduleName);

	if (!handle)
		return nullptr;

	// get the exported Createinterface function
	using CreateInterfaceFn = void* (__cdecl*)(const char*, int*);
	const CreateInterfaceFn createInterface =
		reinterpret_cast<CreateInterfaceFn>(GetProcAddress(handle, "CreateInterface"));

	// return the interface pointer by calling the function
	return createInterface(interfaceName, nullptr);
}
template <typename Interface>
Interface* I::Capture(const char* moduleName, const char* interfaceName) noexcept
{
	const HINSTANCE handle = GetModuleHandle(moduleName);

	if (!handle)
		return nullptr;

	// get the exported Createinterface function
	using CreateInterfaceFn = Interface * (__cdecl*)(const char*, int*);
	const CreateInterfaceFn createInterface =
		reinterpret_cast<CreateInterfaceFn>(GetProcAddress(handle, "CreateInterface"));

	// return the interface pointer by calling the function
	return createInterface(interfaceName, nullptr);
}
