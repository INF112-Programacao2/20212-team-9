#ifndef MORTEIRO_HPP
#define MORTEIRO_HPP
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Defesa.h"

class Morteiro : public Defesa {
private:
    static const int _dano = 30;
    int _projetil_pos_y;
    bool _projetil_subindo = true;
    int _projetil_dy = -15;
public:
    static const int _preco = 200;
    static const int _alcance = 320;
    int getPreco();
    int getAlcance();
    int getDano();
    int getProjetil_pos_y();
    bool isProjetil_subindo();
    void set_projetil_subindo(bool a);
    void setProjetil_pos_y(int y);
    int getProjetil_dy();
    void inverter_Projetil_dy();
    void incrementar_pos_y_projetil();
    void selecionar_alvo(Inimigo inimigos[], int num_inimigos);
    void atirar(Inimigo inimigos[], bool &matou);
};

#endif
