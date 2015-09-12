#include <SevSeg.h>

/* Contact: Colin Lobo (lobocjd@gmail.com)
 * Program Description: Control a two digit common anode seven segment display with 4 buttons (reset, increase, decrease and random) to replicate a dice. Range of the dice is 00-99.
 *                      Reset button changes the display to 00. Increase button increases the display count by one. Decrease button decrease the display count by one. Random button
 *                      displays a rnadom number between 01-99
 * Libraries Used: https://github.com/sparkfun/SevSeg.git

Pinout:
 D0: Segment A
 D1: Segment B
 D2: Segment C
 D3: Segment D
 D4: Segment E
 D5: Segment F
 D6: Segment G
 D7: Digit 1
 D8: Digit 2
*/

//Create an instance of the object
SevSeg myDisplay;

//Pushbuttons pins
const int randombtn = 13;
const int resetbtn = 12;
const int increasebtn = 11;
const int decreasebtn = 10;

//Global variables
char myvalString[10]; //Used for sprintf
int myval; //display value
int randombtnState;
int l_randombtnState = LOW;
int resetbtnState;
int l_resetbtnState = LOW;
int increasebtnState;
int l_increasebtnState = LOW;
int decreasebtnState;
int l_decreasebtnState = LOW;
long l_DebounceTime = 0;
long debounceDelay = 50;

void setup() {
  int displayType = COMMON_ANODE; //Your display is either common cathode or common anode

  pinMode(randombtn, INPUT);
  pinMode(resetbtn, INPUT);
  pinMode(increasebtn, INPUT);
  pinMode(decreasebtn, INPUT);
  
  //Declare what pins are connected to the digits
  int digit1 = 7; 
  int digit2 = 8; 
  int digit3 = 10; //not connected (placeholder)
  int digit4 = 11; //not connected (placeholder)
  
  //Declare what pins are connected to the segments
  int segA = 0;
  int segB = 1;
  int segC = 2;
  int segD = 3;
  int segE = 4;
  int segF = 5;
  int segG = 6;
  int segDP= 9; //not connected (placeholder)

  randomSeed(analogRead(0)); //initializes the pseudo-random number generator
  
  int numberOfDigits = 2; //Two digit display
  myDisplay.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  
  myDisplay.SetBrightness(50); //Set the display to 100% brightness level
}

void loop() {

  //Read all button states
  int r_randombtnState = digitalRead(randombtn);
  int r_resetbtnState = digitalRead(resetbtn);
  int r_increasebtnState = digitalRead(increasebtn);
  int r_decreasebtnState = digitalRead(decreasebtn);
  
  if(r_randombtnState != l_randombtnState) {
    l_DebounceTime = millis();
  }
  if(r_resetbtnState != l_resetbtnState) {
    l_DebounceTime = millis();
  }
  if(r_increasebtnState != l_increasebtnState) {
    l_DebounceTime = millis();
  }
  if(r_decreasebtnState != l_decreasebtnState) {
    l_DebounceTime = millis();
  }

  if ((millis() - l_DebounceTime) > debounceDelay){
    if(r_randombtnState != randombtnState){
      randombtnState = r_randombtnState;
      if (randombtnState == HIGH){
        myval = myrandomval();
        sprintf(myvalString, "%2d", myval); //Convert deciSecond into a string that is right adjusted
      }
    }
  
    if(r_resetbtnState != resetbtnState){
       resetbtnState = r_resetbtnState;
       if (resetbtnState == HIGH){
         myval = 0;
         sprintf(myvalString, "%2d", myval); //Convert deciSecond into a string that is right adjusted
       }
     }
  
     if(r_increasebtnState != increasebtnState){
       increasebtnState = r_increasebtnState;
       if (increasebtnState == HIGH){
         ++myval;
         sprintf(myvalString, "%2d", myval); //Convert deciSecond into a string that is right adjusted
       }
     } 

     if(r_decreasebtnState != decreasebtnState){
       decreasebtnState = r_decreasebtnState;
       if (decreasebtnState == HIGH){
         --myval;
         sprintf(myvalString, "%2d", myval); //Convert deciSecond into a string that is right adjusted
       }
     }  
  
  }
  
  //Produce an output on the display
  myDisplay.DisplayString(myvalString, 0); //(numberToDisplay, decimal point location)
  l_randombtnState = r_randombtnState;
  l_resetbtnState = r_resetbtnState;
  l_increasebtnState = r_increasebtnState;
  l_decreasebtnState = r_decreasebtnState;
}

int myrandomval() {
  int myval = random(0,100);
  return myval;
}

