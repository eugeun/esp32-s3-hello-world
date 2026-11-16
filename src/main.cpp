#include <Arduino.h>

#define LED_PIN 2
#define BUTTON_PIN 13

void reverseGPIO(int pin) {
  digitalWrite(pin, ! digitalRead(pin));
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  Serial.printf("Blink started on GPIO%d, PSRAM: %lu bytes\n", LED_PIN, (unsigned long)ESP.getPsramSize());
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(20);
    if (digitalRead(BUTTON_PIN) == LOW) {
      reverseGPIO(LED_PIN);
    }
    while(digitalRead(BUTTON_PIN) == LOW);
    delay(20);
    //while(digitalRead(BUTTON_PIN) == LOW);
  }
}