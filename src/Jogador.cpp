#include <iostream>
#include "Jogador.hpp"

Jogador::~Jogador() = default;

Jogador::Jogador(int vida, int ouro) {
    
    this -> _vida = vida;
    this -> _ouro = ouro;

}

void Jogador::perdeVida(int ataqueInimigo){
    _vida -= ataqueInimigo;
}

int Jogador::getVida() {
    return _vida;
}

int Jogador::getOuro() {
    return _ouro;
}

int Jogador::getScore() {
    return _score;
}

void Jogador::setOuro(){
    _ouro += 0;
}
void Jogador::setOuro(int ouroInimigo) {
    _ouro += ouroInimigo;
}

void Jogador::ganharScore() {
    _score += 100;
}

void Jogador::pagar(int preco) {
    _ouro -= preco;
}

bool Jogador::isPossivel(int preco)
{
	if (this->_ouro >= preco)
		return true;

	return false;
}