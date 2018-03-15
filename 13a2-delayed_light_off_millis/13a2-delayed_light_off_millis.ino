#define LED_PIN 11
#define BUTTON_PIN 8
#define OFF 0
#define ON 1

// Control variables
int state = OFF;  // Estado inicial con LED apagado
int OffTime = 3000; 

// Internal variables
int timer;        // Used both for "delayed ligh off" and time since last "end of light off" 
long now, last;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin (9600);
  last = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  LEDstep();

  // Time consumption evaluation
  now = millis();
  Serial.print("iteration time (ms)= "); // This line takes 30 ms!!!!!!
  Serial.print(now-last);                // This line takes 3 ms
  Serial.print ("\t timer: ");           // This line takes 14 ms
  Serial.println (timer);                // This line takes 3 ms TOTALLING about 40 ms
  last = now;  
}

void LEDstep() {
  int button;
  static long t0, t1; // t0: time of button push
                      // t1: time since light off
  button = digitalRead(BUTTON_PIN);
  switch (state) {
    case OFF:
      if (button == HIGH) {
        state = ON;
        t0 = millis();
        analogWrite(LED_PIN,255);
      } else
        timer = millis()-t1;
      break;
      
    case ON:
      if (timer >= OffTime){
        state = OFF;
        t1 = millis();
        analogWrite(LED_PIN,0);
      } else
        timer = millis() - t0;   
  }
}

