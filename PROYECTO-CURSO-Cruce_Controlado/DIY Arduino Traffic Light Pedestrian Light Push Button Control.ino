int TrafficRed = 3;  
int TrafficYellow = 4;
int TrafficGreen = 5;
int PedestrianRed = 8;  
int PedestrianGreen = 9;
int button = 13; 
int crossTime = 4000;   
unsigned long buttonGap ; 
void setup () {
  pinMode(TrafficRed, OUTPUT);
  pinMode(TrafficYellow, OUTPUT);
  pinMode(TrafficGreen, OUTPUT);
  pinMode(PedestrianRed, OUTPUT);
  pinMode(PedestrianGreen, OUTPUT);
  pinMode(button, INPUT);
 
  digitalWrite(TrafficGreen,HIGH); 
  digitalWrite(PedestrianRed, HIGH);
}

void loop(){
  int state = digitalRead(button);
  if(state==HIGH && (millis() - buttonGap) > 5000) {
    switchLights();   
  }
}

void switchLights() {
  digitalWrite(TrafficGreen,LOW); 
  digitalWrite(TrafficYellow,HIGH); 
  delay(2000);

  digitalWrite(TrafficYellow,LOW);
  digitalWrite(TrafficRed,HIGH); 
  delay(1000);

  digitalWrite(PedestrianRed,LOW); 
  digitalWrite(PedestrianGreen,HIGH); 
  delay(crossTime);

  for (int x=0; x<10; x++){
    digitalWrite(PedestrianGreen,HIGH);
    delay(250);
    digitalWrite(PedestrianGreen,LOW);
    delay(250);
  }
 
  digitalWrite(PedestrianRed, HIGH); 
  delay(100);
 
  digitalWrite(TrafficRoadGreen,HIGH);
  digitalWrite(TrafficRoadRed,LOW);
 
  buttonGap = millis(); 
 
}