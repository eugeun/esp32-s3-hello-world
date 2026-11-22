#include <Arduino.h>

#define LED_PIN 2
#define BUTTON_PIN 13
#define CHN 0
#define FRQ 1000
#define PWM_BIT 8

int lastButtonState = HIGH;
unsigned long lastChangeTimeStamp = 0;
int debounceTimeout = 30;

int target = 0;
int brightness = 0;
int maxIteration = 255;
int lastStep = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT);
  ledcAttachChannel(LED_PIN, FRQ, PWM_BIT, CHN);
  Serial.printf("Blink started on GPIO%d, PSRAM: %lu bytes\n", LED_PIN, (unsigned long)ESP.getPsramSize());
}

void loop() {
  int currentButtonState = digitalRead(BUTTON_PIN);
  if (currentButtonState != lastButtonState) {
    unsigned long now = millis();
    if (now - lastChangeTimeStamp > debounceTimeout) {
      lastButtonState = currentButtonState;
      lastChangeTimeStamp = now;
      if (lastButtonState == LOW) {
        Serial.printf("pressed\n");
        target = (target == 0) ? 255 : 0;
      }
    }
  }
  if (millis() - lastStep >= 10) {
    lastStep = millis();
    if (brightness < target) ledcWrite(LED_PIN, ++brightness);
    else if (brightness > target) ledcWrite(LED_PIN, --brightness);
  } 
}