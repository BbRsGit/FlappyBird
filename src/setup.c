#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>

#include "res_manager.h"
#include "setup.h"

int game_init()
    {
    srand(time(NULL));
    if(SDL_Init(SDL_INIT_EVERYTHING))
        return -1;
    if(!IMG_Init(IMG_INIT_PNG))
        return -1;
    return 0;
    }

int game_screen_init()
    {
    if(res_create_window()) return -1;
    if(res_create_renderer()) return -1;
    return 0;
    }

int game_quit()
    {
    save_highscore();
    SDL_Quit();
    IMG_Quit();
    exit(0);
    return 0;
    }
