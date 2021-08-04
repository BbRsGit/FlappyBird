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

#define TOWERS_NUM 3

Flappy flappy;
Tower towers[TOWERS_NUM];


static void main_game_init();

int main(int argc,char **argv)
    {
    main_game_init();
	tower_init(towers,TOWERS_NUM);
    int ticks=SDL_GetTicks();
    int last_ticks=0;
	int pressed;
    while(1)
        {
        pressed=input_handle();
        tower_update(towers,TOWERS_NUM);
        flappy_update(&flappy,pressed & 1); /*jump is active if 0b01 or 0b11 are pressed -> ergo pressed & 1*/
        flappy_collision(&flappy,towers,TOWERS_NUM);
		background_update();
		draw_all(&flappy,towers,TOWERS_NUM,16);
        get_res_render_draw();
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

static void main_game_init()
    {
    if(game_init())
        {
        printf("Error: Couldn't initialize SDL or SDL_image\n");
        exit(1);
        }
    if(game_screen_init())
        {
        printf("Error: Can't create a window or the renderer");
        exit(1);
        }
    if(load_res_textures())
        {
        printf("Error: Couldn't load resources\n");
        printf("Find the file \"res/\" and place it next to the application\n");
        exit(1);
        }
    get_highscore();

    state_set(STT_FLYING);
   
   	flappy_reset(&flappy); 
	}
