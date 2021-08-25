/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */


//Beginning of Auto generated function prototypes by Atmel Studio
void myfnUpdateDisplay(byte eightBits);
byte myfnNumToBits(int someNumber);
//End of Auto generated function prototypes by Atmel Studio

const int dataPin = 4;           // DDRD=10010000;
const int latchPin = 7;         //  DDRB=00000001;
const int clockPin = 8; 

 
void setup() {

  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  
  for (int i = 0; i < 10; i++) {
    byte bits =  myfnNumToBits(i) ;

    myfnUpdateDisplay(bits);    
    delay(50);                 
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
