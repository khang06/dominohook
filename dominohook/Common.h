#pragma once

// https://devblogs.microsoft.com/oldnewthing/20041025-00/?p=37483
EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace Common {
    // getting an error icon seems to be impossible from looking at the disassembly...
    enum class LogType {
        Info,
        None,
        Warn,
    };

    void Log(LogType type, const char* format, ...);
    void Warn(const char* format, ...);
    void __declspec(noreturn) Fatal(const char* format, ...);
}