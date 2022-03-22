#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

enum MYKEYS
{
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

//Variáveis globais do jogo
const float FPS = 45;
const int SCREEN_W = 1200;
const int SCREEN_H = 572;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_BITMAP *mapa = NULL;

bool key[4] = { false, false, false, false };
bool redraw = true;
bool sair = false;
int cursor_x, cursor_y;
bool cima, baixo, esq, dir;

//Variáveis da loja
ALLEGRO_BITMAP *fundo_loja = NULL;
ALLEGRO_BITMAP *icone_torre1 = NULL;
ALLEGRO_BITMAP *tower1 = NULL;

const int pos_x_icone_torre1 = 1030;
const int pos_y_icone_torre1 = 25;

const int tower1_x_size = 82;
const int tower1_y_size = 208;

int pos_x_tower1;
int pos_y_tower1;

bool arrastar_torre = false;

int inicializar_allegro()
{
    if(!al_init())
    {
        std::cout << "Falha ao carregar Allegro" << std::endl;
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

//Torres
int coords_torres[10][2];
int num_torres = 0;

void desenhar_torres()
{
    for(int i=0; i<num_torres; i++)
    {
        al_draw_bitmap(tower1, coords_torres[i][0], coords_torres[i][1], 0);
    }
}

int main() {

    //Jogador j1(10, 100);

    if(!inicializar_allegro())
        return -1;

    while(!sair)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) 
            redraw = true;

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
            cursor_y<=pos_y_icone_torre1+190)
            {
                arrastar_torre = true;
            }

        }

        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && arrastar_torre)
        {
            if(ev.mouse.button)
            {
                arrastar_torre = false;
                if(cursor_x+(tower1_x_size/2) < 1000 /*Dimanesão x do mapa*/)
                {
                    coords_torres[num_torres][0] = cursor_x-(tower1_x_size/2);
                    coords_torres[num_torres][1] = cursor_y-(tower1_y_size/2);
                    num_torres++;
                }
            } 
        }

        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_bitmap(mapa,0,0,0);
            al_draw_bitmap(fundo_loja,1000,0,0);
            //al_convert_mask_to_alpha(icone_torre1, al_map_rgb(255, 255, 255));
            al_draw_bitmap(icone_torre1, pos_x_icone_torre1, pos_y_icone_torre1,0);

            if(arrastar_torre)
                al_draw_bitmap(tower1, cursor_x-(tower1_x_size/2), cursor_y-(tower1_y_size/2), 0);

            desenhar_torres();

            al_flip_display();
        }
    }

    al_destroy_bitmap(mapa);
    al_destroy_bitmap(fundo_loja);
    al_destroy_bitmap(icone_torre1);
    al_destroy_bitmap(tower1);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}