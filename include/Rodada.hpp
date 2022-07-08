#ifndef RODADA_H
#define RODADA_H
#include "Mao.hpp"
#include "Jogador.hpp"

using std::string;

class Rodada
{
public:
//Funções e valores da rodada
 Rodada();
 ~Rodada();
 void setRodada(Jogador*, int);
 string getWinners(int);
 Jogador jogadores[8];
};

#endif