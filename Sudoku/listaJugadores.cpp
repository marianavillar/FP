//Mariana Villar Rojas

#include "ListaJugadores.h"
#include <iostream>
#include <string>
#include <fstream>
#include "checkML.h"

using namespace std;

void creaListaVacia(tListaJugadores & lista) {
	lista.cont = 0;
	lista.dimensionActual = MAX_JUGADORES;
	lista.array = new tJugadorPtr[MAX_JUGADORES];
}

bool cargar(tListaJugadores & lista) {
	bool cargado = false;
	ifstream archivo;
	
	creaListaVacia(lista);

	archivo.open("listaJugadores.txt");

	if (archivo.is_open()) {
		// extraemos del fichero (que está ordenado alfabéticamente) y lo guardamos en la lista
		while (!archivo.eof()) {
			lista.array[lista.cont] = new tJugador;

			archivo >> lista.array[lista.cont]->id;
			archivo >> lista.array[lista.cont]->puntuacion;
			lista.cont++;

			if (lista.dimensionActual == lista.cont) {
				ampliar(lista);
			}
		}
		cargado = true;
		archivo.close();
	}
	return cargado;
}

void mostrar(const tListaJugadores & lista, int pos) {

	if (pos == 0) cout << "Esta es la lista de jugadores." << endl << endl;

	if (pos < lista.cont) {
		cout << toString(*lista.array[pos]) << endl;
		mostrar(lista, pos + 1);
	}
}

bool guardar(const tListaJugadores & lista){
	bool guardado = false;
	ofstream archivo;

	archivo.open("listaJugadores.txt");
	if (archivo.is_open()) {
		// guardamos el contenido de la lista en el fichero
		for (int i = 0; i < lista.cont; i++) {
			archivo << toString(*lista.array[i]);
			if (i != lista.cont - 1) {
				archivo << endl;
			}
		}
		guardado = true;

		archivo.close();
	}

	return guardado;
}

void puntuarJugador(tListaJugadores & lista, int puntos){
	string auxId;
	int  pos;

	cout << "Introduzca tu identificador de jugador por teclado" << endl;
	cin >> auxId;

		if (buscar(lista, auxId, 0, lista.cont - 1, pos)) {
			modificarJugador(*lista.array[pos], puntos);
		}
		else {

				if (lista.dimensionActual == lista.cont) {

					ampliar(lista);
				}
				
				//movemos todo desde pos para insertar el nuevo
				for (int i = lista.cont; i > pos; i--) {
					lista.array[i] = lista.array[i - 1];
				}

				lista.array[pos] = new tJugador;
				lista.array[pos]->id = auxId;
				lista.array[pos]->puntuacion = puntos;
				lista.cont++;
		}
}

/*busqueda binaria recursiva que te va haciendo cada vez más pequño el rango de busqueda
  devuelve la posicion donde está (si está) o en la que debeía estar (si no está)*/

bool buscar(const tListaJugadores & lista, string id, int ini, int fin, int & pos) {
	bool encontrado = false;

	if (ini <= fin) { 

		int mitad = (ini + fin) / 2;

		if (id == lista.array[mitad]->id) {
			pos = mitad;
			encontrado = true;
		}
		else if (id < lista.array[mitad]->id) {
			encontrado = buscar(lista, id, ini, mitad - 1, pos);
		}
		else if (id > lista.array[mitad]->id) {
			encontrado = buscar(lista, id, mitad + 1, fin, pos);
		}
	}
	else {
		pos = ini;
	}
	return encontrado;
}

tListaJugadores ordenarPorRanking(const tListaJugadores & lista) {
	tListaJugadores copia;
	int op = 0;

	copia.cont = lista.cont;
	copia.dimensionActual = lista.dimensionActual;
	copia.array = new tJugadorPtr[copia.cont];

	for (int i = 0; i < lista.cont; i++) {
		copia.array[i] = lista.array[i];
	}

	do {
		cout << "Elige el método de ordenación" << endl;
		cout << "1 (inserción) o 2 (burbuja) " << endl;
		cin >> op;

		//mostrará el menú hasta que la opción sea 1 o 2
	} while (op < 1 || op > 2);

	switch (op) {
	case 1: ordenarInserción(copia);
		break;
	case 2: ordenarBurbuja(copia);
		break;
	default:;
	}

	return copia;
}

void ampliar(tListaJugadores & lista) {

	tListaJugadores aux;
	aux.cont = lista.cont;
	aux.dimensionActual = lista.dimensionActual * 2;
	aux.array = new tJugadorPtr[aux.dimensionActual];

	for (int i = 0; i < aux.cont; i++) {
		aux.array[i] = lista.array[i];
	}

	delete[] lista.array;
	lista = aux;
}

void borrarListaJugadores(tListaJugadores & lista) {
	//borrar jugadores
	for (int i = 0; i < lista.cont; i++) {
		delete lista.array[i];
	}

	delete[] lista.array;
	lista.cont = 0;
	lista.dimensionActual = 0;
}

void ordenarBurbuja(tListaJugadores & lista) {
	tJugadorPtr tmp;
	bool ok = true;
	int i = 0;
	// Desde el 1º hasta el penúltimo si hay intercambios...
	while ((i < lista.cont - 1) && ok) {
		ok = false;
		// Desde el último hasta el siguiente a i...
		for (int j = lista.cont - 1; j > i; j--) {

			if (!menor(*lista.array[j], *lista.array[j - 1])) {
				//intercambio de posiciones
				tmp = lista.array[j];
				lista.array[j] = lista.array[j - 1];
				lista.array[j - 1] = tmp;
				ok = true;
			}
		}
		if (ok) i++;
	}
}

void ordenarInserción(tListaJugadores & lista) {
	int pos;
	tJugadorPtr nuevo;
	// Desde el segundo elemento hasta el último...
	for (int i = 1; i < lista.cont; i++) {
		nuevo = lista.array[i];
		pos = 0;
		while ((pos < i) && !(menor(*lista.array[pos], *nuevo))) {
			pos++;
		}
		// pos: índice del primer mayor; i si no lo hay
		for (int j = i; j > pos; j--) {
			lista.array[j] = lista.array[j - 1];
		}
		lista.array[pos] = nuevo;

	}
}
