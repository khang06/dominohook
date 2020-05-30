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
            case StringPatchType::MovEDI: {
                BYTE inst[5];
                inst[0] = 0xBF;
                auto string_addr = string_patch.string;
                memcpy(&inst[1], &string_addr, 4);

                QPatch patch((void*)string_patch.addr, inst, 5);
                patch.patch();
                break;
            }
            case StringPatchType::MovPtrESP: {
                BYTE inst[11] = {};
                size_t len = 0;
                // annoyingly, this uses a different encoding if the offset is greater than 127...
                if (string_patch.offset < 0x80) {
                    inst[0] = 0xC7;
                    inst[1] = 0x44;
                    inst[2] = 0x24;
                    inst[3] = string_patch.offset;
                    memcpy(&inst[4], &string_patch.string, 4);
                    len = 8;
                } else {
                    inst[0] = 0xC7;
                    inst[1] = 0x84;
                    inst[2] = 0x24;
                    inst[3] = string_patch.offset;
                    // inst[4], inst[5], and inst[6] stay zero
                    memcpy(&inst[7], &string_patch.string, 4);
                    len = 11;
                }

                QPatch patch((void*)string_patch.addr, inst, len);
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

