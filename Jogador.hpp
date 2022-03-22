#ifndef JOGADOR_HPP
#define JOGADOR_HPP

    class Jogador
    {
    private:
        int _vida;
        int _ouro;

    public:
        Jogador(int vida, int ouro);
        ~Jogador();
        int getVida();
        int getOuro();
        void setOuro(int ouroInimigo);
        void perdeVida(int ataqueInimigo); 
        void pagar(int preco);
        bool isPossivel(int preco);
    };

#endif
