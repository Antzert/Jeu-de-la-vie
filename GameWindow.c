#include "GameWindow.h"
#include "game.h"
#include <stdlib.h>
#include <math.h>

typedef struct GameWindow
{
    bool grid;
    bool launch;
    bool paused;
    int width;
    int height;
    int caseSize;
    int delay;
    int generation;
    int widthNumberOfCase;
    int heightNumberOfCase;
    SDL_Rect texteRect;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* police;
    SDL_Color redColor;
    Game* game;
    SDL_Texture* texteTexture;
} GameWindow ;
GameWindow* ConstructGameWindow(int width, int height, int caseSize, bool fullscreen)
{
    //initialisation des variables
    GameWindow* gameWindow = malloc(sizeof(GameWindow));
    if(gameWindow == NULL)
        ExitGameWithError(gameWindow, "Creation structure gameWindow");
    gameWindow->grid = true;
    gameWindow->launch = true;
    gameWindow->paused = true;
    gameWindow->width = width;
    gameWindow->height = height;
    gameWindow->caseSize = caseSize;
    gameWindow->delay = 400;
    gameWindow->generation = 0;
    //calcul du nombre de case max  
    gameWindow->widthNumberOfCase = ceil(gameWindow->width / gameWindow->caseSize);
    gameWindow->heightNumberOfCase = ceil(gameWindow->height / gameWindow->caseSize);
    gameWindow->texteRect.x = 0;
    gameWindow->texteRect.y = 0;
    gameWindow->texteRect.w = 0;
    gameWindow->texteRect.h = 0;
    //initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        ExitGameWithError(gameWindow, "Initialisation SDL");
    if(TTF_Init() != 0)
        ExitGameWithError(gameWindow, "Initialisation SDL_TTF");
    //creation de la fenetre
    SDL_WindowFlags windowFlags = fullscreen?SDL_WINDOW_FULLSCREEN:SDL_WINDOW_SHOWN;
    gameWindow->window = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameWindow->width, gameWindow->height, windowFlags);
    if(gameWindow->window == NULL)
        ExitGameWithError(gameWindow, "Creation fenetre");
    SDL_Surface* iconeSurface = SDL_LoadBMP("icone.bmp");
    if(iconeSurface == NULL)
        ExitGameWithError(gameWindow, "Creation icone");
    SDL_SetWindowIcon(gameWindow->window, iconeSurface);
    SDL_FreeSurface(iconeSurface);
    //creation du rendu
    gameWindow->renderer = SDL_CreateRenderer(gameWindow->window, -1, SDL_RENDERER_ACCELERATED);
    if(gameWindow->renderer == NULL)
        ExitGameWithError(gameWindow, "Creation rendu");
    //Creation de la police
    gameWindow->police = TTF_OpenFont("Ubuntu.ttf" , 50);
    if(gameWindow->police == NULL)
        ExitGameWithError(gameWindow, "Creation police");
    gameWindow->redColor.r = 255;
    gameWindow->redColor.g = 0;
    gameWindow->redColor.b = 0;
    //creation de la classe Game
    gameWindow->game = ConstructGame(gameWindow->widthNumberOfCase, gameWindow->heightNumberOfCase, gameWindow->caseSize, gameWindow);
    if(gameWindow->game == NULL)
        ExitGameWithError(gameWindow, "Allocation dynamique pour creer la structure Game");
    gameWindow->texteTexture = NULL;
    return gameWindow;
}
void DestructGameWindow(GameWindow* gameWindow)
{
    SDL_Log("liberation memoire");
    DestructGame(gameWindow->game);    
    SDL_DestroyTexture(gameWindow->texteTexture);
    TTF_CloseFont(gameWindow->police);
    SDL_DestroyRenderer(gameWindow->renderer);
    SDL_DestroyWindow(gameWindow->window);
    TTF_Quit();
    SDL_Quit();
    free(gameWindow);
}
void ExitGameWithError(GameWindow* gameWindow, char* message)
{
    SDL_LogError(0,"%s" ,message);
    DestructGameWindow(gameWindow);
    exit(EXIT_FAILURE);
}
void ChangeTexte(GameWindow* gameWindow)
{
    char texte[8];
    sprintf(texte, " %d", gameWindow->generation);
    SDL_Surface* SurfaceTexte = TTF_RenderText_Blended(gameWindow->police, texte , gameWindow->redColor);
    if(SurfaceTexte == NULL)
        ExitGameWithError(gameWindow, "Creation surface texte");
    gameWindow->texteTexture = SDL_CreateTextureFromSurface(gameWindow->renderer,SurfaceTexte);
    SDL_FreeSurface(SurfaceTexte);
    if(gameWindow->texteTexture == NULL)
        ExitGameWithError(gameWindow, "creation Texture du texte");
    if(SDL_QueryTexture(gameWindow->texteTexture, NULL, NULL, &gameWindow->texteRect.w, &gameWindow->texteRect.h) != 0)
        ExitGameWithError(gameWindow, "recuperation taille texte");     
}
void QuitProgramme(GameWindow* gameWindow)
{
    gameWindow->launch = false;
}
void UpdateGameWindow(GameWindow* gameWindow)
{
    //reinitialiser le font
    if(SDL_SetRenderDrawColor(gameWindow->renderer, 255, 255, 255, 255) != 0)
        ExitGameWithError(gameWindow, "changement de la couleur pour le font");
    if(SDL_RenderClear(gameWindow->renderer) != 0)
        ExitGameWithError(gameWindow, "clear le font");
    //update si le jeu n'est pas en pause
    if(!gameWindow->paused)
    {
        UpdateGame(gameWindow->game);
        ++gameWindow->generation;
    }
    //affichage des case noire
    PrintMapGame(gameWindow->game, gameWindow->renderer);
    ChangeTexte(gameWindow);
    SDL_RenderCopy(gameWindow->renderer, gameWindow->texteTexture, NULL, &gameWindow->texteRect);
    SDL_RenderPresent(gameWindow->renderer);
    if(!gameWindow->paused)
        SDL_Delay(gameWindow->delay);
}
void ChangeGameWindowPaused(GameWindow* gameWindow)
{
    if(gameWindow->paused)
        gameWindow->paused = false;
    else
        gameWindow->paused = true;
}
void ChangeGameWindowSpeed(GameWindow* gameWindow, int newVitesse)
{
    gameWindow->delay = newVitesse;
}
void NextGameWindow(GameWindow* gameWindow)
{
    if(!gameWindow->paused)
        return;
    UpdateGame(gameWindow->game);
    ++gameWindow->generation;
}
void ResetGameWindow(GameWindow* gameWindow)
{
    gameWindow->generation = 0;
    ResetMapGame(gameWindow->game);
}
void RandomGameWindow(GameWindow* gameWindow)
{
    gameWindow->generation = 0;
    RandomMapGame(gameWindow->game);
}
void GetClickCaseGameWindow(GameWindow* gameWindow, SDL_Event* event, bool leftClick)
{
    SetMapCaseGame(gameWindow->game , event->motion.x / gameWindow->caseSize, event->motion.y / gameWindow->caseSize , leftClick);
}
void changeGrid(GameWindow* gameWindow)
{
    if(gameWindow->grid)
        gameWindow->grid = false;
    else
        gameWindow->grid = true;
}
void resetNumberOfGeneration(GameWindow* gameWindow)
{
    gameWindow->generation = 0;
}
bool getGrid(GameWindow* gameWindow)
{
    return gameWindow->grid;
}
bool GetLaunch(GameWindow* gameWindow)
{
    return gameWindow->launch;
}