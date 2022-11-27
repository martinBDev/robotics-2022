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
int pinIzqExt = 11;
int pinDerExt = 10;
int pinServoRight = 9;
int pinServoLeft = 8;

void setup() {
  Serial.begin(9600); // Descomentar si queréis debuguear por consola
  pinMode(pinIrDer, INPUT);
  pinMode(pinIrIzq, INPUT);
    pinMode(pinIzqExt, INPUT);
  pinMode(pinDerExt, INPUT);

  servoLeft.attach(pinServoLeft);
  servoRight.attach(pinServoRight);

  delay(5000);

}

void loop() {
  //seguir hacia delante
  if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == LINE && digitalRead(pinIzqExt) == NO_LINE && digitalRead(pinDerExt) == NO_LINE) {
    servoLeft.write(0);
    servoRight.write(180);
   //giro 180º (se acaba la linea)
  } else if (digitalRead(pinIrIzq) == NO_LINE && digitalRead(pinIrDer) == NO_LINE && digitalRead(pinIzqExt) == NO_LINE && digitalRead(pinDerExt) == NO_LINE){
    servoLeft.write(0);
    servoRight.write(0);
   //corregir trayectoria
  } else if (digitalRead(pinIrIzq) == NO_LINE && digitalRead(pinIrDer) == LINE) {
    girarDerecha();
   //corregir trayectoria
   } else if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == NO_LINE) {
      girarIzquierda();
    //girar a la derecha
   } else if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == LINE &&  digitalRead(pinDerExt) == LINE){
      delay(232);
      girarDerecha();
      delay(800);
    //wsbjbjd
   } else if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == LINE &&  digitalRead(pinDerExt) == NO_LINE && digitalRead(pinIzqExt) == LINE) {
      delay(120);
      if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == LINE) {
        //tiene que seguir recto 
        } else {
          delay(100);
          girarIzquierda();
          delay(800);
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
