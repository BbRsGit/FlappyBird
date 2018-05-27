#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "flappy.h"
#include "res_manager.h"
#include "state_manager.h"
#include "input.h"
#include "draw.h"
#include "setup.h"
#include "towers.h"
#include "score.h"

#define FLOOR_W (168*2)
#define FLOOR_H	(112)
#define FLOOR_Y (512-FLOOR_H)

#define SCREEN_W 288
#define SCREEN_H 512

static int floor_poz=0;

void background_update()
	{
    switch(state_get())
        {
        case STT_FLYING:
        case STT_FLAPING:
            floor_poz+=(1.6)*GAME_SPEED;
            if(floor_poz>FLOOR_W)
                floor_poz%=FLOOR_W;
        break;
        }	
	}

void draw_floor()
    {
    SDL_Rect draw_rect={0,FLOOR_Y,FLOOR_W,FLOOR_H};

    draw_rect.x-=floor_poz;
    get_res_render(FLOOR,NULL,&draw_rect);
    draw_rect.x=FLOOR_W-floor_poz;
    get_res_render(FLOOR,NULL,&draw_rect);
    }

void draw_background(int delta)
    {
    SDL_Rect instructions_rect={SCREEN_W/2-57,SCREEN_H/2-49,114,98};
    SDL_Rect label_rect={SCREEN_W/2-89,50,89*2,24*2};
    get_res_render(BACKGROUND+state_day(),NULL,NULL);
    switch(state_get())
        {
        case STT_FLYING:
            get_res_render(LABEL,NULL,&label_rect);
            get_res_render(INSTRUCTIONS,NULL,&instructions_rect);
        break;
        }
    }

/*
void draw_pause_button()
	{
	SDL_Renderer *ren=get_res_renderer();
    SDL_Rect rect2={10,10,13*2,14*2};
    switch(state_get())
        {
        case STT_FLYING:
        case STT_OPTIONS:
        case STT_FLAPING:
            SDL_RenderCopy(ren,get_res_texture(BUTTON_PAUSE),NULL,&rect2);
        break;
   		}
	}
*/
void draw_all(Flappy *flappy,Tower *towers,int num,int delta)
    {
    draw_background(delta);
    tower_draw(towers,num);
    flappy_draw(flappy);
    draw_floor(delta);
    draw_score();
    draw_score_panel();
    //draw_pause_button();
    }
