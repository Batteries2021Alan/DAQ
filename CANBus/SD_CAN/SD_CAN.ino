#include <SD.h>
int sensor2=5;
int sensor3=10;
int bandera1=0;
String archivo="datalog3.csv";
File Data;

void setup()
{
  Serial.begin(9600);
  Serial.print("Iniciando SD ...");
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
}

void loop()
{
  Data = SD.open(archivo,FILE_WRITE);//abrimos  el archivo
  if (Data) { 
        Serial.print("Escribiendo SD: ");
        //Data.print(buf);
        if(bandera1==0){
          Data.print("tiempo,");
          for(int i=0;i<=48;i++){
            Serial.print(i+",");
          }
          Data.println("");
          bandera1=1;
        }

        Data.print(millis()/1000);
        Data.print(",");
        Data.print(analogRead(A0));
        Data.print(",");
        Data.print(sensor2);
        Data.print(",");
        Data.println(sensor3);
        Data.close(); //cerramos el archivo
        
        Serial.print("Tiempo(ms)=");
        Serial.print(millis()/1000);
        Serial.print(", sensor1=");
        Serial.print(analogRead(A0));
        Serial.print(", sensor2=");
        Serial.print(sensor2);
        Serial.print(", sensor3=");
        Serial.println(sensor3);
  } else {
    Serial.println("Error al abrir el archivo");
  }
  sensor2 ++;
  sensor3 ++;
  delay(1000);
}