#ifndef __GAME__WINDOW__H__
    #define __GAME__WINDOW__H__
    #include "game.h"
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
    typedef struct GameWindow GameWindow;
    GameWindow* ConstructGameWindow(int width, int height, int caseSize, bool fullscreen);
    void DestructGameWindow(GameWindow* gameWindow);
    void ExitGameWithError(GameWindow* gameWindow, char* message);
    void ChangeTexte(GameWindow* gameWindow);
    void QuitProgramme(GameWindow* gameWindow);
    void UpdateGameWindow(GameWindow* gameWindow);
    void ChangeGameWindowPaused(GameWindow* gameWindow);
    void ChangeGameWindowSpeed(GameWindow* gameWindow, int newVitesse);
    void NextGameWindow(GameWindow* gameWindow);
    void ResetGameWindow(GameWindow* gameWindow);
    void RandomGameWindow(GameWindow* gameWindow);
    void GetClickCaseGameWindow(GameWindow* gameWindow, SDL_Event* event, bool leftClick);
    void changeGrid(GameWindow* gameWindow);
    void resetNumberOfGeneration(GameWindow* gameWindow);
    //getter
    bool getGrid(GameWindow* gameWindow);
    bool GetLaunch(GameWindow* gameWindow);

#endif