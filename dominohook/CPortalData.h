#pragma once

class CPortalData {
public:
    char pad0[0x4C];
    unsigned m_uCursorTicks;
};

auto CPortalData_TicksToSeconds = ((double(__thiscall*)(CPortalData*, double, double))0x004A2320);