#include "Inimigo.hpp"
/*
Inimigo::~Inimigo() = default;

Inimigo::Inimigo(int vidaInimigo, int velocidadeInimigo, int ouroInimigo, int tipoInimigo) {
    this -> _vidaInimigo = vidaInimigo;
    this -> _velocidadeInimigo = velocidadeInimigo;
    this -> _ouroInimigo = ouroInimigo;
    this -> _tipoInimigo = tipoInimigo;
}
*/
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

void Inimigo::tomaDano(int dano){
    //dano da torre - vida do inimigo
    _vidaInimigo -= dano;
}
//mexer aqui****
bool Inimigo::isMorto(){
    if(_vidaInimigo <= 0)
        return true;
    else
        return false;    
} //precisa fazer o delete do inimigo quando está morto

bool Inimigo::atravessouMapa(){
    //precisa implementar de acordo com a posicoes no mapa
    return true; //apenas para teste
}

void Inimigo::mover(int ponto, int ponto2){
    if(_posX >= ponto && _posY <= ponto2){
        _posX = ponto;
        _posY++;
    }
    else if(_posX >= ponto && _posY == ponto2){
        _posX++;
    }
}
int Inimigo::get_posX(){
    return this->_posX;
}
int Inimigo::get_posY(){
    return this->_posY;
}
void Inimigo::set_posX(){
    this->_posX += 2;//getVelocidadeInimigo();
}
void Inimigo::set_posY(){
    this->_posY += 2;//getVelocidadeInimigo();
}

bool Inimigo::reset_pos(){
    this->_posX = 0;
    this->_posY = 246;
    this->_vidaInimigo = 50;
}