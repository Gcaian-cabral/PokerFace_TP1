#ifndef JOGADOR_H
#define JOGADOR_H
#include "Mao.hpp"

using std::string;

class Jogador
{
private:
    //Valores de Jogador
    string nome;
    double valor;
    Mao mao;
public:
    //Funções de Jogador
    Jogador();
    Jogador(string, double, Mao);
    string getNome();
    int getValor();
    void setValor(int);
    void setMao(Mao);
    Mao getMao();

    int getAposta();
    void setAposta(int);
    int aposta;

    int getBlefes();
    void setBlefes(int);
    int blefes;
};

#endif