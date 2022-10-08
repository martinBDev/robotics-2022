  //AUTORES:
  //Martin Beltran Diaz - UO276244
  //Stelian Adrian Stanci - UO277653
  //Laura Pernia Blanco - UO276264

  
  //AUTORES:
  //Martin Beltran Diaz - UO276244
  //Stelian Adrian Stanci - UO277653
  //Laura Pernia Blanco - UO276264

//Definimos pines de LEDs
int pinLed1 = 5;
int pinLed2 = 6;
int pinLed3 = 9;
//Definimos pin del potenciometro
int pinPoten = A0;

void setup()
{

Serial.begin(9600);
Serial.println("Setup");
  pinMode(pinLed1,OUTPUT);
  pinMode(pinLed2,OUTPUT);
  pinMode(pinLed3,OUTPUT);
  pinMode(pinPoten,INPUT);
  
}

//Lista para acceder a los limites de input del potenciometro
int valoresLimiteLeds[][3] = {
  {1,32,63},
  {64,100,127},
  {128,160,191}
};

//Valores en los que todos los leds se encienden
int valoresComunesLeds[3] = {192,210,255};

int pinesArray[3] = {pinLed1,pinLed2,pinLed3};


//En funcion del led y del input del potenciometro, se decide cual y cuanto se enciende.
void ledProcessPoten(int numeroLed, int inputPoten){


  if(inputPoten == 0){

    analogWrite(pinLed1,0);
    analogWrite(pinLed2,0);
    analogWrite(pinLed3,0);

  }
  else if(inputPoten == valoresLimiteLeds[numeroLed-1][0]){

    apagarTodas();
    analogWrite(pinesArray[numeroLed-1], 1);


  }else if(inputPoten <= valoresLimiteLeds[numeroLed-1][1] && inputPoten > valoresLimiteLeds[numeroLed-1][0]){
    apagarTodas();
    analogWrite(pinesArray[numeroLed-1], 160);

  }else if(inputPoten <= valoresLimiteLeds[numeroLed-1][2] && inputPoten > valoresLimiteLeds[numeroLed-1][1]){
    apagarTodas();
    analogWrite(pinesArray[numeroLed-1], 255);

  }else{
    Serial.print("Value out of bounds for led ");
    Serial.print(numeroLed);
    Serial.print(": ");
    Serial.println(inputPoten
    );
  }

}



void loop()
{

  //Como el pin PWM me funcionaba solo dando valores aletorios,
  //he decidido usar un pin analogico para que el circutio tenga la funcionalidad
  //esperada
  int inputPoten = (analogRead(pinPoten))/4;

    
    Serial.print("Input poten: ");
    Serial.println(inputPoten);

  if(inputPoten < valoresComunesLeds[0]){
    ledProcessPoten(1, inputPoten);
    ledProcessPoten(2, inputPoten);
    ledProcessPoten(3, inputPoten);
  }
  else if(inputPoten == valoresComunesLeds[0]){
    //Enciende todas con potencia 1
    for(int i = 0; i < sizeof(pinesArray); i++){
      analogWrite(pinesArray[i], 1);
    }
    

  }else if(inputPoten <= valoresComunesLeds[1]){
//Enciende todas con potencia 160
    for(int i = 0; i < sizeof(pinesArray); i++){
      analogWrite(pinesArray[i], 160);
    }

  }else if(inputPoten <= valoresComunesLeds[2]){
//Enciende todas con potencia 255
    for(int i = 0; i < sizeof(pinesArray); i++){
      analogWrite(pinesArray[i], 255);
    }

  }

}

void apagarTodas(){
  for(int i = 0; i < sizeof(pinesArray); i++){
      analogWrite(pinesArray[i], 0);
    }
}