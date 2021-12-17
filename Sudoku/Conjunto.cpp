//Mariana Villar Rojas

#include <iostream>
#include <string>
#include "Conjunto.h"
#include "checkML.h"
using namespace std;


void cjto_vacio(tConjunto & c) {

	c.nElems = 0;

	for (int i = 0; i < DIMENSION; i++) {
		c.elementos[i] = false;
	}
}

void cjto_lleno(tConjunto & c) {
	cjto_vacio(c);

	for (int i = 0; i < DIMENSION; i++) {
		c.elementos[i] = true;
		c.nElems++;
	}
}

//indica si e está en el conjunto
bool pertenece(const tConjunto &c, int e) {
	bool esta = false;

	if (c.elementos[e - 1]) {
		esta = true;
	}

	return esta;
}

void addElemento(tConjunto & c, int e) {

	if (!pertenece(c, e)) {
		c.elementos[e - 1] = true;
		c.nElems++;
	}

}

void delElemento(tConjunto & c, int e) {

	if (pertenece(c, e)) {
		c.elementos[e - 1] = false;
		c.nElems--;
	}

}

int numElems(const tConjunto & c) {
	return c.nElems;
}

// indica si un conjunto tiene un unico valor y lo devuelve
bool esUnitario(const tConjunto & c, int &e) {
	bool encontrado = false;
	int i = 0;

	if (numElems(c) == 1) {
		while (i < DIMENSION && !encontrado) {

			if (c.elementos[i]) {
				encontrado = true;
				e = i + 1;
			}

			i++;
		}
	}

	return encontrado;
}

// muestra los valores a true, es decir, los posibles
void mostrar(const tConjunto &c) {

	cout << " El conjunto tiene " << c.nElems << " elementos." << endl;
	cout << "Los números posibles son ";
	for (int i = 0; i < DIMENSION; i++) {
		if (c.elementos[i]) {
			cout << "" << i + 1 << ". ";
		}
	}

	cout << "" << endl;
}