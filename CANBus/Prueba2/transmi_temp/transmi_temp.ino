/*---------------------------------
            Transmisor
  Este programa lee las variables
  de humedad y temperatura de un 
  sensor DHT11 y los envia
  mediante CAN-Bus a otro arduino.
@author: Daan
Date: Septiembre 2023
----------------------------------*/

#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>
#include <DHT.h>
#include <DHT_U.h>


#define CS 10
int dht11_pin = 2;

struct can_frame data;

MCP2515 mcp2515(CS);
DHT dht(dht11_pin, DHT11);

void setup() {
  SPI.begin();
  mcp2515.reset();
  dht.begin(); 
  // Configuración de CAN-Bus
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();  

}

void loop() {
  // Leemos las variables de humedad
  // y de temperatura
  int temperatura = dht.readTemperature(); 
  int humedad = dht.readHumidity();      
  // Establecemos la dirección 
  data.can_id = 0x30;
  // El número de bytes de la estructura
  data.can_dlc = 8;
  // La humedad se asigna en la primera posición
  data.data[0] = humedad;
  // La temperatura se asigna en la segunda posición
  data.data[1] = temperatura;
  // LLenamos el resto de posiciones con 0
  for (int i = 2; i < 8; i++){
    data.data[i] = 0x00;
  }
  // Enviamos el mensaje a CAN-Bus
  mcp2515.sendMessage(&data);
}
