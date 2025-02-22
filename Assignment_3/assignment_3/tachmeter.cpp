#include <Arduino.h>

// RPM Calculation Variables
/*
count: # of times we detect a propellor blade 
lastTime: Last recorded time in miliseconds where the ir sensor had an interrupt 
rmp: value we are calculating/stores this value 
*/ 
volatile int count = 0; 
volatile unsigned long lastTime = 0;
volatile float rpm = 0;

/*
Triggered whenever propeller blade passes through the sensor (when Ir sensor detects an interrupt)
Stores only the last timestamp in lastTime and uses the time difference between detections to calculate RPM
*/ 
void IR_detect_ISR() {
    unsigned long currentTime = millis();
    if (lastTime > 0) {
        rpm = 60000.0 / (currentTime - lastTime); // Converts time interval to RPM
    }
    lastTime = currentTime;
    count++;
}

// Function to get the calculated RPM from arduino file 
float getRPM() {
    return rpm;
}

// Function to reset RPM count/measurements are restarted 
void resetRPM() {
    count = 0;
    lastTime = 0;
    rpm = 0;
}
