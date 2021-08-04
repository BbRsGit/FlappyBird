#include "state_manager.h"
#include <stdlib.h>

static int st_state=0;
static int st_day=0;

void state_set(int state)
    {
	if(st_state==STT_GROUND)
		{
		st_day=rand()%2;	
		}
    st_state=state;
    }

int state_day()
	{
	return st_day;
	}

int state_get()
    {
    return st_state;
    }
