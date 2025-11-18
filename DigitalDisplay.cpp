#include "DigitalDisplay.h"
// create shift register object (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 sr (2, 12, 13, 11); 

uint8_t numberB[] = {B11000000, //0
                      B11111001, //1 
                      B10100100, //2
                      B10110000, //3 
                      B10011001, //4
                      B10010010, //5
                      B10000011, //6
                      B11111000, //7
                      B10000000, //8
                      B10011000, //9
                      B11111111  // blink
                     };


void Display(int dig){
  
  int digit2 = dig>=10? dig%10 : 10;
  int digit1 = dig>=10? (dig/10)%10 : dig;

  if(dig==-1){ //all light is on
    digit1 = 8;
    digit2 = 8;
  } else if(dig==-2){ /// all light is off
    digit1 = 10;
    digit2 = 10;
  }


  uint8_t numberToPrint[] = {numberB[digit2], numberB[digit1]};


  sr.setAll(numberToPrint);

}

void BlinkingLight(int n){
  for(int i=0; i<=n; i++){
    if(i%2==0)
      Display(-1);
    else
      Display(-2);
    delay(100);
  }
}