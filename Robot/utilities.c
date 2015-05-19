#include "utilities.h"
#include "NU32.h" 


static volatile state_t state = IDLE;

state_t util_state_get(){
	return state;
}

void util_state_set(state_t s){
	state=s;
}