  //AUTORES:
  //Martin Beltran Diaz - UO276244
  //Stelian Adrian Stanci - UO277653
  //Laura Pernia Blanco - UO276264


#include <DHT.h> //Adafruit
#include <SPI.h> //Importamos librería comunicación SPI
#include <Ethernet.h> //Importamos librería Ethernet



////////PARA USAR EL ARDUINO POR ETHERNET//////////////////////////////////////////////////

byte mac[] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x37}; // Tiene
//que ser única en la red local, cuidado, cambiad el último dígito por el
//de vuestro grupo

EthernetServer servidor(80); // Puerto en el 80

// Estos datos cogedlos del ordenador que uséis o del de al lado
IPAddress dnsServer(212,142,173,64); //ESTOS SON LOS DATOS DE MI RED de casa
IPAddress gateway(192,168,0,1);
IPAddress subnet(255, 255, 255, 0);


// Que cada uno ponga la IP de su grupo (20X, dónde X es el número
//del grupo) 201, 202, 203, que es el que tiene asignado. Tiene que ser
//única en la red local, cuidado
IPAddress ip(192,168,0,207);
//////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////SENSORES//////////////////////////////////////////
// Sensor DHT a utilizar:
#define DHTTYPE DHT11 // DHT 11
int pin_sensor = 5;
DHT dht(pin_sensor, DHTTYPE);
float temperature, humidity;

//Led para encender
int led_error = 7;
bool ledOn = false;

void setup(){
       Serial.begin(9600);

       
         //internet
        Ethernet.begin(mac, ip, dnsServer, gateway, subnet);
        servidor.begin();
        Serial.println("Setup");
        // Imprimir la IP
        Serial.println(Ethernet.localIP()); 
     
      //sensores
      dht.begin();
      
      temperature = 0;
      humidity = 0;

      pinMode(led_error, OUTPUT);
      digitalWrite(led_error, ledOn);
 }

void loop(){
        EthernetClient cliente = servidor.available();
        if (cliente) {
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
                         if (c == '\n' && peticion.indexOf("medir") != -1){
                             medirYReturnData(cliente);
                             break;
                         }else if(c == '\n' && peticion.indexOf("interactuarLed") != -1){
                              ledOn = !ledOn;
                              digitalWrite(led_error, ledOn); //se cambia el estado del led
                              medirYReturnData(cliente);
                              break;
                         }
                     }
             }
            
             // Pequeña pausa para asegurar el envio de datos
             delay(1000);
             cliente.stop();// Cierra la conexión
         }
}



void medirYReturnData(EthernetClient cliente){

  Serial.println("Responder");
   // Serial.println(peticion);
  
  

      //Leer sensores
      temperature = dht.readTemperature();
       humidity = dht.readHumidity();
      
       if (isnan(temperature) || isnan(humidity)) {
       Serial.println("Fallo en la lectura del "+DHTTYPE);
       return;
       }
      
       Serial.println("Temperatura: "+String(temperature));
        Serial.println("Humedad: "+String(humidity));
         Serial.println("--------------------------------");
   
     // Enviamos al cliente una respuesta HTTP
     cliente.println("HTTP/1.1 200 OK");
     cliente.println("Content-Type: application/json");
     cliente.println("Access-Control-Allow-Origin: *");
     cliente.println();

     cliente.print("{\"humidity\":");
    cliente.print(humidity);
    cliente.print(",\"temperature\": ");
    cliente.print(temperature);
    cliente.print(",\"led\":");
    cliente.print(ledOn);
    cliente.println("}");
    delay(500);

}
