//AUTORES:
//Martin Beltran Diaz - UO276244
//Stelian Adrian Stanci - UO277653
//Laura Pernia Blanco - UO276264


//Ambos potenciometros
int potencLeer = A1; //Decide qué luces encender
int potencLumen = A2; //Decide qué potencia darles

int led1 = 11;
int led2 = 10;
int led3 = 9;

//Solo modificamos las luces encendidas y su potencia si hay cambio respecto al valor leido con anterioridad
int estadoAnterior = 0;
int potenciaAnterior = 0;
int paso = 1023/7; //Estado


void setup()
{
  Serial.begin(9600); // Iniciar el Serial
  
  pinMode(potencLeer, INPUT);
  pinMode(potencLumen,INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop()
{

  // Comprobamos si algún potenciómetro ha cambiado su valor
  if(analogRead(potencLeer) != estadoAnterior
    || analogRead(potencLumen)/4 != potenciaAnterior) {
    
    // Ha cambiado, por lo que vemos qué luces hay que encender y
    //con qué otencia
  	estadoAnterior = analogRead(potencLeer);
    potenciaAnterior = analogRead(potencLumen)/4;
    
    // Para comprobar qué combinación de luces hacer
    int combi = estadoAnterior/paso;
    
    apagarTodas();
    if(combi == 1){
      	analogWrite(led1, potenciaAnterior);
    } else if(combi == 2){
      	analogWrite(led2, potenciaAnterior);
    } else if(combi == 3){
      	analogWrite(led3, potenciaAnterior);
    } else if(combi == 4){
      	analogWrite(led1, potenciaAnterior);
        analogWrite(led2, potenciaAnterior);
    } else if(combi == 5){
      	analogWrite(led2, potenciaAnterior);
        analogWrite(led3, potenciaAnterior);
    } else if(combi == 6){
        analogWrite(led1, potenciaAnterior);
      	analogWrite(led3, potenciaAnterior);
    } else if(combi == 7){
        analogWrite(led1, potenciaAnterior);
        analogWrite(led2, potenciaAnterior);
      	analogWrite(led3, potenciaAnterior);
    }
  }
}


void apagarTodas(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}
