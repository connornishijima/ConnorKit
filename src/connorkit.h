/*
  connorkit.h - Swiss army knife full of useful Arduino Functions
  Created by Connor Nishijima, September 8th 2016.
  Released under the GPLv3 license.
*/
#ifndef connorkit_h
#define connorkit_h

#include "Arduino.h"

class ConnorKit
{
  public:
    ConnorKit();
	
	// printArray
	void array_print_byte(byte arr[],uint16_t len, char delim);
	void array_print_int(int arr[],uint16_t len, char delim);
	void array_print_float(float arr[],uint16_t len, char delim, byte places);

	// shiftOntoEnd
	void array_shift_byte(byte arr[], uint16_t len, float newVal);
	void array_shift_int(int arr[], uint16_t len, float newVal);
	void array_shift_float(float arr[], uint16_t len, float newVal);
	
	// fillArray
	void array_fill_byte(byte arr[], uint16_t len, float newVal);
	void array_fill_int(int arr[], uint16_t len, float newVal);
	void array_fill_float(float arr[], uint16_t len, float newVal);
	
	float array_sum_byte(byte arr[], uint16_t len);
	float array_sum_int(int arr[], uint16_t len);
	float array_sum_float(float arr[], uint16_t len);
	
	// color fading
	void fadeColor_PWM(byte rStart, byte gStart, byte bStart, byte rEnd, byte gEnd, byte bEnd, byte rPin, byte gPin, byte bPin, uint16_t duration);
};

#endif
