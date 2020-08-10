#pragma once

class CSelection {
public:
    CSelection() {
        // overwrite vtbl with the correct one from domino
        *reinterpret_cast<unsigned*>(this) = 0x00563BE0;
    }
    virtual ~CSelection() = 0;
    virtual BYTE GetType() = 0;
    virtual void field_8() = 0;
    virtual void field_C() = 0;
    virtual void field_10() = 0;
    virtual bool HasSelection() = 0;
    virtual void field_18() = 0;
    virtual void field_1C() = 0;
    virtual void field_20() = 0;
    virtual void field_24() = 0;
    virtual void field_28() = 0;
    virtual void field_2C() = 0;
    virtual void field_30() = 0;
    virtual void field_34() = 0;
    virtual void field_38() = 0;
    virtual void field_3C() = 0;
    virtual void field_40() = 0;
    virtual void field_44() = 0;
};