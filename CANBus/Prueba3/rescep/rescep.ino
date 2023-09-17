
/*---------------------------------
            Receptor
  Este programa recibe los datos de
  cuatro sensores diferentes a partir
  de dos tramas recibidas por CAN-Bus,
  posteriormente los datos son enviados
  por el módulo HC-06 al puerto serial
  para leerlos con un script de Python.
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
    int id = data.can_id;

    // Arduino con sensores de AC
    if (id == 0x30){
      int voltaje = data.data[0];
      int corriente = data.data[1];
      hc06.print(String(1));
      hc06.print("|");
      hc06.print(String(voltaje));
      hc06.print("|");
      hc06.println(String(corriente));
    }
 id = data.can_id;

    // Arduino con sensores de DC
    if (id == 0x31){
      int voltaje = data.data[1];
      int corriente = data.data[0];
      hc06.print(String(2));
      hc06.print("|");
      hc06.print(String(voltaje));
      hc06.print("|");
     hc06.println(String(corriente));
    }
    delay(20);
  } 
}
