#include <Servo.h>
int NO_LINE = LOW; // También podría ponerse 0
int LINE = HIGH; // También podría ponerse 1
Servo servoLeft;
Servo servoRight;
int pinIrDer = 3;
int pinIrIzq = 2;
int pinServoRight = 9;
int pinServoLeft = 8;

void setup(){
 Serial.begin(9600); // Descomentar si queréis debuguear por consola
 pinMode(pinIrDer, INPUT);
 pinMode(pinIrIzq, INPUT);

 servoLeft.attach(pinServoLeft);
 servoRight.attach(pinServoRight);
}
void loop(){
  //seguir línea (hacia delante)
 if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == LINE) {
  servoLeft.write(0);
  servoRight.write(180);
 //rotar izq
 } else if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == NO_LINE) {
    servoLeft.write(180);
    servoRight.write(180);
 //rotar derecha
 } else if (digitalRead(pinIrIzq) == NO_LINE && digitalRead(pinIrDer) == LINE) {
      servoLeft.write(0);
    servoRight.write(0);
 //parado
 } else if (digitalRead(pinIrIzq) == NO_LINE && digitalRead(pinIrDer) == NO_LINE) {
      servoLeft.write(90);
    servoRight.write(90);
  }
}
