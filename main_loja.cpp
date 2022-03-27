#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <ctime>
#include "Torre.hpp"
#include "Jogador.hpp"
#include "Inimigo.hpp"

enum MYKEYS
{
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

//Variáveis globais do jogo======
const float FPS = 45;
const int SCREEN_W = 1200;
const int SCREEN_H = 572;
ALLEGRO_BITMAP *enemy = NULL;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_BITMAP *mapa = NULL;
//int inimigo_x = 0;
//int inimigo_y = SCREEN_H/2-40;
int controle_vida = 0;
bool key[4] = { false, false, false, false };
bool redraw = true;
bool sair = false;
int cursor_x, cursor_y;
bool cima, baixo, esq, dir;
//Variáveis globais do jogo======
int num_frames = 0;

//LOJA===========================
ALLEGRO_BITMAP *fundo_loja = NULL;
ALLEGRO_BITMAP *icone_torre1 = NULL;
ALLEGRO_BITMAP *tower1 = NULL;

const int pos_x_icone_torre1 = 1030;
const int pos_y_icone_torre1 = 25;

const int tower1_x_size = 82;
const int tower1_y_size = 208;

int pos_x_tower1;
int pos_y_tower1;

bool arrastar_torre1 = false;

void desenhar_loja()
{
    al_draw_bitmap(fundo_loja,1000,0,0);
    al_draw_bitmap(icone_torre1, pos_x_icone_torre1, pos_y_icone_torre1,0);
}
//===============================


//JOGADOR========================
Jogador jogador(100, 300);
ALLEGRO_BITMAP *jogador_HUD = NULL;
ALLEGRO_FONT *vida_jogador = NULL;
ALLEGRO_FONT *ouro_jogador = NULL;

void desenhar_HUD()
{
    al_draw_bitmap(jogador_HUD,0,0,0);
    al_draw_textf(vida_jogador, al_map_rgb(255,255,255), 75, 20, 0, "%d", jogador.getVida());
    al_draw_textf(ouro_jogador, al_map_rgb(255,255,255), 245, 20, 0, "%d", jogador.getOuro());
}
//ENEMY==========================

Inimigo inimigos[30];
int num_inimigos = 5;

void libera_inimigo(Inimigo inimigos[], int num_enemy);

void Desenhar_inimigo()
{   
    
    for(int i=0; i<num_inimigos; i++)
    {
        if(!inimigos[i].isMorto())
        {
            if(inimigos[i].get_posX() < 950){
                al_draw_bitmap(enemy, inimigos[i].get_posX(), inimigos[i].get_posY(), 0);
            }
            else if(inimigos[i].get_posX() >= 950){
                jogador.perdeVida(25);
                inimigos[i].reset_pos();
            }
        }    
    }
    
}
void mover_enemy(Inimigo inimigos[], int num_inimigos);
//===============================

//TORRES=========================
Torre torres[20];
int num_torres = 1;

void desenhar_torres()
{
    for(int i=0; i<num_torres; i++)
    {   
        if(torres[i].getTipo() == 1)
            al_draw_bitmap(tower1, torres[i].getPos_x(), torres[i].getPos_y(), 0);
        
        if(arrastar_torre1)
        {
            if(torres[i].isActive(jogador.getOuro()))
            {
                if(cursor_x < 1000 /*Largura do mapa*/)
                al_draw_circle(cursor_x, cursor_y, Torre::_alcance_torre_1, al_map_rgb(254,254,254), 3.0);
            }        
        desenhar_loja();
        al_draw_bitmap(tower1, cursor_x-(tower1_x_size/2), cursor_y-(tower1_y_size/2), 0);
        }
    }
}
void selecionar_alvos()
{   
   for(int i=1; i<=num_torres; i++)
        torres[i].selecionar_alvo(inimigos, num_inimigos);
}

void atirar_projeteis()
{
    int indice;
    bool matou;
    for(int i=1; i<=num_torres; i++)
    {
        matou = false;
        torres[i].atirar(inimigos, matou);
        if(torres[i].getIndice_alvo() != -1)
            al_draw_line((torres[i].getPos_x()+41), (torres[i].getPos_y()+70), (inimigos[torres[i].getIndice_alvo()].get_posX()+40), (inimigos[torres[i].getIndice_alvo()].get_posY()+16), al_map_rgb(20,20,20), 4.0);
        if(matou)
            jogador.setOuro(inimigos[i].getOuroInimigo());
    }
}
//===============================

int inicializar_allegro()
{
    if(!al_init())
    {
        std::cout << "Falha ao carregar Allegro" << std::endl;
        return 0;
    }

    if(!al_init_primitives_addon())
    {
        std::cout << "Falha ao carregar primitives" << std::endl;
        return 0;
    }

    if(!al_init_font_addon())
    {
        std::cout << "Falha ao carregar Fonte" << std::endl;
        return 0;
    }

    if(!al_init_ttf_addon())
    {
        std::cout << "Falha ao carregar ttf" << std::endl;
        return 0;
    }

    if(!al_install_mouse())
    {
        std::cout << "Falha ao iniciar o mouse" << std::endl;
        return 0;
    }

    if(!al_install_keyboard())
    {
        std::cout << "Falha ao iniciar o teclado" << std::endl;
        return 0;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        std::cout << "Falha ao iniciar o temporizador" << std::endl;
        return 0;
    }

    if(!al_init_image_addon())
    {
        std::cout <<"Falha ao iniciar al_init_image_addon!" << std::endl;
        return 0;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        std::cout << "Falha ao iniciar a tela" << std::endl;
        al_destroy_timer(timer);
        return 0;
    }
    //INIMIGO========================

    enemy = al_load_bitmap("Inimigo_p.png");
    if(!enemy)
    {
        std::cout << "Falha ao carregar a inimigo!" << std::endl;
        al_destroy_display(display);
        return 0;
    }
    
    //===============================
    mapa = al_load_bitmap("Mapa_Final_p.bmp");
    if(!mapa) {
        std::cout << "Falha ao carregar o mapa!" << std::endl;
        al_destroy_display(display);
        return 0;
    }
    al_draw_bitmap(mapa,0,0,0);

    fundo_loja = al_load_bitmap("fundo_loja.bmp");
    if(!fundo_loja) {
        std::cout << "Falha ao carregar fundo_loja!" << std::endl;
        al_destroy_display(display);
        return 0;
    }
    al_draw_bitmap(fundo_loja,1000,0,0);

    icone_torre1 = al_load_bitmap("icone1.bmp");
    if(!icone_torre1) {
        std::cout << "Falha ao carregar icone_torre1!" << std::endl;
        al_destroy_display(display);
        return 0;
    }
    al_draw_bitmap(icone_torre1, pos_x_icone_torre1, pos_y_icone_torre1,0);

    tower1 = al_load_bitmap("tower1.bmp");
    if(!tower1) {
        std::cout << "Falha ao carregar tower1!" << std::endl;
        al_destroy_display(display);
        return 0;
    }
    al_convert_mask_to_alpha(tower1, al_map_rgb(255, 255, 255));

    jogador_HUD = al_load_bitmap("jogador_HUD.bmp");
    if(!jogador_HUD) {
        std::cout << "Falha ao carregar jogador_HUD!" << std::endl;
        al_destroy_display(display);
        return 0;
    }
    al_convert_mask_to_alpha(jogador_HUD, al_map_rgb(255, 255, 255));

    vida_jogador = al_load_font("arial.ttf", 36, 0);
    if(!vida_jogador) {
        std::cout << "Falha ao carregar vida_jogador!" << std::endl;
        al_destroy_display(display);
        return 0;
    }

    ouro_jogador = al_load_font("arial.ttf", 36, 0);
    if(!ouro_jogador) {
        std::cout << "Falha ao carregar ouro_jogador!" << std::endl;
        al_destroy_display(display);
        return 0;
    }

    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        std::cout << "Falha ao criar a fila de eventos" << std::endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        return 0;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(0,0,0));
    //al_hide_mouse_cursor(display);
    al_flip_display();
    al_start_timer(timer);

    return 1;
}

int main() {

    //SEED===========================
    unsigned seed = time(0);

    srand(seed);
    //===============================
    if(!inicializar_allegro())
        return -1;

    while(!sair)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				sair = true;
			}
        }

        if(ev.type == ALLEGRO_EVENT_TIMER) {
                num_frames++;
                libera_inimigo(inimigos, num_inimigos);
                mover_enemy(inimigos, num_inimigos);
                selecionar_alvos();
                redraw = true;

        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        
        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            cursor_x = ev.mouse.x;
            cursor_y = ev.mouse.y; 
        }

        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(ev.mouse.button && pos_x_icone_torre1<=cursor_x &&
            cursor_x<= pos_x_icone_torre1+140 && pos_y_icone_torre1<=cursor_y &&
            cursor_y<=pos_y_icone_torre1+190 && jogador.isPossivel(Torre::_preco_torre_1))
            {
                arrastar_torre1 = true;
            }

        }

        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && arrastar_torre1)
        {
            if(ev.mouse.button)
            {
                arrastar_torre1 = false;
                if(cursor_x+(tower1_x_size/2) < 1000 /*Dimanesão x do mapa*/)
                {
                    torres[num_torres].setTipo(1);
                    torres[num_torres].setPos_x(cursor_x-(tower1_x_size/2));
                    torres[num_torres].setPos_y(cursor_y-(tower1_y_size/2));
                    jogador.pagar(torres[num_torres].getPreco());
                    num_torres++;
                }
            } 
        }
        
        if(redraw && al_is_event_queue_empty(event_queue))
        {   
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_bitmap(mapa,0,0,0);
            desenhar_loja();
            Desenhar_inimigo();
            desenhar_torres();
            desenhar_HUD();
             if(num_frames%15==0)
                    atirar_projeteis();
            al_flip_display();
        }
    }

    al_destroy_bitmap(mapa);
    al_destroy_bitmap(fundo_loja);
    al_destroy_bitmap(enemy);
    al_destroy_bitmap(icone_torre1);
    al_destroy_bitmap(tower1);
    al_destroy_bitmap(jogador_HUD);
    al_destroy_font(vida_jogador);
    al_destroy_font(ouro_jogador);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    
    return 0;
}

void libera_inimigo(Inimigo inimigos[], int num_enemy){
    for(int i = 0; i < num_enemy; i++){
        if(inimigos[i].isMorto()){
            if(rand() % 300 == 0){
                inimigos[i].reset_pos();
                break;
            }
            
        }
    }
}

void mover_enemy(Inimigo inimigos[], int num_inimigos){
    for(int i=0; i<num_inimigos; i++)
    {
        if(inimigos[i].get_posX() <= 520 && inimigos[i].get_posY() <=300){
            inimigos[i].set_posX();
        }
        else if(inimigos[i].get_posX() >= 500 && inimigos[i].get_posY() <=350){
            inimigos[i].set_posY();
        }
        else
            inimigos[i].set_posX();
    }

}