#ifndef OS_H
#define OS_H

#include<string>

#ifdef _WIN32 // if current platform is windows
#define WIN32_LEAN_AND_MEAN
#define Rectangle RayRectangle
#define CloseWindow RayCloseWindow
#define ShowCursor RayShowCursor
#include<windows.h>
#include<Lmcons.h>
#undef Rectangle // undefine some stuff that has same names as stuff from raylib
#undef CloseWindow
#undef ShowCursor
#undef DrawText
#undef LoadImage
#undef MessageBox
#else // if current platform isn't windows
#include<iostream>
#endif

class OS {
public:
    static std::string GetUsername(std::string UnknownName = "Unknown") {
#ifdef _WIN32
        char name[UNLEN+1];
        DWORD size = UNLEN + 1;

        if(GetUserName((TCHAR*)name, &size)) {
            return name;
        } else {
            return UnknownName;
        }
#else
        return UnknownName;
#endif
    }

    static void ChangeBackground() {
        
    }
};

#endif