#ifndef IMUHANDLER_H 
#define IMUHANDLER_H 

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class IMUHandler { 
public: 
    // Constructor 
    IMUHandler();
    bool begin();  
    void update(); 

    // Oreintation functionality 
    float getRoll(); 
    float getPitch(); 
    float getYaw(); 

private: 
    Adafruit_BNO055 bno; 
    float roll, pitch, yaw; 

    // Potential TODO - Add mutex maybe for thread safety 

}; 

#endif 

