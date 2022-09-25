// Memoria 1.2
// Martín Beltrán Díaz UO276244
// Stelian Adrian Stanci UO277653
// Laura Pernía Blanco UO276264


int const ledRojo = 8;
int const ledVerde = 9;
int const entradaPulsadorRojo = 11;
int const entradaPulsadorVerde = 10;

int const pinForRandom = 0;
int pushed = 0;

int const numTurnos = 3;
int turnoActual = 0;

int secuenciaActual[3+(numTurnos-1)];
int posicionRepeticionSecuencia;

void setup()
{
  Serial.begin(9600);
  
  pinMode(ledRojo,OUTPUT);
  pinMode(ledVerde,OUTPUT);
  pinMode(entradaPulsadorRojo,INPUT);
  pinMode(entradaPulsadorVerde,INPUT);
  
  randomSeed(analogRead(pinForRandom));
}

void loop()
{
  generarSecuencia();
  posicionRepeticionSecuencia = 0;
  userInput();
  delay(300);
}


void generarSecuencia() 
{
  
  for (int i = 0; i < 3+turnoActual; i++) {
    if (turnoActual == 0 || i == 3 + (turnoActual - 1)) 
    {
      int led = random(ledRojo,ledVerde+1);
      secuenciaActual[i]=led;
    }
    digitalWrite(secuenciaActual[i], HIGH);
    delay(500);
    digitalWrite(secuenciaActual[i], LOW);
    delay(200);
  }
}

void userInput() 
{
  while (true) {
    if(digitalRead(entradaPulsadorRojo) == HIGH && pushed == 0){
      pushed = 1;
      digitalWrite(ledRojo, HIGH);
      delay(400);
      digitalWrite(ledRojo, LOW);

      if (secuenciaActual[posicionRepeticionSecuencia] != ledRojo)
      {
        gameOver();
        break;
      }
      
      posicionRepeticionSecuencia += 1;
      if (posicionRepeticionSecuencia == 3 + (turnoActual)) 
      {
        turnoActual += 1;
        delay(300);
        
        if (turnoActual == numTurnos) 
        {
          victoria();
        }
        break;
      }

    } else if (digitalRead(entradaPulsadorVerde) == HIGH && pushed == 0)
    {
      pushed = 1;
      digitalWrite(ledVerde, HIGH);
      delay(400);
      digitalWrite(ledVerde, LOW);

      if (secuenciaActual[posicionRepeticionSecuencia] != ledVerde)
      {
        gameOver();
        break;
      } 
      
      posicionRepeticionSecuencia += 1;
      if (posicionRepeticionSecuencia == 3 + (turnoActual)) 
      {
        turnoActual += 1;
        delay(300);
        
        if (turnoActual == numTurnos) 
        {
          victoria();
        }
        break;
      }
    }
    pushed = 0;
  }
}

/**
En caso de que el usuario falle al repetir la secuencia, el led
rojo parpadeará 5 veces.
**/
void gameOver() 
{
  Serial.println("GAME OVER");
  for (int i = 0; i < 5; i++) 
  {
    digitalWrite(ledRojo, HIGH);
    delay(200);
    digitalWrite(ledRojo, LOW);
    delay(200);
  }
  
  turnoActual = 0;
  delay(500);
}

/**
En caso de que el usuario gane el juego, el led verde 
parpadeará 5 veces.
**/
void victoria() 
{
  Serial.println("VICTORIA");
  for (int i = 0; i < 5; i++) 
  {
    digitalWrite(ledVerde, HIGH);
    delay(300);
    digitalWrite(ledVerde, LOW);
    delay(300);
  }
  
  turnoActual = 0;
  delay(500);
}
