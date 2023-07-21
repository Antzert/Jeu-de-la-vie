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
    //Allocation de la structure GameWindow
    GameWindow* gameWindow = malloc(sizeof(GameWindow));
    if(gameWindow == NULL)
        ExitGameWithError(gameWindow, "Creation structure gameWindow");
    
    //Initialisation des variables
    gameWindow->grid = true;
    gameWindow->launch = true;
    gameWindow->paused = true;
    gameWindow->width = width;
    gameWindow->height = height;
    gameWindow->caseSize = caseSize;
    gameWindow->delay = 400;
    gameWindow->generation = 0;
    gameWindow->texteTexture = NULL;

    //Calcul du nombre de case max
    gameWindow->widthNumberOfCase = ceil(gameWindow->width / gameWindow->caseSize);
    gameWindow->heightNumberOfCase = ceil(gameWindow->height / gameWindow->caseSize);
    gameWindow->texteRect  = (SDL_Rect){0, 0, 0, 0};

    //Initialisation de la SDL
    if(0 != SDL_Init(SDL_INIT_VIDEO))
        ExitGameWithError(gameWindow, "Initialisation SDL");
    if(0 != TTF_Init())
        ExitGameWithError(gameWindow, "Initialisation SDL_TTF");

    //Creation de la fenetre et du rendu
    if(0!= SDL_CreateWindowAndRenderer(gameWindow->width, gameWindow->height, fullscreen?SDL_WINDOW_FULLSCREEN:SDL_WINDOW_SHOWN, &gameWindow->window, &gameWindow->renderer))
        ExitGameWithError(gameWindow, "Creation fenetre et rendu");

    //Creation de l'icone
    SDL_Surface* iconeSurface = SDL_LoadBMP("icone.bmp");
    if(iconeSurface == NULL)
        ExitGameWithError(gameWindow, "Creation icone");
    SDL_SetWindowIcon(gameWindow->window, iconeSurface);
    SDL_FreeSurface(iconeSurface);

    //Creation de la police
    gameWindow->police = TTF_OpenFont("Ubuntu.ttf" , 50);
    if(gameWindow->police == NULL)
        ExitGameWithError(gameWindow, "Creation police");
    gameWindow->redColor = (SDL_Color){255, 0, 0, SDL_ALPHA_OPAQUE};

    //creation de la structure Game
    gameWindow->game = ConstructGame(gameWindow->widthNumberOfCase, gameWindow->heightNumberOfCase, gameWindow->caseSize, gameWindow);
    if(gameWindow->game == NULL)
        ExitGameWithError(gameWindow, "Allocation dynamique pour creer la structure Game");
    return gameWindow;
}
void DestructGameWindow(GameWindow* gameWindow)
{
    SDL_Log("liberation memoire");
    if(gameWindow == NULL)
        return;
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
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", message);
    DestructGameWindow(gameWindow);
    exit(EXIT_FAILURE);
}
void ChangeTexte(GameWindow* gameWindow)
{
    char texte[8] = "";
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
    //Reinitialiser le font
    if(SDL_SetRenderDrawColor(gameWindow->renderer, 255, 255, 255, 255) != 0)
        ExitGameWithError(gameWindow, "changement de la couleur pour le font");
    if(SDL_RenderClear(gameWindow->renderer) != 0)
        ExitGameWithError(gameWindow, "clear le font");

    //Update si le jeu n'est pas en pause
    if(!gameWindow->paused)
    {
        UpdateGame(gameWindow->game);
        ++gameWindow->generation;
    }
    
    //Affichage des cases noires
    PrintMapGame(gameWindow->game, gameWindow->renderer);
    ChangeTexte(gameWindow);
    SDL_RenderCopy(gameWindow->renderer, gameWindow->texteTexture, NULL, &gameWindow->texteRect);
    SDL_RenderPresent(gameWindow->renderer);
    if(!gameWindow->paused)
        SDL_Delay(gameWindow->delay);
}
void ChangeGameWindowPaused(GameWindow* gameWindow)
{
    gameWindow->paused = gameWindow->paused?false:true;
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
    gameWindow->grid = gameWindow->grid?false:true;
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