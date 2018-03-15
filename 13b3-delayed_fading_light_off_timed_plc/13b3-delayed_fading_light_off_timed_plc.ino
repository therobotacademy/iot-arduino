//timed Light with plcLib
#define LED_PIN 11
#define BUTTON_PIN 8

unsigned int OFF = 1;   // Active state at start
unsigned int ON =  0;
unsigned int FADING = 0;

unsigned long DELAYon     = 0;   // Variable to hold elapsed time for ON state
unsigned long DELAYfading = 0;   // Variable to hold elapsed time for FADING state

// Control variables
int OnTime = 3000; 
int FadingTime = 2000;

int timerON, timerFADING, timerOFF;
byte brillo;  

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print(state);
  Serial.print("\t timerOFF = ");  Serial.print(timerOFF);
  Serial.print("\t timerON = ");  Serial.print(timerON);
  Serial.print("\t timerFADING = ");  Serial.print(timerFADING);
  Serial.print("\t timerON = ");  Serial.print(timerON);
  Serial.print("\t brillo= "); Serial.println(brillo);
  
  set(OFF); // Starting state is 'OFF'
  
  in(X1);   // TRIGGER 'ON': Push button connected to pin A1
  set(ON);
  reset(OFF);
  
  timerOn(DELAYon, OnTime);         // TRIGGER 'FADING': first timer
  set(FADING);
  reset(ON);

  timerOn(DELAYfading, FadingTime); // TRIGGER 'OFF': second timer
  set(OFF);
  reset(FADING);
  
  // State definition
  in(OFF);
  outNot(Y7);   // Led connected to pin D12
  
  in(ON);
  out(Y7);

  inAnalogue(100);
  andBit(FADING);
  outPWM(Y7);
}
