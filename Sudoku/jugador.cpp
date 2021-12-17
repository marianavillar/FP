//Mariana Villar Rojas

#include "jugador.h"
#include <iostream>
#include <string>
#include "checkML.h"

using namespace std;

string toString(tJugador jugador) {
	string cadena = "";

	cadena = to_string(jugador.puntuacion); // función de string que convierte los puntos(int) en cadenas de caracteres

	return jugador.id + " " + cadena;
}

void modificarJugador(tJugador & jugador, int puntos) {
	//incrementa puntos con nivel de sudoku
	jugador.puntuacion += puntos;
}

bool operator<(const tJugador & opIzq, const tJugador & opDer) {
	return opIzq.id < opDer.id;
}

bool menor(const tJugador & j1, const tJugador & j2) {
	//true si j1 tiene menos puntos que j2 o si tienen mismo puntos pero nombre de j1 es mayor que nombre de j2
	return (j1.puntuacion < j2.puntuacion) || (j1.puntuacion == j2.puntuacion && j2 < j1);
}