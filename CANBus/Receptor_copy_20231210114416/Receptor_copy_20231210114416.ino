/*
 * Ejemplo Receptor CAN
*/
#include <SPI.h>
#include <mcp2515.h>
struct can_frame trama;
MCP2515 mcp2515(10);

void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ); 
  mcp2515.setNormalMode();
  Serial.begin(9600);
}

void loop() {
  if (mcp2515.readMessage(&trama) == MCP2515::ERROR_OK) {
    switch (trama.can_id) {
      case 0x30:
        Serial.print("OTRO:     ");
        Serial.print(trama.can_id);
        Serial.print("|");
        Serial.print(trama.data[0]);
        Serial.print("|");
        Serial.println(trama.data[1]);
      break;
      case 0x001:
        // statement
        Serial.print(trama.can_id);
        Serial.print("|");
        Serial.print("Pack Amphours: ");
        Serial.print(((trama.data[0]*pow(2,8))+trama.data[1])*.1);
        Serial.print("|");
        Serial.print("Pack Voltage: ");
        Serial.print(((trama.data[2]*pow(2,8))+trama.data[3])*.1);
        Serial.print("|");
        Serial.print("Pack Current: ");
        Serial.print(((trama.data[4]*pow(2,8))+trama.data[5]))*.1;
        Serial.print("|");
        Serial.print("Pack SOC: ");
        Serial.println(trama.data[6]*.5);
      break;
      case 0x002:
        // statement
        Serial.print(trama.can_id);
        Serial.print("|");
        Serial.print("Pack DCL: ");
        Serial.print(((trama.data[0]*pow(2,8))+trama.data[1]));
        Serial.print("|");
        Serial.print("Pack CCL: ");
        Serial.print(((trama.data[2]*pow(2,8))+trama.data[3]));
        Serial.print("|");
        Serial.print("Relay State: ");
        Serial.print(((trama.data[4]*pow(2,8))+trama.data[5]));
        Serial.print("|");
        Serial.print("high Temperature : ");
        Serial.print(trama.data[6]);
        Serial.print("|");
        Serial.print("low Temperature : ");
        Serial.println(trama.data[7]);
      break;
      case 0x003:
        // statement
        Serial.print(trama.can_id);
        Serial.print("|");
        Serial.print("Low Cell Voltage: ");
        Serial.print(((trama.data[0]*pow(2,8))+trama.data[1])*0.0001 );
        Serial.print("|");
        Serial.print("High Cell Voltage: ");
        Serial.println(((trama.data[2]*pow(2,8))+trama.data[3])*0.0001 );
      break;
      default:
        Serial.print("Mensaje desconocido:     ");
        Serial.print(trama.can_id,HEX);
        Serial.print("|");
        Serial.print(trama.data[0]);
        Serial.print("|");
        Serial.println(trama.data[1]);
      break;
    // statements
  }
     }
  else{
    //Serial.println("No entra");
  }
}
