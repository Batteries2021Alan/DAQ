const float  OffSet = 0.5 ;

float V, P, PSI;

void setup()
{
  Serial.begin(9600);        // Abrir serial port a 9600 baudios
  Serial.println("/** Presion  Sensor MSP300 **/");
}
void loop()
{
  //Connect sensor to Analog 0
  V = analogRead(0) * 5.00 / 1024;     //Se multiplica por 5 por que va d 0 a 5v la entrada analogica, y se divide entre 1024 2 a la 10
  P = (V - OffSet) * 625;             //
  //PSI = P * 0.14503773773;           
  Serial.print("Voltage:");
  Serial.print(V, 3);
  Serial.println("V");

  Serial.print(" Presion:");
  Serial.print(P, 3);
  Serial.println(" PSI");
  Serial.println();

  delay(700);
}
