Assignment A: 6-DOF Robot Arm (6 Servos + 6 Potentiometers)

Course topic: Class 3, Actuators & Servo Motion Platform: Tinkercad Circuits Board: Arduino Uno R3 Simulation link: [paste your Tinkercad link here]

1. Project Overview

This project simulates a robot arm with 6 degrees of freedom (6-DOF). Each joint of the arm is driven by one servo motor, and each servo is controlled by its own potentiometer (knob). Turning a knob makes the matching servo turn to the same position.

A "degree of freedom" is one independent way a part can move. Six servos means six independent movements, just like the joints of a real robot arm.

The six joints
Joint	Servo	What it does
1. Base	Servo 1	Rotates the whole arm left and right
2. Shoulder	Servo 2	Lifts the arm up and down
3. Elbow	Servo 3	Bends the middle of the arm
4. Wrist pitch	Servo 4	Tilts the hand up and down
5. Wrist roll	Servo 5	Rotates the hand
6. Gripper	Servo 6	Opens and closes the claw
2. Components Used
Component	Quantity	Notes
Arduino Uno R3	1	Microcontroller (the brain)
Micro Servo	6	Actuators (the joints)
Potentiometer	6	Set to 10 kΩ, used as input knobs
Breadboard	1	Shares 5V and GND between all parts
Jumper wires	Many	Connections
3. Circuit and Wiring
Power
Arduino 5V to the breadboard red (+) rail
Arduino GND to the breadboard blue (−) rail
The top and bottom rails of the breadboard are linked with wires so every part gets power.
Potentiometers (inputs)

Each potentiometer has three pins:

Left pin to GND rail
Right pin to 5V rail
Middle pin (wiper) to an Arduino analog pin
Servos (outputs)

Each servo has three wires:

Brown to GND rail
Red to 5V rail
Orange (signal) to an Arduino PWM pin
Pin mapping
Joint	Potentiometer (analog in)	Servo signal (PWM out)
Base	A0	D3
Shoulder	A1	D5
Elbow	A2	D6
Wrist pitch	A3	D9
Wrist roll	A4	D10
Gripper	A5	D11
Screenshot of the circuit

(6-DOF-Robot-Arm-circuit-diagram.png)


4. How It Works

The Arduino repeats three steps for every joint, over and over:

Read the knob → convert the number to an angle → move the servo

Potentiometer as a voltage divider. With 0V on one end and 5V on the other, the middle pin outputs a voltage between 0V and 5V depending on the knob position.
Analog-to-digital conversion. analogRead() converts that voltage into a number from 0 to 1023 (the Uno's ADC has 10 bits, which gives 1024 steps).
Scaling with map(). A servo needs an angle from 0 to 180 degrees, so map() rescales 0 to 1023 into 0 to 180.
Moving the servo. write(angle) makes the Servo library send a PWM pulse (roughly 1 ms for 0 degrees up to 2 ms for 180 degrees, repeated every 20 ms). The servo's internal circuit turns the motor until it reaches that angle.
5. Code

File: robot_arm.ino

cpp
#include <Servo.h>                                   // library that generates servo signals

const int NUM_SERVOS = 6;                            // number of joints
const int servoPins[NUM_SERVOS] = {3, 5, 6, 9, 10, 11};     // servo signal pins
const int potPins[NUM_SERVOS]   = {A0, A1, A2, A3, A4, A5}; // potentiometer pins

Servo joints[NUM_SERVOS];                            // one Servo object per joint

void setup() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    joints[i].attach(servoPins[i]);                  // link each servo object to its pin
  }
}

void loop() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    int raw = analogRead(potPins[i]);                // read knob: 0 to 1023
    int angle = map(raw, 0, 1023, 0, 180);           // convert to 0 to 180 degrees
    joints[i].write(angle);                          // move the servo
  }
  delay(15);                                         // short pause so servos can move
}
Line-by-line summary
Code	What it does
#include <Servo.h>	Loads the Servo library
NUM_SERVOS = 6	Stores how many servos we have
servoPins[]	List of the pins the servos are connected to
potPins[]	List of the pins the potentiometers are connected to
Servo joints[]	Creates 6 servo objects
setup()	Runs once at start
attach()	Tells each servo object which pin to use
loop()	Runs forever
for (...)	Repeats the steps for all 6 joints
analogRead()	Reads the knob position as 0 to 1023
map()	Converts 0 to 1023 into 0 to 180
write()	Sends the angle to the servo
delay(15)	Waits 15 ms before the next round

Because servoPins[i] and potPins[i] share the same index, pot 1 always controls servo 1, pot 2 controls servo 2, and so on.

6. How to Run
Open the Tinkercad link above (or rebuild the circuit using the wiring section).
Click Start Simulation.
Click each potentiometer and drag its knob.
Watch the matching servo rotate.
7. Issues Faced and How I Solved Them

(Fill this in with your own experience. Example: "At first the top three servos did not move. I [what you checked] and found [the cause]. I fixed it by [the fix].")

8. What I Learned
How a potentiometer produces a changing voltage
How the Arduino converts a voltage to a number with analogRead()
How map() converts one range of numbers to another
How servos are controlled with PWM signals
How arrays and for loops let one block of code control six joints
9. Possible Improvements
Smooth the movement by averaging several readings
Only update a servo when its angle changes by 2 or more degrees, to reduce jitter
On real hardware, power the servos from an external 5V supply (six servos draw more current than the Arduino's 5V pin can supply) and share GND with the Arduino
