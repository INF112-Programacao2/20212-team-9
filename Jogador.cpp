#include "Jogador.h"

int Jogador::get_vida_do_castelo() {
    return _vida_do_castelo;
}

void Jogador::set_vida_do_castelo(int v) {
    _vida_do_castelo += v;
}

int Jogador::get_dinheiro() {
    return _dinheiro;
}

void Jogador::set_dinheiro(int n) {
    _dinheiro += n;
}