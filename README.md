## Update.
I don't think I'll be working on this anymore and I kinda regerted making this public this is why this repo went private and the reddit post got deleted but I guess I'll put it back up. 

## What's new?
README.md got a rewrite to make it bearable to look at. I hate the old README.md.(Yes this is the reason why most of the new stuff here are unfinished)

Messageboxes now use `MessageboxW` instead of `MessageboxA` that means Messageboxs can display more languages.

Os.h is now a thing while unfinsihed and has an empty void for the background you can use the `OS::GetUsername` function to get the username(Windows only, Linux will return the unknow name).

Now you don't need to make a class object for everything, everything is packed in namespace `OneshotTemplate`.

Removed the center option from `player.start()` as it didn't work correctly and was a left over.

Now all filenames start with a capital letter in `oneshot_template`.

`Animator.h` got a few new comments now.

`build.bat` and `Makefile` are removed due to them being only for building raylib serving no purpose for the template.

`LoadDialogue.h` and `Save.h` are new files here but currently serves no purpose.

## In the beginning
This template uses Windows API, the following things won't work on other opreating systems.

1. MessageBoxs
2. Window Fadeout / Opacity
3. Get username

The Os.h(Name might change in the future) is currently unfiinished i wanted to push this version to fix MessageBoxs to make them support other languages and because os has get Username.

(The the truth is because i hated the readme and wanted to rewrite it...)

This is a highly unfinished project that i worked on during March of 2025 and mostly stopped after it(Working on it a bit now when i want to.) and was made for fun.

This template tries to remake stuff from [Oneshot](https://store.steampowered.com/app/420530/OneShot) and [OneShot: World Machine Edition](https://store.steampowered.com/app/2915460/OneShot_World_Machine_Edition/)(This here because there's an option for world machine movement for the player.) in c++ for raylib and be ready to use for you. (Did it because this game is so good) 

`Menus.h`, `Gamepad.h` and `Os.h` are currently unfinished with `Save.h` being empty but 2 comments.

The reason of releasing this is i haven't worked at it a while so why not release it, hopefully it may help someone with anything.

You can test using examples in the Example folder to see how it would work or you can take whatever piece of code and edit whatever you want in oneshot template to fit what you want and desire.

And all keys are rebindable in `Keybinds.h`

## raylib
Raylib must be installed to use this template as it is built for raylib, [You can get Raylib here](https://www.raylib.com/), you are expected to know how to use Raylib here.


raylib.h is suppose to be in a include folder, otherwise you might have to change the path in most of those files.

The reason is oneshot_template tries to go back a folder then go to include folder and get the raylib.h

## Table of contents
[Settting up Oneshot Template in code.](#settting-up-oneshot-template-in-code)

[Keybinds.](#keybinds)

[Basic window.](#basic-window)

[Adding the player.](#adding-the-player)

[The animator.](#the-animator)

[Os.](#os)

[The end.](#the-end)

The vars and voids of.

[Window.h](#windowh-vars-and-voids)

[Player.h](#playerh-vars-and-voids)

## Settting up Oneshot Template in code
You need to include Oneshot.h using `#include "oneshot_template/Oneshot.h"` and that's it for including, it got everything you need, all files you are seeing are for completing classes for Oneshot.h.

You can now use (Outside of main void) `using namespace OneshotTemplate` or do(In main void) objects for the classes you want to use like `Player player` or `Window window` the namespace creates all the classes objects.

That's it, now you can use the template.

(I created this section for it to not be with Basic window...)

## Keybinds
You can rebind all keys in `oneshot_template/Keybinds.h`.

Inside of it there's a struct with Int vars, it's all just Raylib `KEY_` if your editor doesn't have the suggestion thing or whatever it's called just type the key in Capital like `KEY_K` or `KEY_F10` and `KEY_LEFT_SHIFT`.

For calling the Keybinds, (If you have Oneshot.h included you don't need to do that) you need to include `oneshot_template/Keybinds.h` then type `Keybinds.` and type the name of the var like `Keybinds.MoveUP` or `Keybinds.FullScreenHotKey`.


## Basic window
When setting window size you can use `OneshotWindowWidth` and `OneshotWindowHeight` for the window size which is just the size of Oneshot's window, yes that took me alot of tests to get right.

And it's recommended to use `SetExitKey(KEY_NULL);` to just make it not close when you press esc or any other button.

And instead of using `while(!WindowShouldClose())` you should use `while(!window.ShouldClose(Bool, {List of bools}, Bool, Bool, Bool))` With window being the name of your class object if you used that.

First false is IsInCutscene, which prevent window from closing if you are in a cutscene.

{}(Aka the list) You can put a list of boolean vars to prevent game from closing if the player tried to close the game in case any of them was true, if all vars were false then it will allow closing.

Thrid one, if it was true when you close the game window will fade out(Windows only) other wise it will close without fade out.

Fourth is whether it shows exit dialogue when closing the game or not.

Fifth is whether to show exit during cutscne dialogue or not.

Inside the while loop, you should call `window.HotKeys();` this allows the game to fullscreen on pressing `F8`(Default).

There's an example for Basic window in `Examples/basic_window.cpp`

## Window.h vars and voids
vars:

`fullscreenOnBeing`(Boolean, Default: false) Whether to fullscreens on game being launched or not.

`borderlessFullscreen`(Boolean, Default: false) if true, when fullscreening it will fullscreen using borderless mode instead of fullscreen.

`LetCloseWithoutFadeout`(Boolean, Default: false) Made for the code to not soft-lock on other opreating systems when the game tries to fade out but you can use it to stop the fade out at a certain moment otherwise change it in window.ShouldClose.

`FirstQuitDialogueShowed`(Boolean, default = false), if true it will show the usual exit dialogue that shows up on the rest of the exits.

`FirstQuitDialogue`(Vector aka a list) A list of strings for changing first exit dialogue.

`QuitDialogue;` (Vector aka a list) A list of strings for changing exit dialogue.

`QuitDuringCutscneDialogue`(Vector aka a list) A list of strings for changing exit during cutscene dialogue.

Those all accpet {} lists, you can change them like `FirstQuitDialogue = {"String 1", "String 2", "String 3"}`.

`fadeOutSpeed`(Float, Default: 3) Changes how fast the window fades out on close.

`WinButtons`, This struct got a few button options for Windows Pop ups, just `MB_` but in struct to make it easier to find.

1. Ok,          (Returns ok: 1).

2. Ok/Cancel    (Returns ok: 1, cancel: 2).

3. Retry/Cancel (Returns Retry: 4, cancel: 2).

4. Yes/No, Yes  (Returns Yes: 6, No: 7)

`WinIcons`, This struct got a few icon options for Windows popup, just `MB_ICON` but in a struct to make it easier to find.

1. Information icon.

2. Warning icon.

3. Error icon.

4. Question icon.

Voids: 

`window.WindowOpacity(Float);` For changing opacity of the window, it only accpets 1 and 0 and the between for the rest, below the 0 or above the 1 wouldn't do anything but be 0 or 1.


`MessageBox(String, string, UINT(aka Int), UINT(aka Int))` Displays a Windows messagebox using WindowsAPI.

`ShouldClose(Boolean, Vector boolean, Boolean, Boolean, Boolean)` Use this(from Window.h) instead ShouldClose(Raylib)

(Reused from Basic window section)

First false is IsInCutscene, which prevent window from closing if you are in a cutscene.

{}(Aka the list) You can put a list of boolean vars to prevent game from closing if the player tried to close the game in case any of them was true, if all vars were false then it will allow closing.

Thrid one, if it was true when you close the game window will fade out(Windows only) other wise it will close without fade out.

Fourth is whether it shows exit dialogue when closing the game or not.

Fifth is whether to show exit during cutscne dialogue or not.

`HotKeys()` Currently is only for fullscreening on pressing `F8`(You can change it in Keybinds.h) and fullscreens on launching the game if `fullscreenOnBeing` was true.


## Adding the player
If you didn't use the namespace, Make a Player object `Player player;` outside of the while loop.

Then create a Texture2d for the player image, you can load a normal image or a sprite sheet for the animator.

Optional but you can call `player.start(Texture)` and for agruments just give it the texture,  otherwise use `player.SetScale(Width, Height);` to scale the player.

In the while loop add `player.Update();` this will update the player movement and make the player work in general.

In the draw add `player.Draw(Texture);` This will draw the player.

Now by this, you should have a working player, you can adjust a few things but most importantly is World machine or Oneshot movment.

`player.WorldMachineMovement` bool.

You can check the example in `Examples/player.cpp` on how this suppose to be like and look.

## Player.h vars and voids
While there is remains of controller code this is not an option yet.

vars:

`position` (Vecotr aka a list, Default; {500, 300}) you can get the positon or change it by `player.position[0]`(For X) or `player.position[1]`(For Y).

`scale` (Vecotr aka a list, Default: {0, 0}), you can get the scale or change it by `player.scale[0]`(For width) or `player.scale[1]`(For height).

`pivot` (Vecotr aka a list, Default: {0, 0}) you can get the pivot or change it by `player.pivot[0]`(For X) or `player.pivot[1]`(For Y).

`rotation`(Float, Default: 0.0f) for the rotation of the players image aka sprite.

(Currently not accurate due to Oneshot(Not World machine edition.) using grid system for movement)
`WorldMachineMovement`(Bool, Default: false) When it's true it will use World machine edition type of movement which allows diagonal movement and doesn't have a grid movement otherwise if it's false it will use Oneshot movement (Currently also doesn't support grid) and diagonal movement isn't allowed.

`allowMoving`(Bool, Default: true) Whether to allow the player to move or not, this will usually be disabled by cutscenes.

`Walkspeed`(Float, 100) The speed of the player when moving.

`Runspeed`(Float, 200) The speed of the player when `SHIFT`(Default)

`speed`(Float, Default: `Walkspeed`(100)) The speed of moving which is changed by walking or running.

`horizontal`(Float, Default: 0.0f) This value changes by code to make the player go to the left(-1) or the right(1) or not move horizontally at all.

`vertical` (Float, Default: 0.0f) This value changes by code to make the player go up(-1) or down(1) or not move vertically at all.

`AutoRun`(Float, Default: 0.0f) 

`MovementDirection`(Vector of strings) It's used for Oneshot movement system, when a key is pressed it will be registered at the end of the list and for the movement it will check the last thing in the list to determine in what direction it should go, if it's empty it will not move. You don't need to touch it but it's public you can use it.

`AnimationStateNames`(Vector of strings) It's for the names of the animations that the player have for idle and movment

`IdleUp, IdleDown, IdleLeft, IdleRight, WalkingUp, WalkingDown, WalkingLeft, WalkingRight`

`AnimationState`(String, Default: `IdleDown`(The second thin of `AnimationStateNames`)) This string is for the current animation state, use it for the animator.

Voids:

`player.SetPosition(PosX, PosY)` Sets the position of the player.

`player.SetScale(Width, Height)` Sets the scale of the player.

`player.SetPivot(PosX, PosY)` Sets the pivot of the player.

`player.Start(Texture);` This should resize your player to the images width and height.

`player.Update();` This is the entire Player's logic and movement.

`player.Draw(Texture, rectangle(optional), Texture(optional));` This will draw the player on the screen.

First Texture is the Player's texture

Rectangle is for spritesheet animation.

Second Texture, please do not touch. Lightmaps don't work, it will display the light map in top of the player as it is.


## The animator
While loading textures for animation is an option it's not explained here, I don't even remember it exactly and please use a sprite sheet, I don't want to make 16 vars to load the images and 16 more unloads.

Do all of those out of the while loop.

If you didn't use the namespace, make `Animator` class object `Animator animator;`.

For animations you need to make a struct object which to make it easier I'll call it animation, `Animation animation;`

Now for the texture load the spritesheet.

For the animation you need to give it a list of animations by creating an unordered_map(No need to include anything.) `animation.States = std::unordered_map<std::string, std::array<int, 2>>` now you can pass the list of animations to this, just add `{};` and this is it for the list but for the inside put `{String, {Int, Int}` with the string being the name of the animation and first int being where the first frame is and the second int being where the last frame is, do this for all of your animations.

An example(Works for the orignal Niko sprite)

`{"IdleUp", {12, 12}}, {"IdleDown", {0, 0}}, {"IdleLeft", {4, 4}}, {"IdleRight", {8, 8}}, {"WalkingUp", {12, 15}}, {"WalkingDown", {0, 3}}, {"WalkingLeft", {4, 7}}, {"WalkingRight", {8, 11}}`

Now inside the while loop Make a Rectangle var `Rectangle rectangle` and set it's value to `animator.AnimateSpriteSheet(Texture, &animation, int, int);` This'll do the animation when you give the player the rectangle.

Texture is your spritesheet

`&animation` Is your animation, & is important while passing your animation because this will pass the animation instead of a copy.

First Int is how many rows in the sprite sheet and the second Int is how many columns in the spritesheet.

Now we have `animation.first` and `animation.last` both got to be set to `animation.States[String]` and the string is the name of the animation and for the first end it with `[0]` and for the last `[1]` this'll set beginning and the end of animation, example `animation.first = animation.States[String][0];`

And for the player use `player.AnimationState` for the name of the animation, your animation names got to match the ones that Player animation names have.

For texture use `DrawTexturePro` and pass it the rectangle.

But for the player in `player.Draw` you can pass the rectangle as an agrument after giving it Spritesheet Texture basically `player.Draw(Texture, Rectangle);`

The section was orignally for the player animations but for the rewrite it got changed for animations in general that's why in the example it's called `player_with_anim`.

There's an example for this(For the player) in `Examples/player_with_anim.cpp`.

## Os
I called this Os due to me not knowing what to call it.

Currently very unfinished

`OS::GetUsername(String(Optional))` This'll get the username, the string it takes is optional with default value being `Unknown` it will return this string in case of Player's opreating system not being Windows or in case that it failed get the username.

`ChangeBackground()` Currently useless doesn't do anything but it's purpose is changing Player's background.

This is it for now.

## The end

While the template currently isn't much this entire thing took me very long to do and to fix the Pop ups messing the deltatime during the fade out.

Thank you for reading this, I hope it helped you, I'm not sure if this will be finished at all.

Thank you for being here and good bye.
