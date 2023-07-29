#include "GameWindow.h"
#include <SDL2/SDL.h>
#include <time.h>
#include <string.h>

int main(int argc, char** argv)
{
    char leftClick = 0;
    char rightsClick = 0;
    SDL_Event eventMouse;
    //Aleatoire
    srand(time(NULL));

    //Creation de la structure du jeu
    GameWindow* gameWindow = NULL;
    if(argc == 5)
        gameWindow = ConstructGameWindow(strtol(argv[1],NULL, 10), strtol(argv[2],NULL, 10), strtol(argv[3],NULL, 10),  strtol(argv[4],NULL, 10));
    else
        gameWindow = ConstructGameWindow(1920, 1080,10, true);

    //Boucle du jeu
    while(GetLaunch(gameWindow))
    {
        //Gestion des événements
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
                        case SDLK_KP_ENTER:
                        case SDLK_RETURN:
                            changeGrid(gameWindow);
                            continue;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT)
                        leftClick = 1;
                    else if(event.button.button == SDL_BUTTON_RIGHT)
                        rightsClick = 1;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(event.button.button == SDL_BUTTON_LEFT)
                        leftClick = 0;
                    else if(event.button.button == SDL_BUTTON_RIGHT)
                        rightsClick = 0;
                    break;
                case SDL_MOUSEMOTION:
                    eventMouse = event;
                    break;
                case SDL_QUIT:
                    QuitProgramme(gameWindow);
                    break;
            }
        if(leftClick && !rightsClick)
            GetClickCaseGameWindow(gameWindow, &eventMouse,true);
        if(rightsClick && !leftClick)
            GetClickCaseGameWindow(gameWindow, &eventMouse,false);
        //Appelle de la methode update
        UpdateGameWindow(gameWindow);
    }
    //Femeture du programme
    DestructGameWindow(gameWindow);
    return EXIT_SUCCESS;
}