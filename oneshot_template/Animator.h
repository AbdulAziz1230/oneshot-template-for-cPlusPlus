#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "../include/raylib.h"
#include<vector>
#include<unordered_map>
#include<array>

typedef struct Animation { // Animation stuff
    int first   = 0;
    int last    = 0;
    int current = 0;

    float speed = 5.0f;
    float duration_left = max_duration;
    float max_duration = 1.0f;
    bool stop = false;

    std::unordered_map<std::string, std::array<int, 2>> States; // Animate SpriteSheet only
    std::unordered_map<std::string, std::vector<Texture2D>> Textures; // AnimateTextures only
} Animation;

class Animator {
private:
    void AnimateFrames(Animation* animation) {
        // If animation didn't stop the timer moves on.
        if(!animation->stop) {
            animation->duration_left -= animation->speed * GetFrameTime();
        }

        // If time finished counting it will go to the next frame.
        if(animation->duration_left <= 0) {
            animation->duration_left = animation->max_duration;
            animation->current += 1;
        }

        // if the current frame number was bigger than the last it will will be set to the first
        if(animation->current > animation->last) {
            animation->current = animation->first;
        // otherwise if current frame number was smaller than the first it will be set to the first.
        } else if(animation->current < animation->first) {
            animation->current = animation->first;
        }
    }
public:
    Rectangle AnimateSpriteSheet(Texture2D texture, Animation* animation, int row, int column) {
        AnimateFrames(animation);

        // Basically this crops the spritesheet all the way to the first image on top left making it ready to animate.
        float SpritesheetWidth = (float)texture.width / row;
        float SpritesheetHeight = (float)texture.height / column;
        // Here it moves it using currrent frame giving the frame by index.
        float SourceX = (animation->current % row) * SpritesheetWidth;
        float SourceY = (animation->current / row) * SpritesheetHeight;

        // And at the end it returns it as a rectangle.
        return {SourceX, SourceY, SpritesheetWidth, SpritesheetHeight};
    }

    Texture2D AnimateTextures(Animation* animation, std::string state) {
        AnimateFrames(animation);

        return animation->Textures[state][animation->current];
    }
};

#endif
