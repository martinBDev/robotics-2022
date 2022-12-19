
  //AUTORES:
  //Martin Beltran Diaz - UO276244
  //Stelian Adrian Stanci - UO277653
  //Laura Pernia Blanco - UO276264
#include <Servo.h>
//Se va a usar la libreria REGEXP para parsear el input por consola
#include <Regexp.h>
#include <ctype.h>
Servo servo;


int pin_colision_1 = 2;
int pin_colision_2 = 3;//LadoMotor
bool colisionDelante;
bool colisionDetras;
bool seHaCalibrado = false;
unsigned long tiempoEsquinaIncia_EsquinaExtremo; //La inicial es la del motor
unsigned long tiempoEsquinaExtremo_EsquinaInicial;
//int coordenada = 20;
int coordenadaActual = 0;
unsigned long tiempoEntreCoordenadas;


int numeroCoordenadas = 50;

String userInput = "";

int coordsToGo[] = {};
int timeToWait[] = {};
int countEntries = 0;


void setup() {
  // put your setup code here, to run once:
 
 Serial.begin(9600);
 servo.attach(8);
}


void getUserInout(){

  Serial.println("Introduce coordenadas:");
  while(Serial.available()== 0){
    
  }

  userInput = Serial.readString();
  Serial.println(userInput);
}


bool getUserInputV2(){

  String coord = "";
  String times = "";
  Serial.println("METE CORD;");
  while(Serial.available() == 0){

    

  }



  String input = Serial.readString();

  int modes = 1; //Modo 1 => coordenada, modo 2 => tiempo
  for(int i = 0; i < input.length()-1; i++){

      if (isDigit(coord.charAt(i))){
           if(modes == 1){
              coord += coord.charAt(i);
           }else{
            
           }
      }else{
        if(modes == 1){ modes = 2;}
        else {modes == 1;}
         coord = ""; times = "";
      }
    
  }
  

  coord = Serial.readStringUntil(",");
  for(int i = 0; i < coord.length()-1; i++){
    if(!isDigit(coord.charAt(i))){
      Serial.println("Valor no numerico");
      return false;
    }
  }

    
  
    Serial.println(coord);
    times = Serial.readStringUntil(";");
    for(int i = 0; i < times.length()-1; i++){
      if(!isDigit(times.charAt(i))){
        Serial.println("Valor no numerico");
        return false;
      }
    }


    coordsToGo[countEntries] = coord.toInt();
    timeToWait[countEntries] = coord.toInt();
    countEntries++;


}



void loop(){

    colisionDelante = digitalRead(pin_colision_2) == 0; //0 si se pulsa
    colisionDetras = digitalRead(pin_colision_1) == 0;

if(!seHaCalibrado){

    goToInitialPos(); //Va hasta la esquina del motor: esquina inicial
    doPath(); //Va a la esquina contraria y luego vuelve a la esquina inicial, así medimos los tiempos de la ida y de la vuelta (son diferentes).
   

}else{
  
   if(getUserInputV2()){

      for(int i = 0; i < countEntries; i++){
        moverACoordenada(coordsToGo[i], timeToWait[i]);
      }
    
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

void moverACoordenada(int coordenada, int timeToAwait){

  

  if(coordenada < 0){
    Serial.println("Es menor que cero");
    coordenada = 0;
  }

  if(coordenada > numeroCoordenadas){
    Serial.print("Es mayor que el limite: ");
    Serial.println(numeroCoordenadas);
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

  delay(timeToAwait);

}

int prevDireccion = 180; //direccion por defecto modo automatico
