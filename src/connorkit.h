/*
  connorkit.h - Swiss army knife full of useful Arduino Functions
  Created by Connor Nishijima, September 8th 2016.
  Released under the GPLv3 license.
*/
#ifndef connorkit_h
#define connorkit_h

#include "Arduino.h"
#include "digitalwritefast.h"

// Macros --------------------------------------

// Get true lengths of arrays of any type - very handy!
#define len( x )  ( sizeof( x ) / sizeof( *x ) )

// ---------------------------------------------

class ConnorKit
{
  public:
    ConnorKit();
	
// ----------------------------------------------------------------------
// Array tools ----------------------------------------------------------
	
	// print array values to Serial
	uint8_t array_print(uint8_t arr[],uint16_t len, char delim = ',');
	int16_t array_print(int16_t arr[],uint16_t len, char delim = ',');
	float array_print(float arr[],uint16_t len, uint8_t places = 2, char delim = ',');

	// shift array left, add item on end
	uint8_t array_shift(uint8_t arr[], uint16_t len, uint8_t newVal);
	int16_t array_shift(int16_t arr[], uint16_t len, int16_t newVal);
	float array_shift(float arr[], uint16_t len, float newVal);
	
	// fill array with value
	uint8_t array_fill(uint8_t arr[], uint16_t len, uint8_t newVal);
	int16_t array_fill(int16_t arr[], uint16_t len, int16_t newVal);
	float array_fill(float arr[], uint16_t len, float newVal);

	// return sum of array
	uint8_t array_sum(uint8_t arr[], uint16_t len);
	int16_t array_sum(int16_t arr[], uint16_t len);
	float array_sum(float arr[], uint16_t len);
	
	// return average of array
	uint8_t array_average(uint8_t arr[], uint16_t len);
	int16_t array_average(int16_t arr[], uint16_t len);
	float array_average(float arr[], uint16_t len);

// ----------------------------------------------------------------------
// IO tools -------------------------------------------------------------
	
	void pulse_out(uint8_t pin, uint8_t state, uint32_t duration);

// ----------------------------------------------------------------------
// Math tools -----------------------------------------------------------

	uint8_t interpolate(uint8_t val1, uint8_t val2, float fader);
	int16_t interpolate(int16_t val1, int16_t val2, float fader);
	float interpolate(float val1, float val2, float fader);
	
	void byte_to_bin(byte input, byte output[]);
	byte bin_to_byte(byte input[]);
	
	void print_graph(uint16_t val, uint16_t mn, uint16_t mx, float time, uint16_t graph_width, char point);

// ----------------------------------------------------------------------
// LED tools ------------------------------------------------------------
	
	// color fading
	void fade_color_pwm(uint8_t rStart, uint8_t gStart, uint8_t bStart, uint8_t rEnd, uint8_t gEnd, uint8_t bEnd, uint8_t rPin, uint8_t gPin, uint8_t bPin, uint16_t duration);

// ----------------------------------------------------------------------
// Sound tools ----------------------------------------------------------

	void tone_multi_zx(uint8_t tonePin, int16_t freqs[], int16_t len, uint16_t switchSpeed, uint16_t duration);
	void tone_slide(uint8_t tonePin, int16_t toneStart, int16_t toneEnd, uint16_t duration, bool cont = true);
	void tone_noise(uint8_t tonePin, uint16_t duration);
	void tone_arp(uint8_t tonePin, uint16_t freq, uint16_t arpSpeed, uint16_t duration);
	void tone_siren(uint8_t tonePin, uint16_t freq1, uint16_t freq2, uint16_t sirenSpeed, uint16_t duration);

// ----------------------------------------------------------------------
// Misc tools -----------------------------------------------------------

	void soft_reset(uint8_t soft_reset_bypass);
	long measure_func_us(void (*func)());
	float measure_tx_us(uint16_t message_len, uint32_t baud);

// ----------------------------------------------------------------------

};

#endif
