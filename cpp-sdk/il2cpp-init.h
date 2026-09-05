#pragma once
#include <cstdint>
#if defined(_WIN32)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

inline uintptr_t GetIl2CppBase()
{
#if defined(_WIN32)
    return reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
#else
    // Linux / Android libil2cpp.so resolver
    return reinterpret_cast<uintptr_t>(dlopen("libil2cpp.so", RTLD_NOLOAD));
#endif
}

template <typename T>
inline T ResolveMethod(uintptr_t rva)
{
    uintptr_t base = GetIl2CppBase();
    if (!base) return nullptr;
    return reinterpret_cast<T>(base + rva);
}
