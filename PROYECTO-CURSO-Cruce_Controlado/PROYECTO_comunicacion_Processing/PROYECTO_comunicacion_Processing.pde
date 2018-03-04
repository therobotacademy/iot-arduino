/*
  theRobotAcademy.com
  by B. Ronquillo
  Arduino + Processing: Primeros Pasos
*/

import processing.serial.* ;
Serial ComPort;
String input[];

void setup() {
 /* String portName = Serial.list()[0];
  ComPort = new Serial(this, portName, 9600);
  ComPort.bufferUntil('\n');
  */
  
  println(Serial.list()); //Visualiza los puertos serie disponibles en la consola de abajo
  int port_index = 0; // Indice del puerto seleccionado
  ComPort = new Serial(this, Serial.list()[port_index], 9600); //Abre el puerto serie COM4
  print(ComPort.list()[port_index]);
  
  input = loadStrings("http://app.therobotacademy.com/arduino01/trafico.txt");
  if (input.length != 0){
  String s_current = input[0];
  print("\nESTADO DE ARRANQUE (0: valle, 1:punta)\t"); println(s_current);
  }
   
  }

void draw(){
  input = loadStrings("http://app.therobotacademy.com/arduino01/trafico.txt");
  if (input != null) {
    if (input.length != 0) {
      String s_last = input[0];
      int last = Integer.parseInt(s_last);
      delay(1000);
      input = loadStrings("http://app.therobotacademy.com/arduino01/trafico.txt");
      if (input.length != 0){
        String s_current = input[0];
        int current = Integer.parseInt(s_current);
        if(current != last)  {
          print("\nAnterior (0: valle, 1:punta)\t"); println(last);
          print("Actual   (0: valle, 1:punta)\t"); println(current);
          //ComPort.write(current);
          if (current == 0) {
            ComPort.write("valle");
          }
          else if (current == 1) {
            ComPort.write("punta");
          }
        }
      }
    }
  }
  delay(1000);
}