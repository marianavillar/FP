//Mariana Villar Rojas

#include <iostream>
#include <string>
#include "tablero.h"
#include "checkML.h"
using namespace std;

void iniciaTablero(tTablero &tablero) {

	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			iniciaCasilla(tablero[i][j]);
		}
	}
}

bool cargaTablero(const string &fichero, tTablero &tablero) {
	bool cargado = false;
	ifstream archivo;
	char aux;
	string a;

	archivo.open(fichero);

	if (archivo.is_open()) {
		cargado = true;
		getline(archivo, a);

		while (!archivo.eof()) {
			for (int i = 0; i < DIMENSION; i++) {
				for (int j = 0; j < DIMENSION; j++) {
					aux = a.at(j);
					rellenaCasilla(tablero[i][j], aux, true);
					if (tablero[i][j].estado == FIJA) {
						actualizarPosibles(tablero, i, j, tablero[i][j].numero, true);
					}

				}

				getline(archivo, a);
			}

		}
		archivo.close();
	}

	return cargado;
}

void dibujarTablero(const tTablero &tablero) {

	for (int i = 0; i < DIMENSION; i++) {
		dibujarSeparacion(i);
		for (int j = 0; j < DIMENSION; j++) {
			//para que separe por submatriz con doble linea
			if (j == 0) {
				cout << "|| ";
			}
			dibujaCasilla(tablero[i][j]);

			if ((j + 1) % 3 == 0) {
				cout << " || ";
			}
			else {
				cout << " | ";
			}

		}
		cout << endl;

	}
	colorFondo(PALETA[0]);
	dibujarSeparacion(0);
}

// las lineas dobles son para separarlo en submatrices 3x3.
void dibujarSeparacion(int n) {
	for (int i = 0; i < DIMENSION * 4 + 5; i++) {
		if (n % 3 == 0) {
			cout << "=";
		}
		else {
			cout << "-";
		}

	}
	cout << endl;
}

bool ponerNum(tTablero &t, int fila, int columna, int c) {
	bool posible = false;

	if (t[fila][columna].estado == VACIO && pertenece(t[fila][columna].posibles, c)) {
		rellenaCasilla(t[fila][columna], intTochar(c), false);
		posible = true;
		actualizarPosibles(t, fila, columna, c, true);
	}

	return posible;
}

bool borraNum(tTablero &t, int fila, int columna) {
	bool posible = false;

	if (t[fila][columna].estado == RELLENO) {
		posible = true;

		actualizarPosibles(t, fila, columna, t[fila][columna].numero, false);
		rellenaCasilla(t[fila][columna], ' ', posible);

		for (int i = 0; i < DIMENSION; i++) {
			for (int j = 0; j < DIMENSION; j++) {
				if (t[i][j].estado != VACIO)
					actualizarPosibles(t, i, j, t[i][j].numero, true);
			}
		}
	}

	return posible;
}

void actualizarPosibles(tTablero &t, int fila, int columna, int c, bool borrarPosible) {
	int i = 0, j = 0, f = 0, col = 0;

	//borra c de posibles de elementos de la misma columna
	while (i < DIMENSION) {

		if (borrarPosible) {
			delElemento(t[i][columna].posibles, c);
		}
		else {
			addElemento(t[i][columna].posibles, c);
		}

		i++;
	}

	//borra c de posibles de elementos de la misma fila
	while (j < DIMENSION) {

		if (borrarPosible) {
			delElemento(t[fila][j].posibles, c);
		}
		else {
			addElemento(t[fila][j].posibles, c);
		}

		j++;
	}

	//borra c de posibles de elementos de la misma submatriz de 3x3
	f = fila / 3 * 3;
	col = columna / 3 * 3;

	for (int x = f; x < f + 3; x++) {
		for (int y = col; y < col + 3; y++) {

			if (borrarPosible && pertenece(t[x][y].posibles, c)) {
				delElemento(t[x][y].posibles, c);
			}
			else if (!borrarPosible && !pertenece(t[x][y].posibles, c)) {
				addElemento(t[x][y].posibles, c);
			}
		}
	}
}

bool tableroLleno(const tTablero &t) {
	bool lleno = true;

	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			if (t[i][j].estado == VACIO && t[i][j].numero == 0) {
				lleno = false;
			}
		}
	}
	return lleno;
}


void mostrarPosibles(const tTablero &t, int fila, int columna) {

	mostrar(t[fila][columna].posibles);
}


void rellenarSimples(tTablero &t) {
	int num = 0;

	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			if (esSimple(t[i][j], num)) {
				ponerNum(t, i, j, num);
			}
		}
	}
}