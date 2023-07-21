#ifndef __GAME__H__
    #define __GAME__H__

    #include <SDL2/SDL.h>
    #include "bool.h"

    typedef struct GameWindow GameWindow;
    typedef struct Game Game;
    
    Game* ConstructGame(int width, int height, int caseSize, GameWindow* gameWindow);
    void DestructGame(Game* game);
    void UpdateGame(Game* game);
    void PrintMapGame(Game* game, SDL_Renderer* renderer);
    void RandomMapGame(Game* game);
    void ResetMapGame(Game* game);
    void SetMapCaseGame(Game* game, int width, int height, bool leftClick);
#endif