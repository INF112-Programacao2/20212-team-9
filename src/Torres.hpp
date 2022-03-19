#ifndef TORRES_HPP
#define TORRES_HPP

class Torres
{
private:
    int _dano;
    int _preco;
    int _tipo;
public:
    Torres(int dano, int preco, int tipo);
    ~Torres();
    int getDano();
    int getPreco();
    int getTipo();
};

#endif
