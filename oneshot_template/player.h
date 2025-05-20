#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>
#include<vector>
#include<string>
#include<list>
#include <algorithm>
#include "../include/raylib.h"
#include "Keybinds.h"

class Player {
private:
    float LeftStickX = 0.0f;
    float LeftStickY = 0.0f;
    bool GamepadConnected = false;

    void AnimationStateUpdate() { // sets the state for animaton
        if(horizontal == 1) {
            AnimationState = AnimationStateNames[7]; // Walking Right State
        }

        if(horizontal == -1) {
            AnimationState = AnimationStateNames[6]; // Walking Left State
        }

        if(vertical == -1) {
            AnimationState = AnimationStateNames[4]; // Walking Up State
        }

        if(vertical == 1) {
            AnimationState = AnimationStateNames[5]; // Walking Down State
        }

        if(horizontal == 0 && vertical == 0) { // if no movement
            if(AnimationState == AnimationStateNames[7]) { // if state is walking right
                AnimationState = AnimationStateNames[3]; // IdleRight
            }

            if(AnimationState == AnimationStateNames[6]) { // if state is walking Left
                AnimationState = AnimationStateNames[2]; // IdleLeft
            }

            if(AnimationState == AnimationStateNames[4]) { // if state is walking Up
                AnimationState = AnimationStateNames[0]; // IdleUp
            }

            if(AnimationState == AnimationStateNames[5]) { // if state is walking Down
                AnimationState = AnimationStateNames[1]; // IdleDown
            }
        }
    }

    void OneShotWorldMachine_Movement() {
        // basic movement
        if(IsKeyDown(Keybinds.MoveRIGHT)) { // if key is pressed it makes horizontal 1 making it move to the right
            horizontal = 1;
            AnimationState = "WalkingRight";
        } else if(IsKeyDown(Keybinds.MoveLEFT)) { // other wise if this key is pressed it makes horizontal -1 making it move to the left
            horizontal = -1;
            AnimationState = "WalkingLeft";
        } else { // if neither are pressed, it stops 
            horizontal = 0;
        }

        if(IsKeyDown(Keybinds.MoveUP)) { // if key is pressed it makes vertical -1 making it move up
            vertical = -1;
            AnimationState = AnimationStateNames[5];
        } else if(IsKeyDown(Keybinds.MoveDOWN)) { // other wise if this key is pressed it makes vertical 1 making it move down
            vertical = 1;
            AnimationState = "WalkingDown";
        } else { // if neither are pressed, it stops 
            vertical = 0;
        }
        // if both keys are pressed it will stop player horizontal speed, not allowing him to go right or left until they are no longer pressed
        if(IsKeyDown(Keybinds.MoveRIGHT) && IsKeyDown(Keybinds.MoveLEFT)) {
            horizontal = 0;
        }

        // same as horizontal but this time it's vertical
        if(IsKeyDown(Keybinds.MoveUP) && IsKeyDown(Keybinds.MoveDOWN)) {
            vertical = 0;
        }
    }

    void OneShot_Movement() {
        // these 4 booleans check if RIGHT, LEFT, UP, DOWN is in the list and return false or true
        bool MoveRightInList = (std::find(MovementDirection.begin(), MovementDirection.end(), "RIGHT") != MovementDirection.end());
        bool MoveLeftInList = (std::find(MovementDirection.begin(), MovementDirection.end(), "LEFT") != MovementDirection.end());
        bool MoveUpInList = (std::find(MovementDirection.begin(), MovementDirection.end(), "UP") != MovementDirection.end());
        bool MoveDownInList = (std::find(MovementDirection.begin(), MovementDirection.end(), "DOWN") != MovementDirection.end());

        // all of these check if Key is pressed and check if this direction isn't in the list if it was true, it will add it to the list
        // if key is no longer pressed it will remove it from the list
        if(IsKeyDown(Keybinds.MoveRIGHT) && !MoveRightInList) {
            MovementDirection.push_back("RIGHT");
        } else if(IsKeyUp(Keybinds.MoveRIGHT)) {
            MovementDirection.remove("RIGHT");
        }

        if(IsKeyDown(Keybinds.MoveLEFT) && !MoveLeftInList) {
            MovementDirection.push_back("LEFT");
        } else if(IsKeyUp(Keybinds.MoveLEFT)) {
            MovementDirection.remove("LEFT");
        }

        if(IsKeyDown(Keybinds.MoveUP) && !MoveUpInList) {
            MovementDirection.push_back("UP");
        } else if(IsKeyUp(Keybinds.MoveUP)) {
            MovementDirection.remove("UP");
        }

        if(IsKeyDown(Keybinds.MoveDOWN) && !MoveDownInList) {
            MovementDirection.push_back("DOWN");
        } else if(IsKeyUp(Keybinds.MoveDOWN)) {
            MovementDirection.remove("DOWN");
        }

        if(MovementDirection.size() != 0) {
            // if list isn't empty it will check what is the lastest thing in list and change horizontal to 1 or 0, vertical to 1 or 0 depending on the lastest direction
            if(MovementDirection.back() == "RIGHT") {
                horizontal = 1;
            } else if(MovementDirection.back() == "LEFT") {
                horizontal = -1;
            } else {
                horizontal = 0;
            }
            
            // if both keys are pressed it will stop player horizontal speed, not allowing him to go right or left until they are no longer pressed
            if(IsKeyDown(Keybinds.MoveRIGHT) && IsKeyDown(Keybinds.MoveLEFT)) {
                horizontal = 0;
            }

            if(MovementDirection.back() == "UP") {
                vertical = -1;
            } else if(MovementDirection.back() == "DOWN") {
                vertical = 1;
            } else {
                vertical = 0;
            }
            // same as horizontal but this time it's vertical
            if(IsKeyDown(Keybinds.MoveUP) && IsKeyDown(Keybinds.MoveDOWN)) {
                vertical = 0;
            }
        } else {
            horizontal = 0;
            vertical = 0;
        }
    }

    void input() {
        if(IsKeyDown(Keybinds.LeftRUNKey) || IsKeyDown(Keybinds.RightRUNKey)) {
            // If auto run is enabled it will just walk otherwise it will run
            speed = (AutoRun ? Walkspeed : Runspeed);
        } else {
            // If auto run is enabled it will run otherwise it will just walk
            speed = (AutoRun ? Runspeed : Walkspeed);
        }
        
        if(!WorldMachineMovement) {
            OneShot_Movement();
        } else {
            OneShotWorldMachine_Movement();
        }

        // mulitplies the value by speed and deltatime, making player move faster depending on the speed and constantly no matter the fps
        position[0] += horizontal * speed * GetFrameTime();
        position[1] += vertical * speed * GetFrameTime();;
        
    }
public:
    std::vector<float> position = {500, 300};
    std::vector<float> scale = {0, 0};
    std::vector<float> pivot = {0, 0};
    float rotation = 0.0f;
    bool WorldMachineMovement = false;
    bool allowMoving = true;
    float Walkspeed = 100;
    float Runspeed = 200;
    float speed = Walkspeed;
    float horizontal = 0.0f; // controls if player goes right or left by -1(left) and 1(right)
    float vertical = 0.0f; // controls if player goes up or down by -1(up) and 1(down)
    bool AutoRun = false;
    std::list<std::string> MovementDirection; // list of directions to move for oneshot movement
    std::vector<std::string> AnimationStateNames = {"IdleUp", "IdleDown", "IdleLeft", "IdleRight", "WalkingUp", "WalkingDown", "WalkingLeft", "WalkingRight"};
    std::string AnimationState = AnimationStateNames[1]; // state for animation, All names for state of animations can be found in AnimationStateNames, this is for the animator.

    void SetPosition(float x, float y) {
        position[0] = x;
        position[1] = y;
    }

    void SetScale(float x, float y) {
        scale[0] = x;
        scale[1] = y;
    }

    void SetPivot(float x, float y) {
        pivot[0] = x;
        pivot[1] = y;
    }

    void Start(Texture2D texture = {0, 0}) {
        // usually width and height is started as zero, this fixes it.
        if(texture.id != 0) { // if texture isn't empty aka there is a texture, this changes size
            scale[0] = texture.width;
            scale[1] = texture.height;
        }
    }

    void Update() {
        if(allowMoving) {
            input();
        } else {
            horizontal = 0; // just to make sure it won't break anything
            vertical = 0;
        }
        
        AnimationStateUpdate();
    }

    void Draw(Texture2D Texture, Rectangle rectangle = {0, 0, 0, 0}, Texture2D lightmap = { 0, 0 }) {
        // the first two zeros are position of the texture | edit this comment here later
        Rectangle rectangleDraw = rectangle; // changes rectangle to given rectangle allowing animator to animate spritesheets
        if(rectangle.width == 0 && rectangle.height == 0) {
            rectangle = {0, 0, scale[0], scale[1]}; // edit later
        }

        DrawTexturePro(Texture, rectangle, {position[0], position[1], scale[0], scale[1]}, {pivot[0], pivot[1]}, rotation, WHITE);
        if(lightmap.id != 0) {
            DrawTexturePro(lightmap, rectangle, {position[0], position[1], scale[0], scale[1]}, {pivot[0], pivot[1]}, rotation, WHITE);
        }
    }
};
    

#endif