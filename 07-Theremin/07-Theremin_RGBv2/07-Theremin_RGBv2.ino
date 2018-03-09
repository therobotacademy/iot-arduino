/*
Pseudo Thermin
Outputs a color of the RGB depending on the range of frequency:
  <1000 Hz        RED
  1000-2000 Hz    GREEN
  >2000 Hz        BLUE
*/

int speakerPin = 12;
int photocellPin = 0;
int redPin = 6;
int greenPin = 9;
int bluePin = 10;

byte rojo, verde, azul;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
  Serial.begin(9600);
}

void loop()
{
  int photocellReading = analogRead(photocellPin);
  int pitch = 200*0 + photocellReading*4; // Factor 4 allows to cover the range 1000-3000 Hz for typical lighting in the training room (input 150-700 from LDR)
  tone(speakerPin, pitch);

  rojo = 255.0 - 255.0/3000.0*(float)pitch; 
  azul = 255.0/3000.0*(float)pitch;
   if (pitch < 1500) {
    verde = 255.0/1500.0*(float)pitch;
  }
  else {
    verde = 255.0 * (2 - (float)pitch/1500.0);
  }
    
  setColor(rojo, verde, azul);
  


  Serial.print("Analog reading = ");
  Serial.print(photocellReading);     // the raw analog reading
  Serial.print("\tPitch = ");
  Serial.print(pitch);
  
  Serial.print("\t ROJO = ");
  Serial.print(rojo);
  
  Serial.print("\t VERDE = ");
  Serial.print(verde);
  
  Serial.print("\t AZUL = ");
  Serial.println(azul);
  
  //delay(10);
  //noTone(speakerPin);
  delay(500);
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
