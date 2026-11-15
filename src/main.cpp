#include <Arduino.h>

#define LED_PIN 2
#define BUTTON_PIN 13

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  Serial.printf("Blink started on GPIO%d, PSRAM: %lu bytes\n", LED_PIN, (unsigned long)ESP.getPsramSize());
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED ON");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED OFF");
  }
}
