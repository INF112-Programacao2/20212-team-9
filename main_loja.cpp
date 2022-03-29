#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <ctime>
#include <cmath>
#include "Torre.hpp"
#include "Morteiro.h"
#include "Jogador.hpp"
#include "Inimigo.hpp"

//GLOBAIS DO JOGO================
const float FPS = 45;
const int SCREEN_W = 1200;
const int SCREEN_H = 572;

//ponteiro para o som
ALLEGRO_SAMPLE *trilha_sonora = NULL;
//instancia a trilha sonora para evitar conflitos
ALLEGRO_SAMPLE_INSTANCE *inst_trilha_sonora = NULL;
//Fila de eventos
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
//Display
ALLEGRO_DISPLAY *display = NULL;
//Temporizador
ALLEGRO_TIMER *timer = NULL;
//Bitmaps
ALLEGRO_BITMAP *enemy = NULL;
ALLEGRO_BITMAP *mapa = NULL;
ALLEGRO_BITMAP *menu = NULL;
ALLEGRO_BITMAP *tela_game_over = NULL;

int controle_vida = 0;
int enter = 0;
bool redraw = true;
bool sair = false;
int cursor_x, cursor_y;
int num_frames = 0;
//===============================

//LOJA===========================
ALLEGRO_BITMAP *fundo_loja = NULL;
ALLEGRO_BITMAP *icone_torre = NULL;
ALLEGRO_BITMAP *icone_morteiro = NULL;
ALLEGRO_BITMAP *tower = NULL;
ALLEGRO_BITMAP *morteiro = NULL;

const int pos_x_icone_torre = 1030;
const int pos_y_icone_torre = 25;
const int tower_x_size = 70;
const int tower_y_size = 160;

const int pos_x_icone_morteiro = 1030;
const int pos_y_icone_morteiro = 300;
const int morteiro_x_size = 75;
const int morteiro_y_size = 80;

bool arrastar_torre = false;
bool arrastar_morteiro = false;

void desenhar_loja()
{
    al_draw_bitmap(fundo_loja,1000,0,0);
    al_draw_bitmap(icone_torre, pos_x_icone_torre, pos_y_icone_torre,0);
    al_draw_bitmap(icone_morteiro, pos_x_icone_morteiro, pos_y_icone_morteiro,0);
}
//===============================

//JOGADOR========================
Jogador jogador(100, 300);
ALLEGRO_BITMAP *jogador_HUD = NULL;
ALLEGRO_FONT *vida_jogador = NULL;
ALLEGRO_FONT *ouro_jogador = NULL;
ALLEGRO_FONT *score_jogador = NULL;

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
//prototipo menu
void desenhar_menu();

//DEFESAS=========================
Torre torres[20];
int num_torres = 0;
Morteiro morteiros[20];
int num_morteiros = 0;
int projetil_dy = -6;

void desenhar_defesas()
{
    if(num_torres != 0)
    {
        for(int i=0; i<num_torres; i++)
            al_draw_bitmap(tower, torres[i].getPos_x(), torres[i].getPos_y(), 0);
    }
    if(arrastar_torre)
    {
        if(cursor_x < 1000 /*Largura do mapa*/)
            al_draw_circle(cursor_x, cursor_y, Torre::_alcance, al_map_rgb(254,254,254), 3.0);
        
        desenhar_loja();
        al_draw_bitmap(tower, cursor_x-(tower_x_size/2), cursor_y-(tower_y_size/2), 0);
    }

    if(num_morteiros != 0)
    {
        for(int i=0; i<num_morteiros; i++)
            al_draw_bitmap(morteiro, morteiros[i].getPos_x(), morteiros[i].getPos_y(), 0);
    }
    if(arrastar_morteiro)
    {
        if(cursor_x < 1000 /*Largura do mapa*/)
            al_draw_circle(cursor_x, cursor_y, Morteiro::_alcance, al_map_rgb(254,254,254), 3.0);
        
        desenhar_loja();
        al_draw_bitmap(morteiro, cursor_x-(morteiro_x_size/2), cursor_y-(morteiro_y_size/2), 0);
    }
}
void selecionar_alvos()
{   
    if(num_torres != 0)
        for(int i=0; i<num_torres; i++)
            torres[i].selecionar_alvo(inimigos, num_inimigos);

    if(num_morteiros != 0)
        for(int i=0; i<num_morteiros; i++)
            morteiros[i].selecionar_alvo(inimigos, num_inimigos);
    
}

void atirar_projeteis(int num_frames)
{
    if(num_frames%35==0)
        if(num_torres != 0)
        {
            bool matou;
            for(int i=0; i<num_torres; i++)
            {
                matou = false;
                torres[i].atirar(inimigos, matou);
                if(torres[i].getIndice_alvo() != -1)
                    al_draw_line((torres[i].getPos_x()+33), (torres[i].getPos_y()+55), (inimigos[torres[i].getIndice_alvo()].get_posX()+40), (inimigos[torres[i].getIndice_alvo()].get_posY()+16), al_map_rgb(20,20,20), 4.0);
                if(matou)
                {
                    jogador.setOuro(inimigos[i].getOuroInimigo());
                    jogador.ganharScore();
                }
            }
        }
    
    if(num_morteiros != 0)
    {
        bool matou;
        int distancia;
        int pos1, pos2;
        for(int i=0; i<num_morteiros; i++)
        {
            matou = false;
            if(morteiros[i].getIndice_alvo() != -1)
            {
                if(morteiros[i].getProjetil_pos_y() < -150)
                {
                    morteiros[i].inverter_Projetil_dy();
                    morteiros[i].set_projetil_subindo(false);
                }
            
                if(morteiros[i].getProjetil_pos_y() > inimigos[morteiros[i].getIndice_alvo()].get_posY()+20 && morteiros[i].isProjetil_subindo() == false)
                {
                    morteiros[i].inverter_Projetil_dy();
                    morteiros[i].set_projetil_subindo(true);
                    morteiros[i].atirar(inimigos, matou);
                    if(matou)
                    {
                        jogador.setOuro(inimigos[i].getOuroInimigo());
                        jogador.ganharScore();
                    }

                    morteiros[i].setProjetil_pos_y(morteiros[i].getPos_y());
                }

                if(morteiros[i].getProjetil_dy() < 0)
                    al_draw_filled_circle(morteiros[i].getPos_x()+40, morteiros[i].getProjetil_pos_y(), 12, al_map_rgb(10,10,10));
            
                if(morteiros[i].getProjetil_dy() > 0)
                    al_draw_filled_circle(inimigos[morteiros[i].getIndice_alvo()].get_posX()+40, morteiros[i].getProjetil_pos_y(), 12, al_map_rgb(10,10,10));
                morteiros[i].incrementar_pos_y_projetil();   
            }
        }
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

    //SOM_ADDON======================
    al_install_audio();
    al_init_acodec_addon();
    //quantos sons o jogo vai ter
    al_reserve_samples(1);
    
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

    enemy = al_load_bitmap("imagem/Inimigo_p.png");
    if(!enemy)
    {
        std::cout << "Falha ao carregar a inimigo!" << std::endl;
        al_destroy_display(display);
        return 0;
    }
    
    //===============================

    //SOM============================
    trilha_sonora = al_load_sample("imagem/Trilha_sonora.wav");
    if(!trilha_sonora){
        std::cout << "falha ao carregar o som" << std::endl;
        al_destroy_display(display);
        return 0;
    }
    inst_trilha_sonora = al_create_sample_instance(trilha_sonora);
    al_attach_sample_instance_to_mixer(inst_trilha_sonora, al_get_default_mixer());

    al_set_sample_instance_playmode(inst_trilha_sonora, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(inst_trilha_sonora, 0.8);
    //===============================

    //MENU===========================
    menu = al_load_bitmap("Menu_bmp.bmp");
    if(!menu){
        std::cout << "Faha ao carregar menu!" << std::endl;
    }
    //===============================

    mapa = al_load_bitmap("imagem/Mapa_Final_p.bmp");
    if(!mapa) {
        std::cout << "Falha ao carregar o mapa!" << std::endl;
        al_destroy_display(display);
        return 0;
    }
    al_draw_bitmap(mapa,0,0,0);

    tela_game_over = al_load_bitmap("imagem/GameOver.bmp");
    if(!tela_game_over) {
        std::cout << "Falha ao carregar tela_game_over!" << std::endl;
        al_destroy_display(display);
        return 0;
    }

    fundo_loja = al_load_bitmap("imagem/fundo_loja.bmp");
    if(!fundo_loja) {
        std::cout << "Falha ao carregar fundo_loja!" << std::endl;
        al_destroy_display(display);
        return 0;
    }
    al_draw_bitmap(fundo_loja,1000,0,0);

    icone_torre = al_load_bitmap("imagem/Torre_1.bmp");
    if(!icone_torre) {
        std::cout << "Falha ao carregar icone_torre!" << std::endl;
        al_destroy_display(display);
        return 0;
    }
    al_draw_bitmap(icone_torre, pos_x_icone_torre, pos_y_icone_torre,0);

    icone_morteiro = al_load_bitmap("imagem/Torre_2.bmp");
    if(!icone_morteiro) {
        std::cout << "Falha ao carregar icone_morteiro!" << std::endl;
        al_destroy_display(display);
        return 0;
    }
    al_draw_bitmap(icone_morteiro, pos_x_icone_morteiro, pos_y_icone_morteiro,0);

    tower = al_load_bitmap("imagem/tower.bmp");
    if(!tower) {
        std::cout << "Falha ao carregar tower!" << std::endl;
        al_destroy_display(display);
        return 0;
    }
    al_convert_mask_to_alpha(tower, al_map_rgb(255, 255, 255));

    morteiro = al_load_bitmap("imagem/morteiro.bmp");
    if(!morteiro) {
        std::cout << "Falha ao carregar morteiro!" << std::endl;
        al_destroy_display(display);
        return 0;
    }
    al_convert_mask_to_alpha(morteiro, al_map_rgb(255, 255, 255));

    jogador_HUD = al_load_bitmap("imagem/jogador_HUD.bmp");
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

    score_jogador = al_load_font("arial.ttf", 36, 0);
    if(!score_jogador) {
        std::cout << "Falha ao carregar score_jogador!" << std::endl;
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
        if(num_torres + num_morteiros> 4 && num_torres + num_morteiros < 7){
            num_inimigos = 10;
        }
        else if(num_torres + num_morteiros > 7 && num_torres + num_morteiros < 10){
            num_inimigos = 20;
        }
        else if(num_torres + num_morteiros >= 10){
            num_inimigos = 30;
        }
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				sair = true;
			}
        }
        if(jogador.getVida() == 0){
            al_draw_bitmap(tela_game_over,0,0,0);
            al_draw_textf(score_jogador, al_map_rgb(255,255,255), 580, 292, 0, "%d", jogador.getScore());
            al_flip_display();
            al_rest(5);
            sair = true;
        }
        if(ev.type == ALLEGRO_EVENT_TIMER && enter == 1) {
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
            if(enter == 0 && cursor_x >= 470 && cursor_x <= 720){
                if(cursor_y >= 356 && cursor_y <= 410){
                	if (ev.mouse.button & 1)
		        	{
				        enter = 1;

			        }
                }
            }
            if(ev.mouse.button && pos_x_icone_torre<=cursor_x &&
            cursor_x<= pos_x_icone_torre+140 && pos_y_icone_torre<=cursor_y &&
            cursor_y<=pos_y_icone_torre+190 && jogador.isPossivel(Torre::_preco))
            {
                arrastar_torre = true;
            }

            else if(ev.mouse.button && pos_x_icone_morteiro<=cursor_x &&
            cursor_x<= pos_x_icone_morteiro+140 && pos_y_icone_morteiro<=cursor_y &&
            cursor_y<=pos_y_icone_morteiro+190 && jogador.isPossivel(Morteiro::_preco))
            {
                arrastar_morteiro = true;
            }
        }

        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && arrastar_torre)
        {
            if(ev.mouse.button)
            {
                arrastar_torre = false;
                if(cursor_x+(tower_x_size/2) < 1000 /*Dimanesão x do mapa*/)
                {
                    torres[num_torres].setPos_x(cursor_x-(tower_x_size/2));
                    torres[num_torres].setPos_y(cursor_y-(tower_y_size/2));
                    jogador.pagar(torres[num_torres].getPreco());
                    num_torres++;
                }
            }
        }

        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && arrastar_morteiro)
        {
            if(ev.mouse.button)
            {
                arrastar_morteiro = false;
                if(cursor_x+(morteiro_x_size/2) < 1000 /*Dimanesão x do mapa*/)
                {
                    morteiros[num_morteiros].setPos_x(cursor_x-(morteiro_x_size/2));
                    morteiros[num_morteiros].setPos_y(cursor_y-(morteiro_y_size/2));
                    morteiros[num_morteiros].setProjetil_pos_y(cursor_y-(morteiro_y_size/2));
                    jogador.pagar(morteiros[num_morteiros].getPreco());
                    num_morteiros++;
                }
            } 
        }
        
        if(redraw && al_is_event_queue_empty(event_queue))
        {   
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            if(enter == 0){
                desenhar_menu();
                al_flip_display();
            }else{
                al_play_sample_instance(inst_trilha_sonora);
                al_draw_bitmap(mapa,0,0,0);
                desenhar_loja();
                Desenhar_inimigo();
                desenhar_defesas();
                desenhar_HUD();
                atirar_projeteis(num_frames);
            }
            al_flip_display();
        }
    }

    al_destroy_bitmap(mapa);
    al_destroy_bitmap(fundo_loja);
    al_destroy_bitmap(enemy);
    al_destroy_bitmap(icone_torre);
    al_destroy_bitmap(icone_morteiro);
    al_destroy_bitmap(tower);
    al_destroy_bitmap(morteiro);
    al_destroy_bitmap(jogador_HUD);
    al_destroy_bitmap(menu);
    al_destroy_bitmap(tela_game_over);
    al_destroy_font(vida_jogador);
    al_destroy_font(ouro_jogador);
    al_destroy_font(score_jogador);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_sample(trilha_sonora);

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

void desenhar_menu(){
    al_draw_bitmap(menu, 0, 0, 0);
}