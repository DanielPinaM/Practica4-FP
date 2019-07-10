#include "matrices.h"

void inicializaM(tMatriz &m) {

	m.dimensionMatriz = 1;
	for (int i = 0; i < MAX_TAM; ++i)
		for (int j = 0; j < MAX_TAM; ++j)
			m.arrayMatriz[i][j] = 0;
}//void inicializaM

tMatriz matrizConstante(double x, int n) {			//Crea una matriz n x  con los valores inicializados a x
	tMatriz matrizN;
	matrizN.dimensionMatriz = n;							//Actualizo la dimension de la matriz (n)
	for (int i = 0; i < matrizN.dimensionMatriz; ++i) {
		for (int j = 0; j < matrizN.dimensionMatriz; ++j)
			matrizN.arrayMatriz[i][j] = x;						//Todos los elementos de la matriz seran = x
	}//for
	return matrizN;
}	//matrizConstante

tVector operator*(const tMatriz & m, const tVector & v) {		//Multiplica una matriz por un vector
	tVector vSalida;
	vSalida.tam = v.tam;
	int i;
	double valorPos = 0;
	for (int j = 0; j < m.dimensionMatriz; ++j) {
		valorPos = 0;
		for (i = 0; i < m.dimensionMatriz; ++i) {
			valorPos += m.arrayMatriz[i][j] * v.datos[i];			//Multiplica la pos del array (columna i) * pos i del vector
		}//for
		vSalida.datos[j] = valorPos;
	}//for
	return vSalida;
}//tVector operator*

tMatriz operator+(const tMatriz & m1, const tMatriz & m2) {		//Suma dos matrices.
	tMatriz mSalida;
	mSalida.dimensionMatriz = m1.dimensionMatriz;

	for (int j = 0; j < m1.dimensionMatriz; ++j) {
		for (int i = 0; i < m1.dimensionMatriz; ++i) {
			mSalida.arrayMatriz[i][j] = m1.arrayMatriz[i][j] + m2.arrayMatriz[i][j];
		}//for
	}//for
	return mSalida;
}//tMatriz opertator+

tMatriz operator*(double x, const tMatriz & m) {	//Obtiene la matriz que se obtiene multiplicando cada elemento de m por x
	tMatriz mSalida;
	mSalida.dimensionMatriz = m.dimensionMatriz;

	for (int j = 0; j < m.dimensionMatriz; ++j) {
		for (int i = 0; i < m.dimensionMatriz; ++i) {
			mSalida.arrayMatriz[i][j] = m.arrayMatriz[i][j] * x;
		}//for
	}//for
	return mSalida;
}//tMatriz operator*

tMatriz desdeEnlacesAMatriz(const tMatriz & L) {		//Obtiene M, a partir de L.	Obteniendo primero M' y Cn tal que M = (1 - c)Cn + cM'
	cout << "La dimension de L es: " <<L.dimensionMatriz << "\n";
	for (int i = 0; i < L.dimensionMatriz; ++i) {
		for (int j = 0; j < L.dimensionMatriz; ++j)
			cout << L.arrayMatriz[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
	
	tMatriz Mprima;
	cout << "\n";
	tMatriz M;
	tMatriz Cn;
	int i, j, k;
	int Nj = 0, N = 0;

	for (i = 0; i < L.dimensionMatriz; ++i) {			//Consigo N, la cantidad de enlaces (1.0) en L
		for (j = 0; j < L.dimensionMatriz; ++j) {
			if (L.arrayMatriz[i][j] == 1.0)
				++N;
		}//for
	}//for

	for (j = 0; j < L.dimensionMatriz; ++j) {
		Nj = 0;
		for (k = 0; k < L.dimensionMatriz; ++k) {	//Consigo Nj, la cantidad de enlaces de Aj hacia otro archivo
			if (L.arrayMatriz[k][j] == 1.0)
				++Nj;
		}//for
		Mprima.dimensionMatriz = L.dimensionMatriz;
		for (i = 0; i < L.dimensionMatriz; ++i) {
			if (L.arrayMatriz[i][j] == 1.0)				//Si hay enlace de Aj  a  Ai
				Mprima.arrayMatriz[i][j] = 1 / Nj;
			else if (Nj == 0)							//Si Aj no esta enlazada con nada
				Mprima.arrayMatriz[i][j] = 1 / N;
			else										//cc
				Mprima.arrayMatriz[i][j] = 0;
		}//for
	}//for Mprima										//Aquí ya tengo M' (Mprima)
	Cn.dimensionMatriz = L.dimensionMatriz;
	Cn = matrizConstante(1 / N, Mprima.dimensionMatriz);	//Cn es matriz con todos sus valores 1/N

	Cn = 0.25 * Cn;								//(1 - 0.85)Cn

	Mprima = 0.85 * Mprima;						//cM'

	M = Cn + Mprima;							//M = (1 - c)Cn + cM'
	return M;
}//tMatriz desdeEnlacesAMatriz

tVector vectorUnos(const int &dimensionMatriz) {		//Para conseguir w, el vector de unos
	tVector vectorUnos;
	vectorUnos.tam = dimensionMatriz;

	for (int i = 0; i < dimensionMatriz; ++i)
		vectorUnos.datos[i] = 1.0;
	return vectorUnos;
}//tVector vectorUnos

bool proximos(const tVector &v1, const tVector &v2, double epsilon)		//Comprueba si dos valores estan "proximos"
{
	int i = 0;
	while (i < v1.tam && (1 - v1.datos[i] / v2.datos[i]) < epsilon)
		i++;
	return i == v1.tam;
} // proximos

tVector vectorX(tMatriz &M) {		//Para conseguir el vector X, a partir del cual haremos M * X = X en el main
	tVector X;
	X.tam = M.dimensionMatriz;
	tVector w = vectorUnos(M.dimensionMatriz);
	cout << "Vector w:\n";
	for (int i = 0; i < w.tam; ++i)
		cout << w.datos[i] << "  ";
	cout << "\n";
	w.tam = X.tam;
	tVector w1 = M * w;
	w1.tam = w.tam;
	while (!proximos(w1, w, 0.00001)){
		w = M * w;			//w igual al w1 ANTERIOR
		w1 = M * w;		//w1 sera nuestro w2 = w1 * 
	}//While
	return w1;
	}
