//AUTORES:
//Martin Beltran Diaz - UO276244
//Stelian Adrian Stanci - UO277653
//Laura Pernia Blanco - UO276264

int potencLeer = A0;

int led1 = 7;
int led2 = 6;
int led3 = 5;

int valorAnterior = 0;
int paso = 1023/7;


void setup()
{
  Serial.begin(9600); // Iniciar el Serial
  
  pinMode(potencLeer, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop()
{
  // Comprobamos si el potenciómetro ha cambiado su valor
  if(analogRead(potencLeer) != valorAnterior) {
    
    // Ha cambiado, por lo que vemos qué luces hay que encender
  	valorAnterior = analogRead(potencLeer);
    
    // Para comprobar qué combinación de luces hacer
    int combi = valorAnterior/paso;
    
    if(combi == 0){
    	apagarTodas();
    } else if(combi == 1){
    	apagarTodas();
      	digitalWrite(led1, HIGH);
    } else if(combi == 2){
    	apagarTodas();
      	digitalWrite(led2, HIGH);
    } else if(combi == 3){
    	apagarTodas();
      	digitalWrite(led3, HIGH);
    } else if(combi == 4){
    	apagarTodas();
      	digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
    } else if(combi == 5){
    	apagarTodas();
      	digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
    } else if(combi == 6){
    	apagarTodas();
        digitalWrite(led1, HIGH);
      	digitalWrite(led3, HIGH);
    } else if(combi == 7){
    	apagarTodas();
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
      	digitalWrite(led3, HIGH);
    }
  }
}


void apagarTodas(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}
