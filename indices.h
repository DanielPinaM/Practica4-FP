#include <iostream>					//Mostrar en pantalla informacion
#include <fstream>					//Abrir archivos de texto
#include <string>					//Trabajar con variables 'string'
#include <algorithm>				//Para transformar las mayúsculas a minúsculas
#include <cctype>					//Para la función 'tolower()'
#include "matrices.h"				//Tabrajar con cadenas de clave-valor

using namespace std;

//FUNCIONES:
void completarArchivoActual(tIndicePalabras &tabla, const string &nombreArchivoActual, tListaCadenas &enlaces, tListaCadenas &totales, tMatriz &L, const int posI);
//Dado un archivo no visitado, se guarda en la tabla los valores de ese archivo
//Si encontramos un enlace, lo guardamos en 'enlaces'
void inicializa(tIndicePalabras &tabla);		//Inicializa la tabla
void crearTabla(tIndicePalabras &tabla, const string &archivoInicial, tListaCadenas & totales, tMatriz &L);		//Rellenamos la tabla a partir de archivoInicial

//V2........................................................................................................................

