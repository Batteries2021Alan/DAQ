//Prueba
#include <SD.h>
int sensor2=5;
int sensor3=10;
float val=0;
String nombre="datalogP.csv";
boolean existe=true, titulosPuestos=false;
String token=",", datos, cor1="[", cor2="]";
String tramas[50][7];
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
  if(SD.exists(nombre)&&existe==true){
    SD.remove(nombre);
    Serial.println("Si existe y se borro");
    existe=false;
  }
  Data = SD.open(nombre,FILE_WRITE);//abrimos  el archivo
  if (Data) { 
        Serial.print("Escribiendo SD: ");
        if(titulosPuestos==false){
          Data.print("Tiempo,Prueba,");
          for(int i=1;i<=350;i++){
             if(i<350){
              Data.print("Sensor"+cor1+i+cor2+token);
              val=100000.8851+i;
              datos=val+token+datos+token;
             }
             else{
              Data.println("Sensor"+cor1+i+cor2);
             }
             delay(1);
          }
          Serial.println("Titulo puesto");
          titulosPuestos=true;
        }
        //Data.print(buf);
        for(int j=0;j<50;j++){
          for(int k=0;k<7;k++){
            tramas[j][k]=k+token;
          }
        }
        Data.print(millis()/1000);
        Data.print(token);
        Data.print("prueba 2");
        Data.print(token);/*
        Data.print(analogRead(A0));
        Data.print(",");
        Data.print(sensor2);
        Data.print(",");
        Data.print(sensor3);
        Data.print(",");*/
        for(int j=0;j<50;j++){
          for(int k=0;k<7;k++){
            if(j<49){
              Data.print(tramas[j][k]);
            }
            else{
              Data.println(tramas[j][k]);
            }
            delay(10);
          }
        }
        //Data.println(datos);
        
        Data.close(); //cerramos el archivo
        
        Serial.print("Tiempo(ms)=");
        Serial.println(millis()/1000);
  } else {
    Serial.println("Error al abrir el archivo");
  }
  sensor2 ++;
  sensor3 ++;
  delay(1000);
}