import serial

#! Configuración de la conexión serial
port = "COM9"
baud = 9600
arduino = serial.Serial(port, baud)
print("CAN-Bus Prueba - DAQ UM - HC06")

#! Lectura de datos
for i in range(2000):
    data = tuple(arduino.readline().decode().strip().split('|'))
    print("-- Conexión con Arduino --")
    print(data)
    tipo, arduino_voltaje, arduino_corriente = data
    if int(tipo) ==  1:
        print("-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-")
        print("Voltaje RMS: ", arduino_voltaje)
        print("Corriente RMS: ", arduino_corriente)
        print("-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-")
    if int(tipo) ==  2:
        print("-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-")
        print("Voltaje DC: ", arduino_voltaje)
        print("Corriente DC: ", arduino_corriente)
        print("-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-")