//timed Light with plcLib
#define LED_PIN 11
#define BUTTON_PIN 8

#define OFF     0
#define ON      1
#define FADING  2

// Control variables
int state = OFF;  // Estado inicial con LED apagado
int OffTime = 3000; 
int FadingTime = 2000;

int timerON, timerFADING, timerOFF;
int brillo;  

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  LEDstep();
  Serial.print(state);
  Serial.print("\t timerOFF = ");  Serial.print(timerOFF);
  Serial.print("\t timerON = ");  Serial.print(timerON);
  Serial.print("\t timerFADING = ");  Serial.print(timerFADING);
  Serial.print("\t timerON = ");  Serial.print(timerON);
  Serial.print("\t brillo= "); Serial.println(brillo);
}

void LEDstep() {
  int button;
  static long t0, t0f, t1; // t0: Instant in which button is pressed 
                           // t0f: time when starts fading
                           // t1: time since light off
  button = digitalRead(BUTTON_PIN);
  switch (state) {
    case OFF:                  
      if (button == HIGH) {           // Button event
        state = ON;                       // - Change state to ON
        t0 = millis();                    // - Launch ON timer
        digitalWrite(LED_PIN,HIGH);       // - Switch led ON
        timerOFF = 0;                     // - Reset timer
      } else
        timerOFF = millis()-t1;       // ELSE keep timing OFF state
      break;
      
    case ON:
      if (timerON >= OffTime){        // Timer event
        state = FADING;                   // - Change state to FADING
        t0f = millis();                   // - Launch FADING timer
        timerON = 0;                      // - Reset timer
      } else
        timerON = millis() - t0;      // ELSE keep timing ON state  
      break;

    case FADING:
      if (timerFADING >= FadingTime){ // Timer event
        state = OFF;                      // - Change state to OFF
        t1 = millis();                    // - Launch OFF timer
        digitalWrite(LED_PIN,LOW);        // - Switch led OFF
        timerFADING = 0;                  // - Reset timer
      } else {
        timerFADING = millis()-t0f;       // ELSE keep timing FADING state
        brillo = (255.0 * (FadingTime-timerFADING) / FadingTime);
        if (brillo < 0) brillo = 0;
        analogWrite(LED_PIN,brillo);      // Bright of proportional to countdown
      }
      break;
   }
}
