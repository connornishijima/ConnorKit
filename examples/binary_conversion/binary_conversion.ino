#include "connorkit.h"
ConnorKit ck;

void setup()
{
  Serial.begin(250000);
  byte bin_array[8];

  String input = "BE SURE TO DRINK YOUR OVALTINE";

  byte message[input.length()];
  input.toCharArray(message,len(message)+1);

  for (byte i = 0; i < len(message); i++) {
    ck.byte_to_bin(message[i],bin_array);
    Serial.print(char(ck.bin_to_byte(bin_array)));
    Serial.print("  |  ");
    ck.array_print(bin_array,len(bin_array),char(0));
  }
}

void loop()
{
}