// ===========================================================================
// MinHook / Dobby Function Hooking Scaffold
// ===========================================================================
#include "il2cpp.h"
#include "il2cpp-init.h"

#if defined(_WIN32)
#include <windows.h>

DWORD WINAPI MainThread(LPVOID lpParam)
{
    while (!GetIl2CppBase()) {
        Sleep(100);
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
    }
    return TRUE;
}
#endif
