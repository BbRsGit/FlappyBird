#ifndef _STATE_MANAGER
#define _STATE_MANAGER

enum states{STT_FLYING=0,STT_FLAPING,STT_HIT,STT_GROUND};

void state_set(int state);

int state_get();

#endif // _STATE_MANAGER
