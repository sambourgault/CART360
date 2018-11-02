/*
  Stepper Motor Control - one revolution

  This program drives a unipolar or bipolar stepper motor.
  The motor is attached to digital pins 8 - 11 of the Arduino.

  The motor should revolve one revolution in one direction, then
  one revolution in the other direction.


  Created 11 Mar. 2007
  Modified 30 Nov. 2009
  by Tom Igoe

*/

#include <Stepper.h>
const int RUNNING_SAMPLES = 16;
const int SENSE_PIN = 0;
int runningAverageBuffer[RUNNING_SAMPLES];
int nextCount = 0;
int countRevolution = 1;
bool increasing = true;

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
Stepper myStepper2(stepsPerRevolution, 2, 3, 5, 6);

unsigned long startTime;


void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(40);
  myStepper2.setSpeed(40);
  // initialize the serial port:
  Serial.begin(9600);
  startTime = millis();
}

void loop() {
  // proximity sensor
  int rawSenseVal = analogRead(SENSE_PIN);
  runningAverageBuffer[nextCount] = rawSenseVal;
  nextCount++;

  if (nextCount >= RUNNING_SAMPLES) {
    nextCount = 0;
  }

  int currentSum = 0;
  for (int i = 0; i < RUNNING_SAMPLES; i++) {
    currentSum += runningAverageBuffer[i];
  }

  int averageVal = currentSum / RUNNING_SAMPLES;
  //Serial.println(averageVal);
  delay(10);

  // motor code
  // step one revolution  in one direction:


  /*if (millis() - startTime > 5000) {
    myStepper.step(-stepsPerRevolution);
    } else {*/

  /*}*/
  if (increasing) {
    myStepper.step(stepsPerRevolution);
    myStepper2.step(stepsPerRevolution);
    countRevolution += 1;
  } else {
    myStepper.step(-stepsPerRevolution);
    myStepper2.step(-stepsPerRevolution);
    countRevolution -= 1;
  }

Serial.println(countRevolution);

  if (countRevolution > 6) {
    increasing = false;
  } else if (countRevolution < 1) {
    increasing = true;
  }
  delay(10);



  // step one revolution in the other direction:
  //Serial.println("counterclockwise");
  //  myStepper.step(-stepsPerRevolution);
  // delay(500);
}
