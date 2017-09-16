#include <Arduino.h>
#include <pgmspace.h>
#include "sounddata.h"

#define SAMPLE_FREQUENCY 8000
#define BITS_PER_SAMPLE 15

int led = D4; // For NodeMcu LED_BUILTIN is D4.
int pwm = D0;

int pulse(int s);

void setup() {
    pinMode(led, OUTPUT);
    pinMode(pwm, OUTPUT);
}


void loop() {
  // unsigned int t = 1000000 / (SAMPLE_FREQUENCY * BITS_PER_SAMPLE);
  unsigned int t = 1000 / (8 * BITS_PER_SAMPLE);

  digitalWrite(led, LOW);
  delay(1000);

  for (unsigned int j = 0; j < sizeof(s); j++) {
    int sample = pgm_read_byte(&s[j]);
    for (unsigned int i = 0; i < BITS_PER_SAMPLE; i++) {
      int p = pulse(sample);
      digitalWrite(pwm, p);
      delayMicroseconds(t);
    }
    if (j % 2000 == 0) {
      // delay(0);
    }
  }

  digitalWrite(led, HIGH);
  delay(1000);
}


static int qe = 0;

int pulse(int s) {
  int y;
  int p;

  if (s >= 128 + qe) {
    y = 255;
    p = HIGH;
  }
  else {
    y = 0;
    p = LOW;
  }

  qe = y - s + qe;

  return p;
}
