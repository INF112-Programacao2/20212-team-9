#include <iostream>
#include "Torre.hpp"

Torre::~Torre() = default;

Torre::Torre(int dano, int preco, int tipo, int pos_x, int pos_y){
    this -> _dano = dano;
    this -> _preco = preco;
    this -> _tipo = tipo;
    this -> _pos_x = pos_x;
    this -> _pos_y = pos_y;
}

int Torre::getDano(){
    return _dano;
}

int Torre::getPreco(){
    return _preco;
}

int Torre::getTipo(){
    return _tipo;
}

int Torre::getPos_x(){
    return _pos_x;
}

int Torre::getPos_y(){
    return _pos_y;
}