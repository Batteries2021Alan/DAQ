//Prueba 5
//----------------------------Librerias------------------------------------------//
//------------------------------SD------------------------------------------------//
#include <SD.h>
#include <SPI.h> //Library for using SPI Communication
#include <LinkedList.h> //Library for using Linked List commands
//--------------------------------mcp---------------------------------------------//
#include <SPI.h>
#include <mcp2515.h>
//----------------------------Variables globales------------------------------------------//
double val=0;//No importa si se pone(Solo es para checar cuantos datos se pueden poner por celda)
String nombre="datalogP.csv";//Este es el nombre del archivo
boolean existe=0, titulosPuestos=false, leerTrama=0;//Variables de verificacion para saber si algo ya paso o todavia no
String token=",", cor1="[", cor2="]",sensor="Sensor";//Variables para la escritura (el mas usado y mas importante es el token)
String d1="";//Aqui se guardan los datos para pasar de entero a cadena
//String tramas[50][7];//estas son el numero de celdas que se quieren usar pero no sirve
LinkedList<String> DatosDeTramas=LinkedList<String>();//es una estructura de cadenas
int numeroDeNodos=5;//cuantos nodos se planean tener
File Data;//Variable para un archivo

struct can_frame trama;
struct can_frame Pedir;
MCP2515 mcp2515(10);

//----------------------------setup------------------------------------------//
void setup()
{
  //Inicializa el MCP
   SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ); 
  mcp2515.setNormalMode();
  //Se checa si esta bien conectada la sd
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
  //Checa si existe el archivo y si existe lo borra
  //es solo por comodidad de pruebas
  if(SD.exists(nombre)&&existe==0){
    SD.remove(nombre);
    Serial.print("Si existe y se borro");
    existe=1;
    Serial.println(existe);
  }
  Data = SD.open(nombre,FILE_WRITE);//abrimos  el archivo
  //Checa que el archivo este bien y exista
  if (Data) {
    //Checa si el titulo esta puesto y si no lo pone
    if(titulosPuestos==false){
      Data.print("Tiempo,Prueba,");//primeras dos celdas
      //Llena los titolos con "Sensor[#]"
      for(int i=1;i<=(numeroDeNodos*8);i++){
        if(i<(numeroDeNodos*8)){
        Data.print(sensor+cor1+i+cor2+token);//imprime los titulos
        }
        else{
        Data.println(sensor+cor1+i+cor2);//imprime la ultima parte del titulo y da un salto de linea para ir a la siguiente fila
        }
      }
      //Simula una trama
      /*
      for(int j=0;j<=7;j++){
        val=j*111111.22;//es para checar cual es el numero maximo de de numeros
        d1=(String)val+token;//convierte el flotante en string y le agrega la coma
        DatosDeTramas.add(d1);//Agrega una cadena a la lista
      }//*/
      titulosPuestos=true;//Es para que solo se haga una vez
      Serial.println("Titulos puesto");
    }
    //IMPRIME apartir de aqui
    Serial.print("Escribiendo SD: ");
    Data.print(millis());
    Data.print(token);
    Data.print("prueba 5");
    Data.print(token);
    //Aqui se piden las tramas a todos los transmisores
    for(int i=1;i<=(numeroDeNodos);i++){
      Pedir.can_id  = 160;           //CAN id as 0x036
      Pedir.can_dlc = 1;               //CAN data length as 8
      Pedir.data[0] = i;
      mcp2515.sendMessage(&Pedir);
      Serial.print(i);
      while(mcp2515.readMessage(&trama) != MCP2515::ERROR_OK){
      }
      //if(mcp2515.readMessage(&trama) == MCP2515::ERROR_OK){
        //delay(100);
        if(trama.can_id==i){
          for(int j=0;j<8;j++){
            d1=(String)trama.data[j]+token;
            if(i<numeroDeNodos)
              Data.print(d1);
            else{
              if(j<7){
                Data.print(d1);
              }
              else{
                Data.println(d1);
              }
            }
              
          }/*
        }
        else{
          Serial.println("No lee");
        }*/
      }
      else{
      Serial.println("No entra");
      }
    }

    Data.close(); //cerramos el archivo
    /*
    for(int h=0;h<numeroDeNodos*8;h++){
      //Checa si no es la ultima cadena para imprimirlo en la SD sin salto
      if(h<(numeroDeNodos*8)-1){
        Data.print(DatosDeTramas.get(h));
      }
      else{
        Data.println(DatosDeTramas.get(h));//imprime en la SD con un salto para ir a la siguiente 
      }
    }*/

    Serial.print("Tiempo(ms)=");
    Serial.println(millis()/1000);
  } else {
    Serial.println("Error al abrir el archivo");
  }
}