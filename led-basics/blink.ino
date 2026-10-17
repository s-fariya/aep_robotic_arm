// Week 1: Your First Blink Sketch
// This program turns a breadboard LED on and off repeatedly.

const int ledPin = 13; // We've wired our LED anode to Pin 13

void setup() {
  // Setup code runs once when the board receives power or resets.
  // We configure Pin 13 to act as an OUTPUT (sending electricity out).
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Loop code runs repeatedly in an endless cycle.
  digitalWrite(ledPin, HIGH); // Send 5V to Pin 13 (Turn the LED ON)
  delay(1000);                // Keep the LED on for 1 second (1000 ms)
  digitalWrite(ledPin, LOW);  // Pull Pin 13 down to 0V (Turn the LED OFF)
  delay(1000);                // Keep the LED off for 1 second
}
