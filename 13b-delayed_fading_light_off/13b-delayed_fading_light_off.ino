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
        timer = 500; //10000ms
        analogWrite(ledPin, 255);
      } break;
    case ON:
      if (timer <= 0) {
        state = Fading;
        timer2 = 200;
        break;
      } else timer--;
      break;

    case Fading:
      if (timer2 >= 0) {
        brillo = (255 * timer2 / 200);
        //brillo = timer;
        analogWrite(ledPin, brillo);
        timer2--;
      } else {
        state = OFF;
      }
      break;
  }
}


