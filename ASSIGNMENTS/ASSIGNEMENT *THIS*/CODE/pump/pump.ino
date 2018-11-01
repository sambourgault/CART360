const int RUNNING_SAMPLES = 16;
const int SENSE_PIN = 0;

#define MOTOR_IN1     10
#define MOTOR_IN2     11

#define forward  0
#define normal 5

int speeed = 2000;
int direcshen = 0;

int runningAverageBuffer[RUNNING_SAMPLES];
int nextCount = 0;

void setup() {
    Serial.begin(9600);

  // put your setup code here, to run once:
  //pinMode(MOTOR_EN_1_2, OUTPUT);
  //pinMode(MOTOR_EN_3_4, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(MOTOR_EN_1_2, HIGH);
  //digitalWrite(MOTOR_EN_3_4, HIGH);
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
  Serial.println(averageVal);
  

  if (direcshen == forward) {
    analogWrite(MOTOR_IN1, 0);
    analogWrite(MOTOR_IN2, 255);
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
  }
}
