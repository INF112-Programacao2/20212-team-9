#ifndef INIMIGO_HPP
#define INIMIGO_HPP

class Inimigo{
    private:

    int _vidaInimigo;
    int _velocidadeInimigo = 10;
    int _ouroInimigo;
    int _tipoInimigo;
    int _posX = 0;
    int _posY = 246;

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
    int get_posX();
    int get_posY();
    void set_posX();
    void set_posY();
};

//temos que pensar num metodo para aumentar o ouro do jogador quanto isMorto for true

#endif