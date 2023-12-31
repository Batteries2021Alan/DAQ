a='Welcome Miguel'
print('hello world',a)
"""tkinter vs pyqt"""
"""dis — Disassembler for Python bytecode"""
import tkinter #es la interfaz estándar de Python para el kit de herramientas GUI de Tcl / Tk.
import tk_tools #Proporciona un conjunto de herramientas para administrar ventanas
import serial #Nos permite el acceso al puerto serie
import csv #nos permite leer y escribir datos tabulares en formato CSV (Valores separados por comas)
import datetime #Nos permite obtener la hora y fecha directamente de la computadora
import numpy as np #librería de Python especializada en el cálculo numérico y el análisis de datos,
                    # especialmente para un gran volumen de datos.
from matplotlib.figure import Figure #nos permite crear figuras, modificarlas y componerlas.
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg #Nos permite manipular gráficos o figuras 
                                                                #embebidas en Frames
#codigo se divide en secciones


"""Las siguientes funciones se van a asociar al evento del click
en el boton de la ui"""
def plot_datos():
    global condicion,datos
    if condicion==True:
        dato=arduino.readline() #'\n'
        if len(datos)<100:
            #NOTA: Invetigar append, otra forma de agregar
            datos=np.append(datos,float(dato[0:len(dato)-2]))
            #dato[0:len(dato)-2] para quitar '\n'
        else:
            #Remover el primer dato
            datos[0:99]=datos[1:100]
            datos[99]=float(dato[0:len(dato)-2])

        linea.set_xdata(np.arange(0,len(datos)))
        linea.set_ydata(datos)
        canvas.draw()

        valor=float(dato[0:len(dato)-2].decode('utf-8'))
        display_7seg.set_value(str(valor))
        
        """Guardar el dato en un archivo"""
        with open("datos_sensor.csv",'a',newline='') as f:
            escritor=csv.writer(f,delimiter=',')
            escritor.writerow([datetime.datetime.strftime(
                datetime.datetime.now(), '%Y/%m/%d %H:%M:%S'),
                str(valor)]) #si no tiene 
            #   corchetes separa cada caracter con una coma


    igu.after(1,plot_datos)
    

def iniciar_plot():
    print('hola!!!') #tuve un error con np.arranges
    global condicion #sfsdf
    #sdfsdf
    #NOTA: Para modificar variables declaradas fuera de la 
    #      funcion es necesario hacerla global, asi ya no la 
    #      colocas como parametro en la funcion ni regresas
    #      un valor con return
    condicion=True
    boton_inicio.config(state='disabled')
    boton_detencion.config(state='normal')
    arduino.reset_input_buffer()
    #NOTA: Al momento de iniciar comunicacion serial la 
    #      la computadora va recibir datos y mantenerlos
    #      en el buffer, pero esos datos no nos interesan,
    #      si no los inmediatos posteriores
def detener_plot():

    global condicion
    condicion=False
    boton_inicio.config(state='normal')
    boton_detencion.config(state='disabled')

#Se termina la comunicacion serial con el arduino
#Se destruye el objeto igu
def cerrar():
    arduino.close
    igu.destroy()#cerrar la igu
    #NOTA: Puedes emplear los metodos de los objetos creados
    #      fuera de la funcion

"""creacion de objeto ui"""
igu=tkinter.Tk()#iterfaz grafica de usuario (igu)

"""lo primero a colocar es configuraciones de la igu"""
igu.title('Graficar datos desde arduino')#Titulo de la igu
igu.geometry('900x700')#resolucion de la igu
igu.configure(background='white') #color del fondo de la igu

"""En tk no se tiene un objeto grafica, por ende
se crea una figura con matplotlib y se asociacia
al objeto FigureCanvasTkAgg"""

"""Crecion de la figura en matplotlib"""
fig=Figure(figsize=(8,4),dpi=100)#dpi->resolucion
#no se va a mostrar la figura
ax=fig.add_subplot(111)#se emplear para agregar varias
#   graficas en una sola figura (como una matriz)
ax.set_title('Grafica de datos del sensor') #Titulo
#Titulos de los ejes
ax.set_xlabel('Tiempo')
ax.set_xlabel('Valor')#Lectura del arduino
ax.grid(True,linestyle='-.')#regilla del fondo de la grafica
ax.set_xlim(0,100)
ax.set_ylim(0.000,20.000)#limites de lalectura arduino!!!!!!!!!!!!!
#Se guarda la referencia de la linea ¿?Una coleccionde cosas
#   que se contruye con plot
linea=ax.plot([],[],color='green',marker='o',markersize=6)[0]
"""Se crea el objeto FigureCanvasTkAgg y se asocia a la figura
#en creada en matplotlib"""
canvas=FigureCanvasTkAgg(fig,master=igu)
canvas.draw()

"""Creacion de botones"""
boton_inicio=tkinter.Button(igu,text='Iniciar Graficado', 
font=('Consolas',14),padx=10,pady=10,bg='green',fg='white',
command=lambda:iniciar_plot())

boton_detencion=tkinter.Button(igu,text='Detener Graficado', 
font=('Consolas',14),padx=10,pady=10,bg='red',fg='white',
command=lambda:detener_plot())

boton_cerrar=tkinter.Button(igu,text='Cerrar', 
font=('Consolas',14),padx=10,pady=10,bg='gray',fg='white',
command=cerrar)

etiqueta=tkinter.Label(igu,text='Valor del sensor',
font=('Consolas',14),bg='white')
#Empleando tktools se agrega un display7seg
display_7seg=tk_tools.SevenSegmentDigits(igu,digits=4,
background='white',digit_color='black',height=50)

"""Se muestra el elemento en la igu"""
#Se muestra la grafica de matplotlib asociada a FigureCanvasTkAgg
canvas.get_tk_widget().grid(row=0,column=0,rowspan=2,
columnspan=2,padx=30,pady=30)

#Se muestran la etiquieta
etiqueta.grid(row=2,column=0,pady=10)

#Se muestra el display de 7 seg
display_7seg.grid(row=2,column=1,pady=10)

#Se muestran los botones
boton_inicio.grid(row=3,column=0,pady=20)
boton_detencion.grid(row=3,column=1,pady=10)
boton_cerrar.grid(row=4,column=0,columnspan=2)


"""d"""
datos=np.array([])
condicion=False
arduino=serial.Serial('com6',9600) #PUERTO!!!!
#Despues de un determinado 
# tiempo se ejecuta la funcion
#   "plot_datos"
igu.after(1,plot_datos)#despues de 1 ms se ejecuta la funcion

igu.mainloop()  
""" genera el loop que muestra
la igu con todo lo que contiene (simular a un video
por eso es un loop) """
#los comentarios con triples comillas dobles 
#no se pueden colocar en la mismia linea de codigo
