// #include <Arduino.h>
#include <ESP8266WiFi.h>
#include <aREST.h>

// Declaraciones globales
#define PUERTO_ESCUCHA int(80);

// Variables globales
aREST restObject = aREST();
WiFiServer server(80);
const char* ssid = "SEMARD";
const char* password = "SEMARD123";
int bateria = 100;

// Declaracion de funciones
int bobina(String comando){
    // int state = comando.toInt();
    // Serial.println("Recibido: " + comando + " convertido " + state);
    // digitalWrite(5, state);
    if(comando == "HIGH"){
        Serial.println("HIGH");
        digitalWrite(5, HIGH);
    }else if (comando == "LOW"){
        Serial.println("LOW");
        digitalWrite(5, LOW);
    }
    return 1;
}

void setup(){
    Serial.begin(9600);

    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(16, OUTPUT);

    WiFi.begin("SEMARD", "SEMARD123");
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    // 2 variables and 2 functions for memory limitation
    restObject.variable("bateria",&bateria);
    restObject.function((char *)"bobina",bobina);
    
    //restObject.set_id("1");
    //restObject.set_name("esp8266-master");
    server.begin();
    Serial.println("Server comenzado");
}

void loop(){
    // Handle REST calls
    WiFiClient client = server.available();
    if (!client) {
      return;
    }
    while(!client.available()){
      delay(1);
    }
    restObject.handle(client);
}