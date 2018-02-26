#include <plcLib.h>

// Variables:
unsigned long AUX0 = 0;                 // Pulse low timer variable
unsigned long AUX1 = 0;                 // Pulse high timer variable


void setup() {
  setupPLC();                           // Define inputs and outputs
}

void loop() {
  in (X0);                              // Read Enable input (1 = enable)
  timerCycle(AUX0, 900, AUX1, 100);     // Repeating pulse, low = 0.9 s, high = 0.1 s
                                        // (hence period = 1 second)
  out(Y0);                              // Send pulse waveform to Output 0
}
