// pin definitions for multiplexer
int selectPins[3] = {2, 3, 4}; // S0~2, S1~3, S2~4
int zInput = A0; // Connect common (Z) to A0 (analog input)

// Arduino pins for the motor control connection:
int motor_pin_1 = 8;
int motor_pin_2 = 9;
int motor_pin_3 = 10;
int motor_pin_4 = 11;

//number of photocells connected to the multiplexer
int numberOfPhotocell = 7;
// state of interaction
bool interaction = false;
// arbitrary noise value
int noise = 50;
// previous values of the photocells from the multiplexer
int prevValues[7] = {0, 0, 0, 0, 0, 0, 0};
// motor state
int thisStep = 0;


void setup() {
  // Set up the select pins as outputs:
  for (int i = 0; i < 3; i++)
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

  // begin serial communication
  Serial.begin(9600);
}


void loop() {
  // Loop through seven pins and print the value to the serial
  interaction = false;
  for (byte pin = 0; pin < numberOfPhotocell; pin++)
  {
    selectMuxPin(pin); // Select one at a time
    int inputValue = analogRead(A0); // and read Z
    Serial.print(String(inputValue) + " ");
    // check for interaction, if the previous value is greater than the noise, there is interaction
    if (abs(prevValues[pin] - inputValue) > noise) {
      interaction = (interaction || true);
    }
    prevValues[pin] = inputValue;
  }
  // print a new line
  Serial.println();



  //if users are interacting with the machine
  if (interaction) {
    // the motor is activated
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
    // add delay to slow the rotation
    delay(200);
    // change motor state
    thisStep = (thisStep + 1) % 4;
  }
}


// The selectMuxPin function sets the S0, S1, and S2 pins
// accordingly, given a pin from 0-7.
void selectMuxPin(byte pin)
{
  for (int i = 0; i < 7; i++)
  {
    if (pin & (1 << i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}
