#include <AFMotor.h>

// Create motor objects for Adafruit Motor Shield V1
AF_DCMotor motor1(1);  // Motor port M1
AF_DCMotor motor2(2);  // Motor port M2
AF_DCMotor motor3(3);  // Motor port M3
AF_DCMotor motor4(4);  // Motor port M4

char command;  // Bluetooth input

void setup() {

  // Set initial motor speeds (0–255)
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);
}

void loop() {
    if (Serial.available()) {
    command = Serial.read();    // Read from HC-06
    
    switch (command) {
      case 'F':  // Forward
        motor1.run(BACKWARD);
        motor2.run(BACKWARD);
        motor3.run(BACKWARD);
        motor4.run(BACKWARD);
        break;

      case 'B':  // Backward
        motor1.run(FORWARD);
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(FORWARD);
        break;

      case 'L':  // Left
        motor1.run(BACKWARD);
        motor2.run(BACKWARD);
        motor3.run(RELEASE);
        motor4.run(RELEASE);
        break;

      case 'R':  // Right
        motor1.run(RELEASE);
        motor2.run(RELEASE);
        motor3.run(BACKWARD);
        motor4.run(BACKWARD);
        break;

      case 'S':  // Stop
        motor1.run(RELEASE);
        motor2.run(RELEASE);
        motor3.run(RELEASE);
        motor4.run(RELEASE);
        break;
    }
  }
}
