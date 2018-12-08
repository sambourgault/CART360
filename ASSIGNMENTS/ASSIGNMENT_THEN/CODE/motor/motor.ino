// Arduino pins for the motor control connection
int motor_pin_1 = 8;
int motor_pin_2 = 9;
int motor_pin_3 = 10;
int motor_pin_4 = 11;

// change direction variables
unsigned long changeDirectionAfter1;
bool changeDirectionMotor1 = true;

// motor state
int thisStep = 0;

void setup() {
  // setup the pins for the motor on the microcontroller
  pinMode(motor_pin_1, OUTPUT);
  pinMode(motor_pin_2, OUTPUT);
  pinMode(motor_pin_3, OUTPUT);
  pinMode(motor_pin_4, OUTPUT);
  
  // begin serial communication
  Serial.begin(9600);
}

void loop() {
  // motor 1:
  switch (thisStep) {
    case 0:  // 1010
      digitalWrite(motor_pin_1, HIGH);
      digitalWrite(motor_pin_2, LOW);
      digitalWrite(motor_pin_3, HIGH);
      digitalWrite(motor_pin_4, LOW);
      break;
    case 1:  // 0110
      digitalWrite(motor_pin_1, LOW);
      digitalWrite(motor_pin_2, HIGH);
      digitalWrite(motor_pin_3, HIGH);
      digitalWrite(motor_pin_4, LOW);
      break;
    case 2:  //0101
      digitalWrite(motor_pin_1, LOW);
      digitalWrite(motor_pin_2, HIGH);
      digitalWrite(motor_pin_3, LOW);
      digitalWrite(motor_pin_4, HIGH);
      break;
    case 3:  //1001
      digitalWrite(motor_pin_1, HIGH);
      digitalWrite(motor_pin_2, LOW);
      digitalWrite(motor_pin_3, LOW);
      digitalWrite(motor_pin_4, HIGH);
      break;
  }

  delay(100);

  // change direction
  if (changeDirectionMotor1) {
    // turn forward
    thisStep = (thisStep + 1) % 4;
  } else {
    // turn backward
    thisStep = ((thisStep - 1) + 4) % 4;
    // 0 - 3 // 3 - 2 // 2 - 1 // 1 - 0 //
  }
}
