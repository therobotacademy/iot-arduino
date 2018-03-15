//timed Light

#define ON 1
#define OFF 0
#define Fading 2

int buttonPin = 8;
int ledPin = 11;
int timer ;
int timer2;
int state = 0;
unsigned int brillo;

int t0; // Instant in which button is pressed
int tON, tFADING;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  LEDstep();
  delay(10);//ms

}


void LEDstep() {
  int button;

  Serial.print( state);
  Serial.print("\t");  Serial.print(timer);
  Serial.print("\t");  Serial.print(timer2);
  Serial.print("\t"); Serial.println(brillo);

  button = digitalRead(buttonPin);
  switch (state) {
    case OFF:
      if (button == HIGH) {
        state = ON;
        t0 = millis();
        timer = 2000; // ms, tiempo total de apagado
        analogWrite(ledPin, 255);
      } break;
    case ON:
      tON= millis();
      if ((tON-t0) >= timer) {
        state = Fading;
        timer2 = 200;
        break;
      }
      break;

    case Fading:
      tFADING= millis();
      
      if ((tFADING-t0) >= timer2) {
        brillo = (255.0 * (timer2-(tFADING-t0)) / 200.0);
        analogWrite(ledPin, brillo);
      } else {
        state = OFF;
      }
      break;
  }
}


