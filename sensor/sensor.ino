/*
int SENSOR = 7; 

bool s = true;
int periodo = 15000, contador = 0, TA = 0, valorFijado = 0; 

void setup() {
  Serial.begin(9600);// setup Serial Monitor to display information
  pinMode(SENSOR, INPUT);// define pin as Input  sensor
}

void loop() {
  // Cada minuto imprime las RPM
  if(millis() > (periodo + TA)){
    valorFijado = contador; 
    Serial.println(contador);
    TA = millis();
    contador = 0;
    delay(1000);
    }
  s = digitalRead(SENSOR);
  // Deteccion de metal con el sensor 
  if(s == 0){
    delay(1000); // Delay para que no se acumulen las vueltas
    contador++; 
  }
  Serial.println(s);
}
*/
#define interruptor0 2
volatile int contador = 0; 

void setup(){
  Serial.begin(57600);
  attachInterrupt(0, interrupcion0, CHANGE);
}

void loop(){
  delay(999);
  Serial.print(contador * 60); // 60/6
  Serial.println(" RPM");
  contador = 0; 
}

void interrupcion0(){
  contador++; 
}
