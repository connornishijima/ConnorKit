#include "connorkit.h"
ConnorKit ck;

unsigned long tStart = 0;
unsigned long tEnd = 0;

char* divider = "#############################################################################";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000);
  randomSeed(analogRead(A0));

  Serial.println(divider);
  Serial.println();
  Serial.println(F(" .d8888b.                                              888    d8P  d8b 888"));
  Serial.println(F("d88P  Y88b                                             888   d8P   Y8P 888"));
  Serial.println(F("888    888                                             888  d8P        888"));
  Serial.println(F("888         .d88b.  88888b.  88888b.   .d88b.  888d888 888d88K     888 888888"));
  Serial.println(F("888        d88''88b 888 '88b 888 '88b d88''88b 888P'   8888888b    888 888"));
  Serial.println(F("888    888 888  888 888  888 888  888 888  888 888     888  Y88b   888 888"));
  Serial.println(F("Y88b  d88P Y88..88P 888  888 888  888 Y88..88P 888     888   Y88b  888 Y88b."));
  Serial.println(F(" 'Y8888P'   'Y88P'  888  888 888  888  'Y88P'  888     888    Y88b 888  'Y888"));
  Serial.println();
  Serial.println(F("The Arduino Swiss Army Knife!"));
  Serial.println();
  Serial.println(divider);
  Serial.println();
  delay(3000);
  Serial.println("Over the years I've had to roll many of my own Arduino functions");
  Serial.println("to solve some interesting or tedious problems, and I've decided");
  Serial.println("to put all of these solutions into a single, easy-to-use Arduino");
  Serial.println("library. Don't worry - the only flash and RAM space it takes are");
  Serial.println("the functions you actually use! The compiler is smart enough to");
  Serial.println("ignore everything else.\n");
  
  Serial.println("Let's start with some array tools!\n");
  
  byte count = 15;
  while(count > 0){
	Serial.print(count);
	Serial.println("...");
	delay(1000);
	count--;
  }
  Serial.println();
  delay(1000);

  array_demo(true);
  array_demo(false);
  Serial.println(divider);
  Serial.println();
  delay(3000);
  Serial.print("If you blinked, you missed it! For an example of speed, the sorting function took only ");
  Serial.print(float(tEnd - tStart) / 1000.0);
  Serial.println(" milliseconds!\n");
  delay(5000);
  Serial.println(F("What the hell, here's some more sorts for good measure:"));
  delay(5000);
  byte testArray[16];
  for (byte x = 0; x < 255; x++) {
    for (byte i = 0; i < 16; i++) {
      testArray[i] = random(0, 256);
    }
    Serial.print("Random: ");
    ck.array_print(testArray);
    ck.array_sort(testArray);
    Serial.print("Sorted: ");
    ck.array_print(testArray);
    Serial.println();
  }

  delay(2000);
  Serial.println("Damn, that felt good.");
  delay(1000);
  Serial.println("Let's try the math tools.\n");
  delay(2000);

  math_demo();

  delay(3000);
  Serial.println("That about wraps things up!");
  delay(3000);
  Serial.println("Oh wait, how about we check if Pin 6 is LOW?");
  Serial.println("If it isn't, ck.soft_reset(6) is about to software-reset the AVR!");
  count = 10;
  while(count > 0){
    Serial.print(count);
    Serial.println("...");
  }
  ck.soft_reset(6);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void math_demo() {
  Serial.println(divider);
  Serial.println(F("MATH TOOLS:"));
  Serial.println(divider);
  Serial.println();
  delay(2000);
  uint16_t val1 = random(0, 300);
  uint16_t val2 = random(50700, 60000);
  Serial.print("Say we have two numbers: ");
  Serial.print(val1);
  Serial.print(" and ");
  Serial.print(val2);
  Serial.println(".\n");

  delay(3000);

  Serial.println("We can interpolate between the two with ck.interpolate():\n");
  delay(5000);
  byte fades = 0;
  while (fades < 3) {
    for (float i = 0; i < 1; i += 0.02) {
      Serial.print("Percent: ");
      Serial.print(int(i * 100));
      Serial.print("\t");
      float x = i;
      while (x > 0) {
        Serial.print(' ');
        x -= 0.02;
      }
      Serial.println(ck.interpolate(val1, val2, i * 100));
      delay(50);
    }

    for (float i = 1; i > 0; i -= 0.02) {
      Serial.print("Percent: ");
      Serial.print(int(i * 100));
      Serial.print("\t");
      float x = i;
      while (x > 0) {
        Serial.print(' ');
        x -= 0.02;
      }
      Serial.println(ck.interpolate(val1, val2, i * 100));
      delay(50);
    }

    fades++;
  }
}

void array_demo(bool demo_wait) {
  Serial.println(divider);
  Serial.println(F("ARRAY TOOLS:"));
  Serial.println(divider);
  Serial.println();

  wait(3000, demo_wait);

  byte testArray[16];
  ck.array_fill(testArray, 0);
  Serial.print("Here's our array: "); ck.array_print(testArray);
  wait(3000, demo_wait);
  Serial.println("It's easily printed with ck.array_print()!\n");
  wait(3000, demo_wait);
  Serial.println("Lets shift in some random values with ck.array_shift()...\n");
  wait(3000, demo_wait);
  for (byte i = 0; i < 16; i++) {
    ck.array_shift(testArray, random(0, 100 + 1));
    ck.array_print(testArray);
    wait(100, demo_wait);
  }
  Serial.println();
  Serial.println("Good! Now we'll sort it with ck.array_sort():");
  Serial.println();
  wait(1000, demo_wait);
  if(demo_wait){
    tStart = micros();
    ck.array_sort(testArray);
    tEnd = micros();
  }
  else{
    ck.array_sort(testArray);
  }
  ck.array_print(testArray);
  wait(3000, demo_wait);

  Serial.println();
  Serial.println("Let's reverse it too with ck.array_reverse():");
  Serial.println();
  wait(1000, demo_wait);
  ck.array_reverse(testArray);
  ck.array_print(testArray);
  wait(3000, demo_wait);

  if (demo_wait == true) {
    Serial.println();
    Serial.print("This array demo used huge delays for readability, here's the functions at full speed! ");
    wait(3000, demo_wait);
    byte count = 5;
    while (count > 0) {
      Serial.print(count);
      Serial.print("... ");
      wait(1000, demo_wait);
      count--;
    }
  }
  Serial.println("\n");
}

void wait(uint16_t mil, bool demo_wait) {
  if (demo_wait == true) {
    delay(mil);
  }
}
