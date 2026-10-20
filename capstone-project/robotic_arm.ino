#include <Servo.h>

const int TRIG = 7, ECHO = 8;
const int BUZZER = 4;
const int BTN = 2;
const int POT_BASE = A0;
const int POT_REACH = A1;
const int PIN_BASE = 9, PIN_SHOULDER = 10, PIN_ELBOW = 11, PIN_GRIP = 6;

Servo base, shoulder, elbow, grip;

bool autoMode = false;
int curBase = 90, curShoulder = 90, curElbow = 90, curGrip = 30;
const int GRIP_OPEN = 30, GRIP_CLOSED = 90;
const int DETECT_CM = 20;
const int DANGER_CM = 8;

long readDistanceCm() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long dur = pulseIn(ECHO, HIGH, 30000);
  if (dur == 0) return 999;
  return dur * 0.034 / 2;
}

void beep(int times, int ms) {
  for (int i = 0; i < times; i++) {
    tone(BUZZER, 1000, ms);
    delay(ms * 2);
  }
}

void smoothMove(Servo &s, int &cur, int target, int stepDelay = 12) {
  target = constrain(target, 0, 180);
  while (cur != target) {
    cur += (target > cur) ? 1 : -1;
    s.write(cur);
    delay(stepDelay);
  }
}

void goHome() {
  smoothMove(shoulder, curShoulder, 90);
  smoothMove(elbow, curElbow, 90);
  smoothMove(base, curBase, 90);
  smoothMove(grip, curGrip, GRIP_OPEN);
}

void checkModeButton() {
  static unsigned long last = 0;
  if (digitalRead(BTN) == LOW && millis() - last > 300) {
    last = millis();
    autoMode = !autoMode;
    Serial.println(autoMode ? "MODE: AUTONOMOUS" : "MODE: MANUAL");
    beep(autoMode ? 2 : 1, 100);
    goHome();
  }
}

void manualMode() {
  int b = map(analogRead(POT_BASE), 0, 1023, 0, 180);
  int r = map(analogRead(POT_REACH), 0, 1023, 40, 140);

  base.write(b);        curBase = b;
  shoulder.write(r);    curShoulder = r;
  elbow.write(180 - r); curElbow = 180 - r;

  long d = readDistanceCm();
  if (d < DANGER_CM) tone(BUZZER, 2000, 80);
  Serial.print("Manual | base="); Serial.print(b);
  Serial.print(" reach="); Serial.print(r);
  Serial.print(" dist="); Serial.println(d);
  delay(30);
}

void pickAndPlace() {
  Serial.println("Object found -> pick & place");
  beep(2, 80);
  smoothMove(grip, curGrip, GRIP_OPEN);
  smoothMove(shoulder, curShoulder, 130);
  smoothMove(elbow, curElbow, 60);
  smoothMove(grip, curGrip, GRIP_CLOSED);
  delay(300);
  smoothMove(shoulder, curShoulder, 80);
  smoothMove(elbow, curElbow, 100);
  smoothMove(base, curBase, 170);
  smoothMove(grip, curGrip, GRIP_OPEN);
  beep(1, 300);
  goHome();
}

void autonomousMode() {
  static int dir = 1;
  curBase += dir * 2;
  if (curBase >= 170 || curBase <= 10) dir = -dir;
  base.write(curBase);

  long d = readDistanceCm();
  Serial.print("Auto scan | angle="); Serial.print(curBase);
  Serial.print(" dist="); Serial.println(d);

  if (d < DETECT_CM) pickAndPlace();
  delay(40);
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT); pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  base.attach(PIN_BASE); shoulder.attach(PIN_SHOULDER);
  elbow.attach(PIN_ELBOW); grip.attach(PIN_GRIP);
  goHome();
  beep(1, 150);
  Serial.println("Robotic arm ready. MODE: MANUAL");
}

void loop() {
  checkModeButton();
  if (autoMode) autonomousMode(); else manualMode();
}
