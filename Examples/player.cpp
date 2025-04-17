// this is not a tutorial, just an example code. read README.md to know what is going on here and why there's 4 booleans and {} for window.Should close


#include<iostream>
#include "include/raylib.h"
#include "oneshot_template/oneshot.h"

int main()
{
    const int display_width = OneshotWindowWidth;
    const int display_height = OneshotWindowHeight;

    InitWindow(display_width, display_height, "Oneshot template - Player Example");

    SetTargetFPS(60);

    SetExitKey(KEY_NULL); // optional but oneshot didn't have any key as exit

    Window window;
    Player player;

    Texture NikoSprite = LoadTexture("00_niko.png");

    player.Start(NikoSprite);

    // or player.SetScale(Width, Height);
    // optional but player.SetPosition(PosX, PosY);

    while(!window.ShouldClose(false, {}, true, true, true)) {
        window.HotKeys();
        player.Update();

        BeginDrawing();
            ClearBackground(BLACK);
            player.Draw(NikoSprite, {0, 0});
        EndDrawing();
    }

    UnloadTexture(NikoSprite);

    CloseWindow();
    return 0;
}