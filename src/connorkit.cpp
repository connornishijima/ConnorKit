/*
  connorkit.cpp - Swiss army knife full of useful Arduino Functions
  Created by Connor Nishijima, September 8th 2016.
  Released under the GPLv3 license.
*/

#include "connorkit.h"

ConnorKit::ConnorKit() {
};

void ConnorKit::array_print_byte(byte arr[],uint16_t len, char delim){
  for(uint16_t i = 0; i < len; i++){
    Serial.print(arr[i]);
    Serial.print(delim);
  }
  Serial.println();
}

void ConnorKit::array_print_int(int arr[],uint16_t len, char delim){
  for(uint16_t i = 0; i < len; i++){
    Serial.print(arr[i]);
    Serial.print(delim);
  }
  Serial.println();
}

void ConnorKit::array_print_float(float arr[],uint16_t len, char delim, byte places){
  for(uint16_t i = 0; i < len; i++){
    Serial.print(arr[i],places);
    Serial.print(delim);
  }
  Serial.println();
}

void ConnorKit::array_shift_byte(byte arr[], uint16_t len, float newVal){
  for(int x = 0; x < len-1; x++){
    arr[x] = arr[x+1];
  }
  arr[len-1] = newVal;
}

void ConnorKit::array_shift_int(int arr[], uint16_t len, float newVal){
  for(int x = 0; x < len-1; x++){
    arr[x] = arr[x+1];
  }
  arr[len-1] = newVal;
}

void ConnorKit::array_shift_float(float arr[], uint16_t len, float newVal){
  for(int x = 0; x < len-1; x++){
    arr[x] = arr[x+1];
  }
  arr[len-1] = newVal;
}

void ConnorKit::array_fill_byte(byte arr[], uint16_t len, float newVal){
  for(int x = 0; x < len; x++){
    arr[x] = newVal;
  }
}

void ConnorKit::array_fill_int(int arr[], uint16_t len, float newVal){
  for(int x = 0; x < len; x++){
    arr[x] = newVal;
  }
}

void ConnorKit::array_fill_float(float arr[], uint16_t len, float newVal){
  for(int x = 0; x < len; x++){
    arr[x] = newVal;
  }
}

float ConnorKit::array_sum_byte(byte arr[], uint16_t len){
	float sum = 0;
	for(uint16_t i = 0; i < len; i++){
		sum+=arr[i];
	}
	return sum;
}

float ConnorKit::array_sum_int(int arr[], uint16_t len){
	float sum = 0;
	for(uint16_t i = 0; i < len; i++){
		sum+=arr[i];
	}
	return sum;
}

float ConnorKit::array_sum_float(float arr[], uint16_t len){
	float sum = 0;
	for(uint16_t i = 0; i < len; i++){
		sum+=arr[i];
	}
	return sum;
}

// --------------------------------------------------------------
// PWMfadeColor -------------------------------------------------

// That's right - 10 paramaters!
// This fades between a start and end color using 3 PWM pins for
// red, green and blue over the duration specified. This is done
// by multiplying start and end color's value by the progress of
// the fade, from 0.000 to 1.000 - then summing the two together.
//
// For example: Police lights:
//
// PWMfadeColor(255, 0, 0,   0,   0, 255, 9, 10, 11, 200);
// PWMfadeColor(0,   0, 255, 255, 0, 0,   9, 10, 11, 200);
//
void ConnorKit::fadeColor_PWM(byte rStart, byte gStart, byte bStart,   byte rEnd, byte gEnd, byte bEnd,   byte rPin, byte gPin, byte bPin,   uint16_t duration) {
  float progress = 0;
  float push = 1.0 / float(duration);
  while (progress < 1) {
    byte rVal = rStart * (1 - progress) + rEnd * progress;
    byte gVal = gStart * (1 - progress) + gEnd * progress;
    byte bVal = bStart * (1 - progress) + bEnd * progress;

    analogWrite(rPin, rVal);
    analogWrite(gPin, gVal);
    analogWrite(bPin, bVal);

    progress += push;
    if (progress > 1) {
      progress = 1;
    }
    delay(1);
  }
  analogWrite(rPin, rEnd);
  analogWrite(gPin, gEnd);
  analogWrite(bPin, bEnd);
}