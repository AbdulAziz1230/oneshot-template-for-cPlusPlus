#ifndef MENUS_H
#define MENUSX_H

#include<string>
#include<array>
#include "player.h"

class Menus {
private:
    Texture2D DialogueBox_Icon = {0};
    std::vector<std::string> DialogueBox_Contents = {};
    bool DialogueBox_Show = false;
public:
    Texture2D DialogueBackground = { 0 };

    void DialogueBox(Texture2D Icon, std::vector<std::string> Contents, Texture2D DialogueBackgroundTexture = { 0 }) {
        if(DialogueBackground.id == 0) {
            std::cout << "Dialogue box has no background, please give DialogueBackground a Texture2D by passing a Texture2D as parameter for DialogueBox after the parameter content." << std::endl;
        }

        if(DialogueBackgroundTexture.id != 0) {
            DialogueBackground = DialogueBackgroundTexture;
        }

        DialogueBox_Icon = Icon;
        DialogueBox_Contents = Contents;
        DialogueBox_Show = true;
    }

    void DialogueBoxUpdate(Player& player, bool& InCutscene) {
        if(DialogueBox_Show) {
            player.allowMoving = false;
            InCutscene = true;
        }
    }

    void DialogueBoxDraw(std::array<int, 2> position = {GetScreenWidth() / 2, GetScreenHeight() / 2}, std::array<int, 2> scale = {0, 0}) {
        if(DialogueBox_Show) {
            DrawTexturePro(DialogueBackground, {0, 0, (float)DialogueBackground.width, (float)DialogueBackground.height}, {(float)position[0], (float)position[1], (float)DialogueBackground.width, (float)DialogueBackground.height}, {(float)DialogueBackground.width / 2, (float)DialogueBackground.height / 2}, 0.0f, WHITE);
        }
    }
};

#endif