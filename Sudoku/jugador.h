//Mariana Villar Rojas

#ifndef _jugador
#define _jugador
#include <algorithm>
#include <string>
//#include "juego.h"

using namespace std;

//info de cada jugador
typedef struct {
	string id;	// nombre del jugador
	int puntuacion;
} tJugador;

typedef tJugador * tJugadorPtr; //puntero que apunta a datos de tipo tJugador

string toString(tJugador jugador); //fusiona en un string el nombre y los puntos del jugador
void modificarJugador(tJugador & jugador, int puntos); //añade puntos a los puntos del jugador
bool operator<(const tJugador & opIzq, const tJugador & opDer);
bool menor(const tJugador & j1, const tJugador & j2);

#endif
