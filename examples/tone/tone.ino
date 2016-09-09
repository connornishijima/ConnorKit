// Tone functions demo

#include "connorkit.h"
ConnorKit ck;

void setup() {
  Serial.begin(250000);
}

void loop() {
  ck.tone_noise(13, 1000);
  delay(1000);
  
  ck.tone_slide(13,440,880,1000,false);
  delay(1000);

  const int freqs1[] = {440,880,1760};
  ck.tone_multi_zx(13,freqs1,len(freqs1),15,1000);
  const int freqs2[] = {523,1046,2093};
  ck.tone_multi_zx(13,freqs2,len(freqs2),15,1000);
  delay(1000);
  
  ck.tone_siren(13,635,1112,400,3000);
  ck.tone_siren(13,635,912*2,100,1000);
  ck.tone_siren(13,635,912*2,40,1000);
  ck.tone_siren(13,635,1112,400,3000);
  delay(1000);
  
  ck.tone_arp(13,880,100,5000);
  ck.tone_arp(13,1046,100,5000);
  ck.tone_arp(13,1318,100,5000);
  delay(1000);
}