#include "connorkit.h"
ConnorKit ck;

byte test[16];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000);
  ck.array_fill_byte(test,16,255);
}

void loop() {
  // put your main code here, to run repeatedly:
  ck.shiftOntoEnd_byte(test,16,millis());cannot convert byte* to int* for argument
  Serial.println(ck.array_sum_byte(test,16));
}
