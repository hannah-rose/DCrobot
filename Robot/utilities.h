#ifndef util__H__
#define util__H__

typedef enum { IDLE, STRAIGHT, LEFT, RIGHT, ROAM } state_t;          // the various states

state_t util_state_get();               // get the current state

void util_state_set(state_t s);         // atomically set the current state. 

#endif


