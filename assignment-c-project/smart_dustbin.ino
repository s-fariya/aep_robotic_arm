#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 6
#define GREEN_LED 7
#define RED_LED 8
#define BUTTON_PIN 2

const int OPEN_DISTANCE = 20;
const int CLOSED_ANGLE = 0;
const int OPEN_ANGLE = 90;
const int NUM_READINGS = 5;

Servo lid;
int currentAngle = CLOSED_ANGLE;

long readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  return duration * 0.034 / 2;
}

long averageDistance() {
  long total = 0;
  int valid = 0;
  for (int i = 0; i < NUM_READINGS; i++) {
    long d = readDistance();
    if (d > 0 && d <= 400) {
      total += d;
      valid++;
    }
    delay(10);
  }
  if (valid == 0) return 0;
  return total / valid;
}

void setLeds(bool lidOpen) {
  if (lidOpen) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }
}

void moveLidTo(int target) {
  setLeds(target == OPEN_ANGLE);
  while (currentAngle != target) {
    if (currentAngle < target) currentAngle++;
    else currentAngle--;
    lid.write(currentAngle);
    delay(10);
  }
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lid.attach(SERVO_PIN);
  lid.write(CLOSED_ANGLE);
  setLeds(false);
  Serial.begin(9600);
}

void loop() {
  bool holdOpen = (digitalRead(BUTTON_PIN) == LOW);

  if (holdOpen) {
    Serial.println("Button held: lid kept open");
    moveLidTo(OPEN_ANGLE);
  } else {
    long distance = averageDistance();

    if (distance == 0) {
      Serial.println("Out of range");
      moveLidTo(CLOSED_ANGLE);
    } else {
      Serial.print("Distance (cm): ");
      Serial.println(distance);
      if (distance < OPEN_DISTANCE) {
        moveLidTo(OPEN_ANGLE);
      } else {
        moveLidTo(CLOSED_ANGLE);
      }
    }
  }
  delay(100);
}
