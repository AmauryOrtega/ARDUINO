/*
PCF8591 5V
    YL38 3.3V - 5V
SHT21 3.3V
*/

#include "SHT21.h"
#include "TSL2561.h"
// https://github.com/adafruit/TSL2561-Arduino-Library/blob/master/examples/tsl2561/tsl2561.ino
#include <ESP8266WiFi.h>
#include <Wire.h>

// Definiciones https://www.aurel32.net/elec/pcf8591.pdf
#define PCF8591 (0x90 >> 1) // Dirreccion del bus I2C 1001 0000
#define PCF8591_ACTIVAR_DAC 0x40  //0100 0000
#define PCF8591_ADC0 0x00
#define PCF8591_ADC1 0x01
#define PCF8591_ADC2 0x02
#define PCF8591_ADC3 0x03

// Variables
SHT21 SHT21;
TSL2561 tsl(TSL2561_ADDR_FLOAT);

// Prototipos de funciones
int leerPCF8591_Pin(unsigned int pin);
void leerPCF8591();
void leerSHT21();
void leerTSL2561();

void setup(){
  Serial.begin(9600);
  // Pines D2(SDA GPIO 4) y D1(SCL GPIO 5)
  Wire.begin(4, 5);
  // Inicializa el SHT21
  SHT21.begin();
  // Inicializa el TSL2561
  tsl.begin();
}

void loop(){
  leerPCF8591();
  leerSHT21();
  leerTSL2561();
  Serial.println();
  delay(500);
}

int leerPCF8591_Pin(unsigned int pin){
    Wire.beginTransmission(PCF8591);
    Wire.write(pin);
    Wire.endTransmission();
    Wire.requestFrom(PCF8591, 2);
    Wire.read();  // Se omite el primero porque es el valor anterior
    int valor = (int) Wire.read();
    if(valor < 120){
        return 100;
    }else{
        valor = map(valor, 120, 255, 100, 0);
    }
    return valor;
}

void leerPCF8591(){
    Serial.print("PCF8591 [ ");
    Serial.print("(0:");
    Serial.print(leerPCF8591_Pin(PCF8591_ADC0));
    Serial.print("%) (1:");
    Serial.print(leerPCF8591_Pin(PCF8591_ADC1));
    Serial.print("%) (2:");
    Serial.print(leerPCF8591_Pin(PCF8591_ADC2));
    Serial.print("%) (3:");
    Serial.print(leerPCF8591_Pin(PCF8591_ADC3));
    Serial.println("%) ]");
}

void leerSHT21(){
    Serial.print("SHT21 [ ");
    Serial.print("H: ");Serial.print(SHT21.getHumidity());Serial.print("% ");
    Serial.print("T: ");Serial.print(SHT21.getTemperature());Serial.print(" °C");
    Serial.println(" ]");
}

void leerTSL2561(){
    uint16_t x = tsl.getLuminosity(TSL2561_VISIBLE);
    Serial.print("TSL2561 [ ");
    Serial.print(x, DEC);
    Serial.println(" ]");
}
