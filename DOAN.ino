#include "DistanceSensor.h"
#include "DigitalDisplay.h"
#include "MortorControl.h"

const int BUTTON_PIN = 3;
const int RESET_BUTTON_PIN = 2;

int glassesCount = 0;
volatile bool resetFlag = false; 

// --- ISR: Interrupt Service Routine ---
void softwareReset(){
    glassesCount = 0;
    resetFlag = true; // Set the flag to handle blinking/display in loop()
}

void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    SenSorSetup();
    // Use the physical pin number (RESET_BUTTON_PIN) to set up the interrupt
    attachInterrupt(digitalPinToInterrupt(RESET_BUTTON_PIN), softwareReset, FALLING);
    // Initial blinking at startup (safe in setup())
    BlinkingLight(4);
    // Initialize the display
    Display(0); 
}


void Fill(){
    if(GetDistance()<10) return;
    MortorRun(10);
    while(GetDistance()>=10) {
      if(resetFlag)
        return;
      delay(500);
    }
    glassesCount+=1;
    MortorRun(0);
}


void loop() {
    // --- 1. Handle Software Reset Tasks ---
    if (resetFlag) {
      MortorRun(0);
      BlinkingLight(4); 
      resetFlag = false;
    }
    
    // --- 2. Handle Fill Button ---
    if(digitalRead(BUTTON_PIN) == LOW){
        Fill();
    } else {
        MortorRun(0);
    }

    // --- 3. Display Count ---
    Display(glassesCount);
    delay(20);
}