#include <iostream> 
#include <fstream>
#include <string>
#include <sstream>
#include <locale>
#include <fstream>
#include <time.h>
#include <iomanip>

#include "Poquer.hpp"

int main(int argc, char* argv[])
{
    clock_t start, end;

    start = clock();

    Poquer jogo; //Inicializa um jogo
    jogo.IniciarPoquer(); //Chama função IniciarPoquer para começar o jogo

    end = clock();

    double time_taken = double(end - start)/double(CLOCKS_PER_SEC);
    
    std::cout << "Time taken by program is : " << std::fixed 
         << time_taken << std::setprecision(9);
    std::cout << " sec " << std::endl;

    return 0; 
}