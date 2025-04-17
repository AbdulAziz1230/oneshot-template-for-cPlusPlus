#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "../include/raylib.h"
#include<vector>
#include<unordered_map>
#include<array>

typedef struct Animation {
    int first   = 0;
    int last    = 0;
    int current = 0;

    float speed = 5.0f;
    float duration_left = 1.0f;
    float max_duration = 1.0f;
    bool stop = false;

    std::unordered_map<std::string, std::array<int, 2>> States; // AnimateSpriteSheet only
    std::unordered_map<std::string, std::vector<Texture2D>> Textures; // AnimateTextures only
} Animation;

class Animator {
private:
    void AnimateFrames(Animation* animation) {
        if(!animation->stop) {
            animation->duration_left -= animation->speed * GetFrameTime();
        }

        if(animation->duration_left <= 0) {
            animation->duration_left = animation->max_duration;
            animation->current += 1;
        }

        if(animation->current > animation->last) {
            animation->current = animation->first;
        } else if(animation->current < animation->first) {
            animation->current = animation->first;
        }
    }
public:
    Rectangle AnimateSpriteSheet(Texture2D texture, Animation* animation, int row, int column) {
        AnimateFrames(animation);

        // basically this crops the spritesheet all the way to the first image on top left making it ready to animate
        float SpritesheetWidth = (float)texture.width / row;
        float SpritesheetHeight = (float)texture.height / column;
        // here it moves it using currrent frame giving the frame by index
        float SourceX = (animation->current % row) * SpritesheetWidth;
        float SourceY = (animation->current / row) * SpritesheetHeight;

        return {SourceX, SourceY, SpritesheetWidth, SpritesheetHeight};
    }

    Texture2D AnimateTextures(Animation* animation, std::string state) {
        AnimateFrames(animation);

        return animation->Textures[state][animation->current];
    }
};

#endif