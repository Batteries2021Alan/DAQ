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
    byte datosBin[8]={0,0,0,0,0,0,0,0};
    byte d1=0;
    byte d2=44;
    byte d3=55;
    byte d4=66;
    byte d5=77;
    byte d6=88;
    byte d7=99;
    byte d8=10;
  public :
    // lista de métodos disponibles para otras funciones y objetos de programa
    SensorAnalogico12562(byte pin, int direccion);
    void inicializar();
    float leer();
    struct can_frame construirTrama();
    void arreglar();
};
#endif 