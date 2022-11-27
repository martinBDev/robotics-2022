#include <Ethernet.h>
#include <SPI.h>
#include <MFRC522.h>
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

IPAddress dnsServer(212,142,173,64); //ESTOS SON LOS DATOS DE MI RED de casa
IPAddress gateway(192,168,0,1);
IPAddress subnet(255, 255, 255, 0);	
// Que cada uno ponga la IP de su grupo (20X, dónde X es el número
//del grupo) 201, 202, 203, que es el que tiene asignado. Tiene que ser
//única en la red local, cuidado
IPAddress ip(192,168,0,207);
//////////////////////////////////////////////////////////////////////////////////

//DATA PARA CREAR EL CLIENTE WEB/////////////////////////////////////////////////




int HTTP_PORT = 80;
String HTTP_METHOD = "POST";
char HOST_IP[] = "X.X.X.X";
String PATH_NAME = ""; 

////////////////////////////////////////////////////////////////////////////////

String temp= "data=5";  

    void setup()
    {
            Ethernet.begin(mac, ip, dnsServer, gateway, subnet);
            Serial.begin(9600);
            servidor.begin();
            Serial.println(Ethernet.localIP());
            delay(1000);
            delay(1000);
            Serial.println("connecting...");


            SPI.begin();                                                  
            rfid.PCD_Init();
            
            for (byte i = 0; i < 6; i++) { //La key por defecto es FF FF FF FF FF
                key.keyByte[i] = 0xFF;
            }

    }

    void loop()                                           
    {                      
        EthernetClient client = servidor.available();
        //Si hay peticion HTTP darle prioridad
        if(client){ //Se da preferencia a las peticiones que lleguen desde el server

        }else if(! rfid.PICC_IsNewCardPresent()){ //Si no hay tarjeta, resetea el loop
            return;
        }else{
            readCardAndSend();
        }     

    }



    //Leer el UID de la tarjeta y enviar los datos al server
    void readCardAndSend(){

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


            byte nuidPICC[4]; //para guardar el NUID en un array de bytes
            
            for (byte i = 0; i < 4; i++) {
                nuidPICC[i] = rfid.uid.uidByte[i];
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
              stringUID += nuidPICC[i];
            }

            Serial.println(stringUID);

                        // Halt PICC
            rfid.PICC_HaltA();

            // Stop encryption on PCD
            rfid.PCD_StopCrypto1();

    }





    void sendIDToServer(){
        EthernetClient client;
        if (client.connect(HOST_IP,HTTP_PORT))
            {                                 
                        client.println(HTTP_METHOD + " " + HOST_IP + " HTTP/1.1");
                        client.println("Host: " + String(HOST_IP));
                        client.println("Connection: close");
                        client.println(); // end HTTP header      


                        while(client.connected()) {
                            if(client.available()){
                                // read an incoming byte from the server and print it to serial monitor:
                                char c = client.read();
                                Serial.print(c);
                            }
                        }
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
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
