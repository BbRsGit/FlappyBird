#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "setup.h"
#include "res_manager.h"
#include "flappy.h"
#include "state_manager.h"
#include "input.h"
#include "draw.h"

#define DELAY 16

void ggame_init();

int main(int argc,char **argv)
    {
    ggame_init();
    state_set(STT_FLYING);
    flappy_reset();
    int i;
    struct press press;
    while(1)
        {
        SDL_RenderClear(get_res_renderer());
        input_handle(&press);
        tower_update(DELAY);
        flappy_update(&press,DELAY);
        draw_all(DELAY);
        SDL_RenderPresent(get_res_renderer());
        SDL_Delay(16);
        }
    game_quit();
    return 0;
    }

void ggame_init()
    {
    if(game_init())
        {
        printf("Error: Couldn't initialize SDL or IMG\n");
        game_quit();
        }
    if(game_screen_init())
        {
        printf("Error: Can't create a window or the renderer");
        game_quit();
        }
    if(load_res_textures())
        {
        printf("Error: Couldn't load resources\n");
        printf("Find the file \"res/\" and place it next to the application\n");
        game_quit();
        }
    get_highscore();
    }
