#include "Inimigo.hpp"

Inimigo::~Inimigo() = default;

Inimigo::Inimigo(int vidaInimigo, int velocidadeInimigo, int ouroInimigo, int tipoInimigo) {
    this -> _vidaInimigo = vidaInimigo;
    this -> _velocidadeInimigo = velocidadeInimigo;
    this -> _ouroInimigo = ouroInimigo;
    this -> _tipoInimigo = tipoInimigo;
}

int Inimigo::getOuroInimigo(){
    return _ouroInimigo;
}

int Inimigo::getVelocidadeInimigo(){
    return _velocidadeInimigo;
}

int Inimigo::getVidaInimigo(){
    return _vidaInimigo;
}

int Inimigo::getTipoInimigo(){
    return _tipoInimigo;
}

int Inimigo::tomaDano(int dano){
    //dano da torre - vida do inimigo
    _vidaInimigo -= dano;
}

bool Inimigo::isMorto(){
    if(_vidaInimigo <= 0)
        return true;
} //precisa fazer o delete do inimigo quando está morto

bool Inimigo::atravessouMapa(){
    //precisa implementar de acordo com a posicoes no mapa
}