

int step_number = 0;    // which step the motor is on
int direction = 0;      // motor direction
int last_step_time = 0; // time stamp in us of the last step taken
int number_of_steps = number_of_steps; // total number of steps for this motor

// Arduino pins for the motor control connection:
int motor_pin_1 = 8;
int motor_pin_2 = 9;
int motor_pin_3 = 10;
int motor_pin_4 = 11;
// Arduino pins for the motor2 control connection:
int motor_pin_5 = 2;
int motor_pin_6 = 3;
int motor_pin_7 = 5;
int motor_pin_8 = 6;

// When there are 4 pins, set the others to 0:
//int motor_pin_5 = 0;

// pin_count is used by the stepMotor() method:
int pin_count = 4;
int thisStep = 0;

void setup() {
  // put your setup code here, to run once:
  // setup the pins on the microcontroller:
  pinMode(motor_pin_1, OUTPUT);
  pinMode(motor_pin_2, OUTPUT);
  pinMode(motor_pin_3, OUTPUT);
  pinMode(motor_pin_4, OUTPUT);
  
  pinMode(motor_pin_5, OUTPUT);
  pinMode(motor_pin_6, OUTPUT);
  pinMode(motor_pin_7, OUTPUT);
  pinMode(motor_pin_8, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*if (pin_count == 4) {*/
    switch (thisStep) {
      case 0:  // 1010
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, LOW);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, LOW);

        digitalWrite(motor_pin_5, HIGH);
        digitalWrite(motor_pin_6, LOW);
        digitalWrite(motor_pin_7, HIGH);
        digitalWrite(motor_pin_8, LOW);
        break;
      case 1:  // 0110
        digitalWrite(motor_pin_1, LOW);
        digitalWrite(motor_pin_2, HIGH);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, LOW);

        digitalWrite(motor_pin_5, LOW);
        digitalWrite(motor_pin_6, HIGH);
        digitalWrite(motor_pin_7, HIGH);
        digitalWrite(motor_pin_8, LOW);
        break;
      case 2:  //0101
        digitalWrite(motor_pin_1, LOW);
        digitalWrite(motor_pin_2, HIGH);
        digitalWrite(motor_pin_3, LOW);
        digitalWrite(motor_pin_4, HIGH);

        digitalWrite(motor_pin_5, LOW);
        digitalWrite(motor_pin_6, HIGH);
        digitalWrite(motor_pin_7, LOW);
        digitalWrite(motor_pin_8, HIGH);
        break;
      case 3:  //1001
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, LOW);
        digitalWrite(motor_pin_3, LOW);
        digitalWrite(motor_pin_4, HIGH);

        digitalWrite(motor_pin_5, HIGH);
        digitalWrite(motor_pin_6, LOW);
        digitalWrite(motor_pin_7, LOW);
        digitalWrite(motor_pin_8, HIGH);
        break;
    }
    delay(20);
    thisStep = (thisStep+1) % 4;
    Serial.println(thisStep);
 // }
}
