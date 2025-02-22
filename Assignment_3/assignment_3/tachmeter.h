#ifndef TACHMETER_H 
#define TACHMETER_H 

#include <Arduino.h> 

void IR_detect_ISR(); 
float getRPM(); 
void resetRPM(); 

#endif 