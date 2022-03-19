#ifndef JOGADOR
#define JOGADOR

class Jogador {
private:
    int _vida_do_castelo = 100;
    int _dinheiro = 100;

public:
    int get_vida_do_castelo();
    void set_vida_do_castelo(int v);
    int get_dinheiro();
    void set_dinheiro(int d);
};

#endif