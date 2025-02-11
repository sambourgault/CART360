/**********************ETUDE 2 CART 360 2017*******************************
   WELCOME!
   THE PURPOSE OF THIS EXERCISE IS TO DESIGN A VERY SIMPLE KEYBOARD (5 KEYS)
   WHICH ALLOWS YOU TO PLAY LIVE, RECORD, AND PLAYBACK SINGLE NOTES (NO CHORDS).
   THERE WILL BE A BUTTON WHICH WHEN PRESSED WILL TAKE THE USER TO THE NEXT MODE:
   THERE ARE 5 POSSIBLE MODES
   0 ==  reset    ==   led off == also resets
   1 ==  live     ==   led BLUE
   2 ==  record   ==   led RED
   3 ==  play     ==   led GREEN
   4 ==  looper   ==   led PURPLE

   ADDITIONALLY - WHEN THE USER CHANGES MODE,
   THE RGB LED WILL CHANGE COLOR (ACCORDING TO THE SPECIFICATIONS)

   PLEASE FOLLOW THE INSTRUCTIONS IN THE COMMENTS:
   DO NOT ADD ANY MORE FUNCTION DEFINITIONS
   ONLY IMPLEMENT THE FUNCTION DEFINITIONS SUPPLIED
   THERE IS NO NEED TO ADD ANY NEW VARIABLES OR CONSTANTS
   PROVIDE COMMENTS FOR ANY OF THE CODE IMPLEMENTED
   GOOD LUCK!
*/
/**** CONSTANTS ********************************************************/

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
#define LED_PIN_R 9 // R PIN
#define LED_PIN_G 6 // G PIN
#define LED_PIN_B 5 // B PIN

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

//constant for max number of notes in array
#define MAX_NOTES 16

// a constant for duration
const int duration = 300;

// constant for pin to output for buzzer
#define BUZZER_PIN 3 // PWM

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes = 0;
int mode = 0; // start at off
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES];

// NEW VARIABLES for play and looper functions
int noteAt = 0;
int increment = 1;


/*************************************************************************/


/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{
  pinMode(BUTTON_MODE_PIN, INPUT);
  Serial.begin(9600);
}

/**********************LOOP() DO NOT CHANGE *******************************
   INSTRUCTIONS:
   There is NO NEED to change the loop - it establishes the flow of the program
   We call here 3 functions repeatedly:
   1: chooseMode(): this function will determine the mode that your program is in
   based on if the button (linked to the BUTTON_MODE_PIN) was pressed
   2: setRGB(): will set the color of the RGB LED based on the value of the mode variable
   3: selectMode(): will determine which function to call based on the value of the mode variable

**************************************************************************/
void loop()
{
  chooseMode();
  setRGB();
  selectMode();
}
/******************CHOOSEMODE(): IMPLEMENT *********************************
   INSTRUCTIONS:
   Read the value from the Button (linked to the BUTTON_MODE_PIN) and
   if is being pressed then change the mode variable.
   REMEMBER:
   mode == 0 is reset
   mode == 1 is live
   mode == 2 is record
   mode == 3 is play
   mode == 4 is loopMode
   Every time the user presses the button, the program will go to the next mode,
   once it reaches 4, it should go back to mode == 0.
   (i.e. if mode ==2 and we press, then mode ==3) ...
**************************************************************************/
void chooseMode() {
  // check if the button is being pressed (HIGH) or not (LOW)
  int buttonVal = digitalRead(BUTTON_MODE_PIN);

  // if the button is being pressed (HIGH)
  if (buttonVal) {
    // increase the mode. I use the modulo function to make sure that the mode varies from 0 to 4.
    mode = (mode + 1) % 5;
    // add a delay to encounter time it takes for a user to press and released the button
    delay(300);
  }
}

/******************SETRGB(): IMPLEMENT *********************************
   INSTRUCTIONS:
   Depending on the value of the mode variable:
   if the mode is 0 - RGB LED IS OFF
   if the mode is 1 - RGB LED IS BLUE
   if mode is 2 - RGB LED IS RED
   if mode is 3 - RGB LED IS GREEN
   if mode is 4 - RGB LED iS PURPLE
   YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
**************************************************************************/
void setRGB()
{
  // change the color of the LED depending of the selected mode
  switch (mode) {
    // mode 0, the LED is off.
    case 0:
      digitalWrite(LED_PIN_R, LOW);
      digitalWrite(LED_PIN_G, LOW);
      digitalWrite(LED_PIN_B, LOW);
      break;
    // mode 1: the LED is blue
    case 1:
      digitalWrite(LED_PIN_R, LOW);
      digitalWrite(LED_PIN_G, LOW);
      digitalWrite(LED_PIN_B, HIGH);
      break;
    // mode 2: the LED is red
    case 2:
      digitalWrite(LED_PIN_R, HIGH);
      digitalWrite(LED_PIN_G, LOW);
      digitalWrite(LED_PIN_B, LOW);
      break;
    // mode 3: the LED is green
    case 3:
      digitalWrite(LED_PIN_R, LOW);
      digitalWrite(LED_PIN_G, HIGH);
      digitalWrite(LED_PIN_B, LOW);
      break;
    // mode 4: the led is purple (a mix of blue and red)
    case 4:
      digitalWrite(LED_PIN_R, HIGH);
      digitalWrite(LED_PIN_G, LOW);
      digitalWrite(LED_PIN_B, HIGH);
      break;
  }
}
/**********************SELECTMODE() DO NOT CHANGE *******************************
   INSTRUCTIONS:
   There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
   There are 4 possibilities
   1: reset(): this function will reset any arrays etc, and will do nothing else
   2: live(): this function will play the corresponding notes
   to the user pressing the respective buttons.
   NOTE:: the notes played are NOT stored
   3: record(): this function will play the corresponding notes
   to the user pressing the respective buttons
   AND will STORE up to 16 consecutive notes in an array.
   4: play(): this function will playback any notes stored in the array that were recorded
   in the previous mode
   5: loopMode(): this function will playback any notes stored in the array that were recorded,
   BUT unlike the previous mode, you can choose in which sequence the notes are played.
   REQUIRED: only play notes from the array (no live stuff)

******************************************************************************/
void selectMode()
{
  if (mode == 0) {
    reset();
  }
  else if (mode == 1) {
    live();
  }
  else if (mode == 2) {
    record();
  }

  else if (mode == 3) {
    play();
  }

  else if (mode == 4) {
    looper();
  }
}
/******************RESET(): IMPLEMENT **************************************
   INSTRUCTIONS:
   this function should ensure that any notes recorded are no longer available
**************************************************************************/
void reset()
{
  // go through the array and reset the value of each note to 0
  for (int i = 0; i < countNotes; i++) {
    notes[i] = 0;
  }
  // set the counter back to 0
  countNotes = 0;
  // set noteAt and increment to default values
  noteAt = 0;
  increment = 1;
}
/******************LIVE(): IMPLEMENT **************************************
   INSTRUCTIONS:
   this function will play the corresponding notes
   to the user pressing the respective buttons
   NOTE:: the notes played are NOT stored
   SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
   THEN - output the note to the buzzer using the tone() function
**************************************************************************/
void live()
{
  // read the value from the ladder
  int analogValue = analogRead(NOTE_IN_PIN);

  if (analogValue != 0) {
    tone(BUZZER_PIN, analogValue, duration);
    Serial.println(analogValue);

    // not sure if I need a delay here
    delay(duration);
  }
}
/******************RECORD(): IMPLEMENT **********************************
   INSTRUCTIONS:
   this function will play the corresponding notes
   to the user pressing the respective buttons
   AND will STORE up to 16 consecutive notes in an array.
   SO:you need read in the input from the analog input (linked to the button-resistor ladder combo)
   AND - output the note to the buzzer using the tone() function
   THEN store that note in the array  - BE CAREFUL - you can only allow for up to MAX_NOTES to be stored
**************************************************************************/
void record()
{
  // read the value from the ladder
  int analogValue = analogRead(NOTE_IN_PIN);

  if (analogValue != 0) {
    // send a tone to the piezo
    tone(BUZZER_PIN, analogValue, duration);
  }

  // record a maximum of 16 notes in the array
  if (countNotes < MAX_NOTES && analogValue != 0) {
    notes[countNotes] = analogValue;
    countNotes++;
    // add some delay between each tone
    delay(duration);
  }
}
/******************PLAY(): IMPLEMENT ************************************
   INSTRUCTIONS:
   this function will playback any notes stored in the array that were recorded
   in the previous mode
   SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
   READ each value IN ORDER
   AND output each note to the buzzer using the tone() function
   ALSO: as long as we are in this mode, the notes are played over and over again
   BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void play()
{
  // send a tone to the piezo
  tone(BUZZER_PIN, notes[noteAt], duration);

  // increment noteAt
  noteAt++;
  // set noteAt back to zero when it reaches the amount of notes stored in the array
  if (noteAt >= countNotes) {
    noteAt = 0;
  }
  // add some delay between each tone
  delay(duration);
}
/******************LOOPMODE(): IMPLEMENT *********************************
   INSTRUCTIONS:
   this function will playback any notes stored in the array that were recorded
   in the previous mode
   SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
   READ values IN ANY ORDERING (You MUST use the array - but you can determine your own sequence)
   AND output each note to the buzzer using the tone() function
   ALSO: as long as we are in this mode, the notes are played over and over again
   BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void looper()
{
  // send a tone to the piezo
  tone(BUZZER_PIN, notes[noteAt], duration);

  // increment noteAt
  noteAt += increment;

  // change the increment direction when it reaches one extremity of the array.
  if (noteAt >= countNotes - 1) {
    increment = -1;
  } else if (noteAt <= 0) {
    increment = 1;
  }

  // add delay between each tone
  delay(duration);
}
/**************************************************************************/
/****************************************** PART THREE ********************************************
  The ladder involves five different resistances (10kΩ, 1kΩ, 10kΩ, 100kΩ and 1MΩ) connected in series. 
  Each time the user presses on a button, it allows the current coming from the 5V Arduino output 
  to flow toward the ground passing through between one to five resistance. The analog reading is 
  taken before the first 10kΩ resistance that is directly connected to the ground. Therefore, when 
  the first button is pressed, the analog reading returns 1023, the numerical equivalent to 5V since 
  there is no drop of potential between the 5V source and the point of reading. When the second button 
  is pressed, the current passes through the 1kΩ resistance before being read. Voltage division occurs 
  between the 10kΩ resistance connected to the ground and the first 1kΩ resistance, but the drop in 
  potential is small since 1kΩ is ten times smaller than 10kΩ. The returned analog value is around 931. 
  When the third button is pressed, the current passes through 11kΩ before being read which returns a 
  value of 486. The same goes for the fourth and the fifth buttons that allow the current to pass 
  through 111kΩ and 1111kΩ (1.111MΩ) and output values of 82 and 7 respectively. These specific values 
  can then be associated with different events in the Arduino code.

  The mode selector involves a button connected to the Arduino 5V output and the ground through a 10kΩ 
  resistance. A digital reading is being done at the exit point of the button. When the button is open, 
  the digital reading is 0V or LOW as expressed in the code. When the button is pressed, the current 
  flows and the exit point of the button reaches 5V. In this state, the digital reading is HIGH. In the 
  program, each time the program sees HIGH, it increases the mode value by one unit, evolving from 0 to 
  4 and back to 0 once it reaches 4.

  Finally, once the input is read. The tone function through a PWM digital pin send equivalent voltage 
  to the piezo electric crystal. This voltage indices mechanical vibrations in the crystal which creates 
  audible waves in the perceptive range for human ears.

 ******************************************************************************************************/
