// Traffic Light Controller
// Pin assignments
const int redPin    = 8;
const int yellowPin = 9;
const int greenPin  = 10;

// Timing durations (in milliseconds)
const int redDuration    = 4000; // 4 seconds
const int greenDuration  = 4000; // 4 seconds
const int yellowDuration = 1500; // 1.5 seconds

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  // RED ON
  digitalWrite(redPin, HIGH);
  delay(redDuration);
  digitalWrite(redPin, LOW);

  // GREEN ON
  digitalWrite(greenPin, HIGH);
  delay(greenDuration);
  digitalWrite(greenPin, LOW);

  // YELLOW ON
  digitalWrite(yellowPin, HIGH);
  delay(yellowDuration);
  digitalWrite(yellowPin, LOW);
}
