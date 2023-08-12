/*
    SENSOR DE CORRIENTE AC
        SCT-O13-000
        100A:50mA
        VERSIÓN 1
*/
#include "EmonLib.h"  // Biblioteca para la familia de sensores SCT-013 
EnergyMonitor emon1; 

void setup() {

Serial.begin(9600);
 emon1.current(1, 55.5); // current (pin de entrada, constante de calibración)
/* constante de calibración: Es el valor que se desea leer cuando hay 1V a la salida del sensor 
          55.5 Para una resistencia de 36 Omhs
          *Tentativa a cambio para la versión 2*
*/
}

void loop() {
  double Irms = emon1.calcIrms(1480); 
  Serial.print("Irms = ");
  Serial.print(Irms);
  Serial.println(" [A]");
}