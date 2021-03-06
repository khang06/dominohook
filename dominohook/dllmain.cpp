#include <Windows.h>
#include <shlwapi.h>
#include <stdlib.h>
#include <intrin.h>
#include <bass.h>
#include "Hooks.h"
#include "translations.h"
#include "CustomMenuEntries.h"
#include "GlobalFuncs.h"
#include "CPortalApp.h"
#include "CPortalData.h"
#include "Settings.h"
#include "ReferenceAudio.h"

extern "C" __declspec(dllexport) void dummyexport() {}
#pragma intrinsic(_ReturnAddress)

C_Hook hook_zoomin;
C_Hook hook_zoomout;
C_Hook hook_CPortalApp_InitInstance;
C_Hook hook_CPortalView_Play;
C_Hook hook_CPortalView_Pause;

// fastcall has to be used in place of thiscall
// to get the registers to line up, a dummy argument must be used right after this
// this will be a common thing throughout the hooks
signed int __fastcall custom_zoomin(void* thisptr, void*, unsigned int cur_zoom) {
    if (_ReturnAddress() == (void*)0x4F058B) {
        // vertical zoom, this is horribly broken for that so this just passes the original function through
        hook_zoomin.removeHook();
        auto ret = zoomin(thisptr, cur_zoom);
        hook_zoomin.installHook();
        return ret;
    }
    return min(cur_zoom + 1, 255);
}

signed int __fastcall custom_zoomout(void* thisptr, void*, unsigned int cur_zoom) {
    if (_ReturnAddress() == (void*)0x4F061B) {
        // see above
        hook_zoomout.removeHook();
        auto ret = zoomout(thisptr, cur_zoom);
        hook_zoomout.installHook();
        return ret;
    }
    return max(cur_zoom - 1, 1);
}

void __fastcall custom_CPortalView_Play(CPortalView* thisptr, void*, unsigned a2, unsigned a3, unsigned a4, unsigned a5) {
    //Common::Log(Common::LogType::Info, "playing at %llf", CPortalData_TicksToSeconds(thisptr->m_pPortalData, 0.0, thisptr->m_uCursorTicks));
    auto ref_audio = ReferenceAudio::GetInstance();
    if (ref_audio->m_hStream) {
        auto stream = ref_audio->m_hStream;
        auto secs = CPortalData_TicksToSeconds(thisptr->m_pPortalData, 0.0, thisptr->m_uCursorTicks); // haha secs
        if (!BASS_ChannelSetPosition(stream, BASS_ChannelSeconds2Bytes(stream, secs), BASS_POS_BYTE))
            Common::Log(Common::LogType::Warn, "Seeking failed. BASS returned %d", BASS_ErrorGetCode());
        BASS_ChannelPlay(stream, FALSE);
        
        if (ref_audio->m_tUpdateThread) {
            ref_audio->m_bStopRequested = true;
            ref_audio->m_tUpdateThread->join();
            delete ref_audio->m_tUpdateThread;
            ref_audio->m_tUpdateThread = nullptr;
        }
        ref_audio->m_bStopRequested = false;
        auto thread = new std::thread(&ReferenceAudio::UpdateThreadProc, ref_audio);
        if (!thread)
            Common::Warn(NULL, "Failed to start the audio update thread.");
        ref_audio->m_tUpdateThread = thread;
    }

    // playback thread exists, so i don't want this to start early
    hook_CPortalView_Play.removeHook();
    CPortalView_Play(thisptr, a2, a3, a4, a5);
    hook_CPortalView_Play.installHook();
}

void __fastcall custom_CPortalView_Pause(CPortalView* thisptr, void*, unsigned a2) {
    //Common::Log(Common::LogType::Info, "stopping");
    auto ref_audio = ReferenceAudio::GetInstance();
    if (ref_audio->m_hStream) {
        auto stream = ref_audio->m_hStream;
        BASS_ChannelStop(stream);

        if (ref_audio->m_tUpdateThread) {
            ref_audio->m_bStopRequested = true;
            ref_audio->m_tUpdateThread->join();
            delete ref_audio->m_tUpdateThread;
            ref_audio->m_tUpdateThread = nullptr;
        }
    }

    hook_CPortalView_Pause.removeHook();
    CPortalView_Pause(thisptr, a2);
    hook_CPortalView_Pause.installHook();
}

signed int __fastcall custom_CPortalApp_InitInstance(void* thisptr, void*) {
    hook_CPortalApp_InitInstance.removeHook();
    auto ret = CPortalApp_InitInstance(thisptr);
    hook_CPortalApp_InitInstance.installHook();
    if (ret == FALSE)
        return FALSE;

    // create the custom menu bar
    auto custom_submenu = CreatePopupMenu();
    MENUITEMINFOA item_info;
    item_info.cbSize = sizeof(item_info);

    item_info.fMask = MIIM_ID | MIIM_STRING;
    item_info.wID = ID_REFAUDIO;
    item_info.dwTypeData = (LPSTR)"Load Reference Audio";
    InsertMenuItemA(custom_submenu, ID_REFAUDIO, FALSE, &item_info);

    item_info.fMask = MIIM_ID | MIIM_STRING;
    item_info.wID = ID_SETTINGS;
    item_info.dwTypeData = (LPSTR)"Settings";
    InsertMenuItemA(custom_submenu, ID_SETTINGS, FALSE, &item_info);

    InsertMenuA(custom_submenu, 0, MF_SEPARATOR, 0, NULL);

    item_info.fMask = MIIM_ID | MIIM_STRING;
    item_info.wID = ID_GITHUB;
    item_info.dwTypeData = (LPSTR)"Github";
    InsertMenuItemA(custom_submenu, ID_GITHUB, FALSE, &item_info);

    item_info.fMask = MIIM_ID | MIIM_STRING | MIIM_STATE;
    item_info.wID = ID_BUILDDATE;
    item_info.dwTypeData = (LPSTR)("Compiled on " __DATE__);
    item_info.fState = MFS_DISABLED;
    InsertMenuItemA(custom_submenu, ID_BUILDDATE, FALSE, &item_info);

    // install the custom menu bar item
    auto main_frame = *g_pMainFrame;
    auto menu = GetMenu(main_frame->m_hWnd);
    AppendMenuA(menu, MF_POPUP, (UINT_PTR)custom_submenu, "dominohook");
    SetMenu(main_frame->m_hWnd, menu);

    // inject custom message map for custom menu bar entries
    // TODO: duplicated code
    auto custom_msg_map = new AFX_MSGMAP_ENTRY[CMAINFRAME_MSGMAP_LEN + sizeof(g_custom_frame_entries)];
    memcpy(custom_msg_map, *(void**)CMAINFRAME_MSGMAP_PTR_PTR, CMAINFRAME_MSGMAP_LEN * sizeof(AFX_MSGMAP_ENTRY)); // copy original entries
    memcpy(&custom_msg_map[CMAINFRAME_MSGMAP_LEN - 1], g_custom_frame_entries, sizeof(g_custom_frame_entries));
    QPatch msg_map_patch((void*)CMAINFRAME_MSGMAP_PTR_PTR, (BYTE*)&custom_msg_map, 4);
    msg_map_patch.patch();

    return TRUE;
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
        char domino_path[MAX_PATH];
        char username[256];
        DWORD username_len = sizeof(username); // totally unnecessary...

        if (!GetModuleFileNameA(NULL, domino_path, sizeof(domino_path)))
            Common::Fatal(NULL, "GetModuleFileNameA failed! gle: %x", GetLastError());
        PathRemoveFileSpecA(domino_path);
        if (!GetUserNameA(username, &username_len))
            Common::Fatal(NULL, "GetUserNameA failed! gle: %x", GetLastError());
        auto settings = Settings::Load(std::string(domino_path) + "\\IniFiles\\" + username + "\\dominohook.ini");

        ReferenceAudio::Init();

        if (settings->m_bReplaceZoom) {
            MAKE_HOOK(zoomin);
            MAKE_HOOK(zoomout);
        }
        MAKE_HOOK(CPortalApp_InitInstance);
        MAKE_HOOK(CPortalView_Play);
        MAKE_HOOK(CPortalView_Pause);

        if (settings->m_bReplaceZoom) {
            // patch out the limit on hotkey + toolbar zoom out
            BYTE limit_patch_bytes[] = {
                0x90, // nop
                0x90, // nop
            };
            QPatch limit_patch((void*)0x004FA702, limit_patch_bytes, sizeof(limit_patch_bytes));
            limit_patch.patch();
        }

        if (settings->m_bTranslate) {
            // apply hardcoded string patches
            // TODO: definitely needs a lot of clean up
            auto string_patch_count = sizeof(g_string_patches) / sizeof(StringPatch);
            for (unsigned i = 0; i < string_patch_count; i++) {
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
                case StringPatchType::MovEBP: {
                    BYTE inst[5];
                    inst[0] = 0xBD;
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
                    }
                    else {
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
                case StringPatchType::MovPtrEBP: {
                    BYTE inst[11] = {};
                    size_t len = 0;
                    // only going to handle -0x80 to +0x7F for now
                    inst[0] = 0xC7;
                    inst[1] = 0x45;
                    inst[2] = string_patch.offset;
                    memcpy(&inst[3], &string_patch.string, 4);

                    QPatch patch((void*)string_patch.addr, inst, 7);
                    patch.patch();
                    break;
                }
                case StringPatchType::MovPtr: {
                    BYTE inst[10] = {};
                    inst[0] = 0xC7;
                    inst[1] = 0x05;
                    memcpy(&inst[2], &string_patch.dst, 4);
                    memcpy(&inst[6], &string_patch.string, 4);

                    QPatch patch((void*)string_patch.addr, inst, 10);
                    patch.patch();
                    break;
                }
                default:
                    Common::Fatal(NULL, "Invalid StringPatchType %d!", string_patch.type);
                }
            }
        }
        // disable note overlap warning(?)
        //*(bool*)0x5ACD4D = false;

        // inject custom message map for custom right click menu entries
        auto custom_msg_map = new AFX_MSGMAP_ENTRY[CPORTALVIEW_MSGMAP_LEN + sizeof(g_custom_portal_entries)];
        memcpy(custom_msg_map, *(void**)CPORTALVIEW_MSGMAP_PTR_PTR, CPORTALVIEW_MSGMAP_LEN * sizeof(AFX_MSGMAP_ENTRY)); // copy original entries
        memcpy(&custom_msg_map[CPORTALVIEW_MSGMAP_LEN - 1], g_custom_portal_entries, sizeof(g_custom_portal_entries));
        QPatch msg_map_patch((void*)CPORTALVIEW_MSGMAP_PTR_PTR, (BYTE*)&custom_msg_map, 4);
        msg_map_patch.patch();
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

