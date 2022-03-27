#include <iostream>
#include "Torre.hpp"
#include "Jogador.hpp"
//Torre::~Torre() = default;

/*Torre::Torre(int dano, int preco, int tipo, int pos_x, int pos_y){
    this -> _dano = dano;
    this -> _preco = preco;
    this -> _tipo = tipo;
    this -> _pos_x = pos_x;
    this -> _pos_y = pos_y;
}*/

int Torre::getTipo(){
    return _tipo;
}

void Torre::setTipo(int tipo){
    _tipo = tipo;
    if(tipo == 1)
    {
        _dano = 10;
        _preco = _preco_torre_1;
        _alcance = _alcance_torre_1;
    }

    if(tipo == 2)
    {
        _dano = 20;
        _preco = _preco_torre_2;
        _alcance = _alcance_torre_2;
    }

    if(tipo == 3)
    {
        _dano = 30;
        _preco = _preco_torre_3;
        _alcance = _alcance_torre_3;
    }
}

int Torre::getDano(){
    return _dano;
}

void Torre::setDano(int dano){
    _dano = dano;
}

int Torre::getPreco(){
    return _preco;
}

void Torre::setPreco(int preco){
    _preco = preco;
}

int Torre::getPos_x(){
    return _pos_x;
}

void Torre::setPos_x(int pos_x){
    _pos_x = pos_x;
}

int Torre::getPos_y(){
    return _pos_y;
}

void Torre::setPos_y(int pos_y){
    _pos_y = pos_y;
}

int Torre::getAlcance(){
    return _alcance;
}

void Torre::setAlcance(int alcance){
    _alcance = alcance;
}

bool Torre::isActive(int ouro){
    if(ouro >= 100){
        return true;
    }
    else{
        return false;
    }
 
    //return true;
}

void Torre::selecionar_alvo(Inimigo inimigos[], int num_inimigos){
    int distancia;
    bool tem_alvo = false;
    for(int i = 0; i<num_inimigos; i++)
    {
        distancia = (_pos_x-inimigos[i].get_posX())*(_pos_x-inimigos[i].get_posX()) + 
        (_pos_y-inimigos[i].get_posY())*(_pos_y-inimigos[i].get_posY());

        if(!inimigos[i].isMorto() && distancia<=(_alcance*_alcance))
        {
            tem_alvo = true;
            _indice_do_alvo = i;
            break;
        }
    }
    if(!tem_alvo)
        _indice_do_alvo = -1;
    //std::cout << _indice_do_alvo << std::endl;
}

void Torre::atirar(Inimigo inimigos[]){
    if(_indice_do_alvo != -1)
    {
        inimigos[_indice_do_alvo].tomaDano(_dano);
        //std::cout << "tiro" << std::endl;
    }
}

int Torre::getIndice_alvo(){
    return _indice_do_alvo;
}