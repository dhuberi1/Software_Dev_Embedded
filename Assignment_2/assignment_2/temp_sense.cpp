#include "Arduino.h"
#include "Temp_Sense.h"

/*
Constructor for Temp_Sense

param : pin         Input pin
param : v_ref_in    Refernce voltage of Arduino (V)
*/
Temp_Sense::Temp_Sense(int pin_in, float v_ref_in) {
	pin = pin_in;
  v_ref = v_ref_in;
}

/*
Temp_Sense::mv_conv

Converts analog input of Arduino into milivolt reading

return  :   float mv, Analog voltage of input (mV)
*/
float Temp_Sense::mv_conv() {
    int a = analogRead(pin);
    float mv = a * (v_ref * 1000/1024.0);

    return mv;
}

/*
Temp_Sense::c_conv

Converts voltage of input into a temperature

param   :   float mv, Analog voltage (mV)
return  :   float c, Temperature (C)
*/
float Temp_Sense::c_conv(float mv) {
    float c = (mv - 500)/10;

    return c;
}

/*
Temp_Sense::f_conv

Converts temperature in Celcius into temperature in Farenheit

param   :   float c, Temperature (C)
return  :   float f, Temperature (F)
*/
float Temp_Sense::f_conv(float c) {
    float f = (c * 9/5.0) + 32;

    return f;
}

/*
Temp_Sense::readTemp

Converts analog input of Arduino into temperature in Farenheit

return  :  float f, Temperature (F)
*/
float Temp_Sense::readTemp() {
    float mv = mv_conv();
    float c = c_conv(mv);
    float f = f_conv(c);

    return f;
}