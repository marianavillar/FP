//Mariana de la Caridad Villar Rojas
//Elena Cerro del Pino

//Equipo 14 del grupo 1ºG

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <locale.h>
#include <ctime>
using namespace std;

const int MAX_CARTAS = 8;
const int BARAJA_CARTAS = 40;
typedef int tCartasPorAparecer[MAX_CARTAS];
typedef int tArrayCartas[BARAJA_CARTAS];

typedef struct{
	tArrayCartas cartas;
	int numCartas;
}tCartasConjunto;

//Añadidos al código
int menu();
float puntosCarta(int carta);

void partidaA(ifstream& archivo, int cartas, float &puntJug, float &puntMaq);
void partidaB(ifstream& archivo, int cartas, float &puntJug, float &puntMaq);
void partidaC(ifstream& archivo, tCartasPorAparecer cartasAp, float &puntJug, float &puntMaq);
void partidaD(tCartasConjunto & lista, tCartasConjunto &cartasHumano, tCartasConjunto &cartasMaq, tCartasPorAparecer cartasAp, float &puntJug, float &puntMaq, ifstream &archivo);

void inicializar(tCartasPorAparecer cartas);
int cartasQuedan(const tCartasPorAparecer cartas);

bool cargarArchivo(ifstream&archivo);
int quienGanamodoD(const tCartasConjunto cartasMaquina, const tCartasConjunto cartasHumano, float puntosJugador, float puntosMaquina);
string ganadorAstring(int ganador);
bool cargarArchivoSalida(string nomArch, string gana, tCartasConjunto cartasHumano, tCartasConjunto cartasMaq, float puntJug, float puntMaq);

//Versión 1
float modoA(ifstream& file, int numCartas);
float modoBhumano(ifstream& file, int numCartas);
float modoBmaquina(ifstream& file, int numCartas, float puntosHumano);
int determinaGanador(float puntosJugador, float puntosMaquina);

// Versión 2
void modoChumano(ifstream& file, tCartasPorAparecer cartas, float& puntos);
void modoCmaquina(ifstream& file, tCartasPorAparecer cartas, float puntosHumano, float& puntos);
bool esProbablePasarse(float puntosMaquina, const tCartasPorAparecer cartas);


//Versión 3
void inicializa(tCartasConjunto & listaCartas);
void sacarCarta(tCartasConjunto & listaCartas, int & carta);
void annadirCarta(tCartasConjunto & listaCartas, int carta);
void crearMazo(tCartasConjunto & mazo);
void modoDhumano(tCartasConjunto & mazo, tCartasPorAparecer cartas, tCartasConjunto & cartasHumano, float & puntos);
void modoDmaquina(tCartasConjunto & mazo, tCartasPorAparecer cartas, float puntosHumano, tCartasConjunto
	& cartasMaquina, float & puntos);


int menu() {
	int op;

	cout << "   _____________________________________________" << endl;
	cout << "  |                                             |" << endl;
	cout << "  | Bienvenid@ al juego de Las siete y media :) |" << endl;
	cout << "  |_____________________________________________|" << endl << endl;

	cout << " 1. Jugar Modo A: " << endl;
	cout << " 2. Jugar Modo B: " << endl;
	cout << " 3. Jugar Modo C: " << endl;
	cout << " 4. Jugar Modo D: " << endl;
	cout << " 0. Salir : " << endl;
	cout << " Eige una opción: " << endl;
	cin >> op;

	while (op < 0 || op > 4) {
		cout << " Opción incorrecta. Elige otra opción. " << endl;
		cin >> op;
	}

	return op;
}

float modoA(ifstream& file, int numCartas) {
	int carta;
	float puntos = 0;

	for (int i = 0; i < numCartas; i++) {
		file >> carta;
		puntos = puntos + puntosCarta(carta);

		cout << " Carta: " << carta << endl;
		cout << " Tu puntuación: " << puntos << endl;
	}

	return puntos;
}

float puntosCarta(int carta) {
	float puntuacion;

	if (carta > 7) {
		puntuacion = 0.5;
	}
	else {
		puntuacion = carta;
	}
	return puntuacion;
}

float modoBhumano(ifstream& file, int numCartas) {
	float puntos = 0;
	int i = 0;
	int carta;
	int opcion;
	bool plantarse = false;
	bool pasarse = false;

	while (i < numCartas && !plantarse && !pasarse) {
		file >> carta;
		puntos = puntos + puntosCarta(carta);

		cout << " Carta: " << carta << endl;
		cout << " Tu puntuación: " << puntos << endl;

		if (puntos >= 7.5) {
			pasarse = true;
		}
		else {
			cout << " Quieres plantarte?: " << endl;
			cout << " - 1 : SI " << endl;
			cout << " - 2 : NO " << endl;
			cin >> opcion;

			while (opcion < 1 || opcion > 2) {
				cout << " Opción no válida. " << endl;
				cin >> opcion;
			}

			if (opcion == 1) {
				plantarse = true;
			}
			else {
				plantarse = false;
			}
		}
		i++;
	}

	return puntos;
}

float modoBmaquina(ifstream& file, int numCartas, float puntosHumano) {
	float puntos = 0;
	int i = 0, carta;
	string opcion;
	bool plantarse = false;


	while (i < numCartas && !plantarse) {
		file >> carta;
		puntos = puntos + puntosCarta(carta);

		cout << " Carta: " << carta << endl;
		cout << " Tu puntuación: " << puntos << endl;

		if (puntos > puntosHumano) {
			plantarse = true;
		}
		i++;
	}
	return puntos;
}

int determinaGanador(float puntosJugador, float puntosMaquina) {
	int gana;

	if (puntosJugador <= 7.5 && puntosMaquina <= 7.5) {
		if (puntosJugador == puntosMaquina) {
			gana = 1 + rand() % (2 + 1 - 1);
		}
		if (puntosJugador > puntosMaquina) {
			gana = 1;
		}
		if (puntosJugador < puntosMaquina) {
			gana = 2;
		}
	}
	if (puntosJugador > 7.5) {
		gana = 2;
	}
	else {
		if (puntosMaquina > 7.5) {
			gana = 1;
		}
	}

	return gana;
}

void modoChumano(ifstream& file, tCartasPorAparecer cartas, float& puntos) {
	int i = 0, carta;
	bool plantarse = false;
	float puntuacion = 0;
	int opcion;

	while (i < cartasQuedan(cartas) && !plantarse) {
		file >> carta;
		puntuacion = puntuacion + puntosCarta(carta);

		cout << " Carta: " << carta << endl;
		cout << " Tu puntuación: " << puntuacion << endl;

		if (carta > 7) {
			cartas[0]--;
		}
		else {
			cartas[carta]--;
		}

		if (puntuacion >= 7.5) {
			plantarse = true;
		}
		else {
			cout << " Quieres plantarte?: " << endl;
			cout << " - 1 : SI " << endl;
			cout << " - 2 : NO " << endl;
			cin >> opcion;

			while (opcion < 1 || opcion > 2) {
				cout << " Opción no válida. " << endl;
				cin >> opcion;
			}

			if (opcion == 1) {
				plantarse = true;
			}
			else {
				plantarse = false;
			}
		}
		i++;
	}
	puntos = puntuacion;
}

bool esProbablePasarse(float puntosMaquina, const tCartasPorAparecer cartas) {
	bool pasarse = false;
	float probabilidad;
	int pasado;
	int suma = 0, sumCartasDisp;

	pasado = 8 - puntosMaquina;

	sumCartasDisp = cartasQuedan(cartas);

	for (int j = pasado; j < MAX_CARTAS; j++) {
		suma = suma + cartas[j];
	}
	probabilidad = suma / sumCartasDisp;

	if (probabilidad > 0.5) {
		pasarse = true;
	}

	return pasarse;
}


void modoCmaquina(ifstream& file, tCartasPorAparecer cartas, float puntosHumano, float& puntos) {
	int i = 0, carta;
	float puntuacion = 0;
	bool plantarse = false;

	while (i < cartasQuedan(cartas) && !plantarse) {
		file >> carta;
		puntuacion = puntuacion + puntosCarta(carta);

		if (carta > 7) {
			cartas[0]--;
		}
		else {
			cartas[carta]--;
		}

		cout << " Ha robado un " << carta << endl;
		cout << " Puntuacion: " << puntuacion << endl;

		if (puntuacion > puntosHumano) {
			plantarse = true;
		}
		else if (puntuacion == puntosHumano) {
			plantarse = esProbablePasarse(puntuacion, cartas);
		}
		i++;
	}

	puntos = puntuacion;
}

void inicializar(tCartasPorAparecer cartas) {

	for (int i = 0; i < MAX_CARTAS; i++) {
		if (i == 0) {
			cartas[i] = 12;
		}
		else {
			cartas[i] = 4;
		}
	}
}

int cartasQuedan(const tCartasPorAparecer cartas) {
	int numCartas = 0;

	for (int i = 0; i < MAX_CARTAS; i++) {
		numCartas = numCartas + cartas[i];   //Suma el numero de cartas que hay en cada posicion de i
	}
	return numCartas;
}

int quienGanamodoD(const tCartasConjunto cartasMaquina, const tCartasConjunto cartasHumano, float puntosJugador, float puntosMaquina) {
	int gana;
	
	if (puntosJugador <= 7.5 && puntosMaquina <= 7.5) {
		if (puntosJugador == puntosMaquina) {
			if (cartasMaquina.numCartas == cartasHumano.numCartas) {
				gana = 1 + rand() % (2 + 1 - 1);
			}
			else if (cartasMaquina.numCartas < cartasHumano.numCartas) {
				gana = 2;
			}
			else if (cartasMaquina.numCartas > cartasHumano.numCartas) {
				gana = 1;
			}

		}
		else if (puntosJugador > puntosMaquina) {
			gana = 1;
		}
		else if (puntosJugador < puntosMaquina) {
			gana = 2;
		}
	}
	if (puntosJugador > 7.5) {
		gana = 2;
	}
	else {
		if (puntosMaquina > 7.5) {
			gana = 1;
		}
	}

	return gana;
}

void modoDhumano(tCartasConjunto & mazo, tCartasPorAparecer cartas, tCartasConjunto & cartasHumano, float & puntos) {
	int i = 0;
	bool plantarse = false;
	int opcion, carta;
	float  puntuacion = 0;

	while (i < cartasQuedan(cartas) && !plantarse) {

		sacarCarta(mazo, carta);
		annadirCarta(cartasHumano, carta);
		puntuacion = puntuacion + puntosCarta(cartasHumano.cartas[i]);
		
		cout << " Carta Actual: " << cartasHumano.cartas[i] << endl;
		cout << " Todas las cartas que has robado hasta ahora son: ";
		for (int j = 0; j < cartasHumano.numCartas; j++) {
			cout << cartasHumano.cartas[j] << " ";
		}
		cout << endl;
		cout << " Tu puntuación: " << puntuacion << endl;

		if (cartasHumano.cartas[i] > 7) {
			cartas[0]--;
		}
		else {
			cartas[cartasHumano.cartas[i]]--;
		}

		if (puntuacion >= 7.5) {
			plantarse = true;
		}
		else {
			cout << " Quieres plantarte?: " << endl;
			cout << " - 1 : SI " << endl;
			cout << " - 2 : NO " << endl;
			cin >> opcion;

			while (opcion < 1 || opcion > 2) {
				cout << " Opción no válida. " << endl;
				cin >> opcion;
			}

			if (opcion == 1) {
				plantarse = true;
			}
			else {
				plantarse = false;
			}
		}
		i++;
	}
	puntos = puntuacion;
}

void modoDmaquina(tCartasConjunto & mazo, tCartasPorAparecer cartas, float puntosHumano, tCartasConjunto
	& cartasMaquina, float & puntos) {
	int i = 0, carta;
	float puntuacion = 0;
	bool plantarse = false;

	while (i < cartasQuedan(cartas) && !plantarse) {
		sacarCarta(mazo, carta);
		annadirCarta(cartasMaquina, carta);
		puntuacion = puntuacion + puntosCarta(cartasMaquina.cartas[i]);

		if (cartasMaquina.cartas[i] > 7) {
			cartas[0]--;
		}
		else {
			cartas[cartasMaquina.cartas[i]]--;
		}

		cout << " Carta Actual: " << cartasMaquina.cartas[i] << endl;
		cout << " Todas las cartas que has robado hasta ahora son: ";
		for (int j = 0; j < cartasMaquina.numCartas; j++) {
			cout << cartasMaquina.cartas[j] << " ";
		}
		cout << endl;
		cout << " Tu puntuación: " << puntuacion << endl;

		if (puntuacion > puntosHumano) {
			plantarse = true;
		}
		else if (puntuacion == puntosHumano) {
			plantarse = esProbablePasarse(puntuacion, cartas);
		}
		else if (puntuacion == 7.5) {
			plantarse = true;
		}
		i++;
	}

	puntos = puntuacion;

}

void inicializa(tCartasConjunto & listaCartas){
	for (int i = 0; i < 40; i++) {
		listaCartas.cartas[i] = 0;
	}
	listaCartas.numCartas = 0;
}

void sacarCarta(tCartasConjunto &listaCartas, int &carta){

	if (listaCartas.numCartas > 0){
		carta = listaCartas.cartas[listaCartas.numCartas-1];

		listaCartas.numCartas--;
	}
}

void annadirCarta(tCartasConjunto & listaCartas, int carta) {

	if (listaCartas.numCartas < BARAJA_CARTAS) {
		listaCartas.cartas[listaCartas.numCartas] = carta; //Inserta carta al final
		listaCartas.numCartas++;
	}
}

void crearMazo(tCartasConjunto & mazo){
	int aux, pos;

	for (int i = 0; i < 4; i++) {
		for (int j = 1; j < 8; j++) {
			mazo.cartas[mazo.numCartas] = j;
			mazo.numCartas++;
		}
		for (int j = 10; j < 13; j++) {
			mazo.cartas[mazo.numCartas] = j;
			mazo.numCartas++;
		}
	}

	for (int i = 0; i < mazo.numCartas; i++) {
		pos = rand() % BARAJA_CARTAS;    //Genera una posición aleatoria entre 0 y 39

		aux = mazo.cartas[pos];
		mazo.cartas[pos] = mazo.cartas[i];        //Intercambiamos lo que hay en pos con lo que hay en i
		mazo.cartas[i] = aux;
	}
}

int main() {
	setlocale(LC_CTYPE, "spanish");
	srand(time(NULL));
	ifstream archivo;
	int opcion, cartas, ganador, numPartidas = 0;
	float puntJug, puntMaq;
	int carta;
	string gana;
	string nomArch;

	tCartasPorAparecer cartasAp;
	tCartasConjunto mazo, cartasHumano, cartasMaq;

	opcion = menu();

	while (opcion != 0) {

			switch (opcion) {
			case 1:
				if (cargarArchivo(archivo)) {

					cartas = 3 + rand() % (5 + 1 - 3);
					cout << endl;
					cout << " Ambos vais a robar " << cartas << " cartas." << endl << endl;

					partidaA(archivo, cartas, puntJug, puntMaq);

					ganador = determinaGanador(puntJug, puntMaq);

					gana=ganadorAstring(ganador);

					archivo.close();
				}
				else {
					cout << " Error en el archivo." << endl;
				}
				break;

			case 2:
				if (cargarArchivo(archivo)) {
					cartas = 3 + rand() % (5 + 1 - 3);
					cout << endl;
					cout << " Máximo " << cartas << " cartas a robar." << endl << endl;

					partidaB(archivo, cartas, puntJug, puntMaq);

					ganador = determinaGanador(puntJug, puntMaq);

					gana=ganadorAstring(ganador);

					archivo.close();
				}
				else {
					cout << " Error en el archivo." << endl;
				}
				break;

			case 3:
				if (cargarArchivo(archivo)) {
					inicializar(cartasAp);

					partidaC(archivo, cartasAp, puntJug, puntMaq);
			
					ganador = determinaGanador(puntJug, puntMaq);

					gana=ganadorAstring(ganador);

					archivo.close();
				}
				else {
					cout << " Error en el archivo." << endl;
				}
				break;

			case 4: 
				
				inicializar(cartasAp);

				partidaD(mazo, cartasHumano, cartasMaq, cartasAp, puntJug, puntMaq, archivo);

				ganador = quienGanamodoD(cartasMaq, cartasHumano, puntJug, puntMaq);

				gana=ganadorAstring(ganador);

				break;

			default:
				cout << " GRACIAS POR JUGAR!!! " << endl;

			}
		
		numPartidas++;
		cout << endl << numPartidas << endl << endl;
		nomArch = to_string(numPartidas);

		if (opcion == 4) {
			if (cargarArchivoSalida(nomArch, gana, cartasHumano, cartasMaq, puntJug, puntMaq)) {
				cout << " Se ha cargado el archivo con los resultados. " << endl << endl;
			}
		}
		opcion = menu();
	}

	system("pause");
	return 0;
}

bool cargarArchivoSalida(string nomArch, string gana, tCartasConjunto cartasHumano, tCartasConjunto cartasMaq, float puntJug, float puntMaq) {
	ofstream archSalida;
	bool cargado = false;

	archSalida.open(nomArch + ".txt");
	if (archSalida.is_open()) {
		cargado = true;

		archSalida << gana << endl;

		archSalida << "Máquina" << endl;
		archSalida << "puntos: " << puntMaq << endl;
		archSalida << "Cartas: ";
		for (int i = 0; i < cartasMaq.numCartas; i++) {
			archSalida << cartasMaq.cartas[i] << " ";
		}
		archSalida << endl;

		archSalida << "Jugador" << endl;
		archSalida << "puntos: " << puntJug << endl;
		archSalida << "Cartas: ";
		for (int i = 0; i < cartasHumano.numCartas; i++) {
			archSalida << cartasHumano.cartas[i] << " ";
		}
		archSalida << endl;

		archSalida.close();
	}
	return cargado;
}

string ganadorAstring(int ganador) {
	string gana;

	switch (ganador) {
	case 1:
		gana = " Ha ganado el jugador. ";
		cout << gana << endl << endl;
		break;
	case 2:
		gana = " Ha ganado la máquina. ";
		cout << gana << endl << endl;
		break;
	default:
		cout << " Ganador no válido" << endl;
		cout << endl;
	}
	return gana;
}

bool cargarArchivo(ifstream&archivo) {
	string nomArchivo;
	bool cargado = false;

	cout << " Introduce el nombre del archivo donde está el mazo de cartas (terminado en .txt): " << endl;
	cin >> nomArchivo;
	cout << endl;

	archivo.open(nomArchivo);
	if (archivo.is_open()) {
		cargado = true;
	}

	return cargado;
}


void partidaA(ifstream& archivo, int cartas, float &puntJug, float &puntMaq) {

	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "  Es el turno del jugador. " << endl;
	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;

	puntJug = modoA(archivo, cartas);

	cout << " Fin del Turno--------------------------------" << endl << endl;

	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "  Es el turno de la máquina. " << endl;
	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;

	puntMaq = modoA(archivo, cartas);

	cout << " Fin del Turno--------------------------------" << endl << endl;

}

void partidaB(ifstream& archivo, int cartas, float &puntJug, float &puntMaq) {

	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "  Es el turno del jugador. " << endl;
	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;

	puntJug = modoBhumano(archivo, cartas);

	cout << " Fin del Turno--------------------------------" << endl << endl;

	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "  Es el turno de la máquina. " << endl;
	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;

	puntMaq = modoBmaquina(archivo, cartas, puntJug);

	cout << " Fin del Turno--------------------------------" << endl << endl;

}

void partidaC(ifstream& archivo, tCartasPorAparecer cartasAp, float &puntJug, float &puntMaq) {
	float puntos;


	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "  Es el turno del jugador. " << endl;
	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;

	modoChumano(archivo, cartasAp, puntos);
	puntJug = puntos;

	cout << " Fin del Turno--------------------------------" << endl << endl;

	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "  Es el turno de la máquina. " << endl;
	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;

	modoCmaquina(archivo, cartasAp, puntJug, puntos);
	puntMaq = puntos;

	cout << " Fin del Turno--------------------------------" << endl << endl;

}

void partidaD(tCartasConjunto &lista, tCartasConjunto &cartasHumano, tCartasConjunto &cartasMaq, tCartasPorAparecer cartasAp, float &puntJug, float &puntMaq, ifstream &archivo) {

	float puntos;
	
	inicializa(lista);
	inicializa(cartasHumano);
	inicializa(cartasMaq);


	crearMazo(lista);  //Crea el mazo de forma aleatoria


	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "  Es el turno del jugador. " << endl;
	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;

	modoDhumano(lista, cartasAp, cartasHumano, puntos);
	puntJug = puntos;

	cout << " Fin del Turno--------------------------------" << endl << endl;

	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "  Es el turno de la máquina. " << endl;
	cout << " ++++++++++++++++++++++++++++++++++++++" << endl;

	modoDmaquina(lista, cartasAp, puntJug, cartasMaq, puntos);
	puntMaq = puntos;

	cout << " Fin del Turno--------------------------------" << endl << endl;
	
}

		