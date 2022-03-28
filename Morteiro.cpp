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

bool Morteiro::is_possivel_comprar(int ouro) {
    if(ouro >= _preco)
        return true;
    else
        return false;
}

int Morteiro::getProjetil_pos_y() {
    return _projetil_pos_y;
}

void Morteiro::incrementar_pos_y_projetil(int num) {
    _projetil_pos_y += num;
}

void Morteiro::selecionar_alvo(Inimigo inimigos[], int num_inimigos){
    int distancia;
    bool tem_alvo = false;
    for(int i = 0; i<num_inimigos; i++)
    {
        distancia = ((_pos_x+41)-inimigos[i].get_posX())*((_pos_x+41)-inimigos[i].get_posX()) + 
        ((_pos_y+104)-inimigos[i].get_posY())*((_pos_y+104)-inimigos[i].get_posY());

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