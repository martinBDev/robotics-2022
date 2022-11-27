  //AUTORES:
  //Martin Beltran Diaz - UO276244
  //Stelian Adrian Stanci - UO277653
  //Laura Pernia Blanco - UO276264

#include <Servo.h>

Servo servo;
int boton_pin = 9; // Pin digital para el botón
int X_pin = A0; // Pin analógico para leer eje X
int Y_pin = A1; // Pin analógico para leer eje Y

//Para activar modo automatico
bool modoAutomatico=false;

int pin_colision_1 = 3;
int pin_colision_2 = 2;//Pines de colision

int centro_X = 486;//Valores del centro del joystick que no está exactamente en el centro (512,512)
int centro_Y = 501;
int margen = 10; //Margen para detectar movimiento joystick 

void setup() {
  // put your setup code here, to run once:
 //3.-
 Serial.begin(9600);
 servo.attach(8);
 pinMode(boton_pin, INPUT_PULLUP); 
 pinMode(X_pin, INPUT);
 pinMode(Y_pin,INPUT);
}

void loop(){


    bool colisioDelante = digitalRead(pin_colision_2) == 0; //0 si se pulsa
    bool colisionDetras = digitalRead(pin_colision_1) == 0;

    //Pulsado == 0
    int botonPulsado = digitalRead(boton_pin);

    if(botonPulsado == 0){
      modoAutomatico = !modoAutomatico;
    }

    Serial.println(botonPulsado);

    int valorX = analogRead(X_pin);

    int valorY = analogRead(Y_pin);

    if(modoAutomatico){
      automaticoControl( colisioDelante, colisionDetras);
    }else{
        manualControl(valorX,valorY, colisioDelante, colisionDetras);
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

int prevDireccion = 180; //direccion por defecto modo automatico
void automaticoControl(bool colisioDelante,bool colisionDetras){

    if(colisioDelante){
      prevDireccion = 0;
     
    }else if(colisionDetras){
      prevDireccion = 180;
      
    }

    if(prevDireccion != servo.read()){
 servo.write(prevDireccion);
    }
   

}

  void manualControl(int valorX, int valorY,
   bool colisioDelante, bool colisionDetras){
      
    if(valorX > 913 ){

      if(!colisioDelante){
        //rapido delante
         servo.write(180);
      }else{
        servo.write(90);
      }
      
    
    }else if(valorX <= 913 && valorX > centro_X + margen ){

        if(!colisioDelante){
            // despacio delante
            servo.write(105);
        }else{
        servo.write(90);
      }
      
    }else if(valorX <= centro_X + margen && valorX >= centro_X - margen ){
      //Quieto
      servo.write(90);
    }else if(valorX < centro_X - margen && valorX >= 100 ){

        if(!colisionDetras){
              //despacio atras 
              servo.write(75);
        }else{
        servo.write(90);
      }
      
    }else if( valorX < 100 ){

      if(!colisionDetras){
          //rapido atras 
          servo.write(0);
      }else{
        servo.write(90);
      }
    
    }
  }
