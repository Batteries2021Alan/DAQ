/*---------------------------------
            Transmisor
  Este programa genera números alea-
  torios entre el 1-100 y los envia
  mediante CAN-Bus a otro arduino.
@author: Daan
Date: Septiembre 2023
----------------------------------*/
#include <SPI.h>
#include <mcp2515.h>

#define CS 10
int randomNumber;

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
  // Creamos el número aleatorio
  randomNumber = random(1, 101);
  // Establecemos la dirección 
  data.can_id = 0x30;
  // El número de bytes de la estructura
  data.can_dlc = 8;
  // El número aleatorio en la primera posición
  data.data[0] = randomNumber;
  // LLenamos el resto de posiciones con 0
  for (int i = 1; i < 8; i++){
    data.data[i] = 0x00;
  }
  // Enviamos el mensaje a CAN-Bus
  mcp2515.sendMessage(&data);
  // Esperamos 5 segundos
  delay(5000);
}
