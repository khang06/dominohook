#pragma once

#include <Windows.h>
#include <string>
#include <thread>
#include <bass.h>
#include "Common.h"

class ReferenceAudio {
public:
    static void Init() {
        m_pInstance = new ReferenceAudio;
        return;
    }
    static ReferenceAudio* GetInstance() {
        if (!m_pInstance)
            Common::Fatal(NULL, "ReferenceAudio::GetInstance() called before Init()!");
        return m_pInstance;
    }
    static void OpenDialog();
    void UpdateThreadProc();

    bool m_bBASSInited = false; // save memory for people who don't use this feature
    std::wstring m_wsAudioPath = L"";
    HSTREAM m_hStream = 0;
    int m_iVolume = 100;
    double m_dSongDuration = 0.0;
    std::thread* m_tUpdateThread = nullptr;
    volatile bool m_bStopRequested = false;

    HWND m_hWnd = NULL;
private:
    ReferenceAudio() = default;

    static ReferenceAudio* m_pInstance;
};