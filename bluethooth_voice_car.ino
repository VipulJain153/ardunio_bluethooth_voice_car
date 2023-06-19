#include <SoftwareSerial.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *myMotorOne = AFMS.getMotor(1);  // Motor number depends on the connection to the motor driver module
Adafruit_DCMotor *myMotorTwo = AFMS.getMotor(2);  // Motor number depends on the connection to the motor driver module
Adafruit_DCMotor *myMotorThree = AFMS.getMotor(3);  // Motor number depends on the connection to the motor driver module
Adafruit_DCMotor *myMotorFourth = AFMS.getMotor(4);  // Motor number depends on the connection to the motor driver module

SoftwareSerial bluetooth(2, 3); // RX, TX pins for Bluetooth moduleIf prompted, enter a pairing code. Some Bluetooth modules have a default code like "1234" or "0000".

char[] command;

void move(auto dir){
    myMotorOne->run(dir);
    myMotorTwo->run(dir);
    myMotorThree->run(dir);
    myMotorFourth->run(dir);
    delay(1000);
}

void setup() {
  Serial.begin(9600);         // Initialize serial communication with the computer
  bluetooth.begin(9600); 
  AFMS.begin();// Initialize serial communication with the Bluetooth module
}

void sendResponse(const String& response) {
  bluetooth.print(response);
}

void loop() {
  if (bluetooth.available()) {
    command = bluetooth.readString();
  }
  command.toLowerCase();
  if (command=="forward" || command=="move forward"){
    move(FORWARD);
  } else if (command=="backward" || command=="move backward"){
    move(BACKWARD);
  } else if (command=="left" || command=="move left"){
    myMotorOne->run(FORWARD);
    myMotorTwo->run(BACKWARD);
    myMotorThree->run(FORWARD);
    myMotorFourth->run(BACKWARD);
    delay(1000);
  } else if (command=="right" || command=="move right"){
    myMotorOne->run(BACKWARD);
    myMotorTwo->run(FORWARD);
    myMotorThree->run(BACKWARD);
    myMotorFourth->run(FORWARD);
    delay(1000);
  } else {
    move(RELEASE);
  }
}
