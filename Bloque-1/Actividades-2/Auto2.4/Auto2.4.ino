#include <Keypad.h>

int ledRojo = 11;
int ledVerde = 12;

const byte nfilas = 4;
const byte ncolumnas = 4;
const byte passwordLength = 4;
char teclas[nfilas][ncolumnas] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};


//Variables para medir distancias del ultrasonidos
long distance;
long responseTime;
int pinTrig = 9;
int pinEcho = 8;
bool cerca = false;


//Arrays para guardar la contrasña real y la introducida por el usuario.
char password[passwordLength] = {'9','8','7','6'};
char userPwdInput[passwordLength] = {'z','z','z','z'};



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
  
   pinMode(pinTrig, OUTPUT); 
   pinMode(pinEcho, INPUT);

}
 



void loop() {
  
  int counterPwdInput = 0;
  //Mientras el último elemento de la contraseña no se introduzca,
  //sigue registrando entradas del teclado.
  while(userPwdInput[passwordLength-1] == 'z'){
    char key = teclado.getKey();
    
    //Si no se pulsa ninguna tecla, no se registra la entrada
    if(key){
      userPwdInput[counterPwdInput++] = key;
    }
    
  }
  
  
  //Si las contraseñas coinciden
  if(compararContrasenas()){

    //se abre la puerta
    abrirPuerta();
    
    //Pasan 5 segundos
    int initTime = millis();
    
    //La puerta permanece abierta durante 5 segundos
    //o hasta que se aparte el objeto cercano si ya pasaron los 5 segundos
    while (millis()-initTime < 5000 || estaCerca()){
      
 		//si se pulsa la C se cierra
      if(teclado.getKey() == 'C' && !estaCerca()){
       	 break;
        
      }
      
    }
    
    
  }else{ //la contraseña no coincide
    
    contrasenaIncorrecta();
    
  }
  
  
  //Se limpia el input del usuario
  resetearUserInput();
  
  //Se cierra la puerta
  cerrarPuerta();
}
  

//Si el ultrasonidos detecta algo a menos de 10 centimetros de la puerta, no se cierra 
//hasta que el objeto se aleja.
bool estaCerca(){
  
  //Manda ultrasonidos
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  
  //Apaga el trigger de los ultrasonidos
  digitalWrite(pinTrig, LOW);
  
  // Medimos el tiempo que tarda en "volver" el ultrasonidos
  responseTime = pulseIn(pinEcho, HIGH); 
  
  //velocidad_sonido x tiempo_echo_a_nivel_alto x 1/2
  //Se divide entre dos porque es el tiempo que tarda en ir y en volver
  float distance = 0.034 * responseTime * 0.5f ; 
  Serial.println(distance);
  
  
  return distance < 10;
  
}
  
  
//Se abre la puerta
void abrirPuerta(){

  digitalWrite(ledRojo, HIGH);
  digitalWrite(ledVerde,LOW);

}
  

//Si la contraseña introducida no es correcta, devuelve false
bool compararContrasenas(){
 
  for(int i = 0; i< passwordLength; i++){
   
    if(password[i] != userPwdInput[i]){
      
      return false;
      
    }
    
  }
  
  
  return true;
  
}
  

//Limpia el array con los numeros introducidos por el usuario para
//dejarla vacía
void resetearUserInput(){
  
  
  for(int i = 0; i< passwordLength; i++){
   
  userPwdInput[i] = 'z';
    
  }
  
}


//Si la contraseña introducida no es correcta, se ilumina el 
//led verde 3 veces en 3 segundos
void contrasenaIncorrecta(){
  
  
  int i = 0;
  while(i++ < 3){
    digitalWrite(ledVerde, HIGH);
  delay(800);
  digitalWrite(ledVerde, LOW);
  delay(200);
  }
  
  
  
}
  
//Se cierra la puerta
void cerrarPuerta(){
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledVerde,HIGH);

}