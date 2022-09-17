// C++ code
//

int rojo1 = 12;
int amarillo1 = 11;
int verde1 = 10;

int rojo2 = 7;
int amarillo2 = 6;
int verde2 = 5;

int semaforos[][3] = { 
  {rojo1,amarillo1,verde1},
  {rojo2,amarillo2,verde2}
};

int semaforo1 = 0;
int semaforo2 = 1;

void setup()
{
    pinMode(rojo1,OUTPUT);
    pinMode(amarillo1,OUTPUT);
    pinMode(verde1,OUTPUT);
    pinMode(rojo2,OUTPUT);
    pinMode(amarillo2,OUTPUT);
    pinMode(verde2,OUTPUT);
}

void loop()
{

  secuencia1(semaforo1,semaforo2);
  delay(3000);

  secuencia2(semaforo1);
  delay(3000);

  secuencia3(semaforo2);
  delay(3000);
  
  
  
  secuencia1(semaforo2,semaforo1);
  delay(3000);

  secuencia2(semaforo2);
  delay(3000);

  secuencia3(semaforo1);
  delay(3000);
  
 
  
}

//cuando un semáforo esté en verde, el otro estará en rojo. 
void secuencia1(int semaforoVerdeActual , 
               int semaforoRojoActual){
  
  digitalWrite(semaforos[semaforoRojoActual][0], HIGH); //Uno en rojo
  digitalWrite(semaforos[semaforoVerdeActual][2], HIGH); //Otro en verde
  
}

//Después de un tiempo, 
//el semáforo que está en verde tendrá que pasar a amarillo, y, tras unos segundos, a rojo
void secuencia2(int semaforoVerdeAAmarilloARojo){
  
  digitalWrite(semaforos[semaforoVerdeAAmarilloARojo][2], LOW); //Se apaga la verde
  
  digitalWrite(semaforos[semaforoVerdeAAmarilloARojo][1], HIGH); //El que estaba en verde pasa a amarillo
  delay(1500);
  digitalWrite(semaforos[semaforoVerdeAAmarilloARojo][1], LOW); //El que estaba en amarillo se apaga
  
  digitalWrite(semaforos[semaforoVerdeAAmarilloARojo][0], HIGH); //El que estaba en amarillo pasa a rojo
  
  
}

//Tras una breve pausa para
//esperar a que los coches terminen de cruzar, el otro deberá de ponerse en verde y repetir el
//mismo proceso.
void secuencia3(int rojoPasaAVerde){
  
  digitalWrite(semaforos[rojoPasaAVerde][0], LOW); //El que estaba en rojo SE APAGA
  digitalWrite(semaforos[rojoPasaAVerde][2], HIGH); //El que estaba en rojo pasa a verde
  
  
}
