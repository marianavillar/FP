//Mariana Villar Rojas

#ifndef _juego
#define _juego
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <locale.h>
#include <iomanip>     
#include <cmath>
#include <conio.h>
#include "tablero.h"
using namespace std;

// Tipos de Sudokus
typedef enum { FACIL, MEDIO, DIFICIL } tNivelSudoku;

// tipo Sudoku
typedef struct {
	string fichero;
	int nivel;
} tSudoku;

// Juego
typedef struct {
	tSudoku sudoku;
	tTablero tablero;
	bool terminado;
}tJuego;

// Mostrar menú de acciones para jugar un sudoku
int mostrarMenuJugada();
// Bucle del juego de un sudoku
int JugarUnSudoku(const tSudoku &sudoku);

// Inicializa el juego
void iniciaJuego(tJuego & juego, const tSudoku &sudoku);

//muestra el juego
void mostrarJuego(const tJuego &juego);
void pausa();

//carga del juego
bool cargaJuego(tJuego & juego, const tSudoku &sudoku);

//pide al usuario una fila y una columna ambas en [1,9]
void pedirCoordenadas(int &fila, int &col);
#endif