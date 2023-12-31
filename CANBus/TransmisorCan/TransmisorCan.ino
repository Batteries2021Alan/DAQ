#include <SPI.h>          //Libreria para la comunicacion spi
#include <mcp2515.h>      //Librreria de can
#include "SensorAnalogico12562.h"
struct can_frame canMsg;
struct can_frame Extraccion;
const int analogPin = A0;
MCP2515 mcp2515(10);
unsigned long previousMillis = 0;
/*
class SensorAnalogico12562{// el nombre de la clase generalmente se escribe con mayúscula  
  private :
  // lista de propiedades y métodos para usar dentro de la clase
    byte pin;
    float dato=0;
    struct can_frame trama;
    int direccion;
    byte datosBin[4]={0,0,0,0};
    byte d1=0;
    byte d2=0;
    byte d3=0;
    byte d4=0;
  public :
  // lista de métodos disponibles para otras funciones y objetos de programa
    SensorAnalogico12562(byte pin, int direccion){
      this->pin = pin;
      this->direccion=direccion;
      inicializar();
    }
    void inicializar(){
      pinMode(pin,INPUT);
    }
    float leer(){
      float datoL=analogRead(pin);
      //dato=map(dato,0,1023,0,256);
      return datoL;
    }
    struct can_frame construirTrama(){
      arreglar();
      trama.can_id  = direccion;           //CAN id (Nomvre de la trama)
      trama.can_dlc = 4;               //CAN data tamaño de la trama
      trama.data[0] = datosBin[0];               //Valores maximo de 256
      trama.data[1] = datosBin[1];               //Valores maximo de 256
      trama.data[2] = datosBin[2];               //Valores maximo de 256
      trama.data[3] = datosBin[3];               //Valores maximo de 256
                                                              Serial.println("Mensaje enviado1");
      Serial.print("-----[ ");
      Serial.print(datosBin[0]);
      Serial.println(" ]-----");
      return trama;
    }
    void arreglar(){
      dato=leer();
      d1=int(dato);// Maximo de 256
      d2= int((dato-d1)*100);//.99
      datosBin[0]=d1;
      datosBin[1]=d2;
      datosBin[2]=d3;
      datosBin[3]=d4;
      return datosBin[4];
    }
};// */
SensorAnalogico12562 Ejemplo1(A0,1);
SensorAnalogico12562 Ejemplo2(A0,2);
SensorAnalogico12562 Ejemplo3(A0,3);
SensorAnalogico12562 Ejemplo4(A0,4);
SensorAnalogico12562 Ejemplo5(A0,5);
SensorAnalogico12562 Ejemplo6(A0,10);
void setup() 
{
  Serial.begin(9600);
  SPI.begin();               //Begins SPI communication
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();
}

void loop() 
{
  unsigned long currentMillis = millis();

  if(currentMillis-previousMillis>=1){
  previousMillis = currentMillis;
  /*
  canMsg.can_id  = 0x005;           //CAN id as 0x036
  canMsg.can_dlc = 2;               //CAN data length as 8
  canMsg.data[0] = 10;               //Update humidity value in [0]
  canMsg.data[1] = 7;
  mcp2515.sendMessage(&canMsg);     //Sends the CAN message
  Serial.println("Mensaje enviado1");
  /*
    Serial.print("-----[ ");
    Serial.print(analogRead(A0));
    Serial.println(" ]-----");
    */
    if (mcp2515.readMessage(&Extraccion) == MCP2515::ERROR_OK) {
      if(Extraccion.can_id==160){
      switch (Extraccion.data[0]) {
        case 1:
        Serial.print("entra 1 ");
        Serial.print("[");
        Serial.print(Extraccion.data[0]);
        Serial.print("]");
        mcp2515.sendMessage(&Ejemplo1.construirTrama());
        break;
        case 2:
        mcp2515.sendMessage(&Ejemplo2.construirTrama());
        Serial.print("entra 2 ");
        break;
        case 3:
        mcp2515.sendMessage(&Ejemplo3.construirTrama());
        Serial.print("entra 3 ");
        break;
        case 4:
        mcp2515.sendMessage(&Ejemplo4.construirTrama());
        Serial.print("entra 4 ");
        break;
        case 5:
        mcp2515.sendMessage(&Ejemplo5.construirTrama());
        Serial.print("entra 5 ");
        break;
        case 10:
        mcp2515.sendMessage(&Ejemplo6.construirTrama());
        Serial.println("entra 6 ");
        break;
        case 25:
          canMsg.can_id  = 25;           //CAN id as 0x036
          canMsg.can_dlc = 2;               //CAN data length as 8
          canMsg.data[0] = 10;               //Update humidity value in [0]
          canMsg.data[1] = 7;
          mcp2515.sendMessage(&canMsg);     //Sends the CAN message
          Serial.println("Entra con 25");
        break;
      }
      delay(100);
    }
    }
    else{
    //Serial.println("No entra");
    }
    /*
    mcp2515.sendMessage(&Ejemplo1.construirTrama());
    delay(30);
    mcp2515.sendMessage(&Ejemplo2.construirTrama());
    delay(30);
    mcp2515.sendMessage(&Ejemplo3.construirTrama());
    delay(30);
    mcp2515.sendMessage(&Ejemplo4.construirTrama());
    delay(30);
    mcp2515.sendMessage(&Ejemplo5.construirTrama());
    delay(30);
    mcp2515.sendMessage(&Ejemplo6.construirTrama());
    //*/
  }
}