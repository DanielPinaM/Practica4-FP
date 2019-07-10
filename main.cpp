#include <iostream>				//Mostrar en pantalla y escribir con el teclado
#include <fstream>				//Abrir los archivos de texto
#include <string>				//Trabajar con las cadenas
#include "indices.h"			//Crear la tabla con el archivo raíz
using namespace std;
//Imokementar modulo para calculo de el vector X (PageRanks)
//Por lo que se pondra el nuevo modulo.h en vez de el indices.h, ya que lo tendra incluuido

int main()
{
	tListaCadenas totales;						//TOTALES VERSION 2
	tMatriz L;									//L matriz de version 2
												//PEDIR EL ARCHIVO RAIZ
	tIndicePalabras tabla;		//SU IDX
	inicializa(tabla);		//Inicializamos la tabla que vamos a utilizar
	inicializa(totales);	//Inicializamos la lista de enlaces totales
	inicializaM(L);
	string nombreIndice;						//El nombre del archivo
	string palabraBuscada = "a";				//La palabra que el usuario quiere buscar


	cout << "Por favor, introduzca el nombre del archivo raiz desde el que se creara el indice, "
		<< "(por favor introduzca la extension '.txt' al final): ";
	cin >> nombreIndice;


	//CREAR TABLA

	crearTabla(tabla, nombreIndice, totales, L);			//Creamos la tabla que vamos a utilizar, ACTUALIZADA;
	tMatriz M = desdeEnlacesAMatriz(L); // M = (1 - C) * Cn + C * M´;
	cout << "La dimension de M es: " << M.dimensionMatriz << "\n";
	for (int i = 0; i < M.dimensionMatriz; ++i) {
		for (int j = 0; j < M.dimensionMatriz; ++j)
			cout << M.arrayMatriz[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
	tVector vX;
	vX.tam = M.dimensionMatriz;
	vX = vectorX(M);
	for (int i = 0; i < vX.tam; ++i)
		cout << vX.datos[i] << "  ";
	cout << "\n";
	vX = M * vX;
	cout << "Valor vX (final): \n";
	cout << vX.datos[0] << "  " << vX.datos[1];
	cout << "\n";
	imprimir(tabla);

	cout << "\n \n Escoja que palabra quiere que se busque en el registro('fin' para terminar): ";
	cin >> palabraBuscada;
	while (palabraBuscada != "fin"){
		if (buscar(tabla, palabraBuscada))	//Si la palabra está en la tabla
		{
			int pos = getPosicion(tabla, palabraBuscada);	//Buscamos la posición de la palabra. Nunca saldrá '-1'
															//porque sabemos con seguridad que está en la 'tabla'
			
			cout << "Encontrada en '" << tabla.claves[pos].valor.cadenas[0] << "' ";

			cout << "(relevancia " << vX.datos[pos] << ")\n";	//MOSTRAR EL VALOR DE LA MATRIZ EN LA POSICIÓN CORRECTA
		}//if
		else								//Si la palabra no está en la tabla
			cout << "La palabra buscada no está en la tabla.\n";

		//Código de Ana (Lo que estaba dentro del while de su main)
	/*
		tListaCadenas archivos = getValor(tabla, palabraBuscada);
		tVector valores = valoresSubLista(archivos, totales, v);
		ordenaValores(archivos, valores);
		muestraArchivos(archivos, valores);
	*/

		cout << "\n Escoja que palabra quiere que se busque: ";
		cin >> palabraBuscada;
		//palabra = pedirPalabra();
	}//while
	return 0;
} // main

/*int main()
{
	tListaCadenas totales;						//TOTALES VERSION 2
	tMatriz L;									//L matriz de version 2
	//PEDIR EL ARCHIVO RAIZ
	tIndicePalabras tabla;
	inicializa(tabla);		//Inicializamos la tabla que vamos a utilizar
	inicializa(totales);	//Inicielizamos la lista de enlaces totales
	string nombreIndice;						//El nombre del archivo
	string palabraBuscada = "a";				//La palabra que el usuario quiere buscar

	cout << "Por favor, introduzca el nombre del archivo raiz desde el que se creara el indice,"
		<< " tenga en cuenta que tiene que ser un archivo .txt "
		<< "(por favor introduzca la extension '.txt' al final): ";
	cin >> nombreIndice;
	
	//CREAR TABLA con el algoritmo de pag 6 modulo 3.2.3

	crearTabla(tabla, nombreIndice, totales, L);			//Creamos la tabla que vamos a utilizar, ACTUALIZADA

	//EL USUARIO DICE QUE PALABRA QUIERE QUE SE BUSQUE HASTA 'fin'

	imprimir(tabla);
	  
	cout << "\n \n Escoja que palabra quiere que se busque en el registro('fin' para terminar): ";
	while (palabraBuscada != "fin")
	{
		cin >> palabraBuscada;
		if (palabraBuscada != "fin")
		{
			if (buscar(tabla, palabraBuscada))
				cout << "Esta en el registro.\n";
			else
				cout << "No esta en el registro.\n";

			cout << "\n \n Busqueda terminada, por favor, escoja que "
				<< "palabra quiere que se busque en el registro: ";
		}//if
		else
			cout << "\n Gracias por usar este buscador.\n";
	}//while

	/* COMPROBACION matrizConstate ................................................................
	double x = 2;
	int n = 6;

	tMatriz matrizN;

	matrizN = matrizConstante(x, n);					//matrizConstante CORRECTO

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)								
			cout << matrizN.arrayMatriz[i][j];
		cout << "\n";
	}*///.........................................................................................													

	/*	COMPROBACION operator* (vector).........................................................
	tVector v;
	v.tam = 3;
	v.datos[0] = 0;										//operator*  CORRECTO
	v.datos[1] = 1;
	v.datos[2] = 2;													

	cout << "Vector inicial:  " << v.datos[0] << " " << v.datos[1] << " " << v.datos[2]  << "\n\n";

	
	tMatriz m;
	m.dimensionMatriz = 3;
	m.arrayMatriz[0][0] = 1;
	m.arrayMatriz[0][1] = 0;
	m.arrayMatriz[0][2] = 0;
	m.arrayMatriz[1][0] = 2;
	m.arrayMatriz[1][1] = 1;
	m.arrayMatriz[1][2] = 0;
	m.arrayMatriz[2][0] = 3;
	m.arrayMatriz[2][1] = 2;
	m.arrayMatriz[2][2] = 0;

	tVector resultado;

	resultado = operator*(m, v);

	for (int i = 0; i < m.dimensionMatriz; ++i) {
		for (int j = 0; j < m.dimensionMatriz; ++j)
			cout << m.arrayMatriz[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";

	cout <<  "\nTamano: " << resultado.tam << "\nVector resultado:  " << resultado.datos[0] << "  " << resultado.datos[1] << "  " << resultado.datos[2] << "\n";
	
	*///............................................................................................
	
	/*  COMPROBACION operator+ ...................................................................

	tMatriz m1;
	m1.dimensionMatriz =2;
	m1.arrayMatriz[0][0] = 1;
	m1.arrayMatriz[0][1] = 0;
	m1.arrayMatriz[1][0] = 2;
	m1.arrayMatriz[1][1] = 1;

	tMatriz m2;
	m2.dimensionMatriz = 2;
	m2.arrayMatriz[0][0] = 3;
	m2.arrayMatriz[0][1] = 5;
	m2.arrayMatriz[1][0] = 1;
	m2.arrayMatriz[1][1] = 1;

	tMatriz mComprobado;
	mComprobado = operator+(m1, m2);

	for (int i = 0; i < mComprobado.dimensionMatriz; ++i) {
		for (int j = 0; j < mComprobado.dimensionMatriz; ++j)
			cout << mComprobado.arrayMatriz[i][j] << " ";
		cout << "\n";
	}
	*///.................................................................................................
	
	/*	COMPROBACION operator* (matriz) ......................................................................
	
	tMatriz m1;
	m1.dimensionMatriz = 2;
	m1.arrayMatriz[0][0] = 1;
	m1.arrayMatriz[0][1] = 0;
	m1.arrayMatriz[1][0] = 2;
	m1.arrayMatriz[1][1] = 1;

	double x = 2;
																	tMatriz operator* CORRECTO
	tMatriz mComprobado;
	mComprobado = operator*(x, m1);

	for (int i = 0; i < mComprobado.dimensionMatriz; ++i) {
		for (int j = 0; j < mComprobado.dimensionMatriz; ++j)
			cout << mComprobado.arrayMatriz[i][j] << " ";
		cout << "\n";
	}*///..................................................................................................
