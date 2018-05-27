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

#define SCREEN_W 288
#define SCREEN_H 512

#define MEDAL_SIZE 44
#define PANEL_W (113*2)
#define PANEL_H (57*2)

static const int score_poz[3]={SCREEN_W/2-12,SCREEN_W/2,SCREEN_W/2+12};

static int score_size(int score);

static int get_medal_type(int score);

static int score=0;

static int highscore=-1;

int get_highscore()
    {
    if(highscore==-1)
        {
        FILE *f=fopen("score","rb");
        if(f==NULL)
            {
            highscore=0;
            }
        else
            {
            (void)fread(&highscore,sizeof(int),1,f);
            fclose(f);
            }
        }
    return highscore;
    }

void update_highscore() { if(score>highscore) highscore=score; }

int save_highscore()
    {
    FILE *f=fopen("score","wb+");
    fwrite(&highscore,sizeof(int),1,f);
    fflush(f);
    fclose(f);
    return 0;
    }

int get_score() 	{ return score; 	}

void reset_score() 	{ score = 0; 		}

int update_score() 	{ return ++score; 	}

void draw_score()
    {
    if(state_get()==STT_FLYING)
		{
        return;
		}
	int size=score_size(score);
	int m_score=score;

	SDL_Rect draw_poz={score_poz[size-1],40,24,36};

	int i;
	for(i=0;i<size;i++)
		{
		get_res_render(LARGE_NUMBERS+m_score%10,NULL,&draw_poz);
		draw_poz.x-=24;
		m_score/=10;
		}
    }

void draw_score_panel()
    {
    if(state_get()!=STT_GROUND)
        return;
	
    SDL_Rect score_pannel={SCREEN_W/2-PANEL_W/2,SCREEN_H/2-PANEL_H/2,PANEL_W,PANEL_H};
    SDL_Rect medal={56,242,MEDAL_SIZE,MEDAL_SIZE};

	get_res_render(SCORE_PANNEL,NULL,&score_pannel);

	int medal_type=get_medal_type(score);

	if(medal_type>=0)
		get_res_render(MEDALS+medal_type,NULL,&medal);

	SDL_Rect number_rect;

	number_rect=(SDL_Rect){SCREEN_W/2+77,SCREEN_H/2-25,12,18};

	/*printing score*/
	int len=score_size(score);
	int temp_score=score;

	int i;
	for(i=0;i<len;i++)
		{
		get_res_render(LARGE_NUMBERS+temp_score%10,NULL,&number_rect);
		number_rect.x-=12;
		temp_score/=10;
		}
	
	/*printing highscore*/
	len=score_size(highscore);
	temp_score=highscore;

	number_rect.x=SCREEN_W/2+77;
	number_rect.y=SCREEN_H/2+17;

	for(i=0;i<len;i++)
		{
		get_res_render(LARGE_NUMBERS+temp_score%10,NULL,&number_rect);
		number_rect.x-=12;
		temp_score/=10;
		}
    }


static int score_size(int score)
	{
	int size=0;
	if(score==0)
		return 1;
	while(score!=0)
		{
		score/=10;
		size++;
		}
	return size;
	}

static int get_medal_type(int score)
	{
	if(score>=100)
		return 3;
	if(score>=50)
		return 2;
	if(score>=20)
		return 1;
	if(score>=10)
		return 0;
	return -1;
	}

