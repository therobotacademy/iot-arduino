#include <plcLib.h>

/* Programmable Logic Controller Library for the Arduino and Compatibles

   Crossing regulated with Traffic Lights - Timed Repeating Sequence
   
   Connections:
   Output - PRINCIPAL Green LED connected to output Y0 (Arduino pin 3)
   Output - PRINCIPAL Red   LED connected to output Y1 (Arduino pin 5)
   Output - SECONDARY Green LED connected to output Y2 (Arduino pin 6)
   Output - SECONDARY Red   LED connected to output Y3 (Arduino pin 9)

   Software and Documentation:
   https://github.com/wditch/plcLib



   Sequential Function Chart
   
         |=========|    |---------------|
         |  START  |----|  Y3 Y2 Y1 Y0  | (GREEN and RED lights)
         |=========|    |---------------|
              |
             -|-- DELAY0 = 2000 (ms)
              |
|------>------|
|             |
|        |----|----|    |---------------|
|        |  STEP1  |----|  Y3 -- -- Y0  | (SECONDARY Red - PRINCIPAL Green)
|        |---------|    |---------------|
|             |
|            -|-- DELAY1 = 4000 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP2  |----|  Y3 -- Y1 --  | (SECONDARY Red - PRINCIPAL Red)
|        |---------|    |---------------|
|             |
|            -|-- DELAY2 = 2000 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP3  |----|  -- Y2 Y1 --  | (SECONDARY Green - PRINCIPAL Red)
|        |---------|    |---------------|
|             |
|            -|-- DELAY3 = 3000 (ms)
|             |
|        |----|----|    |---------------|
|        |  STEP4  |----|  Y3 -- Y1 --  | (SECONDARY Red - PRINCIPAL Red)
|        |---------|    |---------------|
|             |
|            -|-- DELAY4 = 1000 (ms)
|             |
|------<------|

  Step (Variable)    S-Red(Y3) S-Green(Y2) P-Red(Y1)  P-Green(Y0)   Duration (Variable)
    0   (START)       -         X          -           X            2000 ms  (DELAY0)
    1   (STEP1)       X         -          -           X            4000 ms  (DELAY1)
    2   (STEP2)       X         -          X           -            2000 ms  (DELAY2)
    3   (STEP3)       -         X          X           -            3000 ms  (DELAY3)
    4   (STEP4)       X         -          X           -            1000 ms  (DELAY4)
    1
    2    etc.

*/
                            // Define step names

unsigned int START = 1;     // Start-up state (START = 1 to automatically start here)
unsigned int STEP1 = 0;     // Step 1
unsigned int STEP2 = 0;     // Step 2
unsigned int STEP3 = 0;     // Step 3
unsigned int STEP4 = 0;     // Step 4

                            // Define time delay variables

unsigned long DELAY0 = 0;   // Variable to hold elapsed time for Step 0
unsigned long DELAY1 = 0;   // Variable to hold elapsed time for Step 1
unsigned long DELAY2 = 0;   // Variable to hold elapsed time for Step 2
unsigned long DELAY3 = 0;   // Variable to hold elapsed time for Step 3
unsigned long DELAY4 = 0;   // Variable to hold elapsed time for Step 4

void setup() {
  setupPLC();               // Setup inputs and outputs
  Serial.begin(9600);
}

void loop() {

  Serial.print("START= ");
  Serial.print(START);
  Serial.print("\tSTEP1= ");
  Serial.print(STEP1);
  Serial.print("\tSTEP2= ");
  Serial.print(STEP2);
  Serial.print("\tSTEP3= ");
  Serial.print(STEP3);
  Serial.print("\tSTEP4= ");
  Serial.print(STEP4); 
  Serial.println("");
  delay(500);

                            // Do timed step transitions
  in(START);                // Read start-up step
  timerOn(DELAY0, 2000);    // 2 seconds delay
  set(STEP1);               // Activate Step 1
  reset(START);             // Cancel Step 0
  
  in(STEP1);                // Read Step 1
  timerOn(DELAY1, 4000);    // 4 seconds delay
  set(STEP2);               // Activate Step 2
  reset(STEP1);             // Cancel Step 1
 
  in(STEP2);                // Read Step 2
  timerOn(DELAY2, 2000);    // 2 seconds delay
  set(STEP3);               // Activate Step 3
  reset(STEP2);             // Cancel Step 2
  
  in(STEP3);                // Read Step 3
  timerOn(DELAY3, 3000);    // 3 seconds delay
  set(STEP4);               // Activate Step 4
  reset(STEP3);             // Cancel Step 3
  
  in(STEP4);                // Read Step 4
  timerOn(DELAY4, 1000);    // 1 second delay
  set(STEP1);               // Activate Step 1 (again)
  reset(STEP4);             // Cancel Step 4
  
  
                            // Display outputs according to table
   
                            // Step S-Red S-Green P-Red P-Green
                            //        Y3     Y2   Y1    Y0
                            //        **     **   **    **
                            //   0     x     x     x     x
                            //   1     x     -     -     x
                            //   2     x     -     x     -
                            //   3     -     x     x     -
                            //   4     x     -     x     -
  
                            // Display Y3 if step = 0, 1, 2 OR 4
  in(START);                // Read Step 0
  orBit(STEP1);                // Read Step 1
  orBit(STEP2);             // Read Step 2
  orBit(STEP4);             // Read Step 4
  out(Y3);                  // Send to Output 3 (SECONDARY Red)
                            
  in(START);                // Display Y2 if step = 0 OR 3
  orBit(STEP3);             
  out(Y2);                  // Send to Output 0 (SECONDARY Green)
  
  in(START);                // Display Y1 if step = 0, 2, 3 OR 4
  orBit(STEP2);
  orBit(STEP3);
  orBit(STEP4);             
  out(Y1);                  // Send to Output 1 (PRINCIPAL Red)

  in(START);                // Display Y0 if step = 0 OR 1
  orBit(STEP1);             
  out(Y0);                  // Send to Output 2 (PRINCIPAL Green)
  
}
