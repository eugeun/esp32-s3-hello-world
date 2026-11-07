#include <Arduino.h>

#ifndef LED_PIN
#define LED_PIN 2
#endif

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  Serial.printf("Blink started on GPIO%d, PSRAM: %u bytes\n", LED_PIN, ESP.getPsramSize());
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED ON");
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED OFF");
  delay(1000);
}
