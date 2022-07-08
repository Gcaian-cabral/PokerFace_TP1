#include <iostream>
#include "Jogador.hpp"
#include "Mao.hpp"
#include "Carta.hpp"
#include <string>
using namespace std;

//Construtor
Jogador::Jogador() {
	this->nome = "";
	this->valor = 0;
}

//Construtor recebendo os valores
Jogador::Jogador(std::string nome, double valor, Mao mao) {
	this->nome = nome;
	this->valor = valor;
	this->mao = mao;
}

//Retorna a mao do jogador
Mao Jogador::getMao() {
 return mao;
}

//Retorna o nome do jogador
string Jogador::getNome() {
 return nome;
}

//Retorna o valor do jogador
int Jogador::getValor() {
 return valor;
}

int Jogador::getAposta() {
	return aposta;
}

int Jogador::getBlefes() {
	return blefes;
}

//Define o valor do jogador
void Jogador::setValor(int valor) {
 this->valor = valor;
}

//Define a mão do jogador
void Jogador::setMao(Mao mao) {
	this->mao = mao;
}

void Jogador::setAposta(int aposta){
	this->aposta = aposta;
}

void Jogador::setBlefes(int blefes){
	this->blefes = blefes;
}

