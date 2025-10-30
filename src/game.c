#include "../include/game.h"
#include "../include/GameWindow.h"
#include <stdlib.h>

typedef struct Game
{
    GameWindow* gameWindow;
    int height;
    int width;
    int caseSize;
    bool *map;
    bool *tempMap;
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
    game->map = (bool*)malloc(sizeof(bool) * height * width);
    game->tempMap = (bool*)malloc(sizeof(bool) * height * width);
    if(game->map == NULL || game->tempMap == NULL)
        return NULL;

    //Mettre toutes les cases de la map en blanc
    ResetMapGame(game);

    return game;
}

void DestructGame(Game* game)
{
    if(game == NULL)
        return;
    if(game->map != NULL)
        free(game->map);
    if(game->tempMap != NULL)
        free(game->tempMap);
    free(game);
}

void UpdateGame(Game* game)
{
    //Copy du tableau
    memcpy(game->tempMap, game->map, game->width * game->height * sizeof(bool));

    //Boucle de verification
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for(int i = 0; i < game->height; ++i)
    {
        for(int j = 0; j < game->width; ++j)
        {
            int numberOfNeighbord = 0;

            for(int k = 0; k < 8; ++k)
            {
                int ni = i + dy[k];
                int nj = j + dx[k];
                if(ni >= 0 && ni < game->height && nj >= 0 && nj < game->width)
                    if(game->tempMap[ni * game->width + nj])
                        ++numberOfNeighbord;
            }

            game->map[i * game->width + j] = (numberOfNeighbord == 3 || (numberOfNeighbord == 2 && game->tempMap[i * game->width + j]));
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
            if(game->map[i * game->width + j])
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
    for(int i = 0 ; i < game->height * game->width; ++i)
        game->map[i] = rand() % 2;
}
void ResetMapGame(Game* game)
{
    for(int i = 0 ; i < game->height * game->width; ++i)
        game->map[i] = false;
}
void SetMapCaseGame(Game* game, int width, int height, bool leftClick)
{
    game->map[height * game->width + width] = leftClick;
}