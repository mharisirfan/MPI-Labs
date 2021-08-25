/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */


//Beginning of Auto generated function prototypes by Atmel Studio
void myfnUpdateDisplay(byte eightBits);
byte myfnNumToBits(int someNumber);
//End of Auto generated function prototypes by Atmel Studio

/*  SevenSegmentLEDdisplay102a.ino
 *   2017-02-20
 *   Mel Lester Jr.
 *  Simple example of using Shift Register with a
 *  Single Digit Seven Segment LED Display
*/
// Globals
const int dataPin = 4;  // blue wire to 74HC595 pin 14
const int latchPin = 7; // green to 74HC595 pin 12
const int clockPin = 8; // yellow to 74HC595 pin 11

/* uncomment one of the following lines that describes your display
 *  and comment out the line that does not describe your display */
const char common = 'a';    // common anode
//const char common = 'c';    // common cathode

 
void setup() {
  // initialize I/O pins
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  
  // generate characters to display for hexidecimal numbers 0 to F
  for (int i = 0; i < 10; i++) {
    byte bits =  myfnNumToBits(i) ;

    myfnUpdateDisplay(bits);    // display alphanumeric digit
    delay(50);                 // pause for 1/2 second
  }
}

void myfnUpdateDisplay(byte eightBits) {
 
  digitalWrite(latchPin, LOW);  // prepare shift register for data
  shiftOut(dataPin, clockPin, LSBFIRST, eightBits); // send data
  digitalWrite(latchPin, HIGH); // update display
}

byte myfnNumToBits(int someNumber) {
  switch (someNumber) {
    case 0:
      return B00000011;
      break;
    case 1:
      return B10011111;
      break;
    case 2:
      return B00100101;
      break;
    case 3:
      return B00001101;
      break;
    case 4:
      return B10011001;
      break;
    case 5:
      return B01001001;
      break;
    case 6:
      return B01000001;
      break;
    case 7:
      return B00011111;
      break;
    case 8:
      return B00000001;
      break;
    case 9:
      return B00001001;
      break;
    
  }
}
