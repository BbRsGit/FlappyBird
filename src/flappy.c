#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "flappy.h"
#include "res_manager.h"
#include "state_manager.h"
#include "input.h"
#include "score.h"
#include "towers.h"

const float TICKS_DIF=1.6;
const float DIFF=TICKS_DIF/60;
const float GRAVITY=6.8*TICKS_DIF;
const int JUMP_SPEED=-180;
const float ROTATE_SPEED=0.7*TICKS_DIF;

#define FLAPPY_W 34
#define FLAPPY_H 24
#define SCREEN_W 288
#define SCREEN_H 512
#define FLOOR_H  (SCREEN_H-112)

#define FLAPPY_START_X 26
#define FLAPPY_START_Y (SCREEN_H/2-12)

/** Handles texture shown depending on flappy state in game */
static void draw_flying(Flappy *flappy);

/** Makes flappy jump */
static void flappy_jump(Flappy *flappy);

/** Applies graviti to flappy */
static void flappy_gravity(Flappy *flappy);

/** Actions flappy does depending on the game state */
static void flappy_flying(Flappy *flappy,int is_jump);

static void flappy_flapping(Flappy *flappy,int is_jump);

static void flappy_hit(Flappy *flappy);

static void flappy_ground(Flappy *flappy,int is_jump);

static void flappy_options(Flappy *flappy,int is_jump);

/**                END OF STATES                     */

void flappy_reset(Flappy *flappy)
    {
    flappy->collision.x=FLAPPY_START_X;
    flappy->collision.y=FLAPPY_START_Y;
    flappy->collision.w=FLAPPY_W;
    flappy->collision.h=FLAPPY_H;
    flappy->texture_id=get_flappy_textures_id();
    flappy->cur_texture=0;
    flappy->rotation=0;
    flappy->y_vel=0;
    }

void flappy_draw(Flappy *flappy)
    {
	get_res_render_ex(flappy->texture_id+flappy->cur_texture,&flappy->collision,flappy->rotation,0);
    }

void flappy_update(Flappy *flappy,int is_jump)
    {
	switch(state_get())
        {
        case STT_FLYING:
			flappy_flying(flappy,is_jump);
		break;
        case STT_FLAPING:
			flappy_flapping(flappy,is_jump);	
        break;
        case STT_HIT:
        	flappy_hit(flappy);
		break;
        case STT_GROUND:
        	flappy_ground(flappy,is_jump);
		break;
        case STT_OPTIONS:
      		flappy_options(flappy,is_jump);
	  	break;
        }
    }



static void draw_flying(Flappy *flappy)
	{
    if(flappy->rotation<-28)
		flappy->cur_texture=1;
	else if(flappy->rotation<-25)
		flappy->cur_texture=2;
	else if(flappy->rotation<-15)
		flappy->cur_texture=1;
	else
		flappy->cur_texture=0;
    flappy->rotation+=ROTATE_SPEED;
	}

static void flappy_jump(Flappy *flappy)
    {
    flappy->y_vel=JUMP_SPEED;
    flappy->rotation=-30;
    }

static void flappy_gravity(Flappy *flappy)
    {
    flappy->collision.y+=flappy->y_vel*DIFF;
    flappy->y_vel+=GRAVITY;
    }

static void flappy_flying(Flappy *flappy,int is_jump)
	{
	//auto jump
    if(flappy->collision.y>=FLAPPY_START_Y)
    	{
        flappy->collision.y=FLAPPY_START_Y;
        flappy_jump(flappy);
        }
	//changes state
    if(is_jump)
    	{
        state_set(STT_FLAPING);
        flappy_jump(flappy);
        reset_score();
        }
    flappy_gravity(flappy);
	draw_flying(flappy);
	}

static void flappy_flapping(Flappy *flappy,int is_jump)
	{
	/* THIS SHOULD OPEN A MENU TODO
	 if(is_jump)
	    {
	  	SDL_GetMouseState(&x,&y);
		if(x>10 && x<36 && y>10 && y<38)
			{
			state_set(STT_OPTIONS);
			}
		}
	*/ 
	if(is_jump)
    	{
        flappy_jump(flappy);
        }
    if(flappy->collision.h+flappy->collision.y>=FLOOR_H)
        {
		flappy->collision.y=FLOOR_H-flappy->collision.h;
        state_set(STT_GROUND);
        update_highscore();
        }
    if(flappy->collision.y<0)
		{
		flappy->y_vel=0;
		flappy->collision.y=0;
		}
    flappy_gravity(flappy);
	draw_flying(flappy);
	}

void flappy_collision(Flappy *flappy,Tower *tower,int num)
	{
	if(state_get()!=STT_FLAPING)
		return;
	int i;
    SDL_Rect rect=flappy->collision;
	rect.w-=5;
	for(i=0;i<num;i++)
		if(tower_collided(&tower[i],&rect))
        	{
        	state_set(STT_HIT);
        	flappy->y_vel=0;
			return;
        	}	
	}

static void flappy_hit(Flappy *flappy)
	{
    if(flappy->collision.h+flappy->collision.y<FLOOR_H)
    	flappy_gravity(flappy);
    if(flappy->collision.h+flappy->collision.y>=FLOOR_H)
    	{
        state_set(STT_GROUND);
      	update_highscore();
       	}
    flappy->rotation=90;
	}

static void flappy_ground(Flappy *flappy,int is_jump)
	{
    if(is_jump)
    	{
        state_set(STT_FLYING);
        flappy_reset(flappy);
        }
	}

static void flappy_options(Flappy *flappy,int is_jump)
	{
	/*
	if(is_jump)
		{
		SDL_GetMouseState(&x,&y);
		if(x>10 && x<36 && y>10 && y<38)
			{
			state_set(STT_FLAPING);
			break;
			}
		}
	*/
	}

