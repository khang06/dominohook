#include <Windows.h>
#include <shlwapi.h>
#include "Common.h"
#include "INIReader.h"
#include "resource.h"
#include "CMainFrame.h"
#include "Settings.h"

Settings* Settings::m_pInstance;

Settings::Settings(std::string path) {
    m_sSavePath = path;
    if (!PathFileExistsA(path.c_str())) {
        Common::Warn(NULL, "No config file for dominohook was found. Loading defaults.");
        Save(); // it will annoy the user until a manual save without this
    }
    
    INIReader reader(path.c_str());
    m_bTranslate = reader.GetBoolean("General", "Translate", m_bTranslate);
    m_bReplaceZoom = reader.GetBoolean("General", "ReplaceZoom", m_bReplaceZoom);
}

void WriteBool(FILE* file, const std::string& name, bool b) {
    if (b)
        fprintf(file, "%s = true\n", name.c_str());
    else
        fprintf(file, "%s = false\n", name.c_str());
}

void Settings::Save() {
    // warning instead of fatal because it's not worth losing work over not being able to save dominohook settings
    if (m_sSavePath.empty()) {
        Common::Warn(NULL, "Attempted to save settings with an empty m_sSavePath. Dominohook settings have not been saved.");
        return;
    }

    FILE* ini = fopen(m_sSavePath.c_str(), "w");
    if (!ini) {
        Common::Warn(NULL, "Failed to open the settings file for writing. Dominohook settings have not been saved.");
        return;
    }

    fprintf(ini, "[General]\n");

    WriteBool(ini, "Translate", m_bTranslate);
    WriteBool(ini, "ReplaceZoom", m_bReplaceZoom);

    fclose(ini);
}

INT_PTR CALLBACK SettingsDlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
    switch (Msg)
    {
    case WM_INITDIALOG: {
        auto settings = Settings::GetInstance();
        CheckDlgButton(hWnd, IDC_TRANSLATE, settings->m_bTranslate ? BST_CHECKED : BST_UNCHECKED);
        CheckDlgButton(hWnd, IDC_REPLACEZOOM, settings->m_bReplaceZoom ? BST_CHECKED : BST_UNCHECKED);
        return TRUE;
        break;
    }
    case WM_COMMAND:
        switch (wParam) {
        case IDOK: {
            auto settings = Settings::GetInstance();
            settings->m_bTranslate = IsDlgButtonChecked(hWnd, IDC_TRANSLATE);
            settings->m_bReplaceZoom = IsDlgButtonChecked(hWnd, IDC_REPLACEZOOM);
            settings->Save();
        }
        [[fallthrough]]; // can't put this in the braces???
        case IDCANCEL: {
            EndDialog(hWnd, 0);
            Settings::GetInstance()->m_hWnd = NULL;
            return TRUE;
        }
        }
    }
    return FALSE;
}

void Settings::OpenDialog() {
    auto& hwnd = GetInstance()->m_hWnd;
    if (!hwnd)
        hwnd = CreateDialogA((HINSTANCE)&__ImageBase, MAKEINTRESOURCEA(IDD_SETTINGS), (*g_pMainFrame)->m_hWnd, SettingsDlgProc);
    ShowWindow(hwnd, TRUE);
    SetFocus(hwnd);
}