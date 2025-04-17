// this is not a tutorial, just an example code. read README.md to know what is going on here and why there's 4 booleans and {} for window.Should close
// and what does what too


#include<iostream>
#include "include/raylib.h"
#include "oneshot_template/oneshot.h"

int main()
{
    const int display_width = OneshotWindowWidth;
    const int display_height = OneshotWindowHeight;

    InitWindow(display_width, display_height, "Oneshot template - basic boring window Example");

    SetTargetFPS(60);

    SetExitKey(KEY_NULL); // optional but oneshot didn't have any key as exit
    Window window;

    while(!window.ShouldClose(false, {}, true, true, true)) {
        window.HotKeys();

        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }


    CloseWindow();
    return 0;
}
