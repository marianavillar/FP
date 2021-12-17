//Mariana Villar Rojas

#ifndef _tablero
#define _tablero
#include <string>
#include <fstream>
#include <iostream>
#include "casilla.h"

using namespace std;

// Tablero Sudoku
typedef tCasilla tTablero[DIMENSION][DIMENSION];

void iniciaTablero(tTablero &tablero); //Inicia todas las casillas del tablero
bool cargaTablero(const string &fichero, tTablero &tablero); //Carga un tablero de fichero

 // Dibuja el tablero en pantalla
void dibujarTablero(const tTablero &tablero);
void dibujarSeparacion(int n);

//Coloca c en x, y
//c, x e y estan 1 y 9
//El resultado booleano indica si se ha podido: para ello la casilla ha de estar vacia y c ser uno de los valores posibles
//Una vez colocado se quita ese valor de fila, columna y submatriz con quitarPosibles
bool ponerNum(tTablero &t, int fila, int columna, int c);

//Borra la casilla x,y siempre que no sea fija y en ella haya un valor, en caso contrario devuelve false
//La vaciamos y procedemos a restablecer los valores posibles que se pueda en fila, columna y submatriz
bool borraNum(tTablero &t, int fila, int columna);

void actualizarPosibles(tTablero &t, int fila, int columna, int c, bool borrarPosible);

//Determina si el tablero ha sido rellenado completamente
//Si el sudoku tiene una unica solucion, como solamente permitimos valores validos no seria posible que estuviese lleno y no fuese correcto
//Si pudiese tener varias soluciones entonces puede terner sentido tener esta funcion
//O si permitiesemos poner valores erroneos
bool tableroLleno(const tTablero &t);

//Muestra los posibles valores de una casilla valida cualquiera
//Si es fija solo figurara su propio valor, ya que no se puede cambiar
void mostrarPosibles(const tTablero &t, int fila, int columna);

//Recorre la matriz mirando que casillas vacias tienen un unico valor posible y lo rellena
//De nuevo quita valores posibles de la fila, columna y submatriz
void rellenarSimples(tTablero &t);

#endif