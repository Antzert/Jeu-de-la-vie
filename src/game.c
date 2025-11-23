#include "../include/game.h"
#include "../include/GameWindow.h"
#include <stdlib.h>
#include <threads.h>
#if defined(_WIN32)
    #include <windows.h>
#elif defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__)
    #include <sys/types.h>
    #include <sys/sysctl.h>
#elif defined(__linux__)
    #include <unistd.h>
#endif


typedef struct Game
{
    GameWindow* gameWindow;
    int height;
    int width;
    int caseSize;
    int thread_number;
    thrd_t* threads;
    mtx_t mutex;
    int current_line;
    bool *map;
    bool *tempMap;
} Game ;

Game* ConstructGame(int width, int height, int caseSize, GameWindow* gameWindow)
{
    Game* game = calloc(1, sizeof(Game));
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

    //Calcul du nombre de thread
    #if defined(_WIN32)
        SYSTEM_INFO sysinfo;
        GetSystemInfo(&sysinfo);
        game->thread_number = (int)sysinfo.dwNumberOfProcessors;
    #elif defined(__APPLE__) // macOS (utilisation de sysctl)
        int nprocs;
        size_t len = sizeof(nprocs);
        if (sysctlbyname("hw.ncpu", &nprocs, &len, NULL, 0) == 0) {
            game->thread_number = nprocs;
        } else {
            game->thread_number = 1;
        }
    #elif defined(__linux__) // Linux et autres systèmes POSIX (avec correction)
        long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
        if (nprocs < 1) {
            game->thread_number = 1;
        } else {
            game->thread_number = (int)nprocs;
        }
    #else
        game->thread_number = 1;
    #endif
    if(game->thread_number < 1)
        game->thread_number = 1;

    printf("%d\n", game->thread_number);


    //Création du mutex
    mtx_init(&game->mutex, mtx_plain);

    //Création des threads
    game->threads = (thrd_t*)malloc(sizeof(thrd_t) * game->thread_number);
    if(game->threads == NULL)
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
    if(game->threads != NULL)
        free(game->threads);
    mtx_destroy(&game->mutex);
    free(game);
}



static int updateLine(void* arg)
{
    Game* game = (Game*)arg;

    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};


    while(true)
    {
        int i = 0;
        mtx_lock(&game->mutex);
        i = game->current_line;
        ++game->current_line;
        mtx_unlock(&game->mutex);
        if(i >= game->height)
        {
            break;
        }


        // Calcul
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

    thrd_exit(thrd_success);
}

void UpdateGame(Game* game)
{
    //Copy du tableau
    memcpy(game->tempMap, game->map, game->width * game->height * sizeof(bool));
    game->current_line = 0;

    for(int i = 0 ; i < game->thread_number ; ++i)
    {
        thrd_create(&game->threads[i], updateLine, game);
    } 

    for(int i = 0 ; i < game->thread_number ; ++i)
        thrd_join(game->threads[i], NULL);
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