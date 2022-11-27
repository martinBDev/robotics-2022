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
int pinServoRight = 9;
int pinServoLeft = 8;


int lineaEncontrada = false;
int lastLeftMov = 0;
int lastRightMov = 0;

void setup(){
 Serial.begin(9600); // Descomentar si queréis debuguear por consola
 pinMode(pinIrDer, INPUT);
 pinMode(pinIrIzq, INPUT);

 servoLeft.attach(pinServoLeft);
 servoRight.attach(pinServoRight);
 
}
void loop(){

  
  espiral(lineaEncontrada);

  
  //corregir trayectoria
   if(digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == NO_LINE) {
        servoLeft.write(0);
        
        servoRight.write(180);
        lastLeftMov = 0;
        lastRightMov = 180;
   } else if (digitalRead(pinIrIzq) == NO_LINE && digitalRead(pinIrDer) == LINE) {
        servoLeft.write(180);
        servoRight.write(0);
        lastLeftMov = 180;
        lastRightMov = 0;
   }

  //seguir línea
 if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == LINE) {
  servoLeft.write(0);
  servoRight.write(40);
  lastLeftMov = 0;
        lastRightMov = 40;
 } else if (digitalRead(pinIrIzq) == LINE && digitalRead(pinIrDer) == NO_LINE) {
    servoLeft.write(180);
    servoRight.write(0);
    lastLeftMov = 180;
        lastRightMov = 0;
 } else if (digitalRead(pinIrIzq) == NO_LINE && digitalRead(pinIrDer) == LINE) {
      servoLeft.write(0);
    servoRight.write(180);
    lastLeftMov = 0;
        lastRightMov = 180;
 } else if (digitalRead(pinIrIzq) == NO_LINE && digitalRead(pinIrDer) == NO_LINE) {
      servoLeft.write(180 - lastLeftMov);
      servoRight.write(180 - lastRightMov);
    
  }
}

void espiral(bool hayLinea){
  if(!hayLinea){

    
  int rango = 0;
  long millis1;
  while (digitalRead(pinIrIzq) == NO_LINE && digitalRead(pinIrDer) == NO_LINE) {

      
        //Palante
        servoLeft.write(0);
        servoRight.write(0);
        millis1 = millis();

        //Palante 3 segundos
        while(millis() - millis1 < 3000){
          if(digitalRead(pinIrIzq) == LINE || digitalRead(pinIrDer) == LINE){
            lineaEncontrada = true;
            return;
          }
        }
        
        //pATRÁ
        servoLeft.write(180);
        servoRight.write(180);
        //Patras 3 segundos
        while(millis() - millis1 < 3000){
          if(digitalRead(pinIrIzq) == LINE || digitalRead(pinIrDer) == LINE){
            lineaEncontrada = true;
            return;
          }
        }

       
        //Giro pa un lao
        servoLeft.write(0);
        servoRight.write(180);
        delay(500);


        
    }
    
  }
}
 
