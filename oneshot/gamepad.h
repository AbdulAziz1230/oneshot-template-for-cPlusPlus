#ifndef GAMEPAD_H
#define GAMEPAD_H

#include<iostream>
#include "../include/raylib.h"

#define XBOX_ALIAS_1 "xbox"
#define XBOX_ALIAS_2 "x-box"
#define PS_ALIAS     "playstation"

int gamepad = 0;

void Gamepad() {
    if(IsGamepadAvailable(gamepad)) {
        std::cout << "Gamepad connected: " << GetGamepadName(gamepad) << std::endl;
    }
}

#endif