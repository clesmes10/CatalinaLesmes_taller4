import matplotlib.pyplot as plt
import numpy as np

#imagen a procesar para frecuencias altas y bajas

imagencitapng = plt.imread("imagen.png")
imagencitapngnueva = imagencitapng[:,:,0]

#dimensiones de la imagen a procesar

dimensionesimag = np.shape(imagencitapng)
largoimagencita = dimensionesimag[0]
anchoimagencita = dimensionesimag[1]

#funcion para obtener la transformada de fourier en 2d para la imagen, implementacion igual que en el primer punto, solo parte real


def transformadapng(elemento, eme, ene):
    for a in range(eme):
        tr =0.0
        for b in range(ene):
            for c in range(eme):
                sr = 0.0
                for d in range(ene):
                    trans = np.exp(np.cos(-2.0*np.pi*(((a*c)/eme)+((b*d)/ene))))
                    sr += elemento*trans
            tr = sr /eme / ene
    return tr

#funcion para obtener la transformada inversa, solo parte real

def transformadainv(convovo, eme, ene):
    for a in range(eme):
        for b in range(ene):
            sr= 0.0
            for c in range(eme):
                for d in range(ene):
                     trans = np.exp(np.cos(2.0*np.pi*(((a*c)/eme)+((b*d)/ene))))
                     sr += convovo*trans
            r = sr + 0.5
    return r

#funcion para gauss

emm = np.linspace(-10,10, largoimagencita)

def gaussi(lins):
    gaa = 1.0-np.exp((lins**2)*-0.05) #ancho del 5%
    return gaa
gausss = gaussi(emm)

#integracion para normalizar
a= -10.0
b= 10.0
N= largoimagencita
total = 0.0
delta = (b-a)/N
for i in range(N):
    ar = (gaussi(a)+gaussi(b+delta))*(delta/2.0)
    total = total + ar
    
#gauss normalizada

gaussinorr = gausss/total

#kernel a partir de gauss normalizado para filtro

kern = np.tile(gaussinorr, (anchoimagencita, 1)).T
dimker = np.shape(kern)
largok = dimker[0]
anchok = dimker[1]

#discriminacion entre frec altas y frec bajas por medio de condicionales

filtroaelegir = raw_input("\n ingrese filtro alto o bajo")

if(filtroaelegir == "alto"):
    transimagenalt = transformadapng(imagencitapngnueva, largoimagencita, anchoimagencita)
    transkeralto = transformadapng(kern, largok, anchok)
    convolucionalt = transkeralto*transimagenalt
    imagenf = transimagenalt-convolucionalt
    dimcon = np.shape(imagenf)
    larcon = dimcon[0]
    ancon = dimcon[1] 
    inversaimagencitaalt = transformadainv(imagenf, larcon, ancon)
    plt.imshow(inversaimagencitaalt)
    plt.savefig("altas.png")
    
elif(filtroaelegir == "bajo"):
    transimagenbaj = transformadapng(imagencitapngnueva, largoimagencita, anchoimagencita)
    transkerbajo = transformadapng(kern, largok, anchok)
    convolucionbaj = transkerbajo*transimagenbaj
    dimconb = np.shape(convolucionbaj)
    larconb = dimconb[0]
    anconb = dimconb[1]
    inversaimagencitabaj = transformadainv(convolucionbaj,larconb, anconb)
    plt.imshow(inversaimagencitabaj)
    plt.savefig("bajas.png")
    
    




                

