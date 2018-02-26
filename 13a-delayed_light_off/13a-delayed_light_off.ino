#define LED_PIN 11
#define BUTTON_PIN 8
#define OFF 0
#define ON 1
int state = OFF;//Estado inicial con LED apagado
int timer = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print ("timer: ");
  Serial.println (timer);
  LEDstep();
  delay(10);
  
}

void LEDstep() {
  int button;
  button = digitalRead(BUTTON_PIN);
  switch (state) {
    case OFF:
      if (button == HIGH) {
        state = ON;
        timer = 1000;
        analogWrite(LED_PIN,255);
      } break;
      
    case ON:
      if (timer <= 0){
        state = OFF;
        analogWrite(LED_PIN,0);
      } else timer--;
  }
}

