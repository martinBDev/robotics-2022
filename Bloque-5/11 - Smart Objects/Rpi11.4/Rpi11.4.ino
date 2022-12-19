#include <Ethernet.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

 //AUTORES:
  //Martin Beltran Diaz - UO276244
  //Stelian Adrian Stanci - UO277653
  //Laura Pernia Blanco - UO276264

///////INFO SOBRE EL LECTOR RFID-RC522//////////////////////////////////////////7
/*
 * Uses MIFARE RFID card using RFID-RC522 reader
 * Uses MFRC522 - Library
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          8 (mod)             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      9(mod)            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#define RST_PIN         8           // Configurable, el pin por defecto es el 9, pero lo cambié porque el pin 10 en mi placa esta defectuoso.
#define SS_PIN          9          // Configurable, el pin por defecto es el 10, pero lo cambié porque en mi placa esta defectuoso.



MFRC522 rfid(SS_PIN, RST_PIN);   // Crear MFRC522 instance
MFRC522::MIFARE_Key key; //Para desencriptar el UID de la tarjeta

//DATOS PARA CREAR EL SERVER////////////////////////////////////////////////////////////////
byte mac[] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x37};

EthernetServer servidor(80); // Puerto en el 80

// Estos datos cogedlos del ordenador que uséis o del de al lado
IPAddress dnsServer(8,8,8,8); //ESTOS SON LOS DATOS DE MI RED de casa
IPAddress gateway(192,168,0,1);
IPAddress subnet(255, 255, 255, 0);


// Que cada uno ponga la IP de su grupo (20X, dónde X es el número
//del grupo) 201, 202, 203, que es el que tiene asignado. Tiene que ser
//única en la red local, cuidado
IPAddress ip(192,168,0,207);
//////////////////////////////////////////////////////////////////////////////////

//DATA PARA CREAR EL CLIENTE WEB/////////////////////////////////////////////////




int HTTP_PORT = 5000;
String HTTP_METHOD = "GET";
char HOST_IP[] = "192.168.0.7"; //ip del servidor python en la raspi
String PATH_NAME = "/checkUser"; 

////////////////////////////////////////////////////////////////////////////////

/////MODOS DEL TORNO///////////////////////

enum ModoTrabajo {
blocked, //bloqueado por avería: led en rojo y torno cerradp
working, //trabajo normal del torno
opened //torno permite pasar todo el rato
};

ModoTrabajo estadoActual;

//ID MODELO: 83130224167
///////////////////////////////////////////////


////ACTUADORES////////////////////

int ledVerde = 2; //abierto o permite entrada
int ledRojo = 3; //bloqueado
int ledAzul = 1; //operativo

Servo servo;

    void setup()
    {

            pinMode(ledVerde, OUTPUT);
            pinMode(ledRojo, OUTPUT);
            pinMode(ledAzul, OUTPUT);
            digitalWrite(ledAzul, HIGH);
            
            
            servo.attach(4);
            servo.write(0);
            estadoActual = working;

            Ethernet.begin(mac, ip, dnsServer, gateway, subnet);
            Serial.begin(9600);
            servidor.begin();
            delay(1000);
            Serial.println(Ethernet.localIP());
            delay(1000);
            delay(1000);
            Serial.println("connecting...");


            SPI.begin();                                                  
            rfid.PCD_Init();
            
            for (byte i = 0; i < 6; i++) { //La key por defecto es FF FF FF FF FF
                                          //La key por defecto se usa para desencriptar los datos de la tarjeta (si los hay)
                key.keyByte[i] = 0xFF;    //LA KEY POR DEFECTO DE TARJETAS DEL FABRICANTE MIFARE (Mini, 1k y 4k) ES LA QUE SE DIJO ARRIBA
            }


    }


    void other(){ //testeo

        bloquear();
      
        EthernetClient client = servidor.available();
        if(client){ //Se da preferencia a las peticiones que lleguen desde el server
            procesarPeticionWeb(client);
        }
      
    }

EthernetClient client;
    void loop()                                           
    { //FALTA AÑADIR CHECKEO DEL MODO DE TRABAJO DEL TORNO  

        
        
        client = servidor.available();
        //Si hay peticion HTTP darle prioridad
        if(client){ //Se da preferencia a las peticiones que lleguen desde el server
            procesarPeticionWeb(client);
        }else if(! rfid.PICC_IsNewCardPresent()){ //Si no hay tarjeta, resetea el loop
            return;
        }else if(estadoActual == working){ //Si hay tarjeta, leer 
            sendIDToServer(readCard());
           
        }     

    }


    //procesa la peticion web que le llegue, ya sea respuesta del server cuando se comprueba un ID, o como peticion independiente
    void procesarPeticionWeb(EthernetClient cliente){
      Serial.println("Nueva peticion");
            String peticion="";
            while (cliente.connected()) {
                if (cliente.available()) {
                
                         char c = cliente.read(); //Leer petición carácter a
                        //carácter
                         peticion.concat(c); // concatenar en un string
                         // Ha acabado la peticion http
                         // Si contiene index responder con una web
                        
                         // la petición ha acabado '\n' y contiene la cadena "index"
                        //al principio: index, indexabc, indexación, etc. Usar equals para que sea
                        //igual
                         if (c == '\n' && peticion.indexOf("userAccepted") != -1){ //se recibe la respuesta del servidor que comprueba si el UID es válido
                             if(peticion.indexOf("true") != -1){ //si se permite entrar al usuario, se abre el torno.
                                  permitirEntrada(true);
                                  

                                    cliente.println("HTTP/1.1 200 OK");
                                   cliente.println("Content-Type: application/json");
                                   cliente.println("Access-Control-Allow-Origin: *");
                                   cliente.println();
                                   cliente.print("{\"opened\":");
                 
                                   cliente.print("true");
                                   cliente.println("}");
                                                            
                                   
                                     Serial.println("Usuario aceptado");
                                  
                                  break;
                               
                                  
                             }else if(peticion.indexOf("false") != -1){ //si no se permite entrar al usuario, se enciende la luz roja unos segundos.
                                  permitirEntrada(false); 
                                  

                                  cliente.println("HTTP/1.1 200 OK");
                                   cliente.println("Content-Type: application/json");
                                   cliente.println("Access-Control-Allow-Origin: *");
                                   cliente.println();
                                   cliente.print("{\"opened\":");
                 
                                   cliente.print("false");
                                   cliente.println("}");
                                               
                                  
                                  
                                  Serial.println("Usuario NO aceptado");
                                  break;
                                  
                             }

                             

                               break;
                         }else if(c == '\n' && peticion.indexOf("bloquear") != -1){ //se cierra el torno
                             
                              
                              bloquear();



                                  cliente.println("HTTP/1.1 200 OK");
                                   cliente.println("Content-Type: application/json");
                                   cliente.println("Access-Control-Allow-Origin: *");
                                   cliente.println();
                                   cliente.print("{\"state\":");
                 
                                   cliente.print("blocked");
                                   cliente.println("}");

                              
                              break;
                              
                         }else if(c == '\n' && peticion.indexOf("abrir") != -1){ //se abre para todo el mundo
                              abrir(); 


                                cliente.println("HTTP/1.1 200 OK");
                                   cliente.println("Content-Type: application/json");
                                   cliente.println("Access-Control-Allow-Origin: *");
                                   cliente.println();
                                   cliente.print("{\"state\":");
                 
                                   cliente.print("opened");
                                   cliente.println("}");


                              
                              
                              break;
                         }else if(c == '\n' && peticion.indexOf("restaurar") != -1){ //se restaura el funcionamiento del torno
                              restaurar(); 
                              

                              cliente.println("HTTP/1.1 200 OK");
                                   cliente.println("Content-Type: application/json");
                                   cliente.println("Access-Control-Allow-Origin: *");
                                   cliente.println();
                                   cliente.print("{\"state\":");
                 
                                   cliente.print("working");
                                   cliente.println("}");

                              
                              
                              
                              break;
                         }


                     }
             }
            
             // Pequeña pausa para asegurar el envio de datos
             delay(1000);
             cliente.stop();// Cierra la conexión
    }


//LED EN ROJO Y SE CIERRA EL TORNO HASTA QUE SE CAMBIE EL ESTADO A WORKING O OPEN
    void bloquear(){
      estadoActual = blocked;
      digitalWrite(ledRojo, HIGH);
      digitalWrite(ledAzul, LOW);
      digitalWrite(ledVerde, LOW);
      servo.write(0);
      
    }
//LED EN VERDE Y TORNO ABIERTO HASTA CAMBIAR DE MODO DE FUNCIONAMIENTO
    void abrir(){
      estadoActual = opened;
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledAzul, LOW);
      digitalWrite(ledVerde, HIGH);
      servo.write(180);
    }

    void restaurar(){
      estadoActual = working;
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledAzul, HIGH);
      digitalWrite(ledVerde, LOW);
      servo.write(0);
    }

    void permitirEntrada(bool permitida){ 

      if(permitida){ //true --> se abre el torno 4 segundos y se enciende la luz verde. Luego se cierra el torno y se apaga la luz
          servo.write(180);  
          digitalWrite(ledAzul,LOW);
          digitalWrite(ledVerde,HIGH);                 
          delay(4000);
          servo.write(0);
          digitalWrite(ledAzul,HIGH);
          digitalWrite(ledVerde,LOW);  
          delay(500);
      }else{ //FALSE --> no se permite entrada, parpadea rojo un par de veces
         digitalWrite(ledAzul,LOW);
         digitalWrite(ledRojo,HIGH);
         delay(1000);
         digitalWrite(ledRojo,LOW);
         delay(500);
         digitalWrite(ledRojo,HIGH);
         delay(1000);
         digitalWrite(ledRojo,LOW);
         delay(500);
         digitalWrite(ledAzul,HIGH);
         
      }
      
      
    }

    //Leer el UID de la tarjeta y enviar los datos al server
    String readCard(){

          // Esto evita que mientras la tarjeta está en el rango de lectura, se lea de forma infinita
            if ( ! rfid.PICC_ReadCardSerial())
              {  return;}


            MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak); //leemos el tipo de tarjeta que se detecta
            // Comprobamos que el tipo de tarjeta es correcto
            if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
                piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
                piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
                Serial.println(F("Your tag is not of type MIFARE Classic."));
                error();
                return;
            }


            Serial.println(F("The NUID tag is:"));
            Serial.print(F("In hex: "));
            printHex(rfid.uid.uidByte, rfid.uid.size);
            Serial.println();
            Serial.print(F("In dec: "));
            printDec(rfid.uid.uidByte, rfid.uid.size);
            Serial.println();

            String stringUID = "";
            for(int i = 0; i < 4; i++){ //TRASNFORMA el uid a string
              stringUID += rfid.uid.uidByte[i]; //LEE EL UID DE LA TARJETA POR BYTES
            }

            Serial.println(stringUID);



            //para dejar de leer la tarjeta
            // Halt PICC
            rfid.PICC_HaltA();

            // Stop encryption on PCD
            rfid.PCD_StopCrypto1();

            return stringUID;
    }





    void sendIDToServer(String uid){
        
        PATH_NAME = "/checkUser?uuid="+uid;
        Serial.println(PATH_NAME);
        if (client.connect(HOST_IP,HTTP_PORT))
            {                                 
                        client.println(HTTP_METHOD + " " + PATH_NAME + " HTTP/1.1");
                        client.println("Host: " + String(HOST_IP));
                        client.println("User-Agent: Arduino/1.0");
                        client.println("Connection: close");
                        client.println(); // end HTTP header      
                        
                        delay(500);

                        
                            // the server's disconnected, stop the server:
                        client.stop();                                 
            }
            else
            {
            Serial.println("Cannot connect to Server");               
            }
    }


    //Enciende el led rojo unos segundos para indicar que no se puede pasar
    void error(){

    }

    /**
 * Printear array de bytes como hexadecimales. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Printear array de bytes como decimales.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
