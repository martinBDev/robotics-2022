#include <Servo.h>

Servo servo;


int pin_colision_1 = 2;
int pin_colision_2 = 3;//LadoMotor
bool colisionDelante;
bool colisionDetras;
bool seHaCalibrado = false;
unsigned long tiempoEsquinaIncia_EsquinaExtremo; //La inicial es la del motor
unsigned long tiempoEsquinaExtremo_EsquinaInicial;

int coordenadaActual = 0;
unsigned long tiempoEntreCoordenadas;
int numeroCoordenadas = 24; //Valor por defecto
int coordenadaObjetivo = 10;

void setup() {
  // put your setup code here, to run once:
 
 Serial.begin(9600);
 servo.attach(8);
}


void leerNumeroCoordenadasPorConsola(){
    Serial.println("Introducir numero de coordenadas:");
    while(Serial.available() == 0){

    }
    
    String input = Serial.readString();
    while(input.toInt() == 0){
      Serial.println("Introducir numero de coordenadas:");

      while(Serial.available() == 0){
        
      }
       input = Serial.readString();
      
    }

    numeroCoordenadas = input.toInt();


}


void introducirCoordenadaObjetivo(){

    Serial.println("Introducir coordenada objetivo:");
    while(Serial.available() == 0){

    }
    
    //String input = Serial.readString();
    //bool isZero = strcmp(input,"0");
    //Serial.println(input);
    //Serial.println(isZero);

    String input = Serial.readString();
    input.trim();
    Serial.println(input);
    if(input != "0" && input.toInt() == 0){
      Serial.println("Valor invalido, introducir coordenada objetivo:");

      while(Serial.available() == 0){
         
      }
       input = Serial.readString();
      
    }

    coordenadaObjetivo = input.toInt();
  
}


void loop(){

    colisionDelante = digitalRead(pin_colision_2) == 0; //0 si se pulsa
    colisionDetras = digitalRead(pin_colision_1) == 0;

if(!seHaCalibrado){
    leerNumeroCoordenadasPorConsola();
    goToInitialPos(); //Va hasta la esquina del motor: esquina inicial
    doPath(); //Va a la esquina contraria y luego vuelve a la esquina inicial, así medimos los tiempos de la ida y de la vuelta (son diferentes).
    
    while(true){
      introducirCoordenadaObjetivo();
      moverACoordenada(coordenadaObjetivo);
    }

}

  
}

void goToInitialPos(){

colisionDetras = digitalRead(pin_colision_1) == 0;

  while(!colisionDetras){
        servo.write(0);
        colisionDetras = digitalRead(pin_colision_1) == 0;
      }

      servo.write(90);

  
}

void doPath(){

  //Medimos tiempo Incial-extremo  
  unsigned long tiempo1 = millis();


  while(!colisionDelante && !seHaCalibrado){
        servo.write(180);
        colisionDelante = digitalRead(pin_colision_2) == 0;
      }

      servo.write(90);

      tiempoEsquinaIncia_EsquinaExtremo = millis()-tiempo1;

    //Medimos tiempo extremo-inicial
    unsigned long tiempo2 = millis();
    goToInitialPos();
    tiempoEsquinaExtremo_EsquinaInicial = millis() - tiempo2;

    servo.write(90);



    seHaCalibrado = true;
}

void moverACoordenada(int coordenada){

  

  if(coordenada < 0){
    Serial.println("Es menor que cero");
    coordenada = 0;
  }

  if(coordenada > numeroCoordenadas){
    Serial.println("Es mayor que cero");
    coordenada = numeroCoordenadas;
  }

    colisionDelante = digitalRead(pin_colision_2) == 0; //0 si se pulsa
    colisionDetras = digitalRead(pin_colision_1) == 0;

int tiempoEntreCoordenadas = 0;
if(coordenada > coordenadaActual){
    tiempoEntreCoordenadas = tiempoEsquinaIncia_EsquinaExtremo/numeroCoordenadas;
  servo.write(180);
  delay((coordenada-coordenadaActual)*tiempoEntreCoordenadas);
  coordenadaActual = coordenada;
    
} else if(coordenada < coordenadaActual){
    tiempoEntreCoordenadas = tiempoEsquinaExtremo_EsquinaInicial/numeroCoordenadas;
  servo.write(0);
  delay((coordenadaActual-coordenada)*tiempoEntreCoordenadas);
  coordenadaActual = coordenada;
}

  servo.write(90);

  delay(1000);

}

int prevDireccion = 180; //direccion por defecto modo automatico
