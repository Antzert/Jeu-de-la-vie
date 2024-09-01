#include "../include/game.h"
#include "../include/GameWindow.h"
#include <stdlib.h>

typedef struct Game
{
    GameWindow* gameWindow;
    int height;
    int width;
    int caseSize;
    bool **map;
    bool **tempMap;
} Game ;

Game* ConstructGame(int width, int height, int caseSize, GameWindow* gameWindow)
{
    Game* game = malloc(sizeof(Game));
    if(game == NULL)
        return NULL;
    game->gameWindow = gameWindow;
    game->width = width;
    game->height = height;
    game->caseSize = caseSize;

    //creation des maps
    game->map = (bool**)malloc(sizeof(bool*) * height);
    game->tempMap = (bool**)malloc(sizeof(bool*) * height);
    if(game->map == NULL || game->tempMap == NULL)
        return NULL;

    for(int i = 0 ; i < game->height ; ++i)
    {
        game->map[i] = (bool*)malloc(sizeof(bool)* game->width);
        game->tempMap[i] = (bool*)malloc(sizeof(bool)* game->width);
        if(game->map[i] == NULL || game->tempMap[i] == NULL)
            return NULL;
    }
    //Mettre toutes les cases de la map en blanc
    ResetMapGame(game);
    return game;
}

void DestructGame(Game* game)
{
    if(game == NULL)
        return;
    for(int i = 0 ; i < game->height ; ++i)
    {
        if(game->map[i] != NULL)
            free(game->map[i]);
        if(game->tempMap[i] != NULL)
            free(game->tempMap[i]);
    }
    if(game->map != NULL)
        free(game->map);
    if(game->tempMap != NULL)
        free(game->tempMap);
    if(game != NULL)
        free(game);
}

void UpdateGame(Game* game)
{
    //Copy du tableau
    for(int i = 0 ; i < game->height ; ++i)
        for(int j = 0 ; j < game->width ; ++j)
            game->tempMap[i][j] = game->map[i][j];

    //Boucle de verification
    for(int i = 0 ; i < game->height ; ++i)
    {
        for(int j = 0 ; j < game->width ; ++j)
        {
            int numberOfNeighbord = 0;
            //Verification si la case en haut a gauche existe
            if(i != 0 && j != 0)
                if(game->tempMap[i - 1][j - 1])
                    ++numberOfNeighbord;
            //verification si la case en haut au milieu existe
            if(i != 0)
                if(game->tempMap[i - 1][j])
                    ++numberOfNeighbord;
            //verification si la case en haut a droite existe
            if(i != 0 && j != game->width -1)
                if(game->tempMap[i - 1][j + 1])
                    ++numberOfNeighbord;
            //verification si la case au mileu a droite existe
            if(j != game->width -1)
                if(game->tempMap[i][j + 1])
                    ++numberOfNeighbord;
            //verification si la case en bas a droite existe
            if(i != game->height - 1 && j != game->width -1 )
                if(game->tempMap[i + 1][j + 1])
                    ++numberOfNeighbord;
            //verification si la case en bas au milieu existe
            if(i != game->height - 1)
                if(game->tempMap[i + 1][j])
                    ++numberOfNeighbord;
            //verification si la case en bas a gauche existe
            if(j!= 0 && i != game->height - 1)
                if(game->tempMap[i + 1][j - 1])
                    ++numberOfNeighbord;
            //verification si la case au milieu a gauche existe
            if(j!= 0)
                if(game->tempMap[i][j - 1])
                    ++numberOfNeighbord;
            //si le nombre de voisin n'est pas 2 ou 3 alors on le suprime
            if(numberOfNeighbord != 2 && numberOfNeighbord != 3)
                game->map[i][j] = false;
            //si le nombre de voisin est 3 alors on créé une case
            if(numberOfNeighbord == 3)
                game->map[i][j] = true;
        }
    }
}

void PrintMapGame(Game* game, SDL_Renderer* renderer)
{
    //Affichage des cases noires
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for(int i = 0 ; i < game->height ; ++i)
    {
        for(int j = 0 ; j < game->width ; ++j)
        {
            SDL_Rect rect = {j* game->caseSize,i*game->caseSize, game->caseSize, game->caseSize};
            if(game->map[i][j])
                SDL_RenderFillRect(renderer, &rect);
        }
    }
    //Creation de la grille
    if(getGrid(game->gameWindow))
    {
        SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);
        for(int i = 0 ; i < game->width ; ++i)
            SDL_RenderDrawLine(renderer, i * game->caseSize, 0, i * game->caseSize, game->height*game->caseSize);
        for(int i = 0 ; i < game->height ; ++i)
            SDL_RenderDrawLine(renderer,0,  i * game->caseSize,game->width*game->caseSize ,i * game->caseSize);
    }
}
void RandomMapGame(Game* game)
{
    //Faire un map random
    for(int i = 0 ; i < game->height ; ++i)
        for(int j = 0 ; j < game->width ; ++j)
        {
            if(rand() % 2 == 1)
                game->map[i][j] = true;
            else
                game->map[i][j] = false;
        }
}
void ResetMapGame(Game* game)
{
    //Mettre toute la map a false
    for(int i = 0 ; i < game->height ; ++i)
        for(int j = 0 ; j < game->width ; ++j)
            game->map[i][j] = false;
}
void SetMapCaseGame(Game* game, int width, int height, bool leftClick)
{
    game->map[height][width] = leftClick;
}