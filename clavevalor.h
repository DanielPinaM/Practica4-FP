#include <string>					// Trabajar con cadenas
#include "listacadenas.h"			// Incluir el struct 'tListaCadenas'
using namespace std;

const int MAX_IND = 200; //Tamaño maximo de un array claves

typedef struct tClaveValor		
{
	string clave;
	tListaCadenas valor;
};// struct tClaveValor

typedef struct tIndicePalabras
{
	tClaveValor claves[MAX_IND];
	int tamVariable;
};// struct tIndicePalabras

//FUNCIONES:
int getTamanno(const tIndicePalabras &l);		//Devuelve el tamanno de la tabla
tClaveValor getRegistro(const tIndicePalabras & l, int pos);		//Devuelve el registro de una posicion concreta
bool buscar(const tIndicePalabras &l, const string &s);		//Busca una palabra en la tabla
int getPosicion(const tIndicePalabras &l, const string &s);				//Obtiene la posición de la clave s, Si no existe, -1
void insertar(tIndicePalabras &idx, const string &palabra, const string &nombreArchivo);		//Inserta una palabra en la tabla
void imprimir(const tIndicePalabras &idx);