  //AUTORES:
  //Martin Beltran Diaz - UO276244
  //Stelian Adrian Stanci - UO277653
  //Laura Pernia Blanco - UO276264

#include <Servo.h>
int NO_LINE = LOW; // También podría ponerse 0
int LINE = HIGH; // También podría ponerse 1

Servo servoLeft;
Servo servoRight;
int pinIrDer = 3;
int pinIrIzq = 2;
int pinIzqExt = 10;
int pinDerExt = 11;
int pinServoRight = 9;
int pinServoLeft = 8;

String caminoSeguido = "";
String caminoOptimo = "";

void setup() {
  Serial.begin(9600); // Descomentar si queréis debuguear por consola
  pinMode(pinIrDer, INPUT);
  pinMode(pinIrIzq, INPUT);
    pinMode(pinIzqExt, INPUT);
  pinMode(pinDerExt, INPUT);

  servoLeft.attach(pinServoLeft);
  servoRight.attach(pinServoRight);

  delay(5000);

  

  bool caminoEncontrado = false;

}

void loop() {
  if (!caminoEncontrado) {
  //seguir hacia delante
  if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == LINE && digitalRead(pinIzqExt) == NO_LINE && digitalRead(pinDerExt) == NO_LINE) {
    servoLeft.write(0);
    servoRight.write(180);
   //giro 180º (se acaba la linea)
  } else if (digitalRead(pinIrIzq) == NO_LINE && digitalRead(pinIrDer) == NO_LINE && digitalRead(pinIzqExt) == NO_LINE && digitalRead(pinDerExt) == NO_LINE){
    caminoSeguido += "R";
    servoLeft.write(0);
    servoRight.write(0);
   //corregir trayectoria
  } else if (digitalRead(pinIrIzq) == NO_LINE && digitalRead(pinIrDer) == LINE) {
    girarDerecha();
   //corregir trayectoria
   } else if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == NO_LINE) {
      girarIzquierda();
   } else if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == LINE &&  digitalRead(pinDerExt) == LINE && digitalRead(pinIzqExt) == LINE) {
      delay(160);
      // ES LA META
      if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == LINE &&  digitalRead(pinDerExt) == LINE && digitalRead(pinIzqExt) == LINE) {
          servoLeft.write(90);
          servoRight.write(90);
          delay(10000);
          calcularCaminoOptimo();
      } else {
        caminoSeguido += "D";
        girarDerecha();
        delay(800);
      }
      
    //girar a la derecha
   } else if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == LINE &&  digitalRead(pinDerExt) == LINE){
      delay(232);
      girarDerecha();
      delay(800);
   } else if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == LINE &&  digitalRead(pinDerExt) == NO_LINE && digitalRead(pinIzqExt) == LINE) {
      delay(120);
      if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == LINE) {
        //tiene que seguir recto
        caminoSeguido += "A";
        } else {
          delay(100);
          girarIzquierda();
          delay(800);
          }
    } 
  } else {
    /// que siga camino óptimo.
  }
}

void calcularCaminoOptimo() {
  while (strlen(caminoOptimo) == 0 || caminoOptimo.indexOf("R") > 0) {
  for (int i = 0; i<strlen(caminoSeguido); i++){
    if (caminoSeguido[i] == 'R') {
      if (caminoSeguido[i-1] == 'A' && caminoSeguido[i+1] == 'D') {
        caminoOptimo = caminoOptimo.substring(0,strlen(caminoOptimo)-2) + 'I';
        i += 1;
      } else if (caminoSeguido[i-1] == 'D' && caminoSeguido[i+1] == 'D') {
        caminoOptimo = caminoOptimo.substring(0,strlen(caminoOptimo)-2) + 'A';
        i += 1;
      } else if (caminoSeguido[i-1] == 'D' && caminoSeguido[i+1] == 'A') {
        caminoOptimo = caminoOptimo.substring(0,strlen(caminoOptimo)-2) + 'I';
        i += 1;
      } else if (caminoSeguido[i-1] == 'I' && caminoSeguido[i+1] == 'D') {
        caminoOptimo = caminoOptimo.substring(0,strlen(caminoOptimo)-2) + 'R';
        i += 1;
      }
    } else {
        caminoOptimo += caminoSeguido[i];
    } 
  }
}
}

void girarDerecha(){

  servoLeft.write(0);
  servoRight.write(0);
}

void girarIzquierda() {
  servoLeft.write(180);
  servoRight.write(180);
}