#include <iostream>
#include "Carta.hpp"
#include "Jogador.hpp"
#include "Mao.hpp"
using namespace std;

//Construtor
Mao::Mao(){}

//Construtor recebendo os valores
Mao::Mao(Carta *mao){ 
	for (int i = 0; i < 5; i++) {
	mao_jogador[i] = mao[i];
	}
}

//Ordena a mao por numero da carta
void Mao::OrdenaMao() {
	for (int i = 0; i < 5 - 1; i++)
		for (int j = 0; j < 5 - i - 1; j++) 
			if ((mao_jogador[j].getNumero() > mao_jogador[j + 1].getNumero()) &&
			!(mao_jogador[j+1].getNumero() == 1 &&mao_jogador[j].getNumero() != 1)) 
				swap(mao_jogador[j],mao_jogador[j + 1]);//Troca caso o valor anterior seja maior que o sucessor (caso o sucessor seja 1, não troca) 
			else if (mao_jogador[j].getNumero()==1 &&mao_jogador[j + 1].getNumero() != 1)
				swap(mao_jogador[j],mao_jogador[j + 1]);//Troca caso o valor anterior seja 1
}

//Checa se a mao é TK
bool Mao::threeOfAKind(){
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
		 	for(int l=0; l<5; l++){
		 		if((mao_jogador[i].getNumero() == mao_jogador[j].getNumero() //Checa por posição se existem 3 numeros iguais
				 && mao_jogador[i].getNumero() == mao_jogador[l].getNumero()) 
				 && (i!=j && i!=l && j!=l))
		 		return true; 
			}
		}
	}
	return false;
}


// Checa se a mao é FK
bool Mao::fourOfAKind()
{
 for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
		 	for(int l=0; l<5; l++){
				for(int k=0; k<5;k++){
		 			if((mao_jogador[i].getNumero() == mao_jogador[j].getNumero() //Checa por posição se existem 4 numeros iguais
					 && mao_jogador[i].getNumero() == mao_jogador[l].getNumero()
					 && mao_jogador[i].getNumero() == mao_jogador[k].getNumero()) 
					 && (i!=j && i!=l && j!=l && i!=k && l!=k && j!=k))
		 			return true;
				} 
			}
		}
	}
	return false;
}

//Checa se a mao é OP
bool Mao::onePair (){
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++) 
		 	if(mao_jogador[i].getNumero() == mao_jogador[j].getNumero() && i!=j) //Checa por posição se existem 2 numeros iguais
		 		return true; 
	}
	return false;
}

//Checa se a mao é TP
bool Mao::twoPairs(){
	if (mao_jogador[0].getNumero() == mao_jogador[1].getNumero() //Par 1 nas primeiras posições
	&& mao_jogador[2].getNumero() == mao_jogador[3].getNumero()) //Par 2 no meio
	{
		return true;
	}
	else if (mao_jogador[0].getNumero() == mao_jogador[1].getNumero() //Par 1 nas primeiras posições
	&& mao_jogador[2].getNumero() == mao_jogador[3].getNumero()) //Par 2 nas ultimas posições
	{
		return true;
	}
	else if (mao_jogador[1].getNumero() == mao_jogador[2].getNumero() //Par 1 no meio
	&& mao_jogador[3].getNumero() == mao_jogador[4].getNumero()) //Par 2 nas ultimas posiçõe
	{
		return true;
	}
	else return false;
}


//Checa se a mao é F
bool Mao::flush(){
	if(mao_jogador[0].getNaipe() == mao_jogador[1].getNaipe() //Checa se todas as posições possuem o mesmo naipe
	&& mao_jogador[0].getNaipe() == mao_jogador[2].getNaipe() 
	&& mao_jogador[0].getNaipe() == mao_jogador[3].getNaipe() 
	&& mao_jogador[0].getNaipe() == mao_jogador[4].getNaipe())
	 	return true;
	return false;
}


//Checa se a mao é S
bool Mao::straight(){
	bool straight;
	if(onePair()==true) return false;
	int counter;
	for (counter = 1; counter < 5; counter++) 
			if ((mao_jogador[counter].getNumero()-1) == mao_jogador[counter-1].getNumero()) //Checa se o valor da posição é exatamente 1 menor que o da posição anterior
			straight = true;
			else {
				straight = false;
				break;
			}
	return straight;
}


//Checa se a mao é RSF
bool Mao::royalStraightFlush(){
	if(!flush())
		return false;
    else if (mao_jogador[0].getNumero() == 10 //Se for flush e se as posições forem de 10 ate 1(Ás)
	&& mao_jogador[1].getNumero() == 11
	&& mao_jogador[2].getNumero() == 12
	&& mao_jogador[3].getNumero() == 13
	&& mao_jogador[4].getNumero() == 1)
	{
		return true;
	}
	return false;
 }


//Checa se a mao é SF
bool Mao::straightFlush(){
	if (straight() && flush()) //É straight e Flush
	   return true;

	return false;
}

//Checa se a mao é FH
bool Mao::fullHouse(){
	if(threeOfAKind()==true && twoPairs()==true) //Possui uma trinca e 1 par diferente dos valores da trinca (possui pelo menos dois pares diferentes)
		return true;
	
	else
		return false;
}

//Pontua a jogada de acordo com a mao
int Mao::tipoJogada(){

	if (royalStraightFlush()){
		return 100000;
	}
	if (straightFlush()){

		return 90000;
 }
	if(fourOfAKind()){ 
		//Definição de desempate
		int quadra, carta_maior; 
		if (mao_jogador[0].getNumero() == mao_jogador[1].getNumero()) //4 primeiras cartas iguais
		{
			quadra = mao_jogador[0].getNumero();
		    carta_maior = mao_jogador[4].getNumero();
		}
		else //4 ultimas cartas iguais
		{
			quadra = mao_jogador[4].getNumero();
			carta_maior = mao_jogador[0].getNumero();
		}

		return 80000 + quadra * 10 + carta_maior;
 }
	if(fullHouse()){
		//Definição de desempate
		int tripla, par;

		if (mao_jogador[1].getNumero() == mao_jogador[2].getNumero()) { //Tripla no inicio
			tripla = mao_jogador[0].getNumero();
			par = mao_jogador[4].getNumero();
		} else //Tripla no final
		{
			tripla = mao_jogador[4].getNumero();
			par = mao_jogador[0].getNumero();
		}

		return 70000 + tripla * 10 + par;
 }
	if(flush()){
		//Definição de desempate
		int carta_maior = mao_jogador[4].getNumero();
		return 60000 + carta_maior;
 }
	if(straight()){
		//Definição de desempate
		int carta_maior = mao_jogador[4].getNumero();
		return 50000 + carta_maior;
 }
	if(threeOfAKind()){
		//Definição de desempate
		int tripla_indices[3];
		int maior = 0;
		int tripla;

		for (int i = 0; i < 5; i++)
		{
			if((mao_jogador[i].getNumero() == (mao_jogador[i+1].getNumero() == mao_jogador[i+2].getNumero()))) {
				tripla = mao_jogador[i].getNumero();
				tripla_indices[0] = i;
				tripla_indices[1] = i+1;
				tripla_indices[2] = i+2;
			}
		}

		for (int i = 0; i < 5; i++) {
			if ((i != tripla_indices[0]) && (i != tripla_indices[1]) && (i != tripla_indices[2]) && (mao_jogador[i].getNumero() > maior))
			{
				maior = mao_jogador[i].getNumero();
			}
		}

			return 40000 + tripla * 10 + maior;
 }


	if(twoPairs()){
		//Definição de desempate
		int par_menor, par_maior, carta_maior;
		if (mao_jogador[0].getNumero() == mao_jogador[1].getNumero()) { //Par no inicio
			if (mao_jogador[2].getNumero() == mao_jogador[3].getNumero()) 	{ //Par maior no meio
			par_menor = mao_jogador[0].getNumero();
			par_maior = mao_jogador[2].getNumero();
			carta_maior = mao_jogador[4].getNumero();
		}
		else if (mao_jogador[3].getNumero() == mao_jogador[4].getNumero()) { //Par maior no final
			par_menor = mao_jogador[0].getNumero();
			par_maior = mao_jogador[4].getNumero();
			carta_maior = mao_jogador[2].getNumero();
		}
 	}
	else { //Carta unica no inicio
		par_maior = mao_jogador[4].getNumero();
		par_menor = mao_jogador[1].getNumero();
		carta_maior = mao_jogador[0].getNumero();
 }
		return 30000 + par_maior * 150 + par_menor * 10 +  carta_maior ;
}


	if(onePair()){
		//Definição de desempate
		int par, carta_maior = 0;
		for (int i = 0; i < 5; i++)
		{
			if ((mao_jogador[i].getNumero() == mao_jogador[i + 1].getNumero())) { //Localiza o par
				par = mao_jogador[i].getNumero();
			} else {
				if (mao_jogador[i].getNumero() > carta_maior) { //Pega a maior carta fora do par
					carta_maior  = mao_jogador[i].getNumero();
				}
			}
		}
		return 20000 + par*10 + carta_maior;
 }
 //Define High Card (HC)
 int high_card = mao_jogador[4].getNumero();
 return 10000 + high_card;
}