#include "indices.h"

void completarArchivoActual(tIndicePalabras &tabla, const string &nombreArchivoActual, tListaCadenas &enlaces, tListaCadenas &totales, tMatriz &L, const int posI)
	/*Dado un archivo no visitado, se guarda en la tabla los valores de ese archivo.
	  Si encontramos un enlace, lo guardamos en 'enlaces', en 'totales' y modificamos 'L'.
	  'j' está para comprobar si un nuevo enlace se encontraba en una posición concreta de 'totales',
	  para modificar correctamente la matriz 'L'*/
{
	ifstream archivoActual;
	string lectura;
	archivoActual.open(nombreArchivoActual);			//Abrimos el archivo para leerlo
	if (archivoActual.is_open())						//Si el archivo existe
	{
		while (!archivoActual.eof())		//Mientras el archivo no esté terminado, seguimos leyendo
		{
			archivoActual >> lectura;		//Lee la siguiente palabra
			//Si el último carácter es un símbolo de puntuación, lo eliminamos para guardar la palabra
			if (ispunct(lectura.at(lectura.length() - 1)))
			{
				int tamFinal = lectura.length() - 1;//Como eliminamos un caracter, cambiaremos el tam de 'lectura'
				
				//Creamos un array char auxiliar y un string auxiliar para 
				//comprobar si el símbolo de puntuación es un '>'
				char arrayAux[1];
				arrayAux[0] = lectura.at(lectura.length() - 1);
				string comprobar(arrayAux, 1);
				if (comprobar != ">")
				{
					lectura.erase(lectura.length() - 1);	//Eliminamos el último carácter de 'lectura'
					lectura.resize(tamFinal);				//Reajustamos el tamaño de 'lectura'
				}//if
			}//if

			transform(lectura.begin(), lectura.end(), lectura.begin(), tolower);//Ponemos todo en minúsculas
			
			//Comprobamos que el primer carácter de la lectura es '<'
			//y el último es '>' con variables auxiliares
			char arrayAuxIni[1], arrayAuxFin[1];
			arrayAuxIni[0] = lectura.at(0);
			arrayAuxFin[0] = lectura.at(lectura.length() - 1);
			string comprobarIni(arrayAuxIni, 1), comprobarFin(arrayAuxFin, 1);
			if (comprobarIni == "<" && comprobarFin == ">")			//Si es un enlace
			{
				char listaAux[200];						//Lista auxiliar para borrar el '<' y el '>'
				unsigned int i;
				int tamFinal = lectura.length() - 2;				//Reajustar el tam de 'lectura'
				for (i = 0; i < lectura.length(); ++i)				//Copiamos 'lectura' en 'listaAux'
					listaAux[i] = lectura.at(i);
				i = 0;
				for (unsigned int j = 1; j < lectura.length() - 1; j++)		//Modificamos 'lectura'
				{
					lectura.at(i) = listaAux[j];
					++i;
				}//for
				lectura.resize(tamFinal);	//Como hemos quitado 2 caracteres, modificamos el tamaño

				//Comprobamos si el archivo debe añadirse a 'totales' y a 'enlaces'

				if (totales.cadenas[posI] == lectura)	//Si el archivo nuevo se encontraba en 'posI' de 'totales'
				{
					L.arrayMatriz[posI][L.dimensionMatriz - 1] = 1.0;	//L(i,j) = 1.0
				}//if
				else
				{
					insertar(totales, lectura);			//Todos los enlaces deben estar en 'totales'
					insertar(enlaces, lectura);			//Declaramos en el programa que hay un nuevo enlace
					
					int j = L.dimensionMatriz - 1;
					++L.dimensionMatriz;				//Incrementamos el tamaño de la matriz
					L.arrayMatriz[L.dimensionMatriz - 1][j] = 1.0;		//L(t-1,j) = 1.0
				}//else
			}//if

			else	//La palabra leída no es un enlace, es una palabra que hay que guardar en el registro
			{
				insertar(tabla, lectura, nombreArchivoActual);
			}//else
		}//while
	archivoActual.close();							//Cerramos el archivo actual
	}//if
	else					//El archivo  no existe
	{
		cout << "No se ha podido abrir el archivo pedido.\n";
	}//else
}//void completarArchivoActual

void inicializa(tIndicePalabras &tabla)			//Inicializa la tabla
{
	tabla.tamVariable = 0;
	for (int i = 0; i < MAX_TAM; ++i)
	{
		inicializa(tabla.claves[i].valor);
	}//for
}//void inicializa

//COMPROBAR
void crearTabla(tIndicePalabras &tabla, const string &archivoInicial, tListaCadenas &totales, tMatriz &L)
//Rellenamos la tabla a partir de archivoInicial
{
	tListaCadenas visitados;		//'visitados' es la lista de enlaces ya visitados
	tListaCadenas noVisitados;		//'noVisitados' es la lista de enlaces pendientes por revisar
	string nombreArchivoActual;		//'nombreArchivoActual' nos indica el archivo que vamos a abrir
	inicializa(noVisitados);
	inicializa(visitados);
	insertar(noVisitados, archivoInicial);
	insertar(totales, archivoInicial);
	inicializa(tabla);
	inicializa(totales);
	inicializaM(L);

	cout << "\n \n CREANDO LA TABLA CON EL ARCHIVO INICIAL ... ";

	//Lo que haremos a continuación es leer el archivo inicial aplicando lo siguiente:
		//1.- Guardaremos en el registro las palabras del archivo de texto.
		//2.- Si nos encontramos un enlace:
					//Si no está en totales añadirlo a totales y no-visitados,
					//ampliar el tamaño de L en 1 (de forma que las nuevas entradas sean nulas) y poner l(t−1,j) a 1.0 siendo t el nuevo tamaño.

					//Si está en totales en la posición i poner l(i,j) a 1.0
	
	int aux = 0;		//Para llamar a la función 'completarArchivoActual'
	completarArchivoActual(tabla, archivoInicial, noVisitados,totales, L, aux);		//Leemos el archivo raíz
	insertar(visitados, archivoInicial);			//Indicamos que ya hemos visitado el archivo raíz

	for (int i = 0; i < noVisitados.tamVariable; ++i)	//Comprobamos que todos los enlaces se han revisado
	{
		if (!buscar(visitados, noVisitados.cadenas[i]))		//Si el enlace no se ha revisado, se revisa.
		{
			insertar(visitados, noVisitados.cadenas[i]);		//a)

			//Abrimos archivo en pos 'i'
			nombreArchivoActual = noVisitados.cadenas[i];
			completarArchivoActual(tabla, nombreArchivoActual, noVisitados, totales, L, i);
			
			//En este comentario estaría modificar 'L' fuera de 'completarArchivoActual'
			/*
			if ((totales.cadenas[i] == noVisitados.cadenas[i])) //Si está en 'totales' en la pos 'i', poner el valor 1.0
			{
				L.arrayMatriz[i][L.dimensionMatriz - 1] = 1.0;
			}//if
			else
			{
				++L.dimensionMatriz;
				L.arrayMatriz[L.dimensionMatriz - 1][j] = 1.0;
			}//else
			*/
		}//if
	}//for

	cout << "(TERMINADA)\n";

}//void crearTabla