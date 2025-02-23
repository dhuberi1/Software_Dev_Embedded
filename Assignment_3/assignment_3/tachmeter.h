#ifndef TACHMETER_H 
#define TACHMETER_H 

#include <Arduino.h> 

// RPM Calculation Variables
/*
count: # of times we detect a propellor blade 
lastTime: Last recorded time in miliseconds where the ir sensor had an interrupt 
rmp: value we are calculating/stores this value 
every_other_count: Since the propellor is spinning and hits the sensor twice for 1 rotation
*/ 
extern volatile int count; 
extern volatile unsigned long lastTime;
extern volatile float rpm;
extern volatile int every_other_count; 

extern float rpmData[1000];  
extern unsigned long timestamps[1000];  

void IR_detect_ISR(); 
float getRPM(); 
void resetRPM(); 

#endif 