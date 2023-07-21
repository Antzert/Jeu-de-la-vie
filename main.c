#include "GameWindow.h"
#include <SDL2/SDL.h>
#include <time.h>
#include <string.h>

int main(int argc, char** argv)
{
    //reinitialiser l'aleatoire
    srand(time(NULL));
    //creation de la classe du jeu
    GameWindow* gameWindow = NULL;
    if(argc == 5)
        gameWindow = ConstructGameWindow(strtol(argv[1],NULL, 10), strtol(argv[2],NULL, 10), strtol(argv[3],NULL, 10),  strtol(argv[4],NULL, 10));
    else
        gameWindow = ConstructGameWindow(1920, 1080,10, true);
    //boucle du jeu
    while(GetLaunch(gameWindow))
    {
        //gestion des événements
        SDL_Event event;
        while(SDL_PollEvent(&event))
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_KP_0:
                            ChangeGameWindowSpeed(gameWindow, 400);
                            continue;
                        case SDLK_KP_1:
                            ChangeGameWindowSpeed(gameWindow, 200);
                            continue;
                        case SDLK_KP_2:
                            ChangeGameWindowSpeed(gameWindow, 100);
                            continue;
                        case SDLK_KP_3:
                            ChangeGameWindowSpeed(gameWindow, 80);
                            continue;
                        case SDLK_KP_4:
                            ChangeGameWindowSpeed(gameWindow, 40);
                            continue;
                        case SDLK_KP_5:
                            ChangeGameWindowSpeed(gameWindow, 20);
                            continue;
                        case SDLK_KP_6:
                            ChangeGameWindowSpeed(gameWindow, 10);
                            continue;
                        case SDLK_KP_7:
                            ChangeGameWindowSpeed(gameWindow, 5);
                            continue;
                        case SDLK_KP_8:
                            ChangeGameWindowSpeed(gameWindow, 1);
                            continue;
                        case SDLK_KP_9:
                            ChangeGameWindowSpeed(gameWindow, 0);
                            continue;
                        case SDLK_p:
                        case SDLK_SPACE:
                            ChangeGameWindowPaused(gameWindow);
                            continue;
                        case SDLK_RIGHT:
                            NextGameWindow(gameWindow);
                            continue;
                        case SDLK_r:
                            ResetGameWindow(gameWindow);
                            continue;
                        case SDLK_a:
                            RandomGameWindow(gameWindow);
                            continue;
                        case SDLK_g:
                            resetNumberOfGeneration(gameWindow);
                            continue;
                        case SDLK_RETURN:
                            changeGrid(gameWindow);
                            continue;
                        default:
                            continue;
                    }
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT)
                        GetClickCaseGameWindow(gameWindow, &event,true);
                    else if(event.button.button == SDL_BUTTON_RIGHT)
                        GetClickCaseGameWindow(gameWindow, &event,false);
                    continue;
                case SDL_QUIT:
                    QuitProgramme(gameWindow);
                    break;
                default:
                    break;

            }
        //appelle de la methode update
        UpdateGameWindow(gameWindow);
    }
    //femeture du programme
    DestructGameWindow(gameWindow);
    return EXIT_SUCCESS;
}