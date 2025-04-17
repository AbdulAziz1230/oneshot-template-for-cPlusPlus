// this is not a tutorial, just an example code. read README.md to know what is going on here and why there's 4 booleans and {} for window.Should close


#include<iostream>
#include "include/raylib.h"
#include "oneshot_template/oneshot.h"

int main()
{
    const int display_width = OneshotWindowWidth;
    const int display_height = OneshotWindowHeight;

    InitWindow(display_width, display_height, "Oneshot template - Player with animations Example");

    SetTargetFPS(60);

    SetExitKey(KEY_NULL); // optional but oneshot didn't have any key as exit

    Window window;
    Player player;
    Animator animator;
    Animation playerAnim;

    Texture NikoSprite = LoadTexture("spritesheet_path");

    player.Start(NikoSprite);

    player.SetScale(55, 70);
    // optional but player.SetPosition(PosX, PosY);

    // compatible with Niko spritesheet
    playerAnim.States = std::unordered_map<std::string, std::array<int, 2>> { // basically in niko image it splits in cols and raws, these are where to begin in frame and where to end
        {"IdleUp", {12, 12}},

        {"IdleDown", {0, 0}},

        {"IdleLeft", {4, 4}},

        {"IdleRight", {8, 8}},

        {"WalkingUp", {12, 15}},

        {"WalkingDown", {0, 3}},

        {"WalkingLeft", {4, 7}},

        {"WalkingRight", {8, 11}}
    };

    while(!window.ShouldClose(false, {}, true, true, true)) {
        window.HotKeys();
        player.Update();

        Rectangle NikoRectangle = animator.AnimateSpriteSheet(NikoSprite, &playerAnim, 4, 4);

        playerAnim.first = playerAnim.States[player.AnimationState][0];
        playerAnim.last = playerAnim.States[player.AnimationState][1];

        BeginDrawing();
            ClearBackground(BLACK);
            player.Draw(NikoSprite, NikoRectangle, {0, 0});
        EndDrawing();
    }

    UnloadTexture(NikoSprite);

    CloseWindow();
    return 0;
}