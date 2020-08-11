#pragma once

#include <string>
#include "Common.h"

class Settings {
public:
    static Settings* Load(std::string path) {
        m_pInstance = new Settings(path);
        return m_pInstance;
    }
    static Settings* GetInstance() {
        if (!m_pInstance)
            Common::Fatal("Settings::GetInstance() called before Load()!");
        return m_pInstance;
    }
    static void OpenDialog();
    void Save();

    std::string m_sSavePath;

    bool m_bTranslate = true;
    bool m_bReplaceZoom = true;
private:
    Settings(std::string path);

    static Settings* m_pInstance;
};