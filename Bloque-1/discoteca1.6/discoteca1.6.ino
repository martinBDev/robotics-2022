
  //AUTORES:
  //Martin Beltran Diaz - UO276244
  //Stelian Adrian Stanci - UO277653
  //Laura Pernia Blanco - UO276264
int pin_potenciometro_leds = A2; //Analog --> 0-1023
int pin_potenciometro_buzz = A1; //Analog --> 0-1023


int pin_analog_led1 = A3; //Analog --> 0-1023
int pin_analog_led2 = A4; //Analog --> 0-1023
int pin_analog_buzzer = 2; 

int max_hz_buzzer = 38000;
int min_hz_buzzer = 100;

void setup(){

    Serial.begin(9600);
    Serial.println("Set Up");

    //INPUTS de los potenciometros
    pinMode(pin_potenciometro_leds,INPUT);
    pinMode(pin_potenciometro_buzz,INPUT);

}

void loop(){
    //Como son PWM, usamos analogWrite(pin, potencia)
    int potenLeds = analogRead(pin_potenciometro_leds);
    int ptenBuzz = analogRead(pin_potenciometro_buzz);

    analogWrite(pin_analog_led1, potenLeds);
    analogWrite(pin_analog_led2, 1023-potenLeds);

    //Funcion para "hacer una regla de 3" entre la lectura del potenciometro y las Hz del buzzer
    int convert_analogBuzz_to_hz = map(ptenBuzz, 0, 1023, 100, 10000); 
    tone(pin_analog_buzzer, convert_analogBuzz_to_hz,1);

   


    Serial.print("Buzz poten: ");
    Serial.println(ptenBuzz);

    Serial.print("Buzz hz: ");
    Serial.println(convert_analogBuzz_to_hz);


}