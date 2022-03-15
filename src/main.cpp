#include<iostream>
#include <allegro5/allegro.h>
#include <cstdlib>
#include <ctime>
using namespace std;

enum MYKEYS
{
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

char MAPA[26][26] =
{
    "1111111111111111111111111",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1000000000000000001000001",
    "1000000000000000001000001",
    "1000000000000000001000001",
    "1000000000000000001000001",
    "1000000000000000001000001",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1000000000000000000000001",
    "1111111111111111111111111",
};
bool morreu = false;
bool esq = false;
//bool movecima = false;
bool dir = false;
bool cima = false;
bool baixo = false;
const float FPS = 5;
const int SCREEN_W = 500;		//constantes para facilitar os calculos
const int SCREEN_H = 500;
const int BOUNCER_SIZE = 20;
int fruit = 0;
int main(int argc, char **argv)
{	
	/*----------------geracao de valores aleatorios paras as frutas--------------*/
	unsigned seed = time(0);

    srand(seed);
    /*---------------------------------------------------------------------------*/
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *bouncer = NULL;
    ALLEGRO_BITMAP *snake = NULL;
    ALLEGRO_BITMAP *fruta = NULL;
    int fruta_x ;
    int fruta_y ;
	fruta_x =120; //definindo um valor fixo GUI
    fruta_y =120;//definindo um valor fixo GUI
    int snake_x = 240;
    int snake_y = 240;
    float bouncer_dx = 20.0;
    bool redraw = true;

    if(!al_init())
    {
        return -1;
    }
    
	if(!al_install_keyboard())
    {
        cout << "Falha ao inicializar o teclado" << endl;
        return 0;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        al_destroy_timer(timer);
        return -1;
    }

    bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);		//cria um bitmap 20 x 20
    snake = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE); //cria a cobra com os tamanhos da variavel bouncer size
    fruta = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);//cria a fruta com tamanho bouncersize
    if(!bouncer)
    {
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
	//cria o mapa
    al_set_target_bitmap(bouncer);                    //muda destino dos desenhos para o bitmap bouncer
    al_clear_to_color(al_map_rgb(255, 0, 255));       //limpa e colore de magenta
    al_set_target_bitmap(al_get_backbuffer(display)); //muda de volta o destino dos desenhos para o display
    //cria a cobra
    al_set_target_bitmap(snake);                    
    al_clear_to_color(al_map_rgb(255, 0, 0));       
    al_set_target_bitmap(al_get_backbuffer(display));
	
	
	
	
	al_set_target_bitmap(fruta);                    
	al_clear_to_color(al_map_rgb(255, 255, 255));       
	al_set_target_bitmap(al_get_backbuffer(display));
	
	

	
	
    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        al_destroy_bitmap(bouncer);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());


    al_clear_to_color(al_map_rgb(0,0,0));

    al_flip_display();

    al_start_timer(timer);
	int i, j;
    while(1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
		/*captura dos movimentos*/
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
            cima = true;
            baixo = false;
            esq = false;
            dir = false;
                break;

            case ALLEGRO_KEY_DOWN:
            cima = false;
            baixo = true;
            esq = false;
            dir = false;
                break;

            case ALLEGRO_KEY_LEFT:
            cima = false;
            baixo = false;
            esq = true;
            dir = false;
                break;

            case ALLEGRO_KEY_RIGHT:
            cima = false;
            baixo = false;
            esq = false;
            dir = true;
                break;
            }
        }
        /*fim da captura*/
        
        /*direita*/
        if(ev.type == ALLEGRO_EVENT_TIMER && dir && MAPA[snake_y/20][(snake_x/20) ] != '1')		//Atualiza posicao do bitmap a cada evento do temporizador
        {	
            snake_x += bouncer_dx;          //muda posicao
            redraw = true;
            if(ev.type == ALLEGRO_EVENT_TIMER && MAPA[snake_y/20][(snake_x/20)] == '1'){
    			morreu = true;
    			redraw = true;
			}
        }
        /*esquerda*/
        else if(ev.type == ALLEGRO_EVENT_TIMER && esq && MAPA[snake_y/20][(snake_x/20) ] != '1')		//Atualiza posicao do bitmap a cada evento do temporizador
        {	
            snake_x -= bouncer_dx;          //muda posicao
            redraw = true;
            if(ev.type == ALLEGRO_EVENT_TIMER && MAPA[snake_y/20][(snake_x/20) ] == '1'){
    			morreu = true;
    			redraw = true;
        	}
    	}
        /*cima*/
        else if(ev.type == ALLEGRO_EVENT_TIMER && cima && MAPA[(snake_y/20) ][(snake_x/20)] != '1')		//Atualiza posicao do bitmap a cada evento do temporizador
        {	
            snake_y -= bouncer_dx;          //muda posicao
            redraw = true;
            if(ev.type == ALLEGRO_EVENT_TIMER && MAPA[(snake_y/20) ][(snake_x/20)] == '1'){
    			morreu = true;
    			redraw = true;
        	}
        }
        /*baixo*/
        else if(ev.type == ALLEGRO_EVENT_TIMER && baixo && MAPA[(snake_y/20)][(snake_x/20)] != '1')		//Atualiza posicao do bitmap a cada evento do temporizador
        {	
            snake_y += bouncer_dx;          //muda posicao
            redraw = true;
            if(ev.type == ALLEGRO_EVENT_TIMER && MAPA[(snake_y/20) ][(snake_x/20)] == '1'){
    			morreu = true;
    			redraw = true;
        	}
        }
    	/*else if(ev.type == ALLEGRO_EVENT_TIMER && MAPA[snake_y/20][(snake_x/20) + 1] == '1'){
    		morreu = true;
    		redraw = true;
		}*/
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }

        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            al_clear_to_color(al_map_rgb(0,0,0));
            
			for(i =0; i<26; i++){
				for(j = 0; j<26; j++){
					if(MAPA[i][j] == '1'){
						al_draw_bitmap(bouncer, j*20, i*20, 0);
					}
				}
			}
				
			if(!morreu){
				al_draw_bitmap(snake, snake_x, snake_y, 0);
       }
        //<----------------devorando a fruta------------->
        	if(snake_y == fruta_y && snake_x == fruta_x){
        		fruit = 1;
				
				int tamanho; //vai ser adicionado ao tamanho da cobra
			
			}
			
			
			if(fruit==1 && morreu==false){ //gerando a frutinha denovo		
				fruta_x=rand()%24*20; //definindo uma nova coordenada paara frutax
				fruta_y=rand()%24*20;	//definindo uma nova coordenada paara frutax
				if(MAPA[(fruta_y/20) ][(fruta_x/20)]=='1'){ //se as coordenadas corresponderem a '1', vai fazer a redefiniÃ§Ã£o
					fruta_x=rand()%24*20;  //redefine as coordenadas x e y.
					fruta_y=rand()%24*20;
					
				}
				////////////////////////////re-setando a fruta com uma nova cor (descartavel)
				al_set_target_bitmap(fruta);                    
				al_clear_to_color(al_map_rgb(rand()%255,rand()%255, rand()%255));     // rand()%255,rand()%255, rand()%255
				al_set_target_bitmap(al_get_backbuffer(display));
				////////////////////////////
				fruit=0;
			}
			
			if(!fruit){
				al_draw_bitmap(fruta, fruta_x, fruta_y, 0);
			}
            al_flip_display();
        }
    }

    al_destroy_bitmap(bouncer);
    al_destroy_bitmap(snake);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
