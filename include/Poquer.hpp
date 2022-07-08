#ifndef POQUER_H
#define POQUER_H

#include <fstream>

#include "Jogador.hpp"
#include "Mao.hpp"
#include "Carta.hpp"
#include "Rodada.hpp"

using std::string;

class Poquer{
    private:
    //Valores classe Poquer
        int n; //Numero de rodadas
        int di; //Dinheiro inicial

    public:
    //Funções da classe Poquer
        Poquer();
        ~Poquer();

        void IniciarPoquer();

        string getTipoJogada(int);

        void RetiraPingo(int, int, Jogador*);
        void OrdenaJogadores(Jogador*);

        int GetNumeroVencedores(string, string*);
        void OrdenaVencedores(string*, int);

        int GetMaiorAposta(int*, int);
        void OrdenaBlefes(Jogador*);
};

#endif
