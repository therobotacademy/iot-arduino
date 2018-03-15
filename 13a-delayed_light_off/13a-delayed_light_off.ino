#define LED_PIN 11
#define BUTTON_PIN 8
#define OFF 0
#define ON 1

// Control variables
int state = OFF;  // Estado inicial con LED apagado
int OffTime = 10000; 

// Internal variables
int timer = 0;
long now, last;
int loop_delay = 40; // Estimated iteration time delay to compute 'real time'
                     // = estimated decrement to sinulate 'real time'

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
  button = digitalRead(BUTTON_PIN);
  switch (state) {
    case OFF:
      if (button == HIGH) {
        state = ON;
        timer = OffTime;
        analogWrite(LED_PIN,255);
      } break;
      
    case ON:
      if (timer <= 0){
        state = OFF;
        analogWrite(LED_PIN,0);
      } else timer -= loop_delay;
  }
}

