#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Alarm with Armed Status LED - 3 input alarm controller with flashing Armed LED

   Connections:
   Input - Sensor 0 - N/A connected to input X0 (Arduino pin A0)
   Input - Sensor 1 - Push Button SET connected to input X1 (Arduino pin A1)
   Input - Sensor 3 - N/A connected to input X2 (Arduino pin A2)
   Input - Reset Alarm - Push Button RESET connected to input X3 (Arduino pin A3)
   Output - Alarm Output - LED connected to output Y0 (Arduino pin 3)
   Output - Armed Output - LED connected to output Y1 (Arduino pin 5)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

// Timer Variables
unsigned long AUX0 = 0;     // Pulse low timer variable
unsigned long AUX1 = 0;     // Pulse high timer variable

void setup() {
  setupPLC();               // Setup inputs and outputs
}

void loop() {
  
  in(X1);                              // Read Sensor 1: push button
  //orBit(X0);                           // OR with Sensor 0- NOT USED
  //orBit(X2);                           // OR with Sensor 2- NOT USED

                                       // Set input to latch taken from sensors
  latch(Y0, X3);                       // Latch command, Q = Output 0, Reset = Input 3

  inNot (X3);                          // Enable input (0 = enable)
  timerCycle(AUX0, 1900, AUX1, 100);   // Repeating pulse 1.9 s low, 0.1 s high.
  andNotBit(Y0);                       // Disable armed pulse if alarm is triggered
  out(Y1);                             // Armed pulse on output Y0
}
