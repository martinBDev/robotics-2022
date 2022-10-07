#include <Servo.h>

Servo servo;
int boton_pin = 9; // Pin digital para el botón
int X_pin = A0; // Pin analógico para leer eje X
int Y_pin = A1; // Pin analógico para leer eje Y


int centro_X = 486;//Valores del centro del joystick que no está exactamente en el centro (512,512)
int centro_Y = 501;
int margen = 10; //Margen para detectar movimiento joystick 

void setup() {
  // put your setup code here, to run once:
 //3.-
 Serial.begin(9600);
 servo.attach(8);
 pinMode(boton_pin, INPUT_PULLUP); 
}
void loop(){



    int valorX = analogRead(X_pin);

    int valorY = analogRead(Y_pin);



    if(valorX > 913){
      //rapido derecha
      servo.write(180);
    
    }else if(valorX <= 913 && valorX > centro_X + margen){

      // despacio derecha
      servo.write(105);
    }else if(valorX <= centro_X + margen && valorX >= centro_X - margen ){
      //Quieto
      servo.write(90);
    }else if(valorX < centro_X - margen && valorX >= 100){
      //despacio iz 
      servo.write(75);
    }else{
    //rapido iz 
      servo.write(0);
    }


    /*
    

    //5.- s
    Serial.println("Enviar: detener");
    servo.write(90);
    delay(2000);

    // Otros valores entre (0-84) y (93-180) hacen que gire
    //más despacio cuanto más cercano al 90 y más rápido cuanto más
    //cercano al 0 y 180
    */
}
