/*
  connorkit.h - Swiss army knife full of useful Arduino Functions
  Created by Connor Nishijima, September 8th 2016.
  Released under the GPLv3 license.
*/
#ifndef connorkit_h
#define connorkit_h

#include "Arduino.h"
#include "digitalwritefast.h"
#include <avr/wdt.h>

//##############################################
// Macros --------------------------------------

// Get true lengths of arrays of any type - very handy!
#define len( x )  ( sizeof( x ) / sizeof( *x ) )

// Serial print mixed values quickly!
#define print_one(a) Serial.println(a);
#define print_two(a,b) Serial.print(a);Serial.print('\t');Serial.println(b);
#define print_three(a,b,c) Serial.print(a);Serial.print('\t');Serial.print(b);Serial.print('\t');Serial.println(c);
#define print_four(a,b,c,d) Serial.print(a);Serial.print('\t');Serial.print(b);Serial.print('\t');Serial.print(c);Serial.print('\t');Serial.println(d);
#define print_five(a,b,c,d,e) Serial.print(a);Serial.print('\t');Serial.print(b);Serial.print('\t');Serial.print(c);Serial.print('\t');Serial.print(d);Serial.print('\t');Serial.println(e);

// We can do work on arrays without specifying their length using macros!
// This trick uses the len() macro above before running the functions.
// Pointers are a pain in the ass sometimes, this took forever to come up with.
#define array_print(arr) array_print_f(arr,len(arr))
#define array_shift(arr, newVal) array_shift_f(arr,len(arr),newVal)
#define array_fill(arr, newVal) array_fill_f(arr,len(arr),newVal)
#define array_sum(arr) array_sum_f(arr,len(arr))
#define array_average(arr) array_average_f(arr,len(arr))
#define array_sort(arr) array_sort_f(arr,len(arr))
#define array_reverse(arr) array_reverse_f(arr,len(arr))
#define array_shuffle(arr) array_shuffle_f(arr,len(arr))

//##############################################
// ---------------------------------------------

/**
ConnorKit class, containing all of the coolest functions! Over the years I've
had to roll many of my own Arduino functions to solve some interesting or tedious
problems, and I've decided to put all of these solutions into a single, easy-to-use
Arduino library. Don't worry - the only flash and RAM space it takes are the
functions you actually use! The compiler is smart enough to ignore everything else.
- Connor Nishijima
*/
class ConnorKit
{
  public:
    ConnorKit();
	
// ----------------------------------------------------------------------
// Array tools ----------------------------------------------------------
	
	// print array values to Serial
	uint8_t array_print_f(uint8_t arr[],uint16_t len, char delim = ',');
	int16_t array_print_f(int16_t arr[],uint16_t len, char delim = ',');
	uint16_t array_print_f(uint16_t arr[],uint16_t len, char delim = ',');
	float array_print_f(float arr[],uint16_t len, char delim = ',');

	// shift array left, add item on end
	uint8_t array_shift_f(uint8_t arr[], uint16_t len, uint8_t newVal);
	int16_t array_shift_f(int16_t arr[], uint16_t len, int16_t newVal);
	uint16_t array_shift_f(uint16_t arr[], uint16_t len, uint16_t newVal);
	float array_shift_f(float arr[], uint16_t len, float newVal);
	
	// fill array with value
	uint8_t array_fill_f(uint8_t arr[], uint16_t len, uint8_t newVal);
	int16_t array_fill_f(int16_t arr[], uint16_t len, int16_t newVal);
	uint16_t array_fill_f(uint16_t arr[], uint16_t len, uint16_t newVal);
	float array_fill_f(float arr[], uint16_t len, float newVal);

	// return sum of array
	uint16_t array_sum_f(uint8_t arr[], uint16_t len);
	int32_t array_sum_f(int16_t arr[], uint16_t len);
	uint32_t array_sum_f(uint16_t arr[], uint16_t len);
	float array_sum_f(float arr[], uint16_t len);
	
	// return average of array
	uint8_t array_average_f(uint8_t arr[], uint16_t len);
	int16_t array_average_f(int16_t arr[], uint16_t len);
	uint16_t array_average_f(uint16_t arr[], uint16_t len);
	float array_average_f(float arr[], uint16_t len);
	
	// sort array
	void array_sort_f(uint8_t arr[], uint16_t len);
	void array_sort_f(int16_t arr[], uint16_t len);
	void array_sort_f(uint16_t arr[], uint16_t len);
	void array_sort_f(float arr[], uint16_t len);
	
	// reverse array
	void array_reverse_f(uint8_t arr[], uint16_t len);
	void array_reverse_f(int16_t arr[], uint16_t len);
	void array_reverse_f(uint16_t arr[], uint16_t len);
	void array_reverse_f(float arr[], uint16_t len);
	
	// reverse array
	void array_shuffle_f(uint8_t arr[], uint16_t len);
	void array_shuffle_f(int16_t arr[], uint16_t len);
	void array_shuffle_f(uint16_t arr[], uint16_t len);
	void array_shuffle_f(float arr[], uint16_t len);

// ----------------------------------------------------------------------
// IO tools -------------------------------------------------------------
	
	void pulse_out(uint8_t pin, uint8_t state, uint32_t duration);

// ----------------------------------------------------------------------
// Math tools -----------------------------------------------------------

	uint8_t interpolate(uint8_t val1, uint8_t val2, float fader);
	int16_t interpolate(int16_t val1, int16_t val2, float fader);
	uint16_t interpolate(uint16_t val1, uint16_t val2, float fader);
	float interpolate(float val1, float val2, float fader);
	
	int16_t rng();
	
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
	float measure_func_us(void (*func)(),uint16_t runs = 1);
	float measure_tx_us(uint16_t message_len, uint32_t baud);

// ----------------------------------------------------------------------

};

#endif
