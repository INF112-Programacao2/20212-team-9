#ifndef MORTEIRO_HPP
#define MORTEIRO_HPP
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Defesa.h"

class Morteiro : public Defesa {
private:
    static const int _dano = 30;
    int _projetil_pos_y = 10;
public:
    static const int _preco = 200;
    static const int _alcance = 320;
    int getPreco();
    int getAlcance();
    int getDano();
    int getProjetil_pos_y();
    void incrementar_pos_y_projetil(int num);
    bool is_possivel_comprar(int ouro); 
    void selecionar_alvo(Inimigo inimigos[], int num_inimigos);
    void atirar(Inimigo inimigos[], bool &matou);
};

#endif
