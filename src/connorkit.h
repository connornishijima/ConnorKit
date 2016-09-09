/*
  connorkit.h - Swiss army knife full of useful Arduino Functions
  Created by Connor Nishijima, September 8th 2016.
  Released under the GPLv3 license.
*/
#ifndef connorkit_h
#define connorkit_h

#include "Arduino.h"

// Macros --------------------------------------

// Get true lengths of arrays of any type
#define len( x )  ( sizeof( x ) / sizeof( *x ) )

// ---------------------------------------------

class ConnorKit
{
  public:
    ConnorKit();
	
// ----------------------------------------------------------------------
// Array tools ----------------------------------------------------------
	
	// print array values to Serial
	void array_print_byte(byte arr[],uint16_t len, char delim);
	void array_print_int(int arr[],uint16_t len, char delim);
	void array_print_float(float arr[],uint16_t len, char delim, byte places);

	// shift array left, add item on end
	void array_shift_byte(byte arr[], uint16_t len, float newVal);
	void array_shift_int(int arr[], uint16_t len, float newVal);
	void array_shift_float(float arr[], uint16_t len, float newVal);
	
	// fill array with value
	void array_fill_byte(byte arr[], uint16_t len, float newVal);
	void array_fill_int(int arr[], uint16_t len, float newVal);
	void array_fill_float(float arr[], uint16_t len, float newVal);

	// return sum of array
	float array_sum_byte(byte arr[], uint16_t len);
	float array_sum_int(int arr[], uint16_t len);
	float array_sum_float(float arr[], uint16_t len);
	
	// return average of array
	float array_average_byte(byte arr[], uint16_t len);
	float array_average_int(int arr[], uint16_t len);
	float array_average_float(float arr[], uint16_t len);
	
// ----------------------------------------------------------------------
// Math tools -----------------------------------------------------------

	float interpolate(float val1, float val2, float percentage);

// ----------------------------------------------------------------------
// LED tools ------------------------------------------------------------
	
	// color fading
	void fadeColor_PWM(byte rStart, byte gStart, byte bStart, byte rEnd, byte gEnd, byte bEnd, byte rPin, byte gPin, byte bPin, uint16_t duration);

// ----------------------------------------------------------------------
// Sound tools ----------------------------------------------------------

	void tone_multi_zx(byte tonePin, int freqs[], int len, uint16_t switchSpeed, uint16_t duration);
	void tone_slide(byte tonePin, uint16_t toneStart, uint16_t toneEnd, uint16_t duration, bool cont = true);
	void tone_noise(byte tonePin, uint16_t duration);
	void tone_arp(byte tonePin, uint16_t freq, uint16_t arpSpeed, uint16_t duration);
	void tone_siren(byte tonePin, uint16_t freq1, uint16_t freq2, uint16_t sirenSpeed, uint16_t duration);

// ----------------------------------------------------------------------
};

#endif
