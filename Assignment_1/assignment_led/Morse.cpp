#include "Arduino.h"
#include "Morse.h"

// Unit delay (in ms)
int _delay = 250;

/*
Constructor for Morse

param : pin     Pin to output morse code signal to
*/
Morse::Morse(int pin_in) {
	pin = pin_in;
}

/* Morse Code Conversion
	param 	: String user_input 		The user input string to convert to Morse 
	returns : String converted_morse 	The morse code corresponding to the inputted string   
 */ 
String Morse::textConversion(String user_input) {
	String converted_morse = ""; 
	String morse_characters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", ".-.-.-", "--..--", "..--..", "-.-.--", "-....-", ".----.", "---...", ".-.-.", "-...-", ".-..-.", ".--.-."};
	char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

	// Using Arduino string class to convert userInput to lowercase to be mapped out
	user_input.toLowerCase(); 

	// Iterate through the userInput and convert each char to morseAlphabet 
	for (int i = 0; i < user_input.length(); i++) { 
		char curr_char = user_input.charAt(i); 
		if (curr_char == ' ') {
			// Actually do word space 
			converted_morse += " "; 
		} else { 
			for (int j = 0; j < 24; j++) {
				if (curr_char == alphabet[j]) {
					// Once you get to the mapped character - break out
					converted_morse += morse_characters[j] + " "; 
					break; 
				}
			}
		}
	}
	return converted_morse; 
}


/* 
Morse writeMorse
param	: String converted_morse 
return	: sends the Morse correctly  
*/
void Morse::writeMorse(String converted_morse) { 
	for (int i = 0; i < converted_morse.length(); i++) {
		char curr_char = converted_morse.charAt(i);
		// Go through each scenario: dot, dash, 
		if (curr_char == '.') {
			dot(); 
		} else if (curr_char == '-') {
			dash();
		} else if (curr_char == ' ') {
			letter_space(); 
		}
		// Delay between the morse characters 
		word_space();
	}
}

/* 
sendUserMessage
Converts and then sends the user input message 
*/
void Morse::sendUserMessage(String user_input) {
	String converted_input = textConversion(user_input); 
	writeMorse(converted_input);
}
/*
Morse Code Dot

Represents a . in morse code.
Sends a high signal to specified pin for one unit delay, followed by a low signal for one unit delay.
*/
void Morse::dot()
{
	digitalWrite(pin, HIGH);
	delay(_delay);
	digitalWrite(pin, LOW);
	delay(_delay);
}

/*
Morse Code Dash

Represents a - in morse code.
Sends a high signal to specified pin for three unit delay, followed by a low signal for one unit delay.
*/
void Morse::dash()
{
	digitalWrite(pin, HIGH);
	delay(_delay * 3);
	digitalWrite(pin, LOW);
	delay(_delay);
}

/*
Morse Code Letter Space

Represents a space between letters.
Sends a low signal to specified pin for three unit delay (one from dot/dash, two from method).
*/
void Morse::letter_space()
{
	digitalWrite(pin, LOW);
	delay(_delay * 2);
}

/*
Morse Code Word Space

Represents a space between words.
Sends a low signal to specified pin for seven unit delay (one from dot/dash, six from method).
*/
void Morse::word_space()
{
	digitalWrite(pin, LOW);
	delay(_delay * 6);
}
