/*
    SENSOR DE CORRIENTE AC
        SCT-O13-000
        100A:50mA
        VERSIÓN 2
*/

#include <Adafruit_ADS1X15.h>
#include <Wire.h>
#define CANTMUESTRAS 100 // muestras a tomar ( mas muestras mas exactidud pero mas tiempo de ejecucion)
#define AMAXSENS 100       // corriente maxima del sensor en este caso es el SCT013 
#define MVMAXSENS 1000 
   // Mv maximos que ofrece el sensor en su corriente maxima soportada
#define VOLTRED 127       // tension de la red

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */

float Int_calculada;

void setup()
{
  Serial.begin(9600);
  ads.setGain(GAIN_TWO);         // 2x gain   +/- 2.048V  1 bit =     0.0625mV
  ads.begin();
}

void loop()
{
  Int_calculada = med_Ieficaz() * 1.41; // se multiplica por un valor de correccion basado en mediciones reales

  Serial.print(Int_calculada);
  Serial.println(" A");
}

float med_Ieficaz() {                                // funcion de medicion
  /* basado en la siguiente teoria de onda:
    Al valor eficaz los norteamericanos le llaman valor RMS
    como abreviatura de Root Mean Square , ya que el mismo está matemáticamente relacionado con la curva senoidal,
    extrayendo la raíz cuadrada de la suma de sus infinitos valores instantáneos, elevados al cuadrado.
    como no podemos medir infinitos valores realizamos una cantidad de mediciones y
    aplicamos un factor de correccion basado en mediciones reales con amperimetro*/
  long tiempoinicio = millis();                       // para medir cuanto tarda en realizar las mediciones
  int16_t bitsads;
  float mVporbit = 0.0625F;
  float Ieficaz;
  float Iinstant;
  float mVinstant;
  float sumIinstant=0;

  for (int i = 0; i < CANTMUESTRAS; i++) {
    bitsads = ads.readADC_Differential_0_1();
    mVinstant = bitsads * mVporbit;
    Iinstant = mVinstant * AMAXSENS / MVMAXSENS;   // regla de tres en base al sensor conectado ya que el sensor ofrece tension y la pasamos directemante proporcional a intensidad
    sumIinstant += sq(Iinstant);                   // suma de cuadrados
  }
  Ieficaz = sqrt(sumIinstant / CANTMUESTRAS);        // raiz cuadrada de la suma de cuadrados dividida por el numero de muestras

  long tiempofin = millis();
  return (Ieficaz);
}