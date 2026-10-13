#include <Servo.h>

const int NUM_SERVOS = 6;
const int servoPins[NUM_SERVOS] = {3, 5, 6, 9, 10, 11};
const int potPins[NUM_SERVOS]   = {A0, A1, A2, A3, A4, A5};

Servo joints[NUM_SERVOS];

void setup() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    joints[i].attach(servoPins[i]);
  }
}

void loop() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    int raw = analogRead(potPins[i]);
    int angle = map(raw, 0, 1023, 0, 180);
    joints[i].write(angle);
  }
  delay(15);
}
