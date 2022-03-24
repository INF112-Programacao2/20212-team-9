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