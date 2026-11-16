#include <Arduino.h>

#define LED_PIN 2
#define BUTTON_PIN 13
#define CHN 0
#define FRQ 1000
#define PWM_BIT 8

int lastState = 0;

void reverseBreath(int pin) {
  if (lastState == 0) {
    for(int i=0; i<255; i++) {
      ledcWrite(LED_PIN, i);
      delay(10);
    }
    lastState = 1;
  } else {
    for(int i=254; i>-1; i--) {
      ledcWrite(LED_PIN, i);
      delay(10);
    }
    lastState = 0;

  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  ledcAttachChannel(LED_PIN, FRQ, PWM_BIT, CHN);
  Serial.printf("Blink started on GPIO%d, PSRAM: %lu bytes\n", LED_PIN, (unsigned long)ESP.getPsramSize());
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(20);
    if (digitalRead(BUTTON_PIN) == LOW) {
      reverseBreath(LED_PIN);
    }
    while(digitalRead(BUTTON_PIN) == LOW);
    delay(20);
  }
}