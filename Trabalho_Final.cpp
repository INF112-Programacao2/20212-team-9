#include<iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

enum TECLAS
{
	CIMA, BAIXO, DIREITA, ESQUERDA
};

//variaveis globais  do jogo
const int SCREEN_W = 1000;		
const int SCREEN_H = 572;
const int BOUNCER_SIZE = 30;
const float FPS = 2;
float Ctr_tst = 0;
bool Fim = false;
bool desenhar = true;
bool desenhar_ponto = false;



int main(){
	//variaveis locais main
	ALLEGRO_EVENT_QUEUE *Fila_Eventos = NULL;
	int Pos_x = 0;
	int Pos_y = SCREEN_H/2 -BOUNCER_SIZE;
    ALLEGRO_BITMAP *Enemy = NULL;
	ALLEGRO_BITMAP *Mapa = NULL;
	ALLEGRO_TIMER *timer = NULL;
	bool teclas[] = {false, false, false, false};
	

	
	//INCIALIZACAO DA ALLEGRO
	ALLEGRO_DISPLAY *display = NULL;
	if(!al_init())
	{
		return -1;
	}		

	display = al_create_display(SCREEN_W, SCREEN_H);

	if(!display)
	{
		return -1;
	}	
	
	//INCIALIZACAO DE ADDONS E INSTALACOES
	al_install_keyboard();
	al_install_mouse();
	Enemy = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
	
	if(!al_init_image_addon())
    {
        cout <<"Falha ao iniciar al_init_image_addon!" << endl;
        return 0;
    }
	
	
	
	Mapa = al_load_bitmap("Mapa_Final_p.bmp");
	
	if(!Mapa){
		cout << "Failed to load map" << endl;
		return 0;
	}

	
	
	
	//cria o timer
	timer = al_create_timer(1.0 / FPS);
    
	if(!timer)
    {
		cout << "falha ao inicializar o timer" << endl;
        return -1;
    }

	al_start_timer(timer);

	//cria o Enemy
    al_set_target_bitmap(Enemy);                    
    al_clear_to_color(al_map_rgb(255, 0, 0));       
    al_set_target_bitmap(al_get_backbuffer(display));
	

	//CRIACAO DA FILA E DEMAIS DESPOSITIVOS
	Fila_Eventos = al_create_event_queue();

	//REGISTROS DE SOURCES
	al_register_event_source(Fila_Eventos, al_get_keyboard_event_source());
	al_register_event_source(Fila_Eventos, al_get_display_event_source(display));
    al_register_event_source(Fila_Eventos, al_get_keyboard_event_source());
	al_register_event_source(Fila_Eventos, al_get_mouse_event_source());
	al_register_event_source(Fila_Eventos, al_get_timer_event_source(timer));

	//LOOP PRINCIPAL
	while (!Fim)
	{
		ALLEGRO_EVENT ev;

		al_wait_for_event(Fila_Eventos, &ev);
		//EVENTOS E LOGICA DO JOGO
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				Fim = true;
			}
			
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_UP:
					teclas[CIMA] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					teclas[BAIXO] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					teclas[DIREITA] = true;
					break;
				case ALLEGRO_KEY_LEFT:
					teclas[ESQUERDA] = true;
					break;
			}

		}
		if(ev.type == ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_UP:
					teclas[CIMA] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					teclas[BAIXO] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					teclas[DIREITA] = false;
					break;
				case ALLEGRO_KEY_LEFT:
					teclas[ESQUERDA] = false;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			Fim = true;
		}
		/*
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
			Pos_x = ev.mouse.x;
			Pos_y = ev.mouse.y;
		}
		*/
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			if (ev.mouse.button & 1)
			{
				desenhar_ponto = true;

			}
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
			desenhar_ponto = false;
		}

		if(teclas[CIMA]){
			Pos_y -= teclas[CIMA] * 10;
		}
		else if(teclas[BAIXO]){
			Pos_y += teclas[BAIXO] * 10;
		}
		else if(teclas[DIREITA]){
			Pos_x += teclas[DIREITA] * 10;
		}
		else if(teclas[ESQUERDA]){
			Pos_x -= teclas[ESQUERDA] * 10;
		}

		//DESENHO
		al_draw_bitmap(Mapa, 0, 0, 0);
		al_draw_bitmap(Enemy, Pos_x, Pos_y, 0);
		if(desenhar_ponto){
			al_draw_pixel(ev.mouse.x, ev.mouse.y, al_map_rgb(255, 0, 0));
		}
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
		if(ev.type == ALLEGRO_EVENT_TIMER){
			cout << "timer" << endl;
			if(Pos_x <= SCREEN_W/2+10){
				Pos_x += BOUNCER_SIZE;
			}
			else if(Pos_x >= SCREEN_W/2 && Ctr_tst <= 3){
				Pos_y += BOUNCER_SIZE;
				Ctr_tst++;
			}
			else{
				Pos_x += BOUNCER_SIZE;
			}
		}
	}
	

	//FINALIZACOE DO PROGRAMA
	al_destroy_display(display);
	al_destroy_event_queue(Fila_Eventos);
	return 0;
}
