#ifndef ONESHOT_H
#define ONESHOT_H

#include "../include/raylib.h"
#include "Player.h"
#include "Animator.h"
#include "Window.h"
#include "Keybinds.h"
#include "Menus.h"
#include "Os.h"

// combines all classes here to make it only one include to include all headers

class Window;

class Player;

class Animator;

class Menus;

class OS;

namespace OneshotTemplate {
    Window window;
    Player player;
    Animator animator;
    Menus menus;
};

#endif
