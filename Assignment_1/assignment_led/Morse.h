#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class Morse
{
	public:
		Morse(int pin_in);
		void dot();
		void dash();
		void letter_space();
		void word_space();
		String textConversion(String user_input); 
		void writeMorse(String converted_morse);
		void sendUserMessage(String user_input);  
	// private:
		int pin;
};

#endif

