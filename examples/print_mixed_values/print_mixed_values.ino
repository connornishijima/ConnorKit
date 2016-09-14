#include "connorkit.h"
ConnorKit ck;

void setup() {
  Serial.begin(250000);
  bool val1 = true;
  byte val2 = 23;
  float val3 = 4.56;
  char* val4 = "78";
  long val5 = 910;

  Serial.println("val1 \tval2 \tval3 \tval4 \tval5");
  print_five(val1,val2,val3,val4,val5);
}

void loop() {
  // put your main code here, to run repeatedly:

}
