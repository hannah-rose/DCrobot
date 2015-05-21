#ifndef util__H__
#define util__H__

typedef enum { IDLE, STRAIGHT, LEFT, RIGHT, ROAM } state_t;          // the various states
typedef enum { NORTH, SOUTH, WEST, EAST} dir_t;

typedef struct {                        // structure used for storing control loop data
  int x;                        // you will modify this to contain the values
  int y;                           // and types that you want to send, the current
  dir_t dir;                        // members are for demonstration purposes
} position_t;

state_t util_state_get();               // get the current state

void util_state_set(state_t s);         // atomically set the current state. 

position_t util_position_get();

state_t util_get_next_action();

position_t update_position(state_t action);

#endif


