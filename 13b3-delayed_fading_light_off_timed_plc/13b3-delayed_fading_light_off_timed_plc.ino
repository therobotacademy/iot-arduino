//timed Light with plcLib
#include <plcLib.h>

#define LED_PIN 9
// Button connected to plcLib input X1, equivalent to       #define BUTTON_PIN A1

unsigned int OFF = 1;
unsigned int ON =  0;
unsigned int FADING = 0;

unsigned long DELAYon      = 0;   // Variable to hold elapsed time for ON state
unsigned long DELAYfading  = 0;   // Variable to hold elapsed time for FADING state
unsigned long cronoTime    = 0;   // Elapsed time of current crono

// Control variables
int OffTime = 1000; 
int OnTime = 3000; 
int FadingTime = 5000;

// Instant LED brightness output
unsigned int brillo;  

void setup() {
  setupPLC();               // Setup inputs and outputs
  Serial.begin(9600);
  set(OFF);
}

void loop() {
  Serial.print("(Button pressed=) ");  Serial.print(in(X1));
  Serial.print("\tOFF = ");  Serial.print(OFF);
  Serial.print("\t ON = ");  Serial.print(ON);
  Serial.print("\t FADING = ");  Serial.print(FADING);
  Serial.print("\t (tiempo=) ");  Serial.print(cronoTime);
  Serial.print("\t (brillo=) "); Serial.println(brillo);
  delay(500);
  
  in(X1);   // TRIGGER 'ON': Push button connected to pin A1
  set(ON);
  reset(OFF);

  in(ON);
  timerOn(DELAYon, OnTime);         // TRIGGER 'FADING': first timer
  set(FADING);
  reset(ON);

  in(FADING);
  timerOn(DELAYfading, FadingTime);  // TRIGGER 'OFF': second timer
  set(OFF);
  reset(FADING);

   
  // OUTPUT STATE DEFINITION

  // Brightness calculation for FADING state
    cronoTime = cronoOn(DELAYfading, FADING); // Elapsed time of this step
  if (FADING)
    brillo = (255.0 * (FadingTime-cronoTime) / FadingTime);
  else if (ON)
    brillo = 255;
    else brillo = 0;
    
  analogWrite(LED_PIN,brillo);
}

//////////////////////////////////////////////////////////////////
/// User defined functions

unsigned int cronoOn(unsigned long &timerState, unsigned int stepIn) {
  if (stepIn)    cronoTime = millis() - timerState;     // Elapsed time of this step
  else           cronoTime = 0;                         // Not running the step
  return(cronoTime);                    // Return result
}
