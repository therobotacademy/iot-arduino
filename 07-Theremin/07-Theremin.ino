/*
Adafruit Arduino - Lesson 10. Pseudo Thermin
*/

int speakerPin = 12;
int photocellPin = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int photocellReading = analogRead(photocellPin);
  int pitch = 200 + photocellReading / 4 ;
  tone(speakerPin, pitch);

  Serial.print("Analog reading = ");
  Serial.print(photocellReading);     // the raw analog reading
  Serial.print("\tPitch = ");
  Serial.println(pitch);
  //delay(10);
  //noTone(speakerPin);
  //delay(1000);
}
