#ifndef TORRE_HPP
#define TORRE_HPP

class Torre
{
private:
    int _dano;
    int _preco;
    int _tipo;
    int _pos_x;
    int _pos_y;

public:
    Torre(int dano, int preco, int tipo, int pos_x, int pos_y);
    ~Torre();
    int getDano();
    int getPreco();
    int getTipo();
    int getPos_x();
    int getPos_y();
};

#endif
