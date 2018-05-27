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

#define TOWER_H (160*2)
#define TOWER_W (26*2)

static void tower_set_poz(Tower *towers,int num);

static void tower_flapping(Tower *towers,int num,int reset);

void tower_init(Tower *towers,int num)
	{
	int i;
	for(i=0;i<num;i++)
		{
		towers[i].upper.w=towers[i].bottom.w=TOWER_W;
		towers[i].upper.h=towers[i].bottom.h=TOWER_H;
		}
	}

int tower_update(Tower *towers,int num)
    {
    int i;
    switch(state_get())
        {
        case STT_FLAPING:
			tower_flapping(towers,num,0);
		break;
        case STT_FLYING:
            for(i=0;i<num;i++)
                towers[i].upper.x=towers[i].bottom.x=299;
			tower_flapping(towers,num,1);
        break;
        }
    return 0;
    }

int tower_draw(Tower *towers,int num)
    {
    int i=0;
    if(state_get()!=STT_FLYING)
        for(i=0;i<num;i++)
            {
            if(towers[i].upper.x<288)
				{
				get_res_render(PIPE_UP+state_day(),NULL,&towers[i].upper);
				get_res_render(PIPE_DOWN+state_day(),NULL,&towers[i].bottom);
				}
            }
    return 0;
    }

int tower_collided(Tower *tower,SDL_Rect *rect)
	{
	if(tower->upper.x>80)
		return 0;

	SDL_Rect tower_collision=tower->upper;
	tower_collision.x+=2; tower_collision.w-=4;
	if(SDL_HasIntersection(rect,&tower_collision))
		return 1;
	tower_collision=tower->bottom;
	tower_collision.x+=2; tower_collision.w-=4;
	if(SDL_HasIntersection(rect,&tower_collision))
		return 1;

	return 0;
	}


static void tower_set_poz(Tower *towers,int num)
	{
	int i;
    for(i=0;i<num;i++)
     	{
        towers[i].upper.x=288+144*i;
        towers[i].upper.y=-260+rand()%200;
		towers[i].bottom.x=288+144*i;
		towers[i].bottom.y=towers[i].upper.y+TOWER_H+110;
        }
	}

static void tower_flapping(Tower *towers,int num,int reset)
	{
	int i;
	static int is_tower_behind=0;
	if(reset)
		{
        tower_set_poz(towers,num);	
        is_tower_behind=0;
		return;
		}
	for(i=0;i<num;i++)
    	{
        const int temp=(1.6)*GAME_SPEED;
        towers[i].bottom.x=towers[i].upper.x-=temp;
        if(towers[i].upper.x<0 && is_tower_behind==0)
        	{
            update_score();
            is_tower_behind=1;
            }
        if(towers[i].upper.x<=-52)
        	{
            towers[i].upper.x=towers[(i+num-1)%num].upper.x+144;

            is_tower_behind=0;
                    
			towers[i].upper.y=-260+rand()%200;
			towers[i].bottom.y=towers[i].upper.y+TOWER_H+110;                    
            }
    	}
	}


