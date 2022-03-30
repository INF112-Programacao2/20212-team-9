#ifndef DEFESA
#define DEFESA

#include "Inimigo.hpp"

class Defesa {
protected:
    int _pos_x;
    int _pos_y;
    int _indice_do_alvo = -1;
public:
    //Getters
    int getPos_x();
    int getPos_y();
    int getIndice_alvo();
    //Setters
    void setPos_x(int pos_x);
    void setPos_y(int pos_y);
};

#endif