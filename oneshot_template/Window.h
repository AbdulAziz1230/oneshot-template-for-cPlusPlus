#ifndef WINDOW_H
#define WINDOW_H

#include "../include/raylib.h"
#include<algorithm>
#include<initializer_list>
#include "Keybinds.h"

// When i say X button, that means anyway of closing the window 

// this is here because this header uses windows api to do some stuff like window fading and windows pop up
// you can use "#undef _WIN32" without the quotes to test how game will run if it's not on windows
#ifdef _WIN32 // if current platform is windows
#define WIN32_LEAN_AND_MEAN
#define Rectangle RayRectangle
#define CloseWindow RayCloseWindow
#define ShowCursor RayShowCursor
#include <windows.h>
#undef Rectangle // undefine some stuff that has same names as stuff from raylib
#undef CloseWindow
#undef ShowCursor
#undef DrawText
#undef LoadImage
#undef MessageBox
#else // if current platform isn't windows
#include<iostream>
#endif

int OneshotWindowWidth = 640; // Width that matches Oneshot window.
int OneshotWindowHeight = 484; // Height that matches Oneshot window.
// these sizes are by me comparing and guessing and winspy was a test to see if it's accurate

class Window {
private:
    bool closewindow = false;
    bool started = false;
    int OrignalDisplayWidth = 0; // stores orignal window size on fullscreen
    int OrignalDisplayHeight = 0; 
    float opacity = 1; // opacity of window (Windows only)
    bool WindowFadedOut = false; // if window faded out compeltley or not (Windows only)
    bool FadeWindowOut = false; // fades the window out (Windows only)
    bool FadeOutNotSupportedMessagePrinted = false;
    bool WindowOpacityNotSupportedMessagePrinted = false;
    bool PopUpNotSupportedMessagePrinted = false;
    float FrameTime = 0.0f; // save deltatime before calling Windows Popup to make sure fading out won't be so incredibly fast
    bool fullscreen = false;

    void fullScreen() {
        if(fullscreen) { 
            // sets window size to your monitor size and fullscreens, if window size didn't change first it would take longer to full screen and it will look bad too.
            SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
            SetWindowState(FLAG_FULLSCREEN_MODE);
        } else {
            // clears the fullscreen flag and reverts window to it's orignal size
            ClearWindowState(FLAG_FULLSCREEN_MODE);
            SetWindowSize(OrignalDisplayWidth, OrignalDisplayHeight);
        }
    }

    void BorderlessWindowed() {
        if(fullscreen) {
            SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE); // borderless fullscreen
        } else {
            ClearWindowState(FLAG_BORDERLESS_WINDOWED_MODE); // removes borderless fullscreen flag
        }
    }

#ifdef _WIN32 // checks if current platform is window
    int exitDialogue() { // dialogue of if X button
        if(!FirstQuitDialogueShowed) { // if this is the first time X button is clicked.
            FirstQuitDialogueShowed = true;
            for(int i = 0; i < FirstQuitDialogue.size(); i++) { // loop of messages to show
                // goes on a for loop and if it wasn't the last pop up it shows ok button otherwise it shows Yes or No.
                if(i == FirstQuitDialogue.size() - 1) {
                    return MessageBox(FirstQuitDialogue[i].c_str(), "", WinIcons.Information, WinButtons.OkCancel); // shows Yes or No information windows pop up
                    // it returns value of 6 if yes or 7 if no
                } else {
                    MessageBox(FirstQuitDialogue[i].c_str(), "", WinIcons.Information, WinButtons.Ok); // shows ok information windows pop up
                }
            }
        } else { // if this isn't the first time X button is clicked. 
            for(int i = 0; i < QuitDialogue.size(); i++) { // loop of messages to show
                // goes on a for loop and if it wasn't the last pop up it shows ok button otherwise it shows Yes or No.
                if(i == QuitDialogue.size() - 1) {
                    return MessageBox(QuitDialogue[i].c_str(), "", WinIcons.Information, WinButtons.OkCancel); // shows Yes or No information windows pop up
                    // it returns value of 6 if yes or 7 if no
                } else {
                    MessageBox(QuitDialogue[i].c_str(), "", WinIcons.Information, WinButtons.Ok); // shows ok information windows pop up
                }
            }
        }
        return 0;
    }

    void QuitDuringSceneDialogue() {
        for(int i = 0; i < QuitDuringCutscneDialogue.size(); i++) { // for loop of messages to appear if you tried to exit during a cutscene
            // shows a windows information pop up with an ok button
            MessageBox(QuitDuringCutscneDialogue[i].c_str(), "", WinIcons.Information, WinButtons.Ok);
        }
    }

    std::wstring ToUTF16(std::string utf8) {
        int size = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
        std::wstring wstr(size, 0);
        MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &wstr[0], size);
        wstr.pop_back();
        return wstr;
    }

    void FadeOut(float fadingSpeed = 0) { // fades the window out
        fadingSpeed = fadeOutSpeed;
        if(FadeWindowOut) {
            if(opacity < 0) {
                opacity = 0;
            }

            WindowOpacity(opacity);

            if(opacity > 0) { // if opacity is bigger than 0 it makes it fade away, it's multiplied by deltatime so frames shouldn't be a big problem hopefully.
                opacity -= fadingSpeed * FrameTime;
            }
        }

        if(opacity <= 0) { // if opacity is 0 or smaller it will make WindowFadedOut true letting the window close.
            WindowFadedOut = true;
        }

    }

#else
    void FadeOut() {
        // checks if message is printed before or not, if it wasn't ir prints it.
        if(!FadeOutNotSupportedMessagePrinted) {
            std::cout << "WindowOpacity: FadeOut is Windows only due to using windows.h, sorry this void won't work on your machine." << std::endl;
            FadeOutNotSupportedMessagePrinted = true;
        }

        WindowFadedOut = true; //  makes WindowFadedOut true to not softlock the player
    }
#endif

public:
    bool fullscreenOnBeing = false; // whether it fullscreens when game is launched or not
    bool borderlessFullscreen = false; // whether it fullscreens on borderless window mode or acutal fullscreen
    bool LetCloseWithoutFadeout = false; // used for other platforms that aren't windows to let the game close without the fade out
    bool FirstQuitDialogueShowed = false; // whether it's the first time the X button is pressed or not
    std::vector<std::string> FirstQuitDialogue = {"This action will record your progress in this world.", "To return to this world again, you need to relaunch the application.", "Proceed?"};
    std::vector<std::string> QuitDialogue = {"Quit and record your progress?"};
    std::vector<std::string> QuitDuringCutscneDialogue = {"You cannot perform this action during cutscenes."};
    float fadeOutSpeed = 3;

#ifdef _WIN32 // checks if current platform is window
    void WindowOpacity(float alpha) { // i don't understand this code but it changes opacity with float alpha
        HWND hwnd = (HWND)GetWindowHandle();
        LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);

        if(!(style & WS_EX_LAYERED)) {
            SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED);
        }

        BYTE alphabyte = (BYTE)(alpha * 255);
        SetLayeredWindowAttributes(hwnd, 0, alphabyte, LWA_ALPHA);
    }
    
    struct { // trying to make it simpler to find icons
        // you can find more icons on MB_ICON (that sounded like "you can find more icons on our website "https://WinIcons.scam" vist us today!" Lol)

        int Information = MB_ICONINFORMATION;
        int Warning = MB_ICONWARNING;
        int Error = MB_ICONERROR;
        int Question = MB_ICONQUESTION;
    } WinIcons;

    struct  { // trying to make it simpler to find buttons 
        // im too lazy to find them and i don't see you needing anything else beside those

        int Ok = MB_OK; // returns 1
        int OkCancel = MB_OKCANCEL; // returns 1 for ok and 2 for cancel
        int RetryCancel = MB_RETRYCANCEL; // returns 4 for retry and 2 for cancel
        int YesNo = MB_YESNO; // returns 6 for yes and 7 for no
    } WinButtons;

    int MessageBox(std::string Content, std::string Caption, UINT icon, UINT buttonsType) { // trying to make it easier to find the MessageBox aka Windows Popup
        std::wstring caption = ToUTF16(Caption);
        std::wstring content = ToUTF16(Content);
        return MessageBoxW(NULL, content.c_str(), caption.c_str(), icon | buttonsType); // calls windows pop up
    }
    
#else // otherwise if platform isn't windows
    void WindowOpacity(float alpha) {
        // checks if message is printed before or not, if it wasn't ir prints it.
        if(!WindowOpacityNotSupportedMessagePrinted) {
            std::cout << "WindowOpacity is Windows only due to using windows.h, sorry this void won't work on your machine." << std::endl;
            WindowOpacityNotSupportedMessagePrinted = true;
        }
    }

    // Just here to not break the code for Linux.

    struct {
        int Information = 0;
        int Warning = 0;
        int Error = 0;
        int Question = 0;
    } WinIcons;

    struct  {
        int Ok = 0;
        int OkCancel = 0;
        int RetryCancel = 0;
        int YesNo = 0;
    } WinButtons;

    int MessageBox(std::string Content, std::string Caption, UINT icon, UINT buttonsType) { // trying to make it easier to find the MessageBox aka Windows Popup
        // checks if message is printed before or not, if it wasn't ir prints it.
        if(!PopUpNotSupportedMessagePrinted) {
            std::cout << "PopUps are Windows only due to using windows.h, sorry this void won't work on your machine." << std::endl;
            PopUpNotSupportedMessagePrinted = true;
        }
    }
#endif
    
    bool ShouldClose(bool InCutscene = false, std::initializer_list<bool> preventClosing = {}, bool fadeoutWhenClose = true, bool QuitDialogue = true, bool CutscneQuitDialogue = true) {
        // one of the main stuff here

        // ShouldClose here will prevent window from closing, makes window fadeout on exit, make pop ups appear. preventClosing list checks if all booleans are false
        // if they were it returns true otherwise false meaning nothing stopping the window from closing
        bool NoClosePreventing = std::all_of(preventClosing.begin(), preventClosing.end(), [](bool b) { return !b; });

#ifdef _WIN32 // checks if current platform is window
        if(CutscneQuitDialogue && InCutscene && WindowShouldClose()) { // if player tried to quit during cutscene and CutscneQuitDialogue is enabled
            QuitDuringSceneDialogue();
        }
#endif

        if(WindowShouldClose() && !InCutscene && NoClosePreventing) {
#ifdef _WIN32 // checks if current platform is window
            if(QuitDialogue) {
                if(exitDialogue() == 1) {
                    FrameTime = GetFrameTime();
                    closewindow = true;
                }
            } else {
                FrameTime = GetFrameTime();
                closewindow = true;
            }
#else // if platform wasn't windows it changes closewindow to true to prevent soft locking
            closewindow = true;    
#endif
        }

        if(closewindow) {
            fullscreen = false;
            fullScreen(); // these two are called to exit fullscreen
            BorderlessWindowed();
            
            if(fadeoutWhenClose && !LetCloseWithoutFadeout) { // if fade out is enabled it fades out the window
                FadeWindowOut = true;
                FadeOut();
            } else { // other wise says yes window faded out letting the game close
                WindowFadedOut = true;
            }
        }

        if(closewindow && NoClosePreventing && (fadeoutWhenClose ? WindowFadedOut : true)) {
            return true;
        }
        
        return false; // if window wasn't ready for closing yet it returns false letting the game continue
    }

    void HotKeys() { // this is made because oneshot full screen thing, add your hotkeys here
        if(!started) {
            OrignalDisplayWidth = GetScreenWidth();
            OrignalDisplayHeight = GetScreenHeight();
        }
        started = true;

        if(fullscreenOnBeing) { // if fullscreen on beginning of the game
            (borderlessFullscreen ? BorderlessWindowed() : fullScreen()); // checks if fullscreen mode is borderless if it was it calls borderless fullscreen otherwise fullscreen
        }

        if(IsKeyPressed(Keybinds.FullScreenHotKey)) { // same as up but this time it's on a press of fullscreen hotkey
            (borderlessFullscreen ? BorderlessWindowed() : fullScreen());

            fullscreen = !fullscreen;
        }
    }
};

#endif
