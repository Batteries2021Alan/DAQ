/*---------------------------------
            Transmisor
  Este programa simula las lecturas
  de dos sensores de DC, uno de corriente
  con unidades en [A] y otro de voltaje con
  unidades en [V].
  Los datos son guardados en una trama 
  y enviados mediante CAN-Bus.
@author: Daan
Date: Septiembre 2023
----------------------------------*/

#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>


#define CS 10

struct can_frame data;

MCP2515 mcp2515(CS);

void setup() {
  SPI.begin();
  mcp2515.reset();
  // Configuración de CAN-Bus
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();  

}

void loop() {
  // Leemos las variables de humedad
  // y de temperatura
  int voltaje = random(200, 237); 
  int corriente = random(90,100);      
  // Establecemos la dirección 
  data.can_id = 0x31;
  // El número de bytes de la estructura
  data.can_dlc = 8;
  // La corriente se asigna en la primera posición
  data.data[0] = corriente;
  // El voltaje se asigna en la segunda posición
  data.data[1] = voltaje;
  // Enviamos el mensaje a CAN-Bus
  mcp2515.sendMessage(&data);
  delay(500);
}