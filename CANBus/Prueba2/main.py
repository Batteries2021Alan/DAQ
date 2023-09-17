import serial

#! Configuración de la conexión serial
port = "COM9"
baud = 9600
arduino = serial.Serial(port, baud)
print("CAN-Bus Prueba - DAQ UM - HC06")

#! Lectura de datos
for i in range(20):
    data = tuple(arduino.readline().decode().strip().split('|'))
    print("-- Conexión con Arduino --")
    arduinoHumedad, arduinoTemperatura = data
    if arduinoTemperatura == 0 and arduinoHumedad == 0:
        print("No hay trama recibida. En espera de datos")
    else:
        print("-.-.-.-.-.-.-.-.-.-   Pruebas CAN-Bus   -.-.-.-.-.-.-.-.-.-")
        print("Arduino Temperatura: ", arduinoTemperatura)
        print("Arduino Humedad: ", arduinoHumedad)
        print("-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-")
