/* Better Debouncer
 * 
 * This debouncing circuit is more rugged, and will work with tilt switches!
 *
 * 
 */
 
int inPin = 2;         // the number of the input pin
int outPin = 11;       // the number of the output pin
 
int LEDstate = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin
 
// the following variables are long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 50;   // the debounce time (milliseconds), increase if the output flickers
 
void setup()
{
  pinMode(inPin, INPUT);
  /* Only if you miss the external pull-up resistor
  digitalWrite(inPin, HIGH);   // turn on the built in pull-up resistor
  */
  pinMode(outPin, OUTPUT);
  Serial.begin(9600); 
}
 
void loop()
{
  int switchstate;
 
  reading = digitalRead(inPin);
 
  // If the switch changed, due to bounce or pressing...
  if (reading != previous) {
    // reset the debouncing timer
    time = millis();
  } 
 
  if ((millis() - time) > debounce) {
     // whatever the switch is at, its been there for a long time
     // so lets settle on it!
     switchstate = reading;
 
     // Now invert the output on the pin13 LED
    if (switchstate == HIGH)
      LEDstate = HIGH;
    else
      LEDstate = LOW;
  }
  digitalWrite(outPin, LEDstate);
 
  // Save the last reading so we keep a running tally
  previous = reading;

  /* Debug
   */ 
  Serial.print("Previous reading= ");
  Serial.print(previous);
  Serial.print("\tPresent reading= ");
  Serial.print(reading);
  Serial.print("\tLED state= ");
  Serial.println(LEDstate);
  delay(200);
  
}
