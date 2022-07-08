#include <iostream>
#include <cstdlib>
#include <string.h>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include "Poquer.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

//Pontuação base por jogada
#define RSF 100000
#define SF 90000
#define FK 80000
#define FH 70000
#define F 60000
#define S 50000
#define TK 40000
#define TP 30000
#define OP 20000
#define HC 10000

bool rodada_valida;

//Construtor Poquer
Poquer::Poquer(){
    cout << "Poquer iniciado!" << endl;
}
//Destrutor Poquer
Poquer::~Poquer(){
    cout << "Poquer foi destruído!" << endl;
}

using namespace std;

void Poquer::IniciarPoquer()
{
    int n_jogadores, pingo, aposta, n_total_jogadores;
    Jogador jogadores[5];
    Jogador participantesRodada[5]; //Auxiliar de jogadores
    string nome_jogador;
    int apostas_rodada[5]; //Array com o valor das apostas da rodada

    this->n = 0;
    this->di = 0;

    //Abre o arquivo entrada.txt para leitura
    ifstream inputFile("entrada.txt", ios_base::in);

    int pote = 0;

    //Abre o arquivo saida.txt para escrita
    ofstream outputFile("saida.txt", ios_base::trunc);
    
    //Leitura da quantidade de rodadas e do dinheiro inicial
    inputFile >> n >> di;

    //Inicia leitura de cada rodada
    for (int i = 0; i < n; i++) {

        inputFile >> n_jogadores >> pingo;
        pote = 0; //Reseta o pote para 0

        rodada_valida = true; //Toda rodada é inicialmente valida

        if(pingo < 50) { //Pingo não pode ser menor que 50
            rodada_valida = false;
        }
        else if (pingo%50 != 0)
        {
            rodada_valida = false;
        }
        

        // Leitura de cada aposta e do nome do jogador
        char nome_tmp[100];
        for (int j = 0; j < n_jogadores; j++) {

            inputFile >> nome_tmp;
            nome_jogador = nome_tmp;

            inputFile >> aposta;
            apostas_rodada[j] = aposta;
            pote += aposta; //Pote sempre conterá todas as apostas recebidas

            
            Carta cartas[5];
            int numeroCarta;
            char naipeCarta;

            // Leitura de cada carta
            for (int k = 0; k < 5; k++) {

                inputFile >> numeroCarta >> naipeCarta;
                Carta carta(numeroCarta, naipeCarta);
                cartas[k] = carta;
            }

            //Inicializa uma mão de acordo com as cartas lidas + Ordena a mão
            Mao mao_jogador(cartas);
            mao_jogador.OrdenaMao();

            if(rodada_valida)
            {
                if (i == 0) { //Primeira rodada -> valor inicial de cada jogador é o di e todos apostam/participam da jogada
                Jogador jogador(nome_jogador, di, mao_jogador); //Auxiliar
                n_total_jogadores = n_jogadores; //total de jogadores = numero de jogadores da primeira rodada
                jogadores[j] = jogador;
                participantesRodada[j] = jogadores[j];
                jogadores[j].setValor(jogadores[j].getValor() - aposta);
                jogadores[j].setAposta(aposta);
                jogadores[j].setBlefes(0);
                } else { 
                    int jogadorIndex = 0;
                    while (jogadorIndex < n_total_jogadores) { //Procura o nome do jogador entre os jogadores existentes
                        if (jogadores[jogadorIndex].getNome() == (nome_jogador)) {
                        jogadores[jogadorIndex].setMao(mao_jogador); //Substitui a mão do jogador pela nova
                        jogadores[jogadorIndex].setAposta(aposta);
                        participantesRodada[j] = jogadores[jogadorIndex]; //Estabelece os participantes da rodada atual
                        break;
                        }
                        jogadorIndex++;
                    }
                    jogadores[jogadorIndex].setValor(jogadores[jogadorIndex].getValor() - aposta);
                }
            }
        }
        //Teste de sanidade (valor do jogador >= pingo + aposta)
        if(rodada_valida){
            for (int l = 0; l < n_total_jogadores; l++)
            {
                if (jogadores[l].getValor() < 0) //Apos retirar a aposta, valor nao pode ser negativo
                {
                    rodada_valida = false;
                    break;
                }
                else if (jogadores[l].getValor() < pingo) //Apos retirar a aposta, valor deve ser maior que o pingo
                {
                    rodada_valida = false;
                    break;
                }    
            }
            if(!rodada_valida){ //Reseta o valor dos jogadores, adicionando a aposta retirada
                for (int m = 0; m < n_jogadores; m++)
                {
                   int jogadorIndex2 = 0;
                   while (jogadorIndex2 < n_total_jogadores) //Busca nome do jogador utilizando os participantes da rodada
                   {
                       if (jogadores[jogadorIndex2].getNome() == participantesRodada[m].getNome())
                       {
                           jogadores[jogadorIndex2].setValor(jogadores[jogadorIndex2].getValor() + apostas_rodada[m]); //Readiciona o valor da aposta
                       }
                       jogadorIndex2++;
                   } 
                }  
            }
        }

        pote += (pingo*n_total_jogadores); //Todos os jogadores contribuem para o pote

        int maior_aposta = GetMaiorAposta(apostas_rodada, n_jogadores);

        if(rodada_valida){ //Inicia a rodada valida
        RetiraPingo(n_total_jogadores, pingo, jogadores); //Retira o pingo do dinheiro de cada jogador
        Rodada rodada;
        rodada.setRodada(participantesRodada, n_jogadores); //Inicializa a rodada com o valor dos participantes

        string winners;

        winners = rodada.getWinners(n_jogadores); //Pega o nome dos vencedores da rodada no valor da string winners

        string vencedores[5]; //Usado para transformar a string com os nomes dos vencedores numa array de strings

        int nv = GetNumeroVencedores(winners, vencedores); //Numero de vencedores da rodada
        OrdenaVencedores(vencedores, nv); //Vencedores em ordem alfabética

        //Imprime a saida
        for(int i = 0; i < nv; i++)
        {
            int count = 0;
            
            while (count < n_total_jogadores)
            {
                if (jogadores[count].getNome() == vencedores[i]) //Procura o nome na Array de vencedores
                {
                if (i == 0)
                {
                    //Imprime o numero de vencedores, o valor recebido por vencedor e a maior jogada da rodada
                    outputFile << nv << " " << (int)(pote/nv) << " " << getTipoJogada(jogadores[count].getMao().tipoJogada()).c_str() << "\n";
                }
                jogadores[count].setValor(jogadores[count].getValor()+(int)(pote/nv));
                outputFile << jogadores[count].getNome().c_str() << "\n"; //Imprime nome dos vencedores da rodada
                }
                else if (jogadores[count].getAposta() == maior_aposta)
                {
                   jogadores[count].setBlefes(jogadores[count].getBlefes() + 1);
                }
                jogadores[count].setAposta(0);
                count++;
            }
        }
        }
        //Imprime os valores da rodada invalida
        else outputFile << "0 0 I\n";
    }

    //Ordena os jogadores por valor
    OrdenaJogadores(jogadores);

    outputFile << "###\n";

    //Imprime o valor final de cada jogador
    for (int count = 0; count < n_total_jogadores; count++){
        outputFile << jogadores[count].getNome().c_str()<< " " << jogadores[count].getValor() << "\n";
    }

    OrdenaBlefes(jogadores);
    cout << "Maior blefador: " << jogadores[0].getNome() << "\n";


    //Fecha os arquivos
    outputFile.close(); 
    inputFile.close();
}

//Função para retirar o valor do pingo atual de todos os jogadores
void Poquer::RetiraPingo(int total_jogadores, int pingo, Jogador* jogadores) {
    for (int i = 0; i < total_jogadores; i++)
    {   
       jogadores[i].setValor(jogadores[i].getValor() - pingo);    
    }
}

//Função para ordenar os jogadores por valor total
void Poquer::OrdenaJogadores(Jogador* jogadores){
    int i, j;
    for ( i = 0; i < 5 - 1; i++)
        for (j = 0; j < 5 - i - 1; j++)
            if (jogadores[j].getValor() < jogadores[j + 1].getValor())
                swap(jogadores[j], jogadores[j + 1]); //Troca
}

//Função para pegar o numero de vencedores na rodada
int Poquer::GetNumeroVencedores(string str, string* vencedores){
    string word;
    std::stringstream iss(str);

    int count = 0;

    while (iss >> word)
    {
        vencedores[count] = word;
        count++;
    }

    return count;
} 

int Poquer::GetMaiorAposta(int* apostas, int jogadores_rodada){
    int i, j;
    for (i = 0; i < jogadores_rodada - 1; i++)
        for(j = 0; j < jogadores_rodada - i - 1; j++)
            if (apostas[j] < apostas[j+1]){
                swap(apostas[j], apostas[j+1]);
            } 

    return apostas[0];         
}

//Ordenar os vencedores em ordem alfabética
void Poquer::OrdenaVencedores(string* vencedores, int count){
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (vencedores[j] > vencedores[j+1])
            {
                swap(vencedores[j], vencedores[j+1]); //Troca
            }
        }
    }
}

void Poquer::OrdenaBlefes(Jogador* jogadores){
    int i, j;
    for ( i = 0; i < 5 - 1; i++)
        for (j = 0; j < 5 - i - 1; j++)
            if (jogadores[j].getBlefes() < jogadores[j + 1].getBlefes())
                swap(jogadores[j], jogadores[j + 1]); //Troca
}


//Função para transformar a pontuação dada em uma string com o nome da jogada pontuada
string Poquer::getTipoJogada(int jogadas) {
    if (jogadas >= RSF)
    {
        return "RSF";
    }
    if (jogadas >= SF)
    {
        return "SF";
    }
    if (jogadas >= FK)
    {
        return "FK";
    }
    if (jogadas >= FH)
    {
        return "FH";
    }
    if (jogadas >= F)
    {
        return "F";
    }
    if (jogadas >= S)
    {
        return "S";
    }
    if (jogadas >= TK)
    {
        return "TK";
    }
    if (jogadas >= TP)
    {
        return "TP";
    }
    if (jogadas >= OP)
    {
        return "OP";
    }
    return "HC";
}