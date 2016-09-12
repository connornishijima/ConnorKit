/*
  connorkit.cpp - Swiss army knife full of useful Arduino Functions
  Created by Connor Nishijima, September 8th 2016.
  Released under the GPLv3 license.
*/

#include "connorkit.h"

ConnorKit::ConnorKit() {
};

uint8_t ConnorKit::array_print(uint8_t arr[],uint16_t len, char delim){
  for(uint16_t i = 0; i < len; i++){
    Serial.print(arr[i]);
	if(i != len-1){
      Serial.print(delim);
	  Serial.print(' ');
	}
  }
  Serial.println();
  return 1;
}

int16_t ConnorKit::array_print(int16_t arr[],uint16_t len, char delim){
  for(uint16_t i = 0; i < len; i++){
    Serial.print(arr[i]);
	if(i != len-1){
      Serial.print(delim);
	  Serial.print(' ');
	}
  }
  Serial.println();
  return 1;
}

float ConnorKit::array_print(float arr[],uint16_t len, char delim, uint8_t places){
  for(uint16_t i = 0; i < len; i++){
    Serial.print(arr[i],places);
	if(i != len-1){
	  Serial.print(delim);
	  Serial.print(' ');
	}
  }
  Serial.println();
  return 1;
}

uint8_t ConnorKit::array_shift(uint8_t arr[], uint16_t len, float newVal){
  for(int32_t x = 0; x < len-1; x++){
    arr[x] = arr[x+1];
  }
  arr[len-1] = newVal;
  return 1;
}

int16_t ConnorKit::array_shift(int16_t arr[], uint16_t len, float newVal){
  for(int32_t x = 0; x < len-1; x++){
    arr[x] = arr[x+1];
  }
  arr[len-1] = newVal;
  return 1;
}

float ConnorKit::array_shift(float arr[], uint16_t len, float newVal){
  for(int32_t x = 0; x < len-1; x++){
    arr[x] = arr[x+1];
  }
  arr[len-1] = newVal;
  return 1;
}

uint8_t ConnorKit::array_fill(uint8_t arr[], uint16_t len, float newVal){
  for(int32_t x = 0; x < len; x++){
    arr[x] = newVal;
  }
  return 1;
}

int16_t ConnorKit::array_fill(int16_t arr[], uint16_t len, float newVal){
  for(int32_t x = 0; x < len; x++){
    arr[x] = newVal;
  }
  return 1;
}

float ConnorKit::array_fill(float arr[], uint16_t len, float newVal){
  for(int32_t x = 0; x < len; x++){
    arr[x] = newVal;
  }
  return 1;
}

uint8_t ConnorKit::array_sum(uint8_t arr[], uint16_t len){
	float sum = 0;
	for(uint16_t i = 0; i < len; i++){
		sum+=arr[i];
	}
	return sum;
}

int16_t ConnorKit::array_sum(int16_t arr[], uint16_t len){
	float sum = 0;
	for(uint16_t i = 0; i < len; i++){
		sum+=arr[i];
	}
	return sum;
}

float ConnorKit::array_sum(float arr[], uint16_t len){
	float sum = 0;
	for(uint16_t i = 0; i < len; i++){
		sum+=arr[i];
	}
	return sum;
}

uint8_t ConnorKit::array_average(uint8_t arr[], uint16_t len){
	float sum = array_sum(arr,len);
	return sum/float(len);
}

int16_t ConnorKit::array_average(int16_t arr[], uint16_t len){
	float sum = array_sum(arr,len);
	return sum/float(len);
}

float ConnorKit::array_average(float arr[], uint16_t len){
	float sum = array_sum(arr,len);
	return sum/float(len);
}

void ConnorKit::tone_multi_zx(uint8_t tonePin, int16_t freqs[], int16_t len, uint16_t switchSpeed, uint16_t duration) {
  long tStart = millis();
  long tEnd = tStart + duration;
  while (millis() < tEnd) {
    for (uint8_t i = 0; i < len; i++) {
      tone(tonePin, freqs[i]);
      delay(switchSpeed);
    }
  }
  noTone(tonePin);
}

void ConnorKit::tone_slide(uint8_t tonePin, int16_t toneStart, int16_t toneEnd, uint16_t duration, bool cont = true) {
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

void ConnorKit::tone_arp(uint8_t tonePin, uint16_t freq, uint16_t arpSpeed, uint16_t duration){
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

void ConnorKit::tone_siren(uint8_t tonePin, uint16_t freq1, uint16_t freq2, uint16_t sirenSpeed, uint16_t duration){
  long tStart = millis();
  long tEnd = tStart+duration;
  while(millis() < tEnd){
    tone_slide(tonePin,freq1,freq2,sirenSpeed);
    tone_slide(tonePin,freq2,freq1,sirenSpeed);
  }
  noTone(tonePin);
}

void ConnorKit::tone_noise(uint8_t tonePin, uint16_t duration) {
  uint16_t y = 0;
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

uint8_t ConnorKit::interpolate(uint8_t val1, uint8_t val2, float fader){
  fader = fader/100.0;
  return val1*(1.00-fader) + val2*fader;
}

int16_t ConnorKit::interpolate(int16_t val1, int16_t val2, float fader){
  fader = fader/100.0;
  return val1*(1.00-fader) + val2*fader;
}

float ConnorKit::interpolate(float val1, float val2, float fader){
  fader = fader/100.0;
  return val1*(1.00-fader) + val2*fader;
}

void ConnorKit::soft_reset(uint8_t soft_reset_bypass){
	void(* restart_func) (void) = 0; //declare reset function @ address 0
	
	pinMode(soft_reset_bypass,INPUT_PULLUP);
	if(digitalRead(soft_reset_bypass) != LOW){
		restart_func();
	}
}

/** @ingroup math
Prints a text-based graph to the Serial Monitor, plotting a value between a minimum and maximum over time, at a specified width of characters.

Example output:
<pre>
0|            +                                        | 1023	1543.00
0|                +                                    | 1023	1546.00
0|                 +                                   | 1023	1549.00
0|              +                                      | 1023	1551.00
0|          +                                          | 1023	1554.00
0|         +                                           | 1023	1557.00
0|             +                                       | 1023	1560.00
0|                +                                    | 1023	1563.00
0|                 +                                   | 1023	1565.00
0|             +                                       | 1023	1568.00
0|          +                                          | 1023	1571.00
0|         +                                           | 1023	1574.00
0|              +                                      | 1023	1576.00
0|                 +                                   | 1023	1580.00
0|                +                                    | 1023	1583.00
0|            +                                        | 1023	1586.00
0|          +                                          | 1023	1588.00
0|          +                                          | 1023	1591.00
0|              +                                      | 1023	1594.00
0|                 +                                   | 1023	1597.00
0|                +                                    | 1023	1600.00
0|            +                                        | 1023	1602.00
0|         +                                           | 1023	1605.00
0|          +                                          | 1023	1608.00
</pre>

@param val The value to plot
@param mn The minimum value measurable
@param mx The maximum value measurable
@param time Can be used to log time, or the value of any variable.
@param graph_width The width of the graph in characters.
@param point The character used to mark val.
*/
void ConnorKit::print_graph(uint16_t val, uint16_t mn, uint16_t mx, float time, uint16_t graph_width, char point){
  float divisor = graph_width/float(mx);
  uint16_t mnG = mn*divisor;
  uint16_t valG = val*divisor;
  uint16_t mxG = mx*divisor;
  
  Serial.print(mn);
  Serial.print(F("| "));
  uint16_t index = mnG;
  while(index<=mxG){
    if(index == valG){
      Serial.print(point);
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

/** @ingroup misc
Measures the amount of time in microseconds that a function takes to complete
@param func The function to measure execution time on. For example, "measure_time(helloWorldFunc)".
@return The execution time in microseconds
*/
long ConnorKit::measure_func_us(void (*func)()){
  long tStart = micros();
  func();
  long tEnd = micros();
  return (tEnd-tStart);
}

float ConnorKit::measure_tx_us(uint16_t message_len, float baud){
  float bitTime = 1.0/float(baud);
  float printTime = bitTime*message_len;
  return printTime*1000000;
}

void ConnorKit::pulse(uint8_t pin, uint8_t state, unsigned long time){
	unsigned long tStart = micros();
	unsigned long tEnd = tStart+time;
	digitalWrite(pin,state);
	while(micros() < tEnd){
		// WAIT
	}
	digitalWrite(pin,!state);	
}

void ConnorKit::byte_to_bin(byte input, byte output[]) {
  for(byte i = 0; i < 8; i++){
    output[i] = char(bitRead(input,7-i));
  }
}

byte ConnorKit::bin_to_byte(byte input[]) {
  byte output = 0;
  for(byte i = 0; i < 8; i++){
    bitWrite(output,7-i,input[i]);
  }
  return output;
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
void ConnorKit::fadeColor_PWM(uint8_t rStart, uint8_t gStart, uint8_t bStart,   uint8_t rEnd, uint8_t gEnd, uint8_t bEnd,   uint8_t rPin, uint8_t gPin, uint8_t bPin,   uint16_t duration) {
  float progress = 0;
  float push = 100.0 / float(duration);
  while (progress < 1) {
    uint8_t rVal = interpolate(rStart,rEnd,progress);
    uint8_t gVal = interpolate(rStart,rEnd,progress);
    uint8_t bVal = interpolate(rStart,rEnd,progress);

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