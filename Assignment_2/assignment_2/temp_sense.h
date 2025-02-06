#ifndef Temp_Sense_h
#define Temp_Sense_h

#include "Arduino.h"

class Temp_Sense
{
	public:
		Temp_Sense(int pin_in, float v_ref_in);
		float mv_conv();
		float c_conv(float mv);
		float f_conv(float c);
    float readTemp();
	private:
		int pin;
    float v_ref;
};

#endif