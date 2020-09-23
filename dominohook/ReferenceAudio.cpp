#include <Windows.h>
#include <CommCtrl.h>
#include "Common.h"
#include "resource.h"
#include "CMainFrame.h"
#include "ReferenceAudio.h"

ReferenceAudio* ReferenceAudio::m_pInstance;

INT_PTR CALLBACK ReferenceAudioDlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
    switch (Msg)
    {
    case WM_INITDIALOG: {
        auto ref_audio = ReferenceAudio::GetInstance();
        SetDlgItemTextW(hWnd, IDC_REFAUDIOPATH, ref_audio->m_wsAudioPath.c_str());

        char dur_text[256];
        snprintf(dur_text, sizeof(dur_text), "%u:%04.1lf", (unsigned)(ref_audio->m_dSongDuration / 60.0), fmod(ref_audio->m_dSongDuration, 60.0));
        SetDlgItemTextA(hWnd, IDC_SONGLEN, dur_text);

        char vol[4];
        snprintf(vol, sizeof(vol), "%d", ref_audio->m_iVolume);
        SetDlgItemTextA(hWnd, IDC_VOLUMEVAL, vol);

        auto slider = GetDlgItem(hWnd, IDC_VOLUMESLIDER);
        SendMessageA(slider, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 200));
        SendMessageA(slider, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)ref_audio->m_iVolume);
        return TRUE;
    }
    case WM_NOTIFY: {
        auto nmhdr = (LPNMHDR)lParam;
        auto slider = GetDlgItem(hWnd, IDC_VOLUMESLIDER);
        if (nmhdr->hwndFrom == GetDlgItem(hWnd, IDC_VOLUMESLIDER)) {
            auto ref_audio = ReferenceAudio::GetInstance();
            auto vol = max(0, min(SendMessageA(slider, TBM_GETPOS, NULL, NULL), 200));
            ref_audio->m_iVolume = vol;

            char vol_text[4];
            snprintf(vol_text, sizeof(vol_text), "%d", ref_audio->m_iVolume);
            SetDlgItemTextA(hWnd, IDC_VOLUMEVAL, vol_text);
            
            if (ref_audio->m_hStream)
                BASS_ChannelSetAttribute(ref_audio->m_hStream, BASS_ATTRIB_VOL, (float)vol / 100.0f);
        }
        break;
    }
    case WM_COMMAND:
        switch (wParam) {
        case IDC_BROWSE: {
            auto ref_audio = ReferenceAudio::GetInstance();
            OPENFILENAMEW ofn{}; // unicode!!!
            WCHAR file[MAX_PATH]{};
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFile = file;
            ofn.nMaxFile = MAX_PATH;
            ofn.lpstrTitle = L"Select a song!";
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
            if (!GetOpenFileNameW(&ofn))
                return TRUE;

            if (!ref_audio->m_bBASSInited) {
                BASS_SetConfig(BASS_CONFIG_DEV_DEFAULT, 1);

                if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
                    Common::Warn(hWnd, "The wrong version of bass.dll is being used. Expected 0x%X, got 0x%X.", BASSVERSION, HIWORD(BASS_GetVersion()));
                    return TRUE;
                }
                // OmniMIDI loads BASS already...
                if (!BASS_Init(-1, 44100, 0, (*g_pMainFrame)->m_hWnd, NULL) && BASS_ErrorGetCode() != BASS_ERROR_ALREADY) {
                    Common::Warn(hWnd, "Failed to initialize BASS. BASS returned %d.", BASS_ErrorGetCode());
                    return TRUE;
                }
                Common::Log(Common::LogType::Info, "BASS initialized successfully.");
                // same for BASSFLAC
                if (!BASS_PluginLoad("bassflac.dll", 0) && BASS_ErrorGetCode() != BASS_ERROR_ALREADY)
                    Common::Log(Common::LogType::Warn, "Couldn't load BASSFLAC. This isn't a big deal, but you won't be able to load FLACs. BASS returned %d.", BASS_ErrorGetCode());
                else
                    Common::Log(Common::LogType::Info, "BASSFLAC loaded successfully.");

                ref_audio->m_bBASSInited = true;
            }

            HSTREAM stream = BASS_StreamCreateFile(FALSE, file, 0, 0, BASS_STREAM_PRESCAN); // accurate seeking is important
            if (!stream) {
                Common::Warn(hWnd, "Failed to load the file. Try converting it to WAV.\nBASS returned %d.", BASS_ErrorGetCode());
                return TRUE;
            }

            auto stream_len = BASS_ChannelGetLength(stream, BASS_POS_BYTE);
            if (stream_len == -1) {
                Common::Warn(hWnd, "Failed to get the length of the stream. BASS returned %d.", BASS_ErrorGetCode());
                BASS_StreamFree(stream);
                return TRUE;
            }
            
            if (ref_audio->m_hStream)
                BASS_StreamFree(ref_audio->m_hStream);
            ref_audio->m_hStream = stream;
            ref_audio->m_wsAudioPath = file;
            SetDlgItemTextW(hWnd, IDC_REFAUDIOPATH, ref_audio->m_wsAudioPath.c_str());

            double dur_secs = BASS_ChannelBytes2Seconds(stream, stream_len);
            ref_audio->m_dSongDuration = dur_secs;
            char dur_text[256];
            snprintf(dur_text, sizeof(dur_text), "%u:%04.1lf", (unsigned)(dur_secs / 60.0), fmod(dur_secs, 60.0));
            SetDlgItemTextA(hWnd, IDC_SONGLEN, dur_text);

            BASS_ChannelSetAttribute(ref_audio->m_hStream, BASS_ATTRIB_VOL, (float)ref_audio->m_iVolume / 100.0f);
            return TRUE;
        }
        case IDCANCEL:
        case IDOK: {
            EndDialog(hWnd, 0);
            ReferenceAudio::GetInstance()->m_hWnd = NULL;
            return TRUE;
        }
        }
        break;
    }
    return FALSE;
}

void ReferenceAudio::OpenDialog() {
    auto& hwnd = GetInstance()->m_hWnd;
    if (!hwnd)
        hwnd = CreateDialogA((HINSTANCE)&__ImageBase, MAKEINTRESOURCEA(IDD_REFAUDIO), (*g_pMainFrame)->m_hWnd, ReferenceAudioDlgProc);
    ShowWindow(hwnd, TRUE);
    SetFocus(hwnd);
}

void ReferenceAudio::UpdateThreadProc() {
    while (!m_bStopRequested) {
        if (m_hStream)
            BASS_ChannelUpdate(m_hStream, 0);
        Sleep(1);
    }
}