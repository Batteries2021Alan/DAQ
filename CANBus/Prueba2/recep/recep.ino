
/*---------------------------------
            Receptor
  Este programa recibe números alea-
  torios entre el 1-100 mediante CAN-Bus.
  Este programa determina si el número
  recibido es par o no.
@author: Daan
Date: Septiembre 2023
----------------------------------*/
#include <Arduino.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <mcp2515.h>


#define CS 10
int TX = 2;
int RX = 3;

struct can_frame data;
MCP2515 mcp2515(CS);
SoftwareSerial hc06(TX, RX); 

void setup() {
  hc06.begin(9600);
  //Serial.println("CAN-Bus Prueba - DAQ UM - HC06");
  SPI.begin();
  mcp2515.reset();
  // Configuración de CAN-Bus
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();  

}

void loop() {
  //Serial.println("---CAN-Bus----");
  if (mcp2515.readMessage(&data) == MCP2515::ERROR_OK){
    int humedad = data.data[0];
    int temperatura = data.data[1];
    hc06.print(String(humedad));
    hc06.print("|");
    hc06.println(String(temperatura));
  } else {
   hc06.print("0");
    hc06.print("|");
    hc06.println("0");
  }
}
