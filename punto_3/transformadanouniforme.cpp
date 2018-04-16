#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

//inicializacion de las funciones a utilizar
int contemoslineas();
int carguemosdatos(float *primeraequis, float *primeraye, int n);
int encontremosi(float x, float *primeraequis, int n);
float creemosarreglo(float hache, float *xn, float *primeraequis, float *primeraye, int i, int n);
int interpolar(float *xn, float* yn, float *primeraequis, float *primeraye, int j, int n, int i);
int hagamosfourier(float *yereal, float *yeimaginaria, float *efeg, float *yn, float hache, float dif, int i, int j, int n);

// funcion para contar lineas, con el numero de lineas se pone el limite a los recorridos de este punto del taller

int contemoslineas(){
  
  string linea;
  int contadordelineas = 0;
  ifstream myfile("datos.txt");
  while(getline(myfile, linea)){
    ++contadordelineas;
  }
  return contadordelineas;
}
//funcion para cargar los datos para la realizacion de la transformada

int carguemosdatos(float *primeraequis, float *primeraye, int n){
  
  int i;
  ifstream in("datos.txt");
  for(i=0; i< n; ++i){
      in >> primeraequis[i] >> primeraye[i];
    }
}
//funcion para indice
int encontremosi(float x, float *primeraequis, int n){
  
	int i = 0;
	while (x > primeraequis[i]){
		i ++;
	}

	if (i>0){
		i --;
	}
	return i;
}
//funcion para retornar h
float creamosarreglo(float hache, float *xn, float *primeraequis, float *primeraye, int i, int n){
  
  hache =(primeraequis[n-1] - primeraequis[0])/(n-1);
  xn[i] = primeraequis[0];
  for(i=1; i<n; ++i){
    xn[i] = xn[i-1] + hache;
  }
  return hache;
}
int interpolar(float *xn, float* yn, float *primeraequis, float *primeraye, int j, int n, int i){

    int inter;
    float ele;
    int ipoli;
    int enem = 3;
    int icero;
    int k;
    float x;
    float yj;
    float lj;

	ipoli = 0;
    for (inter = 0; inter < n; ++inter){
            ele = 0;
	    x = xn[inter];
	    ipoli = encontremosi(x,primeraequis,n);

	    if (ipoli+enem<n){
	    	icero = ipoli;
	    }
	    else{
	    	icero = n-enem;
	    }
	    
	    for (j = icero; j < icero+enem; ++j){
	      	lj = 1.0;
	    	yj = primeraye[j];
	    

	    	
		for (i = icero; i < icero+enem; ++i){
	    		if (i!=j){
	    			lj = lj*(x-primeraequis[i])/(primeraequis[j]-primeraequis[i]);
	    		}
	    	}

	    	ele += yj*lj;
	    }
	    yn[inter] = ele;

	}
    return j;
}
int hagamosfourier(float *yereal, float *yeimaginaria, float *efeg, float *yn, float hache, float dif, int i, int j, int n){
  	for ( i = 0; i < n; ++i){
		for ( j = 0; j < n; ++j){
		        yeimaginaria[i] += yn[j]*sin(-2*3.1415926*i*j/n);
			yereal[i] += yn[j]*cos(-2*3.1415926*i*j/n);
			
		}
		if (i<=n/2){
			efeg[i] = i*dif;
		}
		else{
			efeg[i] = -(0.5/hache) + (i-n/2)*dif;
		}

		cout << efeg[i] << ' ' << yereal[i] << ' ' << yeimaginaria[i] << '\n';
	}
}
	
  

// funcion main para la ejecucion del codigo
int main() {
	
    int n = contemoslineas();
    float primeraequis[n];
    float primeraye[n];
    int i = carguemosdatos(primeraequis, primeraye, n);
    float hache;
    float xn[n];
    hache = creamosarreglo(hache, xn, primeraequis, primeraye, i, n);
    float yn[n];
    int j = 0;
    j = interpolar(xn, yn, primeraequis, primeraye, j, n, i);
    float yereal[n];
    float yeimaginaria[n];
    float efeg[n];
    float dif;
    dif = (0.5/hache)/(n/2);

    int fin = hagamosfourier(yereal, yeimaginaria, efeg, yn, hache, dif, i, j, n);



   return 0;
}
 
