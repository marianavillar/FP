//Mariana Villar Rojas

#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <fstream>
#include <time.h>
#include <locale.h>
#include "listaSudokus.h"
#include "listaJugadores.h"
#include "checkML.h"
using namespace std;

int menuPrincipal();

int menuPrincipal() {
	int op;

	do {
		cout << "1. - Jugar" << endl;
		cout << "2. - Ver jugadores ordenados por identificador" << endl;
		cout << "3. - Ver jugadores ordenados por puntos" << endl;
		cout << "4. - Incorporar/Borrar sudoku" << endl;
		cout << "0. - Salir" << endl;
		cin >> op;
	} while (op < 0 || op > 4);

	return op;
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	system("chcp 1252");
	tListaSudokus l;
	tListaJugadores jug, copia;
	int opcion, resul, pos = 0;
	bool operacion;

	crearListaVacia(l);

	if (cargarListaSudokus(l) && cargar(jug)) {

		do {
			opcion = menuPrincipal();
			

			switch (opcion) {
			case 0: 
				borrarListaJugadores(jug);
				
				cout << "Adios" << endl;
				
				break;
			case 1:
				
				resul = JugarUnSudoku(l.array[menuListaSudokus(l) - 1]);
				puntuarJugador(jug, resul);
				guardar(jug);
				if (resul != 0) {
					cout << "Tablero terminado. Has ganado " << resul << " puntos." << endl;
				}
				else {
					cout << "No has ganado. Tu puntuación es " << resul << endl;
				}

				break;
			case 2:
				mostrar(jug, pos);
				break;
			case 3:
				copia = ordenarPorRanking(jug);
				mostrar(copia, pos);
				delete[] copia.array;
				break;
			case 4:
				switch (menuSud()) {
				case 1:
					operacion = registrarSudoku(l);
					if (!operacion) {
						cout << "No se puede guardar el sudoku" << endl;
					}
					
					break;
				case 2: 
					operacion = borrarSudoku(l);
					if (!operacion) {
						cout << "No se ha podido borrar el sudoku" << endl;
					}
				
					break;
				default:;
				}
				if (operacion) {
					if (guardar(l)) {
						cout << "Se ha actualizado el fichero de sudokus" << endl;
					}
					else {
						cout << "No se ha actualizado el fichero de sudokus" << endl;
					}
				}
				break;
			default:;
			}
			pausa();
		} while (opcion != 0);

	}
	

	system("pausa");
	return 0;
}