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
#include "score.h"
#include "towers.h"

void ggame_init();

int main(int argc,char **argv)
    {
    ggame_init();
    state_set(STT_FLYING);
    flappy_reset();
    int ticks=SDL_GetTicks();
    int last_ticks=0;
    struct press press;
    while(1)
        {
        SDL_RenderClear(get_res_renderer());
        input_handle(&press);
        tower_update(16);
        flappy_update(&press,16);
        draw_all(16);
        SDL_RenderPresent(get_res_renderer());
        last_ticks=ticks;
        ticks=SDL_GetTicks();
        if(ticks-last_ticks>=16)
            SDL_Delay(1);
        else
            SDL_Delay(16-(ticks-last_ticks));
        ticks=SDL_GetTicks();
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
