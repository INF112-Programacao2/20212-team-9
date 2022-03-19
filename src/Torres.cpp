#include <iostream>
#include "Torres.hpp"

Torres::~Torres() = default;

Torres::Torres(int dano, int preco, int tipo){
    this -> _dano = dano;
    this -> _preco = preco;
    this -> _tipo = tipo;
}

int Torres::getDano(){
    return _dano;
}

int Torres::getPreco(){
    return _preco;
}

int Torres::getTipo(){
    return _tipo;
}

