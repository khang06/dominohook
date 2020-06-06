#pragma once

#include <array>

typedef enum {
    Push,
    Address,
    MovEAX,
    MovEDI,
    MovEBP,
    MovPtrESP,
    MovPtrEBP,
    MovPtr,
} StringPatchType;

typedef struct {
    StringPatchType type;
    size_t addr;
    const char* string;
    unsigned char offset = 0;
    size_t dst = 0;
} StringPatch;

StringPatch g_string_patches[] = {
    {StringPatchType::Push, 0x004AA955, "Do you want to analyze MIDI data and restore control change events?\n\n* Analysis may take several minutes.\n* You can turn this message off in [Preferences]->[SMF]."},
    {StringPatchType::Push, 0x004A9DEB, "All supported formats|*%s;*.mid|%s - %s special format|*%s|MID - Standard MIDI File|*.mid||"},
};