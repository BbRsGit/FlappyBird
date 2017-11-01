#include "state_manager.h"

static int st_state=0;

void state_set(int state)
    {
    st_state=state;
    }

int state_get()
    {
    return st_state;
    }
