#ifndef INIMIGO_HPP
#define INIMIGO_HPP

class Inimigo{
    private:

    int _vidaInimigo;
    int _velocidadeInimigo;
    int _ouroInimigo;
    int _tipoInimigo;
    int _posX;
    int _posY;

    public:

    Inimigo(int vidaInimigo, int velocidadeInimigo, int ouroInimigo, int tipoInimigo);
    ~Inimigo();
    bool atravessouMapa();
    bool isMorto();
    int getVidaInimigo();
    int getVelocidadeInimigo();
    int getOuroInimigo();
    int getTipoInimigo();
    void tomaDano(int dano);
    void mover(int ponto, int ponto2);
};

//temos que pensar num metodo para aumentar o ouro do jogador quanto isMorto for true

#endif