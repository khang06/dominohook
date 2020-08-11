#pragma once

#include "CSelection.h"
#include "CPortalData.h"

// TODO: this should be read as virtual functions from the class, not defines
#define CPORTALVIEW_ENABLEIFSELECTION 0x004A8620

class CPortalView {
public:
    char pad0[0x40];
    CPortalData* m_pPortalData;
    char pad44[8];
    unsigned m_uCursorTicks;
    char pad50[0x14];
    CSelection* m_pSelection;
};

// TODO: this isn't good either
auto CPortalView_Play = ((void(__thiscall*)(CPortalView*, unsigned, unsigned, unsigned, unsigned))0x004A89A0);
auto CPortalView_Pause = ((void(__thiscall*)(CPortalView*, unsigned))0x004A8D20);