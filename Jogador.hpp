#ifndef JOGADOR_HPP
#define JOGADOR_HPP

    class Jogador
    {
    private:
        int _vida;
        int _ouro;
        int _score = 0;

    public:
        Jogador(int vida, int ouro);
        ~Jogador();
        int getVida();
        int getOuro();
        int getScore();
        void setOuro(int ouroInimigo);
        void setOuro();
        void ganharScore();
        void perdeVida(int ataqueInimigo); 
        void pagar(int preco);
        bool isPossivel(int preco);
    };

#endif
