// This is the example code of how to make a basic window with Oneshot template.
// Please refer to the README.md to understand what is this.

#include "include/raylib.h"
#include "oneshot_template/Oneshot.h"

using namespace OneshotTemplate;

int main() {
    const int display_width = OneshotWindowWidth;
    const int display_height = OneshotWindowHeight;

    InitWindow(display_width, display_height, "Oneshot template - Basic window example");

    SetTargetFPS(60);

    SetExitKey(KEY_NULL);

    while(!window.ShouldClose(false, {}, true, true, true)) {
        window.HotKeys();

        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }


    CloseWindow();
    return 0;
}
