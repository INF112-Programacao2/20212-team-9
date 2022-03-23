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
    int _alcance;

public:
    //Torre(int dano, int preco, int tipo, int pos_x, int pos_y);
    //~Torre();
    int getDano();
    void setDano(int dano);
    int getPreco();
    void setPreco(int preco);
    int getTipo();
    void setTipo(int tipo);
    int getPos_x();
    void setPos_x(int pos_x);
    int getPos_y();
    void setPos_y(int pos_y);
    int getAlcance();
    void setAlcance(int alcance);
    static const int _preco_torre_1 = 100;
    static const int _preco_torre_2 = 100;
    static const int _preco_torre_3 = 100;
    static const int _alcance_torre_1 = 200;
    static const int _alcance_torre_2 = 250;
    static const int _alcance_torre_3 = 300;
};

#endif
