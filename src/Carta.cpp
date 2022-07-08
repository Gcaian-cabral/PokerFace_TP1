#include <iostream>
#include "Carta.hpp"
#include <string>
using namespace std;

//Construtor
Carta::Carta() {}

//Construtor definindo os valores na chamada
Carta::Carta(int numero, char naipe){
	this->numero = numero;
	this->naipe = naipe;
}

//Retorna Naipe da carta
char Carta::getNaipe() {
 return naipe;
}

//Retorna Numero da carta
int Carta::getNumero() {
 return numero;
}
