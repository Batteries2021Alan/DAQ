#define sensorPin  2 // pin 2 
#define relayPin 8 // pin

const int wait = 3000;// after switched ON, wait for this amount of time

void setup() {

  // Robojax.com 20181110 NJK-5002C hall sensor
  pinMode(sensorPin, INPUT_PULLUP);// define pin  as input for sensor
  // watch video explaining the INPUT_PULLUP
  //http://robojax.com/learn/arduino/?vid=robojax-push_botton_resistor
  
  pinMode(relayPin, OUTPUT);// defind pin as output

  Serial.begin(9600);// initialize serial monitor with 9600 baud.
}

void loop() {
  // Robojax.com 20181110 NJK-5002C hall sensor
  int sensed = digitalRead(sensorPin);// read pin 2 and put the result in the "sensed" variable
  if(sensed == LOW){
    Serial.println("Sensed");
    digitalWrite(relayPin, LOW);// if sensed turn relay ON
    delay(wait);// keep the relay ON for the "wait" amount of time
  }else{
    digitalWrite(relayPin, HIGH);// else turn the relay OFF
    Serial.println("====");
  }
 delay(300);// delay for 0.3 seconds
  
}
