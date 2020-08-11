#include <stdio.h>
#include <stdarg.h>
#include <Windows.h>
#include "GlobalFuncs.h"
#include "Common.h"

namespace Common {
    void Log(LogType type, const char* format, ...) {
        va_list args;
        char buf[1024];

        va_start(args, format);
        vsnprintf(buf, sizeof(buf), format, args);
        va_end(args);
        //log_to_window(64, "[dominohook] %s", buf);
        unsigned flags = 0;
        switch (type) {
        case LogType::Info:
            flags = 0x40;
            break;
        case LogType::None:
            break;
        case LogType::Warn:
            flags = 0x20;
            break;
        default:
            Fatal("invalid logtype");
        };
        log_to_window(flags, "[dominohook] %s", buf);
    }

    void Warn(const char* format, ...) {
        va_list args;
        char buf[1024];

        va_start(args, format);
        vsnprintf(buf, sizeof(buf), format, args);
        va_end(args);

        MessageBoxA(NULL, buf, "dominohook warning", MB_ICONWARNING);
    }

    void __declspec(noreturn) Fatal(const char* format, ...) {
        va_list args;
        char buf[1024];

        va_start(args, format);
        vsnprintf(buf, sizeof(buf), format, args);
        va_end(args);

        MessageBoxA(NULL, buf, "dominohook fatal error (please report)", MB_ICONSTOP);
        exit(1); // TODO: generate a minidump?
    }
}