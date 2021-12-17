//Mariana Villar Rojas

#include <iostream>
#include <string>
#include "casilla.h"
#include "checkML.h"
#include <Windows.h>
using namespace std;

//inicializa la casilla a vacía
void iniciaCasilla(tCasilla & casilla) {

	casilla.estado = VACIO;
	casilla.numero = 0;
	cjto_lleno(casilla.posibles);

}

// convierte un char c en un int 
int chartoInt(const char c) {
	int num = 0;

	switch (c) {
	case ' ': num = 0;
		break;
	case '1': num = 1;
		break;
	case '2': num = 2;
		break;
	case '3': num = 3;
		break;
	case '4': num = 4;
		break;
	case '5': num = 5;
		break;
	case '6': num = 6;
		break;
	case '7': num = 7;
		break;
	case '8': num = 8;
		break;
	case '9': num = 9;
		break;
	default:;
	}

	return num;
}

// convierte un int c en un char
char intTochar(const int c) {
	char a = ' ';

	switch (c) {
	case 0: a = ' ';
		break;
	case 1: a = '1';
		break;
	case 2: a = '2';
		break;
	case 3: a = '3';
		break;
	case 4: a = '4';
		break;
	case 5: a = '5';
		break;
	case 6: a = '6';
		break;
	case 7: a = '7';
		break;
	case 8: a = '8';
		break;
	case 9: a = '9';
		break;
	default:;
	}

	return a;
}

/*fija = true casilla fija. fija = false casilla rellenada. c= espacio casilla vacia.
numero de la casilla es el entero del char c */
void rellenaCasilla(tCasilla & casilla, char c, bool fija) {

	casilla.numero = chartoInt(c);

	if (c == ' ') {
		casilla.estado = VACIO;
	}
	else {

		if (fija) {
			casilla.estado = FIJA;
		}
		else {
			casilla.estado = RELLENO;
		}
	}
}

// Dibuja una casilla
void dibujaCasilla(const tCasilla &casilla) {

	switch (casilla.estado) {
	case VACIO: colorFondo(PALETA[0]);
		cout << intTochar(casilla.numero);
		colorFondo(PALETA[0]);

		break;
	case FIJA: colorFondo(PALETA[1]);
		cout << intTochar(casilla.numero);
		colorFondo(PALETA[0]);

		break;
	case RELLENO: colorFondo(PALETA[2]);
		cout << intTochar(casilla.numero);
		colorFondo(PALETA[0]);

		break;
	default: colorFondo(PALETA[3]);
	}
}

//devuelve si la casilla tiene un unico valor posible y dicho valor
bool esSimple(const tCasilla & casilla, int & numero) {

	return (esUnitario(casilla.posibles, numero) && casilla.estado == VACIO);
}

void colorFondo(int color) {

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}