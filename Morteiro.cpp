#include <iostream>
#include "Morteiro.h"

int Morteiro::getPreco(){
    return _preco;
}

int Morteiro::getAlcance(){
    return _alcance;
}

int Morteiro::getDano(){
    return _dano;
}

bool Morteiro::isProjetil_subindo() {
    return _projetil_subindo;
}

void Morteiro::set_projetil_subindo(bool a) {
    _projetil_subindo = a;
}


int Morteiro::getProjetil_dy() {
    return _projetil_dy;
}

void Morteiro::inverter_Projetil_dy() {
    _projetil_dy *= -1;
}

int Morteiro::getProjetil_pos_y() {
    return _projetil_pos_y;
}

void Morteiro::setProjetil_pos_y(int y) {
    _projetil_pos_y = y;
}

void Morteiro::incrementar_pos_y_projetil() {
    _projetil_pos_y += _projetil_dy;
}

void Morteiro::selecionar_alvo(Inimigo inimigos[], int num_inimigos){
    int distancia;
    bool tem_alvo = false;
    for(int i = 0; i<num_inimigos; i++)
    {
        distancia = ((_pos_x+38)-inimigos[i].get_posX())*((_pos_x+38)-inimigos[i].get_posX()) + 
        ((_pos_y+40)-inimigos[i].get_posY())*((_pos_y+40)-inimigos[i].get_posY());

        if(!inimigos[i].isMorto() && distancia<=(_alcance*_alcance))
        {
            tem_alvo = true;
            _indice_do_alvo = i;
            break;
        }
    }
    if(!tem_alvo)
        _indice_do_alvo = -1;
}

void Morteiro::atirar(Inimigo inimigos[], bool &matou){
    if(_indice_do_alvo != -1)
    {
        if(inimigos[_indice_do_alvo].getVidaInimigo() - _dano <= 0)
                matou = true;
        inimigos[_indice_do_alvo].tomaDano(_dano);
    }
}