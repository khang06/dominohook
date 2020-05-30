#include <Windows.h>
#include <stdlib.h>
#include "Hooks.h"
#include "translations.h"

extern "C" __declspec(dllexport) void dummyexport() {}

auto zoomin = ((signed int(__thiscall*)(void*, unsigned int))0x004FA780);
auto zoomout = ((signed int(__thiscall*)(void*, unsigned int))0x004FA720);

C_Hook hook_zoomin;
C_Hook hook_zoomout;

signed int g_zoom = 15;

signed int __fastcall custom_zoomin(void*, void*, unsigned int cur_zoom) {
    g_zoom = min(cur_zoom + 1, 255);
    return g_zoom;
}

signed int __fastcall custom_zoomout(void*, void*, unsigned int cur_zoom) {
    g_zoom = max(cur_zoom - 1, 1);
    return g_zoom;
}

// why do i even have to make 3 macros for 1???
#define MAKE_HOOK(x) MAKE_HOOK_HIDDEN1(x).setSubs((void*)x, (void*)MAKE_HOOK_HIDDEN2(x)); \
                     MAKE_HOOK_HIDDEN1(x).installHook();
#define MAKE_HOOK_HIDDEN1(x) hook_##x
#define MAKE_HOOK_HIDDEN2(x) custom_##x

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        MAKE_HOOK(zoomin);
        MAKE_HOOK(zoomout);

        // patch out the limit on hotkey + toolbar zoom out
        BYTE limit_patch_bytes[] = {
            0x90, // nop
            0x90, // nop
        };
        QPatch limit_patch((void*)0x004FA702, limit_patch_bytes, sizeof(limit_patch_bytes));
        limit_patch.patch();

        // apply hardcoded string patches
        auto string_patch_count = sizeof(g_string_patches) / sizeof(StringPatch);
        for (int i = 0; i < string_patch_count; i++) {
            auto& string_patch = g_string_patches[i];
            switch (string_patch.type) {
            case StringPatchType::Push: {
                // construct the instruction
                BYTE inst[5];
                inst[0] = 0x68;
                auto string_addr = string_patch.string;
                memcpy(&inst[1], &string_addr, 4);

                QPatch patch((void*)string_patch.addr, inst, 5);
                patch.patch();
                break;
            }
            case StringPatchType::Address: {
                QPatch patch((void*)string_patch.addr, (BYTE*)&string_patch.string, 4);
                patch.patch();
                break;
            }
            case StringPatchType::MovEAX: {
                BYTE inst[5];
                inst[0] = 0xB8;
                auto string_addr = string_patch.string;
                memcpy(&inst[1], &string_addr, 4);

                QPatch patch((void*)string_patch.addr, inst, 5);
                patch.patch();
                break;
            }
            case StringPatchType::MovPtrESP: {
                BYTE inst[8] = {};
                inst[0] = 0xC7;
                inst[1] = 0x44;
                inst[2] = 0x24;
                inst[3] = string_patch.offset;
                //auto string_addr = _byteswap_ulong((unsigned long)string_patch.string);
                auto string_addr = string_patch.string;
                memcpy(&inst[4], &string_addr, 4);

                QPatch patch((void*)string_patch.addr, inst, 8);
                patch.patch();
                break;
            }
            default:
                MessageBoxA(NULL, "invalid string patch type, exiting...", "dominohook fatal error", 0);
                exit(1);
            }

            // disable note overlap warning(?)
            *(bool*)0x5ACD4D = false;
        }
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

