#include<iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

enum TECLAS
{
	CIMA, BAIXO, DIREITA, ESQUERDA
};

//variaveis globais  do jogo
const int SCREEN_W = 500;		
const int SCREEN_H = 500;
const int BOUNCER_SIZE = 30;
bool Fim = false;
bool desenhar = true;
bool desenhar_ponto = false;


int main(){
	//variaveis locais main
	ALLEGRO_EVENT_QUEUE *Fila_Eventos = NULL;
	int Pos_x = 100;
	int Pos_y = 100;
    ALLEGRO_BITMAP *square = NULL;
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
	square = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
	
	//cria o square
    al_set_target_bitmap(square);                    
    al_clear_to_color(al_map_rgb(255, 0, 0));       
    al_set_target_bitmap(al_get_backbuffer(display));

	//CRIACAO DA FILA E DEMAIS DESPOSITIVOS
	Fila_Eventos = al_create_event_queue();

	//REGISTROS DE SOURCES
	al_register_event_source(Fila_Eventos, al_get_keyboard_event_source());
	al_register_event_source(Fila_Eventos, al_get_display_event_source(display));
    al_register_event_source(Fila_Eventos, al_get_keyboard_event_source());
	al_register_event_source(Fila_Eventos, al_get_mouse_event_source());

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
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
			Pos_x = ev.mouse.x;
			Pos_y = ev.mouse.y;
		}
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
			if(desenhar_ponto){
				al_draw_pixel(ev.mouse.x, ev.mouse.y, al_map_rgb(255, 255, 255));
			}
			al_flip_display();
			//al_clear_to_color(al_map_rgb(0,0,0));
		
	}
	

	//FINALIZACOE DO PROGRAMA
	al_destroy_display(display);
	al_destroy_event_queue(Fila_Eventos); 
	return 0;
}
