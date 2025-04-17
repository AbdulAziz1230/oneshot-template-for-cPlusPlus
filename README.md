## at the beginning
hi im abdul aziz.

This is a highly unfinished project that i worked on during ramadan(March, so basically last month) and mostly stopped after it, it's for Raylib

So, let's begin by explaing what this is. this template is made for c++ for fun, it replicates mechanics from oneshot 2016 and does stuff for you, currently, Player, Window stuff(mostly not useful for linux), and a bad animator / animation system

menus.h, gamepad.h they're unfinished, menus, you can get a text box but it's useless

i haven't worked on this project for a while so i decided to release it.

You can test using examples, to see how it would work.

or you can take whatever piece of code or edit whatever you want in oneshot template to fit what you want and desire

and a quick thing, when i tell you to make a class object. make it out of the while loop not inside.

## basic window
first you need to include oneshot.h using `#include <oneshot_template/oneshot.h>` and that's it for including, it got everything you need. all files you are seeing are for completing classes for oneshot.h

when setting window size you can use `OneshotWindowWidth` or `OneshotWindowHeight` which is just size of oneshot window, yes that took me alot of tests to get right.

and it's recommended to use `SetExitKey(KEY_NULL);` to just make it not gonna close when you press esc or any other button.

anyway add `Window window;` which creates a window class object

and instead of using `while(WindowShouldClose)` you should use `while(!window.ShouldClose(false, {}, true, true, true))` with window being the name of your class object

first false is IsInCutscene, which prevent window from closing

{} you can put boolean vars to prevent game from closing, it could be whatever you want, if all vars are false then it will close, but if one single var is true it will prevent closing

thrid one if it was true when you closing the game window will fadeOut(windows only) other wise it will close without fadeOut

fourth is exit Dialogue, fifth is Dialogue that appears when you try to exit during a scene

inside the while, you should call `window.HotKeys();` this allows the game to fullscreen on pressing `F8` which can be changed in binding.h

this is it for a basic window, but because you read all of that you can get these two things.

## windows.h vars and voids
vars:

`borderlessFullscreen` this boolean if true, when fullscreening it will fullscreen using borderless instead of fullscreen

`FirstQuitDialogueShowed` this boolean, will change exit dialogue if false, it will show first time quit dialogue, if it was true, it will show the usual exit message

`window.FirstQuitDialogue = {};`

`window.QuitDialogue = {};`

`window.QuitDuringCutscneDialogue = {} `

these all accpet {} lists you can put anything and it would show like `{"you expected good example?", "No", "i am steve"}`, all gotta be string though

and this would change it

`WinButtons` this struct got a few button options for windows popup, just `MB_` but in struct to make it easier to find

1 - Ok, returns 1

2 - Ok/Cancel, ok returns 1, cancel returns 2

3 - Retry/Cancel, Retry returns, cancel returns 2

4 - Yes/No, Yes returns 6, No returns 7

`WinIcons` this  struct got a few icon options for windows popup, just `MB_` but in struct to make it easier to find

`LetCloseWithoutFadeout` which is a boolean, made for cases fadeout can't succeed

voids: 

`window.WindowOpacity(Value);` this changes window opacity, it accpets 

`window.fadeOutSpeed = Value;` changes fadeout speed, default is 3.

`MessageBox(Content, Caption, icon, buttons)` name are self-explaintory, it just calls MessageboxA from windows API

## adding a player
just make a new class object `Player player;`

than load a Texture, you know how, it's a raylib thing i won't explain raylib

optional but, call `player.start(Texture)` and for agruments give it the texture, this should resize your player to the images width and height

otherwise use `player.SetScale(Width, Height);` to scale the player

in the while loop, add `player.Update();` this will update the player, with well, everything

in the draw add `player.Draw(Texture);`

now by this you should an actual working player, look at `Examples/player.cpp` to see how your code suppose to look like or not.

## player.h vars and voids
all keys are rebindable in rebinds.

vars:

`WorldMachineMovement` boolean if true, movement system will change to world machine movement system, if false, it will be oneshot movement system(not entirely accurate due to not using grid system for movement)

`rotation` float for rotation....

`allowMoving` boolean to allow moving or not....

`Walkspeed`, `Runspeed` they have names...

`horizontal` horizontal is moving left and right. it's value between -1(left) and 1(right)

`vertical` vertical is moving up and down. it's value between -1(up) and 1(down)

`AutoRun` if this was true default movement gonna be run and when shift is clicked you will walk, if it was false, just default movement, and shift to run

`MovementDirection` you don't need to touch that but

every keys you press(arrows, unless rebinded) it will add it to the list, when key is released it will get removed from the list and the code checks the last thing to decide if player is moving left/right/up/down or not moving at all(oneshot movement only)

`AnimationStateNames` when you move, it will choose these name as the animation state

`AnimationState` the current animation state(by default, "IdleUp", which is niko facing up while not moving)

voids:

transforms are

`player.SetPosition(PosX, PosY)`

`player.SetScale(Width, Height)`

`player.SetPivot(PosX, PosY)`

the other stuff

`player.Start();`

`player.Update();`

`player.Draw(Texture, rectangle(optional, needed for spritesheet animation), (This takes a Texture)Lightmap(will do nothing, lightmaps are not implemented yet...));`


## adding animations to OUR player Warning: bad animation system


first add `Animator animator;` class object.

and add `Animation playerAnim;` this one is for player animations as the name suggests

if you have mulitple images scroll down, this is for spritesheet

instead of loading a single image, load the entire spritesheet

still out of the while loop add `playerAnim.States = std::unordered_map<std::string, std::array<int, 2>> ` and inside put ` {"name", {place_in_row, place_in_col}}` add `,` if you are gonna put another anim after it `"name", {place_in_row, place_in_col}}, "name", {place_in_row, place_in_col}}`

now finally inside the while loop

add `Rectangle PlayerRectangle  = animator.AnimateSpriteSheet(Texture, &playerAnim(& give the struct(var) itself allowing edit to it), how_many_rows, how_many_cols);`

after it

`playerAnim.first = playerAnim.States[player.AnimationState][0];`, `playerAnim.first` this sets frame to start at and the other one is the last

`playerAnim.States` is the animation list you made and `[player.AnimationState][0]` take animation state from the player and [0] at the end takes the first frame while [1] take the last frame

and when drawing the player add `, PlayerRectangle`

as in `player.Draw(PlayerSpritesheet, PlayerRectangle)`

check `Examples/player_with_anim.cpp` to understand better. i tried but i'm in a hurry.

there's another one for more images but i don't wanna explain it... make a sprite sheet... loading alot of images is too much.


## keybinds
to call a keybind you can just use

`Keybinds.` and you'll find all the keybinds, or add your own, `int name = KEY_;`, `KEY_` should have all the keys you need

you can enter `Keybinds.h` and edit the vars to change the bind


## the end

it took me long time to do these. while they're not much, THE POPUP MESSES DELTATIME

Thank you for reading this, hope it helped you, and hope atleast one thing helps you here, i'm not sure if i'm coming for this but it was fun working on it.

See you Next time! 靴を履いたピンクのサメ(this is Japanese)!