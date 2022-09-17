 //AUTORES:
  //Martin Beltran Diaz - UO276244
  //Stelian Adrian Stanci - UO277653
  //Laura Pernia Blanco - UO276264

int rojo1 = 12;
int azul1 = 11;
int verde1 = 10;

int rojo2 = 7;
int azul2 = 6;
int verde2 = 5;


int pinCebraVerde = 3;
int pinCebraRojo = 4;
int buzzer = 2;

int semaforos[][3] = { 
  {rojo1,azul1,verde1},
  {rojo2,azul2,verde2}
};

int semaforo1 = 0;
int semaforo2 = 1;

void setup()
{
    pinMode(rojo1,OUTPUT);
    pinMode(azul1,OUTPUT);
    pinMode(verde1,OUTPUT);
    pinMode(rojo2,OUTPUT);
    pinMode(azul2,OUTPUT);
    pinMode(verde2,OUTPUT);
    pinMode(pinCebraVerde,OUTPUT);
    pinMode(pinCebraRojo,OUTPUT);
    pinMode(buzzer,OUTPUT);

    digitalWrite(pinCebraRojo, HIGH); //Encender LUZ ROJO  de peatones
    digitalWrite(buzzer, LOW); //aPAGAR Buzzer por si acaso, que a veces puede hacer ruidos "residuales"(?) molestos
}

void loop()
{

//Se pone en verde el semaforo 1 y en rojo el de peatones
  secuencia1(semaforo1,semaforo2);
  delay(3000);

  secuencia2(semaforo1);

  delay(2000);
  abrirPasosDePeatones();
  proximoCierrePasoDePeatones();
  cerrarPasosDePeatones();
  delay(2000);

  secuencia3(semaforo2);
  
  
  //Se pone en verde el de peatones y en rojo el semaforo 1
  secuencia1(semaforo2,semaforo1);
  delay(3000);

  secuencia2(semaforo2);

  delay(2000);
  abrirPasosDePeatones();
  proximoCierrePasoDePeatones();
  cerrarPasosDePeatones();
  delay(2000);

  secuencia3(semaforo1);
  
  
 
  
}


void abrirPasosDePeatones(){
    digitalWrite(pinCebraRojo, LOW); //Encender LUZ ROJO  de peatones
    digitalWrite(pinCebraVerde, HIGH); //Encender LUZ VERDE  de peatones
    for(int i = 0; i < 5; i++){
        tone(buzzer, 5000, 1500);
        delay(2000);
    }

    digitalWrite(buzzer, LOW);
}

void proximoCierrePasoDePeatones(){

    
    for(int i = 0; i < 5; i++){
        digitalWrite(pinCebraVerde, HIGH); //Encender LUZ VERDE  de peatones
        tone(buzzer, 10000, 500);
        digitalWrite(pinCebraVerde, LOW); //Apagar LUZ VERDE  de peatones
        delay(1000);
    }

    digitalWrite(buzzer, LOW);

}

void cerrarPasosDePeatones(){
    digitalWrite(pinCebraRojo, HIGH); //Encender LUZ ROJO  de peatones
}

void establecerAmarillo(int semaforo, int state){
    //Amarillo = verde + rojo

    digitalWrite(semaforos[semaforo][0], state); //Encender en rojo
    digitalWrite(semaforos[semaforo][2], state); //Encender en verde
}

void establecerRojo(int semaforo, int state){

    digitalWrite(semaforos[semaforo][0], state); //Encender en rojo
}

void establecerVerde(int semaforo, int state){
    digitalWrite(semaforos[semaforo][2], state); //Encender en rojo
}


//cuando un semáforo esté en verde, el otro estará en rojo. 
void secuencia1(int semaforoVerdeActual , 
               int semaforoRojoActual){
  
  establecerRojo(semaforoRojoActual, HIGH);
  establecerVerde(semaforoVerdeActual, HIGH);

    //Enciende el color correcto del paso de peatones, y el buzzer si es necesario
  
  
}

//Después de un tiempo, 
//el semáforo que está en verde tendrá que pasar a amarillo, y, tras unos segundos, a rojo
void secuencia2(int semaforoVerdeAAmarilloARojo){
  
  establecerVerde(semaforoVerdeAAmarilloARojo, LOW);//Se apaga la verde
  
  establecerAmarillo(semaforoVerdeAAmarilloARojo, HIGH); //El que estaba en verde pasa a amarillo

  delay(1500);

  establecerAmarillo(semaforoVerdeAAmarilloARojo, LOW); //El que estaba en amarillo se apaga
  
  establecerRojo(semaforoVerdeAAmarilloARojo,HIGH);//El que estaba en amarillo pasa a rojo
  
  
}

//Tras una breve pausa para
//esperar a que los coches terminen de cruzar, el otro deberá de ponerse en verde y repetir el
//mismo proceso.
void secuencia3(int rojoPasaAVerde){
  
  establecerRojo(rojoPasaAVerde,LOW);//El que estaba en rojo SE APAGA
  establecerVerde(rojoPasaAVerde,HIGH);//El que estaba en rojo pasa a verde
  
  
}
