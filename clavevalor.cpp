#include <iostream>				//Mostrar en pantalla
#include <string>				//Trabajar con cadenas
#include "clavevalor.h"
using namespace std;

//COMPROBAR
int getTamanno(const tIndicePalabras &l) //Devuelve el tamanno de la tabla
{
	int resultado;
	resultado = l.tamVariable;
	return resultado;
}// int getTamanno

//SE DA POR SENTADO QUE LA POSICION ENTREGADA ES MENOR QUE EL TAMAÑO DE LA LISTA
tClaveValor getRegistro(const tIndicePalabras & l, int pos) //Devuelve el registro de una posicion concreta
{
	tClaveValor registro;
	registro = l.claves[pos];
	return registro;
}// tClaveValor getRegistro
//COMPROBAR
bool buscar(const tIndicePalabras &l, const string &s) //Busca una palabra en la tabla
{
	bool resultado = false;
	int ini = 0;
	int fin = l.tamVariable - 1;
	int mid;
	while ((ini <= fin) && (!resultado))
	{
		mid = (ini + fin) / 2;
		if (l.claves[mid].clave == s)			//Si es el valor que buscamos
			resultado = true;
		else if (l.claves[mid].clave < s)		//Si el valor buscado está en posiciones posteriores
			ini = mid + 1;
		else									//Si el valor buscado está en posiciones anteriores
			fin = mid - 1;
	}//while
	//Versión anterior, pendiente de confirmación para borrar
	/*
	for (int i = 0; i < l.tamVariable; ++i)
		if (s == l.claves[i].clave)
			resultado = true;
	*/
	return resultado;
}//  bool buscar

int getPosicion(const tIndicePalabras &l, const string &s)  //Obtiene la posición de la clave s, 
															//si no existe, -1
{
	int pos = -1, i = 0;
	if (buscar(l, s))
	{
		while ((i < l.tamVariable) && (pos == -1))	//Mientras siga quedando parte del array sin comprobar
													//si no hemos encontrado la clave deseada todavía
		{
			if (s == l.claves[i].clave)
				pos = i;
			++i;
		}//while
	}//if
	return pos;
}//int getPosicion

//COMPROBAR
void insertar(tIndicePalabras &idx, const string &palabra, const string &nombreArchivo)
{
	int pos = getPosicion(idx, palabra), i = 0;

	if (pos == -1)		//La palabra no esta en idx
	{
		++idx.tamVariable;
		while ((i < idx.tamVariable) && (idx.claves[i].clave < palabra))
			++i;
		if(i == idx.tamVariable)
		{
			idx.claves[idx.tamVariable - 1].clave = palabra;
			insertar(idx.claves[idx.tamVariable - 1].valor, nombreArchivo);
		}//if
		else
		{
			for (int j = idx.tamVariable; j > i; --j)
			{
				idx.claves[j] = idx.claves[j - 1];
				idx.claves[j - 1].valor.tamVariable = 0;
			}//for
			idx.claves[i].clave = palabra;
			insertar(idx.claves[i].valor, nombreArchivo);
		}//else
	}//if
	else
	{
		insertar(idx.claves[pos].valor, nombreArchivo);
	}
}//void insertar

void imprimir(const tIndicePalabras &idx) //Mostrar en pantalla
{
	for (int i = 0; i < idx.tamVariable; ++i)
	{
		cout << "CLAVE: " << idx.claves[i].clave << "			VALORES ASOCIADOS: ";
		imprimir(idx.claves[i].valor);
		cout << "\n";
	}//for
}//void imprimir