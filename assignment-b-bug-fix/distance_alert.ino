#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 5
#define SERVO_PIN 6

Servo myservo;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  myservo.attach(SERVO_PIN);
  myservo.write(0);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  long distance = duration * 0.034 / 2;

  if (distance == 0 || distance > 400) {
    Serial.println("Out of range");
    myservo.write(0);
    noTone(BUZZER_PIN);
  } else {
    Serial.print("Distance (cm): ");
    Serial.println(distance);

    if (distance < 20) {
      myservo.write(90);
      tone(BUZZER_PIN, 1000);
      delay(200);
      noTone(BUZZER_PIN);
    } else {
      myservo.write(0);
      noTone(BUZZER_PIN);
    }
  }

  delay(500);
}
