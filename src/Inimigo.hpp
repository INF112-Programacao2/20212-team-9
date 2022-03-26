#ifndef INIMIGO_HPP
#define INIMIGO_HPP

class Inimigo{
    private:

    int _vidaInimigo;
    int _velocidadeInimigo;
    int _ouroInimigo;
    int _tipoInimigo;

    public:

    Inimigo(int vidaInimigo, int velocidadeInimigo, int ouroInimigo, int tipoInimigo);
    ~Inimigo();
    bool atravessouMapa();
    bool isMorto();
    int getVidaInimigo();
    int getVelocidadeInimigo();
    int getOuroInimigo();
    int getTipoInimigo();
    int tomaDano();
}

//temos que pensar num metodo para aumentar o ouro do jogador quanto isMorto for true

#endif