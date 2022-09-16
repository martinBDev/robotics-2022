  //PINES DE LOS LED
  int const led1 = 10;
  int const led2 = 11;
  int const led3 = 12;
  int const entradaPulsador = 7;

  

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // Iniciar el Serial
  Serial.println("Setup");

  //Definimos los pines como salida
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(entradaPulsador, INPUT);


  /* Si usamos el pin 0 para generar aleatorios,
 * este pin deberá de estar vacío, es decir, no puede
 * tener nada conectado.
 * Le pasaremos este pin al generador de semillas
 */
 int pinRandomSeed = 0;
 randomSeed(analogRead(pinRandomSeed));


}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  if(digitalRead(entradaPulsador) == HIGH){
    int rand = random(led1,led3 + 1);
    Serial.println(rand);
    apagarTodas();
    switch(rand){
      case led1:
        digitalWrite(led1, HIGH);
        break;
      case led2:
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        break;
      case led3:
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3,HIGH);
        break;
    }

  }

  
  

}


void apagarTodas(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3,LOW);

}
