#ifndef CARTA_H
#define CARTA_H

class Carta
{
private:
    //Valores de Carta
    char naipe;
    int numero;    
public:
    //Funções de Carta
    Carta();
    Carta(int, char);
    int getNumero();
    char getNaipe();
};
#endif