// This is the example code of how to make a player with Oneshot template.
// Please refer to the README.md to understand what is this.

#include "include/raylib.h"
#include "oneshot_template/Oneshot.h"

using namespace OneshotTemplate;

int main()
{
    const int display_width = OneshotWindowWidth;
    const int display_height = OneshotWindowHeight;

    InitWindow(display_width, display_height, "Oneshot template - Player example");

    SetTargetFPS(60);

    SetExitKey(KEY_NULL);

    Texture NikoSprite = LoadTexture("Sprite.png");

    player.Start(NikoSprite); // Optionally you can use player.SetScale(Width, Height); to set the size to a specfic size.

    // If the player position incorrect you can use player.SetPosition(PosX, PosY);

    while(!window.ShouldClose(false, {}, true, true, true)) {
        window.HotKeys();
        player.Update();

        BeginDrawing();
            ClearBackground(BLACK);
            player.Draw(NikoSprite);
        EndDrawing();
    }

    UnloadTexture(NikoSprite);

    CloseWindow();
    return 0;
}