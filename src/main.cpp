#include <Arduino.h>

#define LED_PIN 2
#define BUTTON_PIN 13
#define CHN 0
#define FRQ 1000
#define PWM_BIT 12

const int MAX_DUTY = (1 << PWM_BIT) - 1;
const int FADE_STEPS = 255;  // brightness range, independent of PWM resolution
const unsigned long DEBOUNCE_MS = 30;
const unsigned long FADE_STEP_MS = 10;

int lastButton = HIGH;
unsigned long lastDebounce = 0;

int target = 0;
int brightness = 0;
unsigned long lastStep = 0;

// Gamma 2 curve: maps linear brightness (0..FADE_STEPS) to PWM duty (0..MAX_DUTY)
int toDuty(int b) {
  return (b * b * MAX_DUTY) / (FADE_STEPS * FADE_STEPS);
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT);
  ledcAttachChannel(LED_PIN, FRQ, PWM_BIT, CHN);
  Serial.printf("Lamp started on GPIO%d, button on GPIO%d\n", LED_PIN, BUTTON_PIN);
}

void loop() {
  unsigned long now = millis();

  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastButton && now - lastDebounce > DEBOUNCE_MS) {
    lastDebounce = now;
    lastButton = reading;
    if (lastButton == LOW) {
      Serial.println("pressed");
      target = (target == 0) ? FADE_STEPS : 0;
    }
  }

  if (now - lastStep >= FADE_STEP_MS) {
    lastStep = now;
    if (brightness != target) {
      brightness += (brightness < target) ? 1 : -1;
      ledcWrite(LED_PIN, toDuty(brightness));
    }
  }
}
