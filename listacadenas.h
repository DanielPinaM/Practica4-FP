#ifndef listacadenas_h
#define listacadenas_h
#include <string>		//Trabajar con las cadenas
using namespace std;

//CONSTANTES 'listacadenas'

const int MAX_TAM = 50;

typedef struct tListaCadenas
{
	int tamVariable;
	string cadenas[MAX_TAM];
};//struct tListaCadenas

//FUNCIONES 'listacadenas'
int getTamanno(const tListaCadenas &l);		//Obtiene el tamanno de la lista
string getCadena(const tListaCadenas &l, int pos);		//Obtiene una cadena de la lista
void  insertar(tListaCadenas &l, const string & s);		//Inserta un elemento en el array
bool buscar(const tListaCadenas &l, const string &s);		//Busca un elemento del array
void eliminar(tListaCadenas &l, int pos);		//Elimina un valor concreto de la lista
void inicializa(tListaCadenas &tabla);		//Inicializa la lista dejándola vacía
void imprimir(const tListaCadenas &l);		//Muestra en pantalla la lista
#endif