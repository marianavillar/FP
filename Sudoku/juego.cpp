//Mariana Villar Rojas

#include <iostream>
#include <string>
#include "juego.h"
#include "checkML.h"
using namespace std;

void iniciaJuego(tJuego &juego, const tSudoku &sudoku) {
	juego.sudoku = sudoku;
	juego.terminado = false;
	iniciaTablero(juego.tablero);
}

int mostrarMenuJugada() {
	int eleccion;

	do {
		cout << "1. - Ver posibles valores de una casilla vacía" << endl;
		cout << "2. - Colocar valor en una casilla" << endl;
		cout << "3. - Borrar valor de una casilla" << endl;
		cout << "4. - Reiniciar el tablero" << endl;
		cout << "5. - Autocompletar celdas simples" << endl;
		cout << "0. - Abortar la resolución y volver al menú principal" << endl;
		cin >> eleccion;

	} while ((eleccion < 0) || (eleccion > 5));

	return eleccion;
}

int JugarUnSudoku(const tSudoku &sudoku) {
	tJuego juego;
	int op, f, c, num = 0, nivel = 0;

	iniciaJuego(juego, sudoku);

	if (cargaJuego(juego, sudoku)) {
		do {
			mostrarJuego(juego);

			if (tableroLleno(juego.tablero)) {
				juego.terminado = true;
				nivel = juego.sudoku.nivel;
			}

			op = mostrarMenuJugada();

			switch (op) {
			case 0:
				cout << "Abortar juego. Vuelta al menú principal" << endl << endl;
				break;
			case 1:
				pedirCoordenadas(f, c);
				mostrarPosibles(juego.tablero, f - 1, c - 1);
				
				break;
			case 2:
				cout << " ¿Qué número desea colocar?" << endl;
				cin >> num;
				pedirCoordenadas(f, c);

				//mensajes dependiendo del estado de la casilla cuando no se ha podido poner número
				if (!ponerNum(juego.tablero, f - 1, c - 1, num)) {
					switch (juego.tablero[f - 1][c - 1].estado) {
					case VACIO: cout << "Número no válido para esa casilla." << endl;
						break;
					case RELLENO: cout << "Esta casilla esta rellenada, borra primero." << endl;
						break;
					case FIJA: cout << "Esta casilla es fija." << endl;
						break;
					default:;
					}
					
				}

				break;
			case 3:
				pedirCoordenadas(f, c);

				if (!borraNum(juego.tablero, f - 1, c - 1)) {
					switch (juego.tablero[f - 1][c - 1].estado) {
					case FIJA: cout << "No se ha podido borrar el número de esa casilla porque es fija." << endl;
						break;
					case VACIO: cout << "Esa casilla no tiene número." << endl;
						break;
					default:;
					}
				
				}

				break;
			case 4:
				iniciaJuego(juego, sudoku);
				if (!cargaJuego(juego, sudoku)) {
					cout << "Error inesperado al cargar el tablero" << endl;
				}
				break;
			case 5:
				rellenarSimples(juego.tablero);
				break;
			default:;

			}
			pausa();

		} while (op != 0 && !juego.terminado);
	}
	else {
		cout << "No se ha podido cargar el archivo" << endl;
	}
	return nivel;
}

void mostrarJuego(const tJuego &juego) {
	cout << "Sudoku " << juego.sudoku.fichero << endl;
	cout << "Puntuación del sudoku " << juego.sudoku.nivel << endl;

	dibujarTablero(juego.tablero);

}

void pausa() {

	cout << "Pulsa enter para continuar" << endl;

	if (cin.get()) {
		cin.sync();
		cin.clear();
		cin.get();
	}
	system("cls");
}

bool cargaJuego(tJuego & juego, const tSudoku &sudoku) {

	return cargaTablero(sudoku.fichero, juego.tablero);
}

void pedirCoordenadas(int &fila, int &col) {
	cout << " Dime fila[1,9] y columna[1,9]" << endl;
	cin >> fila >> col;
}

