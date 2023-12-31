//Prueba 2
//----------------------------Librerias------------------------------------------//
#include <SD.h>
#include <SPI.h> //Library for using SPI Communication
#include <LinkedList.h> //Library for using Linked List commands
//----------------------------Variables globales------------------------------------------//
int sensor2=5;//Ya no se usa
int sensor3=10;// Ya no se usa
float val=0;//No importa si se pone(Solo es para checar cuantos datos se pueden poner por celda)
String nombre="datalogP.csv";//Este es el titulo
boolean existe=false, titulosPuestos=false;//Variables de verificacion para saber si algo ya paso o todavia no
String token=",", datos, cor1="[", cor2="]",d1="",sensor="Sensor";//Variables para la escritura (el mas usado y mas importante es el token)
//String tramas[50][7];//estas son el numero de celdas que se quieren usar pero no sirve
LinkedList<String> DatosDeTramas=LinkedList<String>();
File Data;//Variable para un archivo

//----------------------------setup------------------------------------------//
void setup()
{
  Serial.begin(9600);
  Serial.println("Iniciando SD ...");
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
}
//----------------------------loop------------------------------------------//
void loop()
{
  if(SD.exists(nombre)&&existe==0){
    SD.remove(nombre);
    Serial.print("Si existe y se borro");
    existe=1;
    Serial.println(existe);
  }
  Data = SD.open(nombre,FILE_WRITE);//abrimos  el archivo
  if (Data) {
        if(titulosPuestos==false){
          Data.print("Tiempo,Prueba,");
          for(int i=1;i<=350;i++){
             if(i<350){
              Data.print(sensor+cor1+i+cor2+token);
              val=100000.8851+i;
              datos=val+token+datos+token;
             }
             else{
              Data.println(sensor+cor1+i+cor2);
             }
             delay(1);
          }
          for(int j=1;j<=7;j++){
            d1=(String)j+",";
            DatosDeTramas.add(d1);
            Serial.print("Entra 1 "+d1);
          }
          titulosPuestos=true;
          Serial.println("Titulos puesto");
        }
        Serial.print("Escribiendo SD: ");
        //Data.print(buf);
        Data.print(millis()/1000);
        Data.print(token);
        Data.print("prueba 2.2");
        Data.print(token);/*
        Data.print(analogRead(A0));
        Data.print(",");
        Data.print(sensor2);
        Data.print(",");
        Data.print(sensor3);
        Data.print(",");*/
        for(int h=0;h<50;h++){
          for(int j=0;j<DatosDeTramas.size();j++){
            if(h<49){
              Data.print(DatosDeTramas.get(j));
            }
            else{
              if(j<6)
                Data.print(DatosDeTramas.get(j));
              else
                Data.println(DatosDeTramas.get(j));
            }
            delay(1);
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