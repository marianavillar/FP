//Mariana Villar Rojas

#include "listaSudokus.h"
#include <iostream>
#include <string>
#include <fstream>
#include "checkML.h"
using namespace std;


void crearListaVacia(tListaSudokus & lista){
	lista.cont = 0;
}

void mostrarListaSudokus(const tListaSudokus &lista, int pos){

	if (pos < lista.cont) {
		cout << pos + 1 << "- " << lista.array[pos].fichero << " de nivel "
			<< lista.array[pos].nivel << endl;

		mostrarListaSudokus(lista, pos + 1);
	}
}

bool cargarListaSudokus(tListaSudokus &lista){
	bool cargado = false;
	ifstream archivo;
	
	archivo.open("listaSudokus.txt");

	if (archivo.is_open()){
		//guarda en la lista el contenido del fichero
		while (!archivo.eof() && lista.cont < MAX_SUDOKUS) {
			archivo >> lista.array[lista.cont].fichero;
			archivo >> lista.array[lista.cont].nivel;
			lista.cont++;
		}
		cargado = true;
		archivo.close();
	}
	
	return cargado;
}

int  menuListaSudokus(const tListaSudokus & lista){
	int op;
	do {
		cout << "Elige un sudoku:" << endl;
		mostrarListaSudokus(lista, 0);
		cin >> op;

		//pedirá opción siempre que el jugador ponga una mayor que el número de sudokus de la lista
	} while (op < 1 || op > lista.cont);

	return op;
}

bool guardar(const tListaSudokus & lista) {
	bool guardado = false;
	ofstream archivo;

	archivo.open("listaSudokus.txt");
	if (archivo.is_open()) {
		// guardamos el contenido de la lista en el fichero
		for (int i = 0; i < lista.cont; i++) {
			archivo << lista.array[i].fichero << " " << lista.array[i].nivel;
			if (i != lista.cont - 1) {
				archivo << endl;
			}
		}
		guardado = true;

		archivo.close();
	}

	return guardado;
}

int menuSud() {
	int op;
	do {
		cout << "Elige 1. Introducir sudoku o 2. Borrar sudoku" << endl;
		cin >> op;

	} while (op < 1 || op > 2);
	return op;
}

bool borrarSudoku(tListaSudokus & lista) {
	bool borrado = false;
	tSudoku aux;
	int pos = 0;

	cout << "Dime el nombre del fichero" << endl;
	cin >> aux.fichero;

	if (lista.cont > 0) {
		if (buscarFichero(lista, aux.fichero, pos)) {
			//movemos desde pos una a la izquierda 
			for (int i = pos; i < lista.cont - 1; i++) {
				lista.array[i] = lista.array[i + 1];
			}
			
			lista.cont--;
			borrado = true;
		}
		else {
			cout << "Ese fichero no estaba en la lista" << endl;
		}
	}

	return borrado;
}

bool registrarSudoku(tListaSudokus & lista) {
	bool registrado = false;
	tSudoku aux;
	int pos;

	cout << "Dime el nombre del fichero y puntos que permite conseguir" << endl;
	cin >> aux.fichero >> aux.nivel;

	if (lista.cont < MAX_SUDOKUS) {
		if (!buscarFichero(lista, aux.fichero, pos)) {
			pos = buscarPos(lista, aux);
			//movemos desde pos una a la derecha
			for (int i = lista.cont; i > pos; i--) {
				lista.array[i] = lista.array[i - 1];
			}
			//insertamos el nuevo
			lista.array[pos] = aux;
			lista.cont++;
			registrado = true;
		}
		else {
			cout << "Ese fichero ya está en la lista" << endl;
		}
	}

	return registrado;
}

bool buscarFichero(const tListaSudokus & lista, string nombreFich, int &pos) {
	bool encontrado = false;
	int i = 0;

	//buscamos si ese nombre está hasta encontrarlo o recorrer toda la lista
	while (!encontrado && i < lista.cont) {
		if (lista.array[i].fichero == nombreFich) {
			encontrado = true;
			pos = i;
		}
		i++;
	}

	return encontrado;
}

int buscarPos(const tListaSudokus & lista, const tSudoku & sudoku) {
	int pos, ini = 0, fin = lista.cont - 1, mitad;
			
	mitad = (ini + fin) / 2;

	//con esto hacemos el intervalo de busqueda más pequeño
	if (sudoku.nivel < lista.array[mitad].nivel) {
	fin = mitad - 1;
	}
	else if (sudoku.nivel > lista.array[mitad].nivel) {
	ini = mitad + 1;
	}
	pos = ini;

	/*devuelve la posición donde debería ir el sudoku dado
	  buscando desde ini a fin la pos del mayor(nivel) al dado
	  y a mismo nivel el mayor en nombre*/
	while (pos <= fin && (lista.array[pos].nivel < sudoku.nivel || (lista.array[pos].nivel == sudoku.nivel && lista.array[pos].fichero < sudoku.fichero))) {
		pos++;
	}
			
	return pos;
}

bool operator<(const tSudoku & opIzq, const tSudoku & opDer) {
	return opIzq.fichero < opDer.fichero;
}