//Mariana Villar Rojas

#ifndef _listaSudokus
#define _listaSudokus
#include <algorithm>
#include <string>
#include "juego.h"

using namespace std;

// Número máximo de Sudokus registrados
const int MAX_SUDOKUS = 20;

// Array de Sudokus
typedef tSudoku tSudokus[MAX_SUDOKUS];

// Lista de Sudokus
typedef struct {
	tSudokus array;	// Array de sudokus
	int cont;	
} tListaSudokus;

void crearListaVacia(tListaSudokus & lista);
bool cargarListaSudokus(tListaSudokus & lista); // guarda en la lista el contenido del archivo
void mostrarListaSudokus(const tListaSudokus &lista, int pos);
int  menuListaSudokus(const tListaSudokus & lista); // para elegir el sudoku a resolver

// Métodos de la versión 2
bool guardar(const tListaSudokus & lista);  //guarda la lista en el archivo 
bool registrarSudoku(tListaSudokus & lista);
bool buscarFichero(const tListaSudokus & lista, string nombreFich, int &pos);
int buscarPos(const tListaSudokus & lista, const tSudoku & sudoku);
bool operator<(const tSudoku & opIzq, const tSudoku & opDer);
int menuSud();
bool borrarSudoku(tListaSudokus & lista);
#endif