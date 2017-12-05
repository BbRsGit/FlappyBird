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

int tower_poz[3]={288,288,288};
int tower_h[3]={288,288,288};
int is_tower_behind=0;

int tower_update(int delta)
    {
    static int state=STT_FLYING;
    int i;
    switch(state_get())
        {
        case STT_FLAPING:
            if(state!=STT_FLAPING)
                {
                state=STT_FLAPING;
                for(i=0;i<3;i++)
                    {
                    tower_poz[i]=288+144*i;
                    tower_h[i]=-260+rand()%200;
                    is_tower_behind=0;
                    }
                }
            for(i=0;i<3;i++)
                {
                int temp=((float)delta/10)*GAME_SPEED;
                tower_poz[i]-=temp;
                if(tower_poz[i]<0 && is_tower_behind==0)
                    {
                    set_score(get_score()+1);
                    is_tower_behind=1;
                    }
                if(tower_poz[i]<=-52)
                    {
                    if(i==0)
                        tower_poz[i]=tower_poz[2]+144;
                    else
                        tower_poz[i]=tower_poz[i-1]+144;
                    is_tower_behind=0;
                    tower_h[i]=-260+rand()%200;
                    }
                }
        break;
        case STT_FLYING:
            state=state_get();
            for(i=0;i<3;i++)
                tower_poz[i]=299;
        break;
        default:
            state=state_get();
        break;
        }
    return 0;
    }

static int twr_draw(int x,int y)
    {
    SDL_Renderer *ren=get_res_renderer();
    if(x<0)
        {
        SDL_Rect rect={0,y,26*2+x,160*2};
        SDL_Rect src={-x/2,0,26+x/2,160};
        SDL_RenderCopy(ren,get_res_texture(PIPE_UP),&src,&rect);
        rect.y+=160*2+110;
        SDL_RenderCopy(ren,get_res_texture(PIPE_DOWN),&src,&rect);
        }
    else{
        SDL_Rect rect={x,y,26*2,160*2};
        SDL_RenderCopy(ren,get_res_texture(PIPE_UP),NULL,&rect);
        rect.y+=160*2+110;
        SDL_RenderCopy(ren,get_res_texture(PIPE_DOWN),NULL,&rect);
        }
    return 0;
    }

int tower_draw(int delta)
    {
    int i=0;
    if(state_get()!=STT_FLYING)
        for(i=0;i<3;i++)
            {
            if(tower_poz[i]<288)
                twr_draw(tower_poz[i],tower_h[i]);
            }
    return 0;
    }

int tower_collision(SDL_Rect *r)
    {
    int i;
    SDL_Rect flap=*r;
    flap.w-=5;
    SDL_Rect rect={0,0,48,318};
    for(i=0;i<3;i++)
        {
        if(tower_poz[i]<80)
            {
            rect.y=tower_h[i];
            rect.x=tower_poz[i]+2;
            if(SDL_HasIntersection(&flap,&rect))
                return 1;
            rect.y+=320+112;
            if(SDL_HasIntersection(&flap,&rect))
                return 1;

            }
        }
    return 0;
    }
