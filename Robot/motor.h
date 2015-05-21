#ifndef MOTOR_H
#define MOTOR_H value

typedef enum { BLACK,WHITE,PURPLE} color_t;

void motor_init(void);
void sensor_init(void);

int getColorL();
int getColorR();
int getGyro();
int getRange();
#endif
