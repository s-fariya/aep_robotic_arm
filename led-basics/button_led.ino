// Button LED: the LED is on while the button is pressed

int buttonState = 0;       // stores whether the button is pressed

void setup() {
  pinMode(2, INPUT);       // button is connected to pin 2 (input)
  pinMode(13, OUTPUT);     // LED is connected to pin 13 (output)
}

void loop() {
  buttonState = digitalRead(2);   // read the button (HIGH = pressed)

  if (buttonState == HIGH) {
    digitalWrite(13, HIGH);       // button pressed: LED on
  } else {
    digitalWrite(13, LOW);        // button not pressed: LED off
  }

  delay(15);                      // short pause to keep the simulation smooth
}
