#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "IMUHandler.h"

// Constructor - initially rpw to (0,0,0)
IMUHandler::IMUHandler()
    : bno(55, 0x28, &Wire), roll(0), pitch(0), yaw(0) {}

// Initialise the IMU sensor
bool IMUHandler::begin() {
    // From: https://github.com/adafruit/Adafruit_BNO055/blob/master/examples/sensorapi/sensorapi.ino
    if(!bno.begin()) {
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        return false; 
    }

    bno.setExtCrystalUse(true);
    return true; 
}

void IMUHandler::update() {
    sensors_event_t event;
    bno.getEvent(&event);

    // TODO - Potentially wrap this in a mutex 
    // Setting private class members here
    roll = event.orientation.x;
    pitch = event.orientation.y;
    yaw = event.orientation.z;    
} 

// Oreintation functionality - simple getter functions 
float IMUHandler::getRoll() { 
    return roll;    
}
float IMUHandler::getPitch() {
    return pitch; 
}
float IMUHandler::getYaw() {
    return yaw;
} 