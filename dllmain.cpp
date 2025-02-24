#include "Windows.h"
#include "hooks.h"
#include <cstdio>
#include "interfaces.h"
DWORD WINAPI Init(LPVOID smth) {
	AllocConsole();
    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    I::Init();
	hk::Init();
    while (true) {
        Sleep(1000);
    }
    return 0;
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);

        const HANDLE hThread = CreateThread(
            nullptr,
            NULL,
            Init,
            hModule,
            NULL,
            nullptr
        );

        if (hThread)
            CloseHandle(hThread);
    }
    
    }
    return TRUE;
}

