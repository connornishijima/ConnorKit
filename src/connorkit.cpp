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

float ConnorKit::array_average_byte(byte arr[], uint16_t len){
	float sum = array_sum_byte(arr,len);
	return sum/float(len);
}

float ConnorKit::array_average_int(int arr[], uint16_t len){
	float sum = array_sum_int(arr,len);
	return sum/float(len);
}

float ConnorKit::array_average_float(float arr[], uint16_t len){
	float sum = array_sum_float(arr,len);
	return sum/float(len);
}

void ConnorKit::tone_multi_zx(byte tonePin, int freqs[], int len, uint16_t switchSpeed, uint16_t duration) {
  long tStart = millis();
  long tEnd = tStart + duration;
  while (millis() < tEnd) {
    for (byte i = 0; i < len; i++) {
      tone(tonePin, freqs[i]);
      delay(switchSpeed);
    }
  }
  noTone(tonePin);
}

void ConnorKit::tone_slide(byte tonePin, uint16_t toneStart, uint16_t toneEnd, uint16_t duration, bool cont = true) {
  float progress = 0;
  float push = 100.0 / float(duration);
  while (progress < 100) {
    uint16_t toneVal = interpolate(toneStart,toneEnd,progress);
    tone(tonePin, toneVal);

    progress += push;
    if (progress > 100) {
      progress = 100;
    }
    delayMicroseconds(850);
  }
  tone(tonePin, toneEnd);
  if(cont == false){
	noTone(tonePin);
  }
}

void ConnorKit::tone_arp(byte tonePin, uint16_t freq, uint16_t arpSpeed, uint16_t duration){
  uint16_t freqLow = freq/2;
  uint16_t freqLowest = freq/4;
  uint16_t freqHigh = freq*2;
  uint16_t freqHighest = freq*4;
  long tStart = millis();
  long tEnd = tStart+duration;
  while(millis() < tEnd){
    tone(tonePin,freqHighest);
    delay(arpSpeed);
    tone(tonePin,freqLow);
    delay(arpSpeed);
    tone(tonePin,freq);
    delay(arpSpeed);
    tone(tonePin,freqLowest);
    delay(arpSpeed);
    tone(tonePin,freqHigh);
    delay(arpSpeed);
    tone(tonePin,freq);
    delay(arpSpeed);
  }
  noTone(tonePin);
}

void ConnorKit::tone_siren(byte tonePin, uint16_t freq1, uint16_t freq2, uint16_t sirenSpeed, uint16_t duration){
  long tStart = millis();
  long tEnd = tStart+duration;
  while(millis() < tEnd){
    tone_slide(tonePin,freq1,freq2,sirenSpeed);
    tone_slide(tonePin,freq2,freq1,sirenSpeed);
  }
  noTone(tonePin);
}

void ConnorKit::tone_noise(byte tonePin, uint16_t duration) {
  static unsigned int y = 0;
  long tStart = millis();
  long tEnd = tStart + duration;
  while (millis() < tEnd) {
    y = 0;
    y += micros(); // seeded with changing number
    y ^= y >> 7;
    y ^= y << 7;
    tone(tonePin, y);
  }
  noTone(tonePin);
}

float ConnorKit::interpolate(float val1, float val2, float fader){
  fader = fader/100.0;
  return val1*(1.00-fader) + val2*fader;
}

void ConnorKit::soft_reset(byte soft_reset_bypass){
	static void(* restart_func) (void) = 0; //declare reset function @ address 0
	
	pinMode(soft_reset_bypass,INPUT_PULLUP);
	if(digitalRead(soft_reset_bypass) != LOW){
		restart_func();
	}
}


void ConnorKit::print_graph(uint16_t val, uint16_t mn, uint16_t mx, float time, uint16_t graph_width){
  float divisor = graph_width/float(mx);
  uint16_t mnG = mn*divisor;
  uint16_t valG = val*divisor;
  uint16_t mxG = mx*divisor;
  
  Serial.print(mn);
  Serial.print(F("| "));
  uint16_t index = mnG;
  while(index<=mxG){
    if(index == valG){
      Serial.print(F("+"));
    }
    else{
      Serial.print(F(" "));
    }
    index++;
  }
  Serial.print(F(" | "));
  Serial.print(mx);
  Serial.print(F("\t"));
  Serial.println(time);
}

long ConnorKit::measure_time(void (*func)()){
  static long tStart = micros();
  func();
  static long tEnd = micros();
  return (tEnd-tStart);
}


// --------------------------------------------------------------
// PWMfadeColor -------------------------------------------------

// That's right - 10 paramaters!
// This fades between a start and// end color using 3 PWM pins for
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
  float push = 100.0 / float(duration);
  while (progress < 1) {
    byte rVal = interpolate(rStart,rEnd,progress);
    byte gVal = interpolate(rStart,rEnd,progress);
    byte bVal = interpolate(rStart,rEnd,progress);

    analogWrite(rPin, rVal);
    analogWrite(gPin, gVal);
    analogWrite(bPin, bVal);

    progress += push;
    if (progress > 100) {
      progress = 100;
    }
    delay(1);
  }
  analogWrite(rPin, rEnd);
  analogWrite(gPin, gEnd);
  analogWrite(bPin, bEnd);
}