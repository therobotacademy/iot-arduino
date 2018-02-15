int pushButton = 8;
int pushButton_Analog = A1;
int led = 5; // LED que responderá a la pulsación

int buttonState = 0;  // Estado del pulsador
int buttonAnalog = 0;  // Lectura analógica del pulsador

void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  buttonState = digitalRead(pushButton);
  buttonAnalog = analogRead(pushButton_Analog);
  Serial.print(buttonState);
  delay(1);

  if (buttonState == LOW) {   // Button NOT pressed
    digitalWrite(led, LOW);
    Serial.print("  Apago Led con valor analógico ");
  }
  else {
    digitalWrite(led, HIGH);  // // Button pressed
    Serial.print("\tEnciendo Led con valor analógico (voltios) ");
  }
  Serial.println((float)buttonAnalog/1023*5);
  delay(200);
}
