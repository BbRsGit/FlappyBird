/* TODO- fix flappy flap animation*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "flappy.h"
#include "res_manager.h"
#include "state_manager.h"
#include "input.h"
#include "score.h"

const float DIFF=60;
const float GRAVITY=6.8;
const int JUMP_SPEED=-180;

static SDL_Rect col;
static float y_vel;
static SDL_Texture **textures;
static float rotation;
static int cur_texture;
static int jumped=0;
static int rotation_acc;

void flappy_reset()
    {
    col.x=26;
    col.y=256-12;
    col.w=34;
    col.h=24;
    textures=get_flappy_textures();
    cur_texture=0;
    rotation=0;
    y_vel=0;
    }

void flappy_draw(int delta)
    {
    static int last_jump;
    float ticks=(float)delta/10.0;
    if(jumped)
        {
        jumped=0;
        last_jump=0;
        rotation=-30;
        }
    switch(state_get())
        {
        case STT_GROUND:
        break;
        case STT_HIT:
            rotation=90;
        break;
        case STT_FLAPING:
        case STT_FLYING:
            rotation+=0.7*ticks;
            cur_texture++;
        break;
        }
    SDL_RenderCopyEx(get_res_renderer(),textures[cur_texture%3],NULL,&col,rotation,NULL,0);
    }

void flappy_jump()
    {
    y_vel=JUMP_SPEED;
    jumped=1;
    }

void flappy_gravity(float ticks_dif)
    {
    col.y+=y_vel*ticks_dif/DIFF;
    y_vel+=GRAVITY*ticks_dif;
    }

void flappy_update(struct press *press,int delta)
    {
    float ticks_dif=(float)(delta)/10.0;
    switch(state_get())
        {
        case STT_FLYING:
            //auto jump
            //resets frame_count to zero so the draw flappy can manage sprites
            if(col.y>=256-12)
                {
                col.y=256-12;
                flappy_jump();
                }
            //changes state
            if(press->is_pressed)
                {
                state_set(STT_FLAPING);
                flappy_jump();
                set_score(0);
                }
            flappy_gravity(ticks_dif);
        break;
        case STT_FLAPING:
            if(press->is_pressed==1)
                {
                flappy_jump();
                }
            if(tower_collision(&col))
                {
                state_set(STT_HIT);
                y_vel=0;
                }
            if(col.h+col.y>=512-56*2)
                {
                state_set(STT_GROUND);
                int hscore=get_highscore();
                if(hscore<get_score())
                    set_highscore(get_score());
                }
            flappy_gravity(ticks_dif);
        break;
        case STT_HIT:
            if(col.h+col.y<512-56*2)
                flappy_gravity(ticks_dif);
            if(col.h+col.y>=512-56*2)
                {
                state_set(STT_GROUND);
                int hscore=get_highscore();
                if(hscore<get_score())
                    set_highscore(get_score());
                }
        break;
        case STT_GROUND:
            if(press->is_pressed==1)
                {
                state_set(STT_FLYING);
                flappy_reset();
                }
        break;
        }
    }
