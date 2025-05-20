#ifndef KEYBINDS_H
#define KEYBINDS_H

#include "../include/raylib.h"

// put your new keybinds here please.
// 
struct {
    // Player
    int MoveUP = KEY_UP;
    int MoveDOWN = KEY_DOWN;
    int MoveLEFT = KEY_LEFT;
    int MoveRIGHT = KEY_RIGHT;
    int LeftRUNKey = KEY_LEFT_SHIFT;
    int RightRUNKey = KEY_RIGHT_SHIFT;
    // Hotkeys
    int FullScreenHotKey = KEY_F8;
} Keybinds;

#endif
