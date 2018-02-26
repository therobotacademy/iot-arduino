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
  int pitch = 200 + photocellReading*4 ; // Factor 4 allows to cover the range 1000-3000 Hz for typical lighting in the training room (input 150-700 from LDR)
  tone(speakerPin, pitch);
  if(pitch <= 1000) setColor(255, 0, 0);  // red
  else if (pitch > 1000 and pitch <= 2000) setColor(0, 255, 0);  // green
  else if (pitch > 2000) setColor(0, 0, 255);  // blue

  Serial.print("Analog reading = ");
  Serial.print(photocellReading);     // the raw analog reading
  Serial.print("\tPitch = ");
  Serial.println(pitch);
  //delay(10);
  //noTone(speakerPin);
  //delay(1000);
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
