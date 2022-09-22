  //AUTORES:
  //Martin Beltran Diaz - UO276244
  //Stelian Adrian Stanci - UO277653
  //Laura Pernia Blanco - UO276264
  // C++ code
//

//Definimos pines de LEDs
int pinLed1 = 5;
int pinLed2 = 6;
int pinLed3 = 9;
//Definimos pin del potenciometro
int pinPoten = 3;

void setup()
{

Serial.begin(9600);
Serial.println("Setup");
  pinMode(pinLed1,OUTPUT);
  pinMode(pinLed2,OUTPUT);
  pinMode(pinLed3,OUTPUT);
  pinMode(pinPoten,INPUT);
  
}

int valoresLimiteLeds[][3] = {
  {1,32,63},
  {64,100,127},
  {128,160,191}
};

int valoresComunesLeds[3] = {192,210,255};

int pinesArray[3] = {pinLed1,pinLed2,pinLed3};

void ledProcessPoten(int numeroLed, int inputPoten){


  if(inputPoten == 0){

    analogWrite(pinLed1,0);
    analogWrite(pinLed2,0);
    analogWrite(pinLed3,0);

  }
  else if(inputPoten == valoresLimiteLeds[numeroLed-1][0]){

    analogWrite(pinesArray[numeroLed-1], 1);


  }else if(inputPoten <= valoresLimiteLeds[numeroLed-1][1]){

    analogWrite(pinesArray[numeroLed-1], 160);

  }else if(inputPoten <= valoresLimiteLeds[numeroLed-1][2]){

    analogWrite(pinesArray[numeroLed-1], 255);

  }else{
    Serial.print("Value out of bounds: ");
    Serial.println(inputPoten
    );
  }

}



void loop()
{
  int inputPoten = analogRead(pinPoten);

    delay(3000);
    Serial.print("Input poten: ");
    Serial.println(inputPoten);

  if(inputPoten < valoresComunesLeds[0]){
    ledProcessPoten(1, inputPoten);
    ledProcessPoten(2, inputPoten);
    ledProcessPoten(3, inputPoten);
  }
  else if(inputPoten == valoresComunesLeds[0]){

    for(int i = 0; i < sizeof(pinesArray); i++){
      analogWrite(pinesArray[i], 1);
    }
    

  }else if(inputPoten <= valoresComunesLeds[2]){

    for(int i = 0; i < sizeof(pinesArray); i++){
      analogWrite(pinesArray[i], 160);
    }

  }else if(inputPoten <= valoresComunesLeds[3]){

    for(int i = 0; i < sizeof(pinesArray); i++){
      analogWrite(pinesArray[i], 255);
    }

  }

}
