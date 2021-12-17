//Mariana Villar Rojas

#ifndef _ListaJugadores
#define _ListaJugadores
#include <algorithm>
#include <string>
#include "jugador.h"

using namespace std;

// N�mero m�ximo de jugadores registrados
const int MAX_JUGADORES = 5;

// Lista de jugadores
typedef struct {
	tJugadorPtr *array;	// Array din�mico de jugadores
	int cont;
	int dimensionActual;
} tListaJugadores;

void creaListaVacia(tListaJugadores & lista);
bool cargar(tListaJugadores & lista);
void mostrar(const tListaJugadores & lista, int pos);
bool guardar(const tListaJugadores & lista);
void puntuarJugador(tListaJugadores & lista, int puntos);

tListaJugadores ordenarPorRanking(const tListaJugadores & lista); // devulve una copia ordenada de mayor a menor por puntos (a igual puntos de menor a mayor por nombre)
void ordenarBurbuja(tListaJugadores & lista); //opcional que ordena mediante el m�todo de la burbuja
void ordenarInserci�n(tListaJugadores & lista);//opcional que ordena mediante el m�todo de inserci�n

//Versi�n 3
void ampliar(tListaJugadores & lista);
void borrarListaJugadores(tListaJugadores & lista);
bool buscar(const tListaJugadores & lista, string id, int ini, int fin, int & pos);
#endif
