#include <iostream>
#include <string>
#include "Jogador.hpp"
#include "Mao.hpp"
#include "Carta.hpp"
#include "Rodada.hpp"
using namespace std;

//Construtor
Rodada::Rodada(){}
//Destrutor
Rodada::~Rodada(){}

//Define o dados da rodada
void Rodada::setRodada(Jogador *jogadores, int n_jogadores)
{
 for (int i = 0; i < n_jogadores; i++) {
  this->jogadores[i] = jogadores[i];
 }
}

//Retorna a string com o nome dos jogadores com a maior pontuação na rodada
string Rodada::getWinners(int n)
{
  string vencedores = ""; //String retornada

  //Ordena os jogadores por pontuação
  for (int i = 0; i < n - 1; i++){
    for (int j = 0; j < n - i - 1; j++) {
      if (jogadores[j].getMao().tipoJogada() > jogadores[j + 1].getMao().tipoJogada()) {
        swap(jogadores[j], jogadores[j + 1]); //Troca
      }
    }
  }

  //Encontra o nome dos vencedores, analisando empates
  for (int i = n-1; i >= 0; i--) {
    if(jogadores[i].getMao().tipoJogada() == jogadores[n - 1].getMao().tipoJogada()) {
        vencedores += jogadores[i].getNome() + "\n";
    }
  }
  
  return vencedores;
}