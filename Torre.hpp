#ifndef TORRE_HPP
#define TORRE_HPP
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Defesa.h"

class Torre : public Defesa {
private:
    static const int _dano = 10;
public:
    static const int _preco = 100;
    static const int _alcance = 170;
    int getPreco();
    int getAlcance();
    int getDano();
    void selecionar_alvo(Inimigo inimigos[], int num_inimigos);
    void atirar(Inimigo inimigos[], bool &matou);
};

#endif
