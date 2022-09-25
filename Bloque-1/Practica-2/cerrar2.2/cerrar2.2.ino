//AUTORES:
//Martin Beltran Diaz UO276244
//Stelian Adrian Stanci UO277653
//Laura Pernía Blanco UO276264

#include <Keypad.h>

int ledRojo = 11;
int ledVerde = 12;

const byte nfilas = 4;
const byte ncolumnas = 4;
char teclas[nfilas][ncolumnas] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

//3.-
byte pfilas[nfilas] = {2,3,4,5}; // Filas
byte pcolumnas[ncolumnas] = {A0,A1,A2,A3}; //Columnas
//4.-
Keypad teclado = Keypad(makeKeymap(teclas), pfilas, pcolumnas,
nfilas, ncolumnas);

void setup() {
  Serial.begin(9600);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  digitalWrite(ledVerde,HIGH);
}

void loop() {
  char key = teclado.getKey();

  if(key == 'A'){
  abrirPuerta();

  //Pasan 5 segundos
  int initTime = millis();
  while (millis()-initTime < 5000){
    
    if(teclado.getKey() == 'C'){
      break;
    }
  }

  }
  cerrarPuerta();
}

void abrirPuerta(){
  digitalWrite(ledRojo, HIGH);
  digitalWrite(ledVerde,LOW);
}

void cerrarPuerta(){
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledVerde,HIGH);
}