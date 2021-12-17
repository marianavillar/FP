//Mariana Villar Rojas

#ifndef _casilla
#define _casilla
#include "Conjunto.h"
// Estado de cada casilla
typedef enum { VACIO, FIJA, RELLENO } tEstadoCasilla;

// Casilla en tablero
typedef struct {
	int numero; // si el estado es fija o rellenada
	tEstadoCasilla estado;
	tConjunto posibles; //valores posibles de una casilla, si es vacia
}tCasilla;

const int PALETA[5] = { 0,1,4,15 };

//Inicialmente casilla vacia con todos los valores posibles
void iniciaCasilla(tCasilla & casilla);

//Rellena con el caracter c la casilla 
//Si fija es true el estado se pone a FIJA: cuando se carga el tablero se llama con true, el resto de los casos a false
//El valor por defecto de fija es false

void rellenaCasilla(tCasilla & casilla, char c, bool fija = false); //fija es true cuando se lee de fichero
int chartoInt(const char c);
char intTochar(const int c);

// Dibuja una casilla
void dibujaCasilla(const tCasilla &casilla);

// Determina si una casilla aun no rellena tiene un unico valor posible
//Devuelve falso para las casillas fijas o ya rellenas
bool esSimple(const tCasilla & casilla, int & numero);

// Establece el color de fondo de una casilla
void colorFondo(int color);
#endif

