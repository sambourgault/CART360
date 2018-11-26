const int RUNNING_SAMPLES = 16;
const int SENSE_PIN = 0;

int step_number = 0;    // which step the motor is on
int direction = 0;      // motor direction
int last_step_time = 0; // time stamp in us of the last step taken
//int number_of_steps = number_of_steps; // total number of steps for this motor

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

unsigned long startTime1;
unsigned long startTime2;
unsigned long changeDirectionAfter1;
unsigned long changeDirectionAfter2;
bool changeDirectionMotor1 = true;
bool changeDirectionMotor2 = true;

// pump
#define pump_pin1 12
#define pump_pin2 13

#define forward  0
#define normal 5

int speeed = 2000;
int direcshen = 0;

// When there are 4 pins, set the others to 0:
//int motor_pin_5 = 0;

// pin_count is used by the stepMotor() method:
int pin_count = 4;
int thisStep = 0;
int thisStep2 = 0;


int runningAverageBuffer[RUNNING_SAMPLES];
int nextCount = 0;

void setup() {
  // put your setup code here, to run once:
  // setup the pins on the microcontroller:
  pinMode(motor_pin_1, OUTPUT);
  pinMode(motor_pin_2, OUTPUT);
  pinMode(motor_pin_3, OUTPUT);
  pinMode(motor_pin_4, OUTPUT);

 /* pinMode(motor_pin_5, OUTPUT);
  pinMode(motor_pin_6, OUTPUT);
  pinMode(motor_pin_7, OUTPUT);
  pinMode(motor_pin_8, OUTPUT);*/

  //activate pump pin
  /*pinMode(pump_pin1, OUTPUT);
  pinMode(pump_pin2, OUTPUT);*/

  startTime1 = millis();
  changeDirectionAfter1 = random(2000, 6000);
  /*startTime2 = millis();
  changeDirectionAfter2 = random(2000, 6000);*/

  Serial.begin(9600);
  //Serial.begin(19200);
}

void loop() {
  /*int rawSenseVal = analogRead(SENSE_PIN);
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
  Serial.println(averageVal);*/

  // motors are activated when people are close enough.
  //if (averageVal < 100) {
    // motor 1:
    switch (thisStep) {
      case 0:  // 1010
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, LOW);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, LOW);

        /*digitalWrite(motor_pin_5, HIGH);
        digitalWrite(motor_pin_6, LOW);
        digitalWrite(motor_pin_7, HIGH);
        digitalWrite(motor_pin_8, LOW);*/
        break;
      case 1:  // 0110
        digitalWrite(motor_pin_1, LOW);
        digitalWrite(motor_pin_2, HIGH);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, LOW);

        /*digitalWrite(motor_pin_5, LOW);
        digitalWrite(motor_pin_6, HIGH);
        digitalWrite(motor_pin_7, HIGH);
        digitalWrite(motor_pin_8, LOW);*/
        break;
      case 2:  //0101
        digitalWrite(motor_pin_1, LOW);
        digitalWrite(motor_pin_2, HIGH);
        digitalWrite(motor_pin_3, LOW);
        digitalWrite(motor_pin_4, HIGH);

        /*digitalWrite(motor_pin_5, LOW);
        digitalWrite(motor_pin_6, HIGH);
        digitalWrite(motor_pin_7, LOW);
        digitalWrite(motor_pin_8, HIGH);*/
        break;
      case 3:  //1001
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, LOW);
        digitalWrite(motor_pin_3, LOW);
        digitalWrite(motor_pin_4, HIGH);

       /* digitalWrite(motor_pin_5, HIGH);
        digitalWrite(motor_pin_6, LOW);
        digitalWrite(motor_pin_7, LOW);
        digitalWrite(motor_pin_8, HIGH);*/
        break;
    }

    // motor 2:
    switch (thisStep2) {
      case 0:  // 1010
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, LOW);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, LOW);

        /*digitalWrite(motor_pin_5, HIGH);
        digitalWrite(motor_pin_6, LOW);
        digitalWrite(motor_pin_7, HIGH);
        digitalWrite(motor_pin_8, LOW);*/
        break;
      case 1:  // 0110
        digitalWrite(motor_pin_1, LOW);
        digitalWrite(motor_pin_2, HIGH);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, LOW);

       /* digitalWrite(motor_pin_5, LOW);
        digitalWrite(motor_pin_6, HIGH);
        digitalWrite(motor_pin_7, HIGH);
        digitalWrite(motor_pin_8, LOW);*/
        break;
      case 2:  //0101
        digitalWrite(motor_pin_1, LOW);
        digitalWrite(motor_pin_2, HIGH);
        digitalWrite(motor_pin_3, LOW);
        digitalWrite(motor_pin_4, HIGH);

       /* digitalWrite(motor_pin_5, LOW);
        digitalWrite(motor_pin_6, HIGH);
        digitalWrite(motor_pin_7, LOW);
        digitalWrite(motor_pin_8, HIGH);*/
        break;
      case 3:  //1001
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, LOW);
        digitalWrite(motor_pin_3, LOW);
        digitalWrite(motor_pin_4, HIGH);

        /*digitalWrite(motor_pin_5, HIGH);
        digitalWrite(motor_pin_6, LOW);
        digitalWrite(motor_pin_7, LOW);
        digitalWrite(motor_pin_8, HIGH);*/
        break;
    }

    delay(100);

    if (changeDirectionMotor1) {
      // turn forward
      thisStep = (thisStep + 1) % 4;
    } else {
      // turn backward
      thisStep = ((thisStep - 1) + 4) % 4;
      // 0 - 3 // 3 - 2 // 2 - 1 // 1 - 0 //
    }

    if (changeDirectionMotor2) {
      // turn forward
      thisStep2 = (thisStep2 + 1) % 4;
    } else {
      // turn backward
      thisStep2 = ((thisStep2 - 1) + 4) % 4;
      // 0 - 3 // 3 - 2 // 2 - 1 // 1 - 0 //
    }

    /*if ( millis() - startTime1 > changeDirectionAfter1) {
      changeDirectionMotor1 = !changeDirectionMotor1;
     // Serial.println(changeDirectionMotor1);
      changeDirectionAfter1 = random(8000, 15000);
      //  Serial.println(changeDirectionAfter1);
      startTime1 = millis();
    }

    if ( millis() - startTime2 > changeDirectionAfter2) {
      changeDirectionMotor2 = !changeDirectionMotor2;
      changeDirectionAfter2 = random(9000, 16000);
      startTime2 = millis();
    }*/

    //Serial.println(thisStep);
 // }


  //digitalWrite(pump_pin1, LOW);
  //digitalWrite(pump_pin2, HIGH);
  //delay(20);
  /*if (direcshen == forward) {
    digitalWrite(pump_pin1, LOW);
    digitalWrite(pump_pin2, HIGH);
    delay(speeed);
    //analogWrite(MOTOR_IN1, 0);
    //analogWrite(MOTOR_IN2, 200);
    //delay(speeed);
    /* digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, LOW);
    digitalWrite(MOTOR_IN3, HIGH);
    digitalWrite(MOTOR_IN4, LOW);
    delay(speeed);
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, LOW);
    digitalWrite(MOTOR_IN3, LOW);
    digitalWrite(MOTOR_IN4, HIGH);
    delay(speeed);*/
  // }
  // }
}
