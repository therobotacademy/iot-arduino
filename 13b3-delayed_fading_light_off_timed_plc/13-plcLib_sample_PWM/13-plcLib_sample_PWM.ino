#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   PWM (Pulse Width Modulation) - Analogue control of a PWM output

   Connections:
   Input - potentiometer connected to input X0 (Arduino pin A0)
   Output - LED connected to output Y0 (Arduino pin 3)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

void setup() {
  setupPLC();      // Setup inputs and outputs
}

void loop() {

  // Simple ON-OFF
  //in(X1);    // Read Analogue Input 1
  //out(Y3);      // Send to Output 3
  
  // Led brightness control with analogue sensor (i.e., potentiometer)
  inAnalog(X1);    // Read Analogue Input 1
  outPWM(Y2);      // Send to Output 2 as PWM waveform
}


