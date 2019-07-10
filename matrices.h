#include <iostream>					//Mostrar en pantalla informacion
#include <fstream>					//Abrir archivos de texto
#include <string>					//Trabajar con variables 'string'
#include <algorithm>				//Para transformar las mayúsculas a minúsculas
#include <cctype>					//Para la función 'tolower()'
#include <math.h>
#include "clavevalor.h"				//Tabrajar con cadenas de clave-valor

using namespace std;

typedef struct tMatriz {
	double arrayMatriz[MAX_TAM][MAX_TAM];
	int dimensionMatriz;
};

typedef struct  tVector {
	double datos[MAX_TAM];
	int tam;
};

void inicializaM(tMatriz &m);
tMatriz matrizConstante(double x, int n);		//Crea una matriz de n ∙ n, en la que todos los valores iniciales son x.
tVector operator*(const tMatriz & m, const tVector & v);			//Multiplica una matriz por un vector.
tMatriz operator*(double x, const tMatriz & m);		//Obtiene la matriz que se obtiene multiplicando cada elemento de m por x.
tMatriz operator+(const tMatriz & m1, const tMatriz & m2);		//Suma dos matrices.
tMatriz desdeEnlacesAMatriz(const tMatriz & L);		//Devuelve la matriz M obtenida de L como en la introducción de la sección 4.
tVector vectorUnos(const int &dimensionMatriz);
tVector vectorPropio(const tMatriz & M, double epsilon);
bool proximos(const tVector &v1, const tVector &v2, double epsilon);
//M es una matriz tal que todas sus columnas suman 1, devuelve un vector v con la primera componente igual a 1 tal que MM ∙ v ≃ v */
tVector vectorX(tMatriz &M);