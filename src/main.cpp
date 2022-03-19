#include <iostream>
#include "Torres.hpp"
#include "Jogador.hpp"

int main(){

    Jogador j1 (10, 100);
    Torres t1(10, 50, 1);
    int preco = t1.getPreco();

    if(j1.isPossivel(preco))
        std::cout << "ok" << std::endl;
    

    return 0;
}