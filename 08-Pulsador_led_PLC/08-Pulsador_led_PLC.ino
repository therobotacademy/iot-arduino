#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Bare Minimum - Single bit digital input and output

   Connections:
   Input - switch connected to input X1 (Arduino pin A1)
   Output - LED connected to output Y1 (Arduino pin 5)

   Software and Documentation:
   https://github.com/wditch/plcLib

*/

void setup() {
  setupPLC();  // Setup inputs and outputs
}

void loop() {
  in(X1);      // Read Input 0
  out(Y1);     // Send to Output 0
}
