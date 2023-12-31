#include "SensorAnalogico12562.h";
SensorAnalogico12562::SensorAnalogico12562(byte pin, int direccion){
    this->pin = pin;
    this->direccion=direccion;
    inicializar();
}
void SensorAnalogico12562::inicializar(){
    pinMode(pin,INPUT);
}
float SensorAnalogico12562::leer(){
    float datoL=analogRead(pin);
    //dato=map(dato,0,1023,0,256);
    return datoL;
}
struct can_frame SensorAnalogico12562::construirTrama(){
    arreglar();
    trama.can_id  = direccion;           //CAN id (Nomvre de la trama)
    trama.can_dlc = 8;               //CAN data tamaño de la trama
    trama.data[0] = datosBin[0];               //Valores maximo de 256
    trama.data[1] = datosBin[1];               //Valores maximo de 256
    trama.data[2] = datosBin[2];               //Valores maximo de 256
    trama.data[3] = datosBin[3];               //Valores maximo de 256
    trama.data[4] = datosBin[4];
    trama.data[5] = datosBin[5];
    trama.data[6] = datosBin[6];
    trama.data[7] = datosBin[7];
    /*Serial.print("-----[ ");
    Serial.print(datosBin[0]);
    Serial.println(" ]-----");*/
    return trama;
}
void SensorAnalogico12562::arreglar(){
    dato=leer();
    d1=int(dato);// Maximo de 256
    //d2= int((dato-d1)*100);//.99
    datosBin[0]=d1;
    datosBin[1]=d2;
    datosBin[2]=d3;
    datosBin[3]=d4;
    datosBin[4]=d5;
    datosBin[5]=d6;
    datosBin[6]=d7;
    datosBin[7]=d8;
}