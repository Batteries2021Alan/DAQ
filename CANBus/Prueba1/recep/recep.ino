#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>



/*---------------------------------
            Receptor
  Este programa recibe números alea-
  torios entre el 1-100 mediante CAN-Bus.
  Este programa determina si el número
  recibido es par o no.
@author: Daan
Date: Septiembre 2023
----------------------------------*/


#define CS 10
int numeroRecibido;

struct can_frame data;
MCP2515 mcp2515(CS);


void setup() {
  Serial.begin(9600);
  Serial.println("CAN-Bus Prueba - DAQ UM");
  SPI.begin();
  mcp2515.reset();
  // Configuración de CAN-Bus
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();  

}

void loop() {
  Serial.println("---CAN-Bus----");
  if (mcp2515.readMessage(&data) == MCP2515::ERROR_OK){
    numeroRecibido = data.data[0];
    if (numeroRecibido % 2 == 0){
      Serial.println("El número recibido es par");
    } else {
      Serial.println("El número recibido es impar");
    }
    Serial.print("El número recibido es: ");
    Serial.println(numeroRecibido);
    Serial.println("");
  }
  Serial.println("Mensaje no recibido. En espera");
  delay(1000);
}
