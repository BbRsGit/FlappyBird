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

int score=0;

int highscore=-1;

int get_highscore()
    {
    int error=-1;
    if(highscore==-1)
        {
        FILE *f=fopen("score","rb");
        if(f==NULL)
            {
            highscore=0;
            }
        else
            {
            error=fread(&highscore,sizeof(int),1,f);
            fclose(f);
            }
        }
    if(error==100000)
       return -1;
    else
        return highscore;
    }

int set_highscore(int hscore)
    {
    return highscore=hscore;
    }

int save_highscore()
    {
    FILE *f=fopen("score","wb+");
    fwrite(&highscore,sizeof(int),1,f);
    fflush(f);
    fclose(f);
    return 0;
    }

int get_score()
    {
    return score;
    }

int set_score(int n)
    {
    score = n;
    return score;    
    }

void draw_num(int x,int y,SDL_Texture *texture,SDL_Renderer *ren)
    {
    SDL_Rect rect={x,y,24,36};
    SDL_RenderCopy(ren,texture,NULL,&rect);
    }

void draw_score()
    {
    SDL_Renderer *ren=get_res_renderer();
    SDL_Texture **tex=get_res_texture_list(LARGE_NUMBERS);
    if(state_get()==STT_FLYING)
        return;
    if(score<10)
        {
        draw_num(144-12,40,tex[score],ren);
        }
    else if(score<100)
        {
        draw_num(144-24,40,tex[score/10],ren);
        draw_num(144+0,40,tex[score%10],ren);
        }
    else if(score<1000)
        {
        draw_num(144-24-12,40,tex[score/100],ren);
        draw_num(144-12,40,tex[(score/10)%10],ren);
        draw_num(144+12,40,tex[score%10],ren);
        }
    }
void draw_mid_num(int x,int y,SDL_Texture *texture,SDL_Renderer *ren)
    {
    SDL_Rect rect={x,y,12,18};
    SDL_RenderCopy(ren,texture,NULL,&rect);
    }

void draw_score_panel()
    {
    if(state_get()!=STT_GROUND)
        return;
    SDL_Renderer *ren=get_res_renderer();
    SDL_Texture **tex=get_res_texture_list(LARGE_NUMBERS);
    SDL_Rect rect={144-113,256-57,113*2,57*2};
    SDL_RenderCopy(ren,get_res_texture(SCORE_PANNEL),NULL,&rect);

    SDL_Rect medal={56,242,22*2,22*2};

    if(score>100)
        {
        SDL_RenderCopy(ren,get_res_texture(MEDALS+3),NULL,&medal);
        }
    else if(score>50)
        {
        SDL_RenderCopy(ren,get_res_texture(MEDALS+2),NULL,&medal);
        }
    else if(score>20)
        {
        SDL_RenderCopy(ren,get_res_texture(MEDALS+1),NULL,&medal);
        }
    else if(score>10)
        {
        SDL_RenderCopy(ren,get_res_texture(MEDALS+0),NULL,&medal);
        }



    draw_mid_num(144-113+160-6+12*3,256-57+32,tex[score%10],ren);

    if(score>=10)
        {
        draw_mid_num(144-113+160-6+12*2,256-57+32,tex[(score/10)%10],ren);
        }
    if(score>=100)
        {
        draw_mid_num(144-113+160-6+12*1,256-57+32,tex[score/100],ren);
        }


    draw_mid_num(144-113+160-6+12*3,256-15+32,tex[highscore%10],ren);

    if(highscore>=10)
        {
        draw_mid_num(144-113+160-6+12*2,256-15+32,tex[(highscore/10)%10],ren);
        }
    if(highscore>=100)
        {
        draw_mid_num(144-113+160-6+12*1,256-15+32,tex[highscore/100],ren);
        }
    }

