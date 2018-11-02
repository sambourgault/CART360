const int RUNNING_SAMPLES = 16;
const int SENSE_PIN = 0;
int runningAverageBuffer[RUNNING_SAMPLES];
int nextCount = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
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
  delay(100);
}
