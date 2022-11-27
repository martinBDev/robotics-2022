// Zumbador 1.3
// Martín Beltrán Díaz UO276244
// Stelian Adrian Stanci UO277653
// Laura Pernía Blanco UO276264

// CONSTANTE PARA CAMBIAR EL NÚMERO DE TURNOS
int const numTurnos = 3;


int const ledRojo = 4;
int const ledVerde = 3;
int const ledAzul = 2;

int const zumbador = 9;
  
int const entradaPulsadorRojo = 11;
int const entradaPulsadorVerde = 10;

int const pinForRandom = 0;
int pushed = 0;

int turnoActual = 0;

int secuenciaActual[3+(numTurnos-1)];
int posicionRepeticionSecuencia;

void setup()
{
  Serial.begin(9600);
  
  pinMode(ledRojo,OUTPUT);
  pinMode(ledAzul,OUTPUT);
  pinMode(ledVerde,OUTPUT);
  
  pinMode(zumbador,OUTPUT);
  
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
      int led = random(ledVerde,ledRojo+1);
      secuenciaActual[i]=led;
    }
    digitalWrite(secuenciaActual[i], HIGH);
    encenderZumbador(secuenciaActual[i]);
    delay(500);
    digitalWrite(secuenciaActual[i], LOW);
    apagarZumbador();
    delay(200);
  }
}

void userInput() 
{
  while (true) {
    if(digitalRead(entradaPulsadorRojo) == HIGH && pushed == 0){
      pushed = 1;
      digitalWrite(ledRojo, HIGH);
      encenderZumbador(ledRojo);
      delay(300);
      digitalWrite(ledRojo, LOW);
      apagarZumbador();

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
      encenderZumbador(ledVerde);
      delay(300);
      digitalWrite(ledVerde, LOW);
      apagarZumbador();

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
Si el led encendido es rojo suena una nota, y si es verde otra
distinta
**/
void encenderZumbador(int led) 
{
  if (led == ledRojo) 
  {
    analogWrite(zumbador, 1500);
  } else 
  {
    analogWrite(zumbador, 250);
  }
}

void apagarZumbador() 
{
  analogWrite(zumbador, 0);
}


/**
En caso de que el usuario falle al repetir la secuencia, el led
rojo parpadeará 5 veces.
**/
void gameOver() 
{
  delay(200);
  
  Serial.println("GAME OVER");

  digitalWrite(ledAzul, HIGH);
  delay(2000);
  digitalWrite(ledAzul, LOW);
  
  turnoActual = 0;
  delay(1500);
}

/**
En caso de que el usuario gane el juego, el led verde 
parpadeará 5 veces.
**/
void victoria() 
{
  delay(200);
  
  Serial.println("VICTORIA");
  for (int i = 0; i < 5; i++) 
  {
    digitalWrite(ledVerde, HIGH);
    delay(300);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRojo, HIGH);
    delay(300);
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAzul, HIGH);
    delay(300);
    digitalWrite(ledAzul, LOW);
  }
  
  turnoActual = 0;
  delay(1500);
}
