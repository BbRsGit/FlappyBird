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

void draw_floor(int delta)
    {
    static int floor_poz=0;
    SDL_Renderer *ren=get_res_renderer();
    SDL_Texture *floor=get_res_texture(FLOOR);
    SDL_Rect draw_rect={0,512-56*2,168*2,56*2};
    SDL_Rect source_rect=draw_rect;
    switch(state_get())
        {
        case STT_FLYING:
        case STT_FLAPING:
            floor_poz+=((float)delta/10)*GAME_SPEED;
            if(floor_poz>168*2)
                floor_poz%=168*2;
        break;
        }
    source_rect.y=0;
    source_rect.h=56;
    source_rect.w=168;

    draw_rect.w-=floor_poz;
    source_rect.x+=floor_poz/2;
    SDL_RenderCopy(ren,floor,&source_rect,&draw_rect);
    source_rect.x=0;
    draw_rect.x=168*2-floor_poz;
    draw_rect.w=168*2;
    SDL_RenderCopy(ren,floor,&source_rect,&draw_rect);
    }

void draw_background(int delta)
    {
    SDL_Renderer *ren=get_res_renderer();
    SDL_Rect rect={144-57,256-49,114,98};
    SDL_Rect rect2={144-89,50,89*2,24*2};
    SDL_RenderCopy(ren,get_res_texture(BACKGROUND),NULL,NULL);
    switch(state_get())
        {
        case STT_FLYING:
            SDL_RenderCopy(ren,get_res_texture(LABEL),NULL,&rect2);
            SDL_RenderCopy(ren,get_res_texture(INSTRUCTIONS),NULL,&rect);
        break;
        }
    }

void draw_all(int delta)
    {
    draw_background(delta);
    tower_draw(delta);
    flappy_draw(delta);
    draw_floor(delta);
    draw_score();
    draw_score_panel();
    }
