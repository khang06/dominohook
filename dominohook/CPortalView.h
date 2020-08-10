#pragma once

#include "CSelection.h"

#define CPORTALVIEW_ENABLEIFSELECTION 0x004A8620

class CPortalView {
public:
    char pad0[0x64];
    CSelection* m_pSelection;
};