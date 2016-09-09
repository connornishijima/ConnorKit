#include "connorkit.h"
ConnorKit ck;

byte test[16];

void setup() {
  Serial.begin(250000);
  ck.array_fill_byte(test,16,255);
}

void loop() {
  ck.array_shift_byte(test,16,millis());
  ck.array_print_byte(test,16,',');
}