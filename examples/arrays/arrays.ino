// CK Array Functions demo
// by Connor Nishijima
//
// This sketch uses the Serial Plotter to show the read of Pin A0, and
// the average of the last 128 samples. Connect a 6-12in wire to A0,
// and leave it as an open antenna. Now watch the output when you walk
// past the Arduino!

#include "connorkit.h"
ConnorKit ck;
int storage[64];

void setup() {
  Serial.begin(250000);
  ck.array_fill(storage,len(storage),255);
}

void loop() {
  int val = analogRead(A0);
  ck.array_shift(storage,len(storage),val);
  int average = ck.array_average(storage,len(storage));

  Serial.print(val); Serial.print("\t1023\t"); Serial.println(average);
}

//###################################################################
// ------------------------------------------------------------------
// Acheiving the same effect without CK: line count increased by 200%
/*
int storage[128];
int length = sizeof(storage)*4

void setup() {
  Serial.begin(250000);
  for(byte i = 0; i < 128; i++){
    storage[i] = 255;
  }
}

void loop() {
  int val = analogRead(A0);
  for(byte i = 0; i < 128-1; i++){
    storage[i] = storage[i+1];
  }
  storage[127] = val;

  long sum = 0;
  for(byte i = 0; i < 128; i++){
    sum+=storage[i];
  }
  int average = sum/128; 

  Serial.print(val); Serial.print("\t1023\t"); Serial.println(average);
}
*/
// ------------------------------------------------------------------