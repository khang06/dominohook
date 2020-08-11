#pragma once
#include <Windows.h>

class CMainFrame {
public:
    char gap0[0x1C];
    HWND m_hWnd;
};

static auto g_pMainFrame = (CMainFrame**)0x005B474C;