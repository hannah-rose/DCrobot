#ifndef MOTOR_H
#define MOTOR_H value

typedef enum { BLACK,WHITE,PURPLE} color_t;

void motor_init(void);
void sensor_init(void);

color_t getColorL();
color_t getColorR();
int getGyro();
int getRange();
#endif
