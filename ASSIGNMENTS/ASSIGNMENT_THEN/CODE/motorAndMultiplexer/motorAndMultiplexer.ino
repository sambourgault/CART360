


/////////////////////
// Pin Definitions //
/////////////////////
const int selectPins[3] = {2, 3, 4}; // S0~2, S1~3, S2~4
const int zOutput = 5; 
const int zInput = A0; // Connect common (Z) to A0 (analog input)


int step_number = 0;    // which step the motor is on
int direction = 0;      // motor direction
int last_step_time = 0; // time stamp in us of the last step taken
//int number_of_steps = number_of_steps; // total number of steps for this motor

// Arduino pins for the motor control connection:
int motor_pin_1 = 8;
int motor_pin_2 = 9;
int motor_pin_3 = 10;
int motor_pin_4 = 11;


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



int nextCount = 0;

void setup() {
  // Set up the select pins as outputs:
  for (int i=0; i<3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }
  pinMode(zInput, INPUT); // Set up Z as an input
  
  // put your setup code here, to run once:
  // setup the pins on the microcontroller:
  pinMode(motor_pin_1, OUTPUT);
  pinMode(motor_pin_2, OUTPUT);
  pinMode(motor_pin_3, OUTPUT);
  pinMode(motor_pin_4, OUTPUT);



  startTime1 = millis();
  changeDirectionAfter1 = random(2000, 6000);

  Serial.begin(9600);
  //Serial.begin(19200);
}

void loop() {
  // Loop through all eight pins.
  for (byte pin=0; pin<5; pin++)
  {
    selectMuxPin(pin); // Select one at a time
    int inputValue = analogRead(A0); // and read Z
    Serial.print(String(inputValue) + " ");
    //Serial.println(String(inputValue));
  }
    Serial.println();


  // motors are activated when people are close enough.

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

    // motor 2:
    switch (thisStep2) {
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

}


// The selectMuxPin function sets the S0, S1, and S2 pins
// accordingly, given a pin from 0-7.
void selectMuxPin(byte pin)
{
  for (int i=0; i<5; i++)
  {
    if (pin & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}
