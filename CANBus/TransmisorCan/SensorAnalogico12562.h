#ifndef _SENSORANALIGICO12562_H
#define _SENSORANALIGICO12562_H
#include <Arduino.h>
#include <SPI.h>          //Libreria para la comunicacion spi
#include <mcp2515.h>      //Librreria de can

class SensorAnalogico12562{// el nombre de la clase generalmente se escribe con mayúscula  
  private :
    // lista de propiedades y métodos para usar dentro de la clase
    byte pin;
    float dato=0;
    struct can_frame trama;
    int direccion;
    byte datosBin[7]={0,0,0,0,0,0,0};
    byte d1=0;
    byte d2=0;
    byte d3=0;
    byte d4=0;
    byte d5=0;
    byte d6=0;
    byte d7=0;
  public :
    // lista de métodos disponibles para otras funciones y objetos de programa
    SensorAnalogico12562(byte pin, int direccion);
    void inicializar();
    float leer();
    struct can_frame construirTrama();
    void arreglar();
};
#endif 