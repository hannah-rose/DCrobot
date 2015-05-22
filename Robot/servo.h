#ifndef SERVO_H
#define SERVO_H

//Sets externam interrupt to alert robot when time is almost out
void init_time();

//Checks time and returns current time in seconds
int check_time();

//Initialize pins to control servo
void init_servo();

//Sweep blocks out of robot
void sweep();

void delay_ms(int time);

#endif 