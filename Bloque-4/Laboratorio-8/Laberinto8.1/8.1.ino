#include <Servo.h>
int NO_LINE = LOW; // También podría ponerse 0
int LINE = HIGH; // También podría ponerse 1
Servo servoLeft;
Servo servoRight;
int pinIrDer = 3;
int pinIrIzq = 2;
int pinIzqExt = 1;
int pinDerExt = 6;
int pinServoRight = 9;
int pinServoLeft = 8;

void setup(){
 Serial.begin(9600); // Descomentar si queréis debuguear por consola
 pinMode(pinIrDer, INPUT);
 pinMode(pinIrIzq, INPUT);

 servoLeft.attach(pinServoLeft);
 servoRight.attach(pinServoRight);

 delay(5000);
}

void loop(){

  if(hayCaminoDelante() && hayCaminoDrch() && hayCaminoIzq()){ //Condicion 6-7-8
    //Lo q dice adri
   girarDerecha();
   servoLeft.write(0);
   servoRight.write(180);
   delay(1000);
   
  }else if(hayCaminoDrch()){
    servoLeft.write(0);
   servoRight.write(180);
   delay(300);
   //GIRAR DERECHA 
   girarDerecha();
   //P lante con un delay
   servoLeft.write(0);
   servoRight.write(180);
   delay(300);
  }else if(hayCaminoDelante() ){
    //seguir palante (no comprobamos camino nizq)
    //correcciones de trayectoria

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
  }else if(hayCaminoIzq()){
    //gira izq
    girarIzq();
  }else if( !(hayCaminoDelante() || hayCaminoDrch() || hayCaminoIzq()) ){ ///se salio del camino gira 180º
    //girar 180
    cientoOchenta();
  }
  
}


void cientoOchenta(){
  servoLeft.write(180);
    servoRight.write(180);
    delay(3500); //delay pa girar
}

void girarDerecha(){
  servoLeft.write(0);
    servoRight.write(0);
    delay(1750); //delay pa girar
}

void girarIzq(){
  
    servoLeft.write(180);
    servoRight.write(180);
    delay(1750); //delay pa girar
  
}




//TRUE si hay camino delante
  bool hayCaminoDelante(){

    return (digitalRead(pinIrIzq) == LINE || digitalRead(pinIrDer) == LINE);
  }

  //TRUE si hay camino derecha
  bool hayCaminoDrch(){
    return digitalRead(pinDerExt) == LINE;
  }

//TRUE si hya camino izq
  bool hayCaminoIzq(){
    return digitalRead(pinIzqExt) == LINE;
  }
