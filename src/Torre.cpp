#include <iostream>
#include "Torre.hpp"

int Torre::getPreco(){
    return _preco;
}

int Torre::getAlcance(){
    return _alcance;
}

int Torre::getDano(){
    return _dano;
}

void Torre::selecionar_alvo(Inimigo inimigos[], int num_inimigos){
    int distancia;
    bool tem_alvo = false;
    for(int i = 0; i<num_inimigos; i++)
    {
        distancia = ((_pos_x+35)-inimigos[i].get_posX())*((_pos_x+35)-inimigos[i].get_posX()) + 
        ((_pos_y+80)-inimigos[i].get_posY())*((_pos_y+80)-inimigos[i].get_posY());

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

void Torre::atirar(Inimigo inimigos[], bool &matou){
    if(_indice_do_alvo != -1)
    {
        if(inimigos[_indice_do_alvo].getVidaInimigo() - _dano <= 0)
                matou = true;
        inimigos[_indice_do_alvo].tomaDano(_dano);
    }
}