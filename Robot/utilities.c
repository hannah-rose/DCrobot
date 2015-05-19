#include "utilities.h"
#include "NU32.h" 


static volatile state_t state = IDLE;

static volatile position_t position = {0,0,NORTH};

static state_t stateProgressions[8][4][4];

position_t util_position_get(){
	return position;
}

state_t util_get_next_action(){
	//RETURN turn right or left or straight ect
	position_t curr=util_position_get();
	return stateProgressions[curr.x][curr.y][curr.dir];
}

position_t update_position(state_t action){
	position_t pos = util_position_get();
	if (action == STRAIGHT){
		if (pos.dir==WEST){
			pos.x--;
		} else if (pos.dir==EAST){
			pos.x++;
		} else if (pos.dir==SOUTH){
			pos.y--;
		} else if (pos.dir==NORTH){
			pos.y++;
		}
	}else if (action == RIGHT){
		if (pos.dir == WEST){
			pos.dir = NORTH;
		} else if (pos.dir == NORTH){
			pos.dir = EAST;
		} else if (pos.dir == EAST){
			pos.dir = SOUTH;
		} else if (pos.dir == SOUTH){
			pos.dir = WEST;
		}
	}else if (action == LEFT){
		if (pos.dir == WEST){
			pos.dir = SOUTH;
		} else if (pos.dir == NORTH){
			pos.dir = WEST;
		} else if (pos.dir == EAST){
			pos.dir = NORTH;
		} else if (pos.dir == SOUTH){
			pos.dir = EAST;
		}
	}
	position = pos;
	return pos;
}



state_t util_state_get(){
	return state;
}

void util_state_set(state_t s){
	state=s;
}

void util_setup(){
	//FOR WHITE
	stateProgressions[ 0 ][ 0 ][ NORTH ]=STRAIGHT;
	stateProgressions[ 1 ][ 0 ][ NORTH ]=LEFT;
	stateProgressions[ 2 ][ 0 ][ NORTH ]=LEFT;
	stateProgressions[ 3 ][ 0 ][ NORTH ]=LEFT;
	stateProgressions[ 4 ][ 0 ][ NORTH ]=LEFT;
	stateProgressions[ 5 ][ 0 ][ NORTH ]=LEFT;
	stateProgressions[ 6 ][ 0 ][ NORTH ]=LEFT;
	stateProgressions[ 7 ][ 0 ][ NORTH ]=LEFT;

	stateProgressions[ 0 ][ 1 ][ NORTH ]=STRAIGHT;
	stateProgressions[ 1 ][ 1 ][ NORTH ]=LEFT;
	stateProgressions[ 2 ][ 1 ][ NORTH ]=LEFT;
	stateProgressions[ 3 ][ 1 ][ NORTH ]=LEFT;
	stateProgressions[ 4 ][ 1 ][ NORTH ]=LEFT;
	stateProgressions[ 5 ][ 1 ][ NORTH ]=LEFT;
	stateProgressions[ 6 ][ 1 ][ NORTH ]=LEFT;
	stateProgressions[ 7 ][ 1 ][ NORTH ]=LEFT;

	stateProgressions[ 0 ][ 2 ][ NORTH ]=STRAIGHT;
	stateProgressions[ 1 ][ 2 ][ NORTH ]=RIGHT;
	stateProgressions[ 2 ][ 2 ][ NORTH ]=RIGHT;
	stateProgressions[ 3 ][ 2 ][ NORTH ]=RIGHT;
	stateProgressions[ 4 ][ 2 ][ NORTH ]=RIGHT;
	stateProgressions[ 5 ][ 2 ][ NORTH ]=RIGHT;
	stateProgressions[ 6 ][ 2 ][ NORTH ]=RIGHT;
	stateProgressions[ 7 ][ 2 ][ NORTH ]=LEFT;

	stateProgressions[ 0 ][ 3 ][ NORTH ]=RIGHT;
	stateProgressions[ 1 ][ 3 ][ NORTH ]=RIGHT;
	stateProgressions[ 2 ][ 3 ][ NORTH ]=RIGHT;
	stateProgressions[ 3 ][ 3 ][ NORTH ]=RIGHT;
	stateProgressions[ 4 ][ 3 ][ NORTH ]=RIGHT;
	stateProgressions[ 5 ][ 3 ][ NORTH ]=RIGHT;
	stateProgressions[ 6 ][ 3 ][ NORTH ]=RIGHT;
	stateProgressions[ 7 ][ 3 ][ NORTH ]=RIGHT;

	stateProgressions[ 0 ][ 0 ][ EAST ]=LEFT;
	stateProgressions[ 1 ][ 0 ][ EAST ]=LEFT;
	stateProgressions[ 2 ][ 0 ][ EAST ]=LEFT;
	stateProgressions[ 3 ][ 0 ][ EAST ]=LEFT;
	stateProgressions[ 4 ][ 0 ][ EAST ]=LEFT;
	stateProgressions[ 5 ][ 0 ][ EAST ]=LEFT;
	stateProgressions[ 6 ][ 0 ][ EAST ]=LEFT;
	stateProgressions[ 7 ][ 0 ][ EAST ]=LEFT;

	stateProgressions[ 0 ][ 1 ][ EAST ]=LEFT;
	stateProgressions[ 1 ][ 1 ][ EAST ]=LEFT;
	stateProgressions[ 2 ][ 1 ][ EAST ]=LEFT;
	stateProgressions[ 3 ][ 1 ][ EAST ]=LEFT;
	stateProgressions[ 4 ][ 1 ][ EAST ]=LEFT;
	stateProgressions[ 5 ][ 1 ][ EAST ]=LEFT;
	stateProgressions[ 6 ][ 1 ][ EAST ]=LEFT;
	stateProgressions[ 7 ][ 1 ][ EAST ]=RIGHT;

	stateProgressions[ 0 ][ 2 ][ EAST ]=LEFT;
	stateProgressions[ 1 ][ 2 ][ EAST ]=STRAIGHT;
	stateProgressions[ 2 ][ 2 ][ EAST ]=STRAIGHT;
	stateProgressions[ 3 ][ 2 ][ EAST ]=STRAIGHT;
	stateProgressions[ 4 ][ 2 ][ EAST ]=STRAIGHT;
	stateProgressions[ 5 ][ 2 ][ EAST ]=STRAIGHT;
	stateProgressions[ 6 ][ 2 ][ EAST ]=RIGHT;
	stateProgressions[ 7 ][ 2 ][ EAST ]=RIGHT;

	stateProgressions[ 0 ][ 3 ][ EAST ]=STRAIGHT;
	stateProgressions[ 1 ][ 3 ][ EAST ]=STRAIGHT;
	stateProgressions[ 2 ][ 3 ][ EAST ]=STRAIGHT;
	stateProgressions[ 3 ][ 3 ][ EAST ]=STRAIGHT;
	stateProgressions[ 4 ][ 3 ][ EAST ]=STRAIGHT;
	stateProgressions[ 5 ][ 3 ][ EAST ]=STRAIGHT;
	stateProgressions[ 6 ][ 3 ][ EAST ]=STRAIGHT;
	stateProgressions[ 7 ][ 3 ][ EAST ]=RIGHT;

	stateProgressions[ 0 ][ 0 ][ SOUTH ]=RIGHT;
	stateProgressions[ 1 ][ 0 ][ SOUTH ]=RIGHT;
	stateProgressions[ 2 ][ 0 ][ SOUTH ]=RIGHT;
	stateProgressions[ 3 ][ 0 ][ SOUTH ]=RIGHT;
	stateProgressions[ 4 ][ 0 ][ SOUTH ]=RIGHT;
	stateProgressions[ 5 ][ 0 ][ SOUTH ]=RIGHT;
	stateProgressions[ 6 ][ 0 ][ SOUTH ]=RIGHT;
	stateProgressions[ 7 ][ 0 ][ SOUTH ]=RIGHT;

	stateProgressions[ 0 ][ 1 ][ SOUTH ]=RIGHT;
	stateProgressions[ 1 ][ 1 ][ SOUTH ]=RIGHT;
	stateProgressions[ 2 ][ 1 ][ SOUTH ]=RIGHT;
	stateProgressions[ 3 ][ 1 ][ SOUTH ]=RIGHT;
	stateProgressions[ 4 ][ 1 ][ SOUTH ]=RIGHT;
	stateProgressions[ 5 ][ 1 ][ SOUTH ]=RIGHT;
	stateProgressions[ 6 ][ 1 ][ SOUTH ]=RIGHT;
	stateProgressions[ 7 ][ 1 ][ SOUTH ]=STRAIGHT;

	stateProgressions[ 0 ][ 2 ][ SOUTH ]=LEFT;
	stateProgressions[ 1 ][ 2 ][ SOUTH ]=LEFT;
	stateProgressions[ 2 ][ 2 ][ SOUTH ]=LEFT;
	stateProgressions[ 3 ][ 2 ][ SOUTH ]=LEFT;
	stateProgressions[ 4 ][ 2 ][ SOUTH ]=LEFT;
	stateProgressions[ 5 ][ 2 ][ SOUTH ]=LEFT;
	stateProgressions[ 6 ][ 2 ][ SOUTH ]=STRAIGHT;
	stateProgressions[ 7 ][ 2 ][ SOUTH ]=STRAIGHT;

	stateProgressions[ 0 ][ 3 ][ SOUTH ]=LEFT;
	stateProgressions[ 1 ][ 3 ][ SOUTH ]=LEFT;
	stateProgressions[ 2 ][ 3 ][ SOUTH ]=LEFT;
	stateProgressions[ 3 ][ 3 ][ SOUTH ]=LEFT;
	stateProgressions[ 4 ][ 3 ][ SOUTH ]=LEFT;
	stateProgressions[ 5 ][ 3 ][ SOUTH ]=LEFT;
	stateProgressions[ 6 ][ 3 ][ SOUTH ]=LEFT;
	stateProgressions[ 7 ][ 3 ][ SOUTH ]=STRAIGHT;

	stateProgressions[ 0 ][ 0 ][ WEST ]=RIGHT;
	stateProgressions[ 1 ][ 0 ][ WEST ]=RIGHT;
	stateProgressions[ 2 ][ 0 ][ WEST ]=STRAIGHT;
	stateProgressions[ 3 ][ 0 ][ WEST ]=STRAIGHT;
	stateProgressions[ 4 ][ 0 ][ WEST ]=STRAIGHT;
	stateProgressions[ 5 ][ 0 ][ WEST ]=STRAIGHT;
	stateProgressions[ 6 ][ 0 ][ WEST ]=STRAIGHT;
	stateProgressions[ 7 ][ 0 ][ WEST ]=STRAIGHT;

	stateProgressions[ 0 ][ 1 ][ WEST ]=RIGHT;
	stateProgressions[ 1 ][ 1 ][ WEST ]=STRAIGHT;
	stateProgressions[ 2 ][ 1 ][ WEST ]=STRAIGHT;
	stateProgressions[ 3 ][ 1 ][ WEST ]=STRAIGHT;
	stateProgressions[ 4 ][ 1 ][ WEST ]=STRAIGHT;
	stateProgressions[ 5 ][ 1 ][ WEST ]=STRAIGHT;
	stateProgressions[ 6 ][ 1 ][ WEST ]=STRAIGHT;
	stateProgressions[ 7 ][ 1 ][ WEST ]=LEFT;

	stateProgressions[ 0 ][ 2 ][ WEST ]=RIGHT;
	stateProgressions[ 1 ][ 2 ][ WEST ]=RIGHT;
	stateProgressions[ 2 ][ 2 ][ WEST ]=RIGHT;
	stateProgressions[ 3 ][ 2 ][ WEST ]=RIGHT;
	stateProgressions[ 4 ][ 2 ][ WEST ]=RIGHT;
	stateProgressions[ 5 ][ 2 ][ WEST ]=RIGHT;
	stateProgressions[ 6 ][ 2 ][ WEST ]=RIGHT;
	stateProgressions[ 7 ][ 2 ][ WEST ]=LEFT;

	stateProgressions[ 0 ][ 3 ][ WEST ]=RIGHT;
	stateProgressions[ 1 ][ 3 ][ WEST ]=RIGHT;
	stateProgressions[ 2 ][ 3 ][ WEST ]=RIGHT;
	stateProgressions[ 3 ][ 3 ][ WEST ]=RIGHT;
	stateProgressions[ 4 ][ 3 ][ WEST ]=RIGHT;
	stateProgressions[ 5 ][ 3 ][ WEST ]=RIGHT;
	stateProgressions[ 6 ][ 3 ][ WEST ]=RIGHT;
	stateProgressions[ 7 ][ 3 ][ WEST ]=RIGHT;
}