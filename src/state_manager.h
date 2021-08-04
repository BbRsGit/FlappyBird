#ifndef _STATE_MANAGER
#define _STATE_MANAGER

enum states{STT_FLYING=0,STT_FLAPING,STT_HIT,STT_GROUND,STT_OPTIONS};

void state_set(int state);

/** returns 0 if day and 1 if night */
int state_day();

int state_get();

#endif // _STATE_MANAGER
