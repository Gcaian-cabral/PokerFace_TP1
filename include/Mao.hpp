#ifndef MAO_H
#define MAO_H
#include "Carta.hpp"
#include "Jogador.hpp"

class Mao
{
private:
    //Valor de Mao
    Carta mao_jogador[5];
public:
    //Funções de Mao
    Mao();
    Mao(Carta *mao);

    //Funções de cada jogada
    bool threeOfAKind();
    bool fourOfAKind();
    bool onePair();
    bool twoPairs();
    bool flush();
    bool straight();
    bool fullHouse();
    bool royalStraightFlush();
    bool straightFlush();

    int tipoJogada();
    void OrdenaMao();
};

#endif