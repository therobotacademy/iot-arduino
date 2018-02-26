#include <plcLib.h>

// Timer Variables
unsigned long AUX0 = 0;     // Pulse low timer variable
unsigned long AUX1 = 0;     // Pulse high timer variable

void setup() {
  setupPLC();               // Setup inputs and outputs
}

void loop() {
  
  in(X1);                              // Read Sensor 1
  //orBit(X0);                           // OR with Sensor 0
  //orBit(X2);                           // OR with Sensor 2

                                        // Set input to latch taken from sensors
   latch(Y0, X3);                       // Latch command, Q = Output 0, Reset = Input 3
  }
