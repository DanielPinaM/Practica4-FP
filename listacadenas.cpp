#include <iostream>				//Mostrar en pantalla
#include <string>				//Trabajar con las cadenas
#include "listacadenas.h"
using namespace std;
//COMPROBAR QUE FUNCIONA
int getTamanno(const tListaCadenas &l) //Obtiene el tamanno de la lista
{
	int resultado;
	resultado = l.tamVariable;
	return resultado;
}//int getTamanno
 //COMPROBAR QUE FUNCIONA
string getCadena(const tListaCadenas &l, int pos) //Obtiene una cadena de la lista
{
	string resultado;
	resultado = l.cadenas[pos];
	return resultado;
}//string getCadena
 //COMPROBAR QUE FUNCIONA
void insertar(tListaCadenas &l, const string &s)//Inserta un elemento en el array
{
	++l.tamVariable; //Aumentamos en 1 el tamaño del array
	l.cadenas[l.tamVariable - 1] = s; //Guardamos el nuevo valor en el array
}//void insertar
 //COMPROBAR QUE FUNCIONA
bool buscar(const tListaCadenas &l, const string &s) //Busca un elemento del array
{
	bool resultado = false;
	for (int i = 0;(resultado == false) && (i < l.tamVariable); ++i)
		if (l.cadenas[i] == s)
			resultado = true;
	return resultado;
}//bool buscar
//COMPROBAR QUE FUNCIONA
void eliminar(tListaCadenas &l, int pos) //Elimina un valor concreto de la lista
{
	for (int i = pos; i < l.tamVariable; ++i) //El array lo movemos hacia la izquierda desde pos + 1
		l.cadenas[i] = l.cadenas[i + 1];
}//void eliminar
 //COMPROBAR QUE FUNCIONA
void inicializa(tListaCadenas &lista)	//Inicializa la lista dejándola vacía
{
	lista.tamVariable = 0;
}//void inicializa

void imprimir(const tListaCadenas &l) //Muestra en pantalla la lista
{
	for (int i = 0; i < l.tamVariable; ++i)
	{
		cout << l.cadenas[i] << ", ";
	}//for
}//void imprimir