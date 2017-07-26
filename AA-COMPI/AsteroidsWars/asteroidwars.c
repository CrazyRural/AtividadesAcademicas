#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	
	int tipo;
	SDL_Rect quadAsteroid;
	int destruido;
	int anguloAsteroid;
}ASTEROID;

typedef struct{
	
	SDL_Rect quadTiro;
	int ativo;
	int angulo_tiro;
}TIRO;

int colisao_nave(float x, float y, SDL_Rect B, SDL_Surface *C);
int colisao_tiro(SDL_Rect A, SDL_Rect B);
void retorna(float *x, float *y, float *vel, int *angle);
int geraAsteroidInicial(ASTEROID asteroides[]);
int destroiAsteroid(ASTEROID asteroides[], int soma, int contador);
int achar_vazio(ASTEROID asteroides[]);
void animacao(SDL_Rect gif[]);


int main(int argc,char** argv){

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	TTF_Font *fonte = TTF_OpenFont("fonts/Starjedi.ttf", 32);
	TTF_Font *fonte2 = TTF_OpenFont("fonts/Starjedi.ttf", 16);
	SDL_Surface *screen = SDL_SetVideoMode(800,600,16,SDL_SWSURFACE);

	srand(time(NULL));

	SDL_Surface *tela = IMG_Load("images/main-menu.png");
	SDL_Surface *recordes = IMG_Load("images/fundo-recordes.png");
	SDL_Surface *escolha = IMG_Load("images/lightsaber.png");
	SDL_Surface *perso = IMG_Load("images/menu-perso.png");
	SDL_Surface *escolha2 = IMG_Load("images/seletor2.png");

	
	SDL_Surface *fundo = IMG_Load("images/fundo.png");
	SDL_Surface *nave;
	SDL_Surface *tiro;
	SDL_Surface *explosao = IMG_Load("images/explosao.png");
	SDL_Surface *asteroid1 = IMG_Load("images/deathstar.png");
	SDL_Surface *asteroid2 = IMG_Load("images/deathstar2.png");
	SDL_Surface *asteroid3 = IMG_Load("images/tiefighter.png");
	SDL_Surface *vida = IMG_Load("images/r2d2vida.png");
	SDL_Surface *integrantes = IMG_Load("images/creditos.png");
	SDL_Surface *extralife = IMG_Load("images/r2d2.png");
	SDL_Surface *end = IMG_Load("images/gameover.png"); 
	SDL_Surface *pontuacao_ttf;
	SDL_Surface *tiros_ttf;
	SDL_Surface *recarga_ttf;
	SDL_Surface *nome_ttf;
	SDL_Surface *barra_ttf;
	
	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
	
	Mix_Music *theme = Mix_LoadMUS("sounds/SWT.mp3");
	Mix_Music *jogando = Mix_LoadMUS("sounds/SWMI.mp3");
	Mix_Chunk *choice = Mix_LoadWAV("sounds/LIGHTSABER2.wav");
	Mix_Chunk *shotsound = Mix_LoadWAV("sounds/bcfire02.wav");
	Mix_Chunk *explode = Mix_LoadWAV("sounds/explosao.wav");
	Mix_Chunk *choice2 = Mix_LoadWAV("sounds/ltsaberhit07.wav");
	Mix_Chunk *explode2 = Mix_LoadWAV("sounds/explo2.wav");
	Mix_Chunk *R2 = Mix_LoadWAV("sounds/R2-D2.wav");
	
	
	SDL_Rect quad = {0,0};
	SDL_Rect seletor = {40,225};
	
	SDL_Color color = {255, 255, 0};
	SDL_Rect pontuacao_recttf = {700, 0};
	SDL_Rect tiros_recttf = {10, 550};
	SDL_Rect recarga_recttf = {40, 570};
	SDL_Rect nome_recttf = {300, 425};
	SDL_Rect pontosfinais_recttf = {375, 300};
	SDL_Rect barra_recttf = {30, 550};
	
	int menu = 1;
	int record = 0;
	int running = 0;
	int menu_personagens = 0;
	int creditos = 0;
	char barra[10];
	barra[0] = '/';
	
	Mix_PlayMusic(theme, -1);
	
	int FPS = 30;
	Uint32 start;
	
	while(menu != 0){
		
		int selecao = 0;
		int selecao2 = 0;
		start = SDL_GetTicks();
		
		SDL_Rect quadPerso = {120, 485};
		
		SDL_Event event;
		
			
		while(SDL_PollEvent(&event)){
			
			switch(event.type){
				
				case SDL_QUIT:
					menu = 0;
					exit(1);
					break;

				case SDL_KEYDOWN:
				
					switch(event.key.keysym.sym){
					
						case SDLK_ESCAPE:
							menu = 0;
							exit(1);
							break;
							
						case SDLK_DOWN:
							if(seletor.y < 450)
								seletor.y += 75;
							else
								seletor.y = 225;
							break;
						
						case SDLK_UP:
							if(seletor.y > 225)
								seletor.y -= 75;
							else
								seletor.y = 450;
							break;
								
						case SDLK_RETURN:
							Mix_PlayChannel(-1, choice,0);
							selecao = 1;
							break;
							
						default:
							break;
					}
					
					default:
						break;
				}
			}
			
		if(selecao == 1){
			
			if(seletor.y == 225)
				menu_personagens = 1;
			else if(seletor.y == 300)
				record = 1;
			else if(seletor.y == 375)
				creditos = 1;
			else if(seletor.y == 450){
				menu = 0;
				exit(1);
			}
		}	
		
		while(menu_personagens == 1){
			
			SDL_Event event;
		
			while(SDL_PollEvent(&event)){
			
				switch(event.type){
				
					case SDL_QUIT:
						menu_personagens = 0;
						menu = 0;
						break;

					case SDL_KEYDOWN:
				
						switch(event.key.keysym.sym){
					
							case SDLK_ESCAPE:
								menu_personagens = 0;
								break;
								
							case SDLK_RIGHT:
								if(quadPerso.x < 620)
									quadPerso.x += 250;
								else
									quadPerso.x = 120;
								break;
								
							case SDLK_LEFT:
								if(quadPerso.x > 120)
									quadPerso.x -= 250;
								else
									quadPerso.x = 620;
								break;
									
							case SDLK_RETURN:
								selecao2 = 1;
								Mix_PlayChannel(-1, choice2,0);
							default:
								break;
					}
					default:
						break;
				}
			}
			
			if(selecao2 == 1){
				if(quadPerso.x == 120){
				
					nave = IMG_Load("images/yodaship.png");
					tiro = IMG_Load("images/tiroverde.png");
					running = 1;
					menu_personagens = 0;
					Mix_PlayMusic(jogando, -1);
				}
				else if(quadPerso.x == 370){
				
					nave = IMG_Load("images/anakinship.png");
					tiro = IMG_Load("images/tirovermelho.png");
					running = 1;
					menu_personagens = 0;
					Mix_PlayMusic(jogando, -1);
				}
				else if(quadPerso.x == 620){
				
					nave = IMG_Load("images/obiwanship.png");
					tiro = IMG_Load("images/tiroazul.png");
					running = 1;
					menu_personagens = 0;
					Mix_PlayMusic(jogando, -1);
				}
			}
			
				SDL_FillRect(screen,NULL,0);
			
				SDL_BlitSurface(perso, NULL, screen, &quad);
				SDL_BlitSurface(escolha2, NULL, screen, &quadPerso);	
			
				SDL_Flip(screen);
			
				SDL_Rect quadFundo = {0,0};
				SDL_Rect quadExplosao[25];
				SDL_Rect quadExplosao2;
				SDL_Rect quadVidas = {0,0};
				SDL_Rect r2d2;
				SDL_Rect quad_extra;
				r2d2.x = 0;
				r2d2.y = 0;
				r2d2.h = 30;
	
				animacao(quadExplosao);
	
				int i = 0;
				int escudo = 0;
				int vidas = 3;
				int game_over = 0;
	
				int contador = 0;
				int soma = 0;
				
				char nome_jogador[10];
				int posicao_nome = 0;
	
				ASTEROID asteroides[24];
				TIRO shot[5];

//*********************** Variáveis Asteroid ***************************
				srand(time(NULL));
				float asteroide_x;
				float asteroide_y;
	
//*********************** Ângulo e Teclas ******************************
				int vetor[3] = {0, 0, 0};
				int angle = 0;
	
//********************* Variáveis tiro *********************************
				int vel_tiro = 20;
				int limites_tiro = 0;
				int contador_tiro = 0;
				int recarga_tiro = 90;
				int armazena_tiro = 5;
				int center_nave_x;
				int center_nave_y; 
				char tiros_txt[10];
				char recarga_txt[10];
			
//******************** Variáveis Nave **********************************
				int angle_nave = 0;
				float x_inicial = 400;
				float y_inicial = 300;
				float vel = 0.0;
				float x = x_inicial;
				float y = y_inicial;
				int pontuacao = 0;
				int dead = 0;
				int gera_vida;
				int vida_extra = 0;
				char pontuacao_txt[10];
				
			for(contador = 0; contador < 10; contador++){
				
				nome_jogador[contador] = '\0';
				
			}
				
				
			soma = geraAsteroidInicial(asteroides);
	
			while(running != 0){
		
				start = SDL_GetTicks();
		
				SDL_Event event;
				
				sprintf(pontuacao_txt, "%i", pontuacao);
				sprintf(recarga_txt, "%i", recarga_tiro);
				sprintf(tiros_txt, "%i", armazena_tiro);
				
				
				pontuacao_ttf = TTF_RenderText_Blended(fonte, pontuacao_txt, color);
				tiros_ttf = TTF_RenderText_Blended(fonte, tiros_txt, color); 
				recarga_ttf = TTF_RenderText_Blended(fonte2, recarga_txt, color);
				barra_ttf = TTF_RenderText_Blended(fonte, barra, color);
				
				while(SDL_PollEvent(&event)){
					
					switch(event.type){
				
						case SDL_QUIT:
							running = 0;
							break;
				
						case SDL_KEYDOWN:
					
							switch(event.key.keysym.sym){
					
								case SDLK_ESCAPE:
									running = 0;
									break;
							
							case SDLK_UP:
								vetor[0] = 1;
								if(escudo == 1)
									escudo = 0;
								break;
							
							case SDLK_RIGHT:
								vetor[1] = 1;
								if(escudo == 1)
									escudo = 0;
								break;
							
							case SDLK_LEFT:
								vetor[2] = 1;
								if(escudo == 1)
									escudo = 0;
								break;
							
							case SDLK_SPACE:
								
								if(escudo == 1)
										escudo = 0;
										
								if(limites_tiro < 5){
									Mix_PlayChannel(-1, shotsound,0);
									shot[limites_tiro].ativo = 1;
									shot[limites_tiro].angulo_tiro = angle;
							
									shot[limites_tiro].quadTiro.x = center_nave_x;
									shot[limites_tiro].quadTiro.y = center_nave_y;
									armazena_tiro--;
									limites_tiro++;
								}
								break;
								
							case SDLK_LSHIFT:
								
								if(limites_tiro >= 5 && recarga_tiro > 0){
									
									recarga_tiro -= 5;
									limites_tiro = 0;
									armazena_tiro = 5;
								}
								break;
									
												
							default:
								break;
						}
						
						break;
					
					case SDL_KEYUP:
					
						switch(event.key.keysym.sym){
						
							case SDLK_UP:
								vetor[0] = 0;
								break;
						
							case SDLK_RIGHT:
								vetor[1] = 0;
								break;
								
							case SDLK_LEFT:
								vetor[2] = 0;
								break;
							
							default:
								break;
							}
							break;
				}				
			}
			
//***************************** Variáveis Vida *************************
			if(recarga_tiro == 0 && limites_tiro == 0){
				
				vidas--;
				recarga_tiro = 50;
			}
			
			if(vida_extra == 0 && vidas < 5){
				
				gera_vida = rand()%5000;
				if(gera_vida == 77 || gera_vida == 99 || gera_vida == 83 || gera_vida == 5 || gera_vida == 3 || gera_vida == 80){
					vida_extra = 1;
					quad_extra.x = 0;
					quad_extra.y = 550;
				}
			}
			
			if(vida_extra == 1){
				
				quad_extra.x += 12;
				quad_extra.y -= 9;
				
				if(quad_extra.x >=800 || quad_extra.y <= 0)
					vida_extra = 0;
			}
			
			if(vidas == 1){
				
				r2d2.w = 24;	
			}
			
			if(vidas == 2){
				
				r2d2.w = 48;	
			}
			if(vidas == 3){
				
				r2d2.w = 72;
			}
			
			if(vidas == 4){
				
				r2d2.w = 96;
			}	
			
			if(vidas == 5){
				
				r2d2.w = 120;
			}	
			
			if(vidas == 0){
				running = 0;
				game_over = 1;
			}
//************************ Aceleração **********************************
			if(vetor[0] == 1){
		// CIMA	
				angle_nave = angle;
			
				x -= sin(angle_nave * M_PI/180.0) * vel;
				y -= cos(angle_nave * M_PI/180.0) * vel;
			
				if(vel < 15)
					vel+= 3;
			
			}
		
			if(vetor[1] == 1){
		// DIREITA
		
				angle -= 7;
			}
		
		// 
			if(vetor[2] == 1){	
		// ESQUERDA
				angle += 7;
			}
		
//*********************** Desaceleração ********************************
			if(vetor[0] == 0){
				x -= sin(angle_nave * M_PI/180.0) * vel;
				y -= cos(angle_nave * M_PI/180.0) * vel;
		
				if(vel > 0)
					vel-=0.5;
			}	
			
				
			if(angle >= 360)
				angle -= 360;
				
			if (angle <= -360)
				angle += 360;

//*********************** Movimentação Asteroid ************************
			for(contador = 0; contador < 24; contador++){
			
				if(asteroides[contador].destruido == 0){
					asteroide_x = asteroides[contador].quadAsteroid.x;
					asteroide_y = asteroides[contador].quadAsteroid.y;
						
					asteroide_x -= (sin(asteroides[contador].anguloAsteroid * M_PI/180.0)*3.1);
					asteroide_y -= (cos(asteroides[contador].anguloAsteroid * M_PI/180.0)*3.1);
			            
					asteroides[contador].quadAsteroid.x = (int) asteroide_x;
					asteroides[contador].quadAsteroid.y = (int) asteroide_y;
			            
					if(asteroides[contador].quadAsteroid.x >= 800)
						asteroides[contador].quadAsteroid.x = 0;

					if(asteroides[contador].quadAsteroid.x < 0)
						asteroides[contador].quadAsteroid.x = 800 - asteroides[contador].quadAsteroid.w;
				
					if(asteroides[contador].quadAsteroid.y >= 600)
						asteroides[contador].quadAsteroid.y = 0;
								
					if(asteroides[contador].quadAsteroid.y < 0)
						asteroides[contador].quadAsteroid.y = 600 - asteroides[contador].quadAsteroid.h;
				}
			}
		
		
//********************** Rotação Nave *********************************
			SDL_Surface* rotadedimage = rotozoomSurface(nave, angle, 1.0, 0);
		
			SDL_Rect quadNave = {(int)x,(int)y,0,0};
			quadNave.x -= rotadedimage -> w/2 - nave -> w/2;
			quadNave.y -= rotadedimage -> h/2 - nave -> h/2;
			
//******************* Condição Tiro ***********************************
			
			
			for(contador_tiro = 0; contador_tiro < 5; contador_tiro++){
				
				if(shot[contador_tiro].ativo == 1){
			
					shot[contador_tiro].quadTiro.x -= sin(shot[contador_tiro].angulo_tiro * M_PI/180.0) * vel_tiro;
					shot[contador_tiro].quadTiro.y -= cos(shot[contador_tiro].angulo_tiro * M_PI/180.0) * vel_tiro;
				}
			}
	
			center_nave_x = quadNave.x + rotadedimage -> w/2;
			center_nave_y = quadNave.y + rotadedimage -> h/2;
		

//****************** Travessia Nave ************************************
				
			if(x < 0)
				x = 800 - rotadedimage -> w;								
	
			if(x >= 800)
				x = 0;
		
			if(y < 0)
				y = 600 - rotadedimage -> h;						
	
			if(y >= 600)
				y = 0;				
		
//********************* Colisão Asteroid - Tiro ************************
	
			for(contador = 0; contador < 24; contador++){
				
				for(contador_tiro = 0; contador_tiro < 5; contador_tiro++){	
					
					if((asteroides[contador].destruido == 0) && (colisao_tiro(shot[contador_tiro].quadTiro, asteroides[contador].quadAsteroid)) == 1 && shot[contador_tiro].ativo == 1){
					
						if(asteroides[contador].tipo == 8)
							pontuacao += 20;
						else if(asteroides[contador].tipo == 4)
							pontuacao += 40;
						else 
							pontuacao += 80;
						
						asteroides[contador].destruido = 1;
						soma = destroiAsteroid(asteroides, soma, contador);
						Mix_PlayChannel(-1, explode,0);
						shot[contador_tiro].ativo = 0;
					}
				}
			}	


//***************************** Colisão Asteroid - Nave ****************

			for(contador = 0; contador < 24; contador++){	
			
				if(asteroides[contador].destruido != 1 && colisao_nave(x, y, asteroides[contador].quadAsteroid, rotadedimage) == 1 && dead == 0 && escudo == 0){
					
					
					soma = destroiAsteroid(asteroides, soma, contador);
					vidas--;
					Mix_PlayChannel(-1, explode2,0);
					printf("1\n");
					dead = 1;
					escudo = 1;
					quadExplosao2.x = quadNave.x;
					quadExplosao2.y = quadNave.y;
				}
				
			}		

//***********************Colisão Nave - Vida ***************************

			if(colisao_nave(x, y, quad_extra, rotadedimage) == 1 && vida_extra == 1){
				Mix_PlayChannel(-1, R2, 0);
				vidas += 1;
				vida_extra = 0;	
			}
		
//******************* Blit Imagens *************************************
		
			SDL_FillRect(screen,NULL,0);
		
			SDL_BlitSurface(fundo, NULL, screen, &quadFundo);
		
		
			for( contador = 0; contador < 24; contador++){
			
				if(asteroides[contador].destruido == 0){
				
					if(asteroides[contador].tipo == 8)
						SDL_BlitSurface( asteroid1, NULL, screen, &asteroides[contador].quadAsteroid);
				
					if(asteroides[contador].tipo == 4)
						SDL_BlitSurface( asteroid2, NULL, screen, &asteroides[contador].quadAsteroid);
				
					if(asteroides[contador].tipo == 2)
						SDL_BlitSurface( asteroid3, NULL, screen, &asteroides[contador].quadAsteroid);
				}				
			}
		
			for(contador_tiro = 0; contador_tiro < 5; contador_tiro++){
				
				if(shot[contador_tiro].ativo == 1)
					SDL_BlitSurface(tiro, NULL, screen, &shot[contador_tiro].quadTiro);
			}
			if(dead == 0)
				SDL_BlitSurface(rotadedimage, NULL, screen, &quadNave);
		
			if(dead == 1){
			
				SDL_BlitSurface(explosao, &quadExplosao[i], screen, &quadExplosao2);
					i++;
				
				if(i == 25){
					dead = 0;
					i = 0;
					escudo = 1;
				
					retorna(&x, &y, &vel, &angle);
				}
			}
			if(vida_extra == 1)
				SDL_BlitSurface(extralife, NULL, screen, &quad_extra);
				
				
			SDL_BlitSurface(vida, &r2d2, screen, &quadVidas);
			
			SDL_BlitSurface(pontuacao_ttf, NULL, screen, &pontuacao_recttf);
			SDL_BlitSurface(tiros_ttf, NULL, screen, &tiros_recttf);
			SDL_BlitSurface(recarga_ttf, NULL, screen, &recarga_recttf);
			SDL_BlitSurface(barra_ttf, NULL, screen, &barra_recttf);
			
			SDL_Flip(screen);
			
			while(game_over == 1){
				
				SDL_Event event;
				
				nome_ttf = TTF_RenderText_Blended(fonte, nome_jogador, color);
	
				while(SDL_PollEvent(&event)){
			
					switch(event.type){
						
						case SDL_QUIT:
							game_over = 0;
							break;
				
						case SDL_KEYDOWN:
					
							switch(event.key.keysym.sym){
							
							case SDLK_ESCAPE:
								game_over = 0;
								break;
								
							case SDLK_RETURN:
								game_over = 0;
								
						
								break;	
							
							case SDLK_a:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'a';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_b:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'b';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_c:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'c';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_d:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'd';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_e:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'e';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_f:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'f';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_g:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'g';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_h:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'h';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_i:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'i';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_j:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'j';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_k:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'k';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_l:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'l';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_m:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'm';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_n:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'n';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_o:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'o';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_p:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'p';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_q:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'q';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_r:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'r';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_s:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 's';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_t:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 't';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_u:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'u';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_v:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'v';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_w:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'w';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_x:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'x';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_y:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'y';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_z:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'z';
									posicao_nome++;
								}
								
								break;
							
							case SDLK_BACKSPACE:
								
								if(posicao_nome > 0){
									
									posicao_nome--;
									nome_jogador[posicao_nome] = '\0';
									
								}
								
								break;
							
							default:
								break;
							
							}
						
						default:
							break;
					}
				
				
				}
				
				SDL_BlitSurface(end, NULL, screen, NULL);
				SDL_BlitSurface(pontuacao_ttf, NULL, screen, &pontosfinais_recttf);
				SDL_BlitSurface(nome_ttf, NULL, screen, &nome_recttf);
				
				SDL_Flip(screen);
			}
			
			if(running == 0){
				Mix_PlayMusic(theme, -1);
			}
//*********************** Controle de Frames ***************************
			if(1000/FPS > SDL_GetTicks() - start)
				SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
	
		}
			
			
			if(pontuacao != 0)
				printf("%d\n", pontuacao);
			
			
		
			if(1000/FPS > SDL_GetTicks() - start)
				SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
		}
		
		while(creditos == 1){
			
			SDL_Event event;
	
			while(SDL_PollEvent(&event)){
			
				switch(event.type){
				
					case SDL_QUIT:
						creditos = 0;
						menu = 0;
						break;

					case SDL_KEYDOWN:
				
						switch(event.key.keysym.sym){
					
							case SDLK_ESCAPE:
								creditos = 0;
								break;
							
							default:
								break;
					}
					default:
						break;
				
				}
			}
			SDL_FillRect(screen,NULL,0);
			
			SDL_BlitSurface(integrantes, NULL, screen, &quad);	
			
			SDL_Flip(screen);
		
			if(1000/FPS > SDL_GetTicks() - start)
				SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
		}
		
		
	
		while(record == 1){
			
			SDL_Event event;
	
			while(SDL_PollEvent(&event)){
			
				switch(event.type){
				
					case SDL_QUIT:
						record = 0;
						menu = 0;
						break;

					case SDL_KEYDOWN:
				
						switch(event.key.keysym.sym){
					
							case SDLK_ESCAPE:
								record = 0;
								break;
							
							default:
								break;
					}
					default:
						break;
				
				}
			}
			SDL_FillRect(screen,NULL,0);
			
			SDL_BlitSurface(recordes, NULL, screen, &quad);	
			SDL_Flip(screen);
		
			if(1000/FPS > SDL_GetTicks() - start)
				SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
		}
		
		SDL_FillRect(screen,NULL,0);
		
		SDL_BlitSurface(tela, NULL, screen, &quad);
		SDL_BlitSurface(escolha, NULL, screen, &seletor);
		
		SDL_Flip(screen);
		
		if(1000/FPS > SDL_GetTicks() - start)
			SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
	} 
		SDL_FreeSurface(screen);
		SDL_FreeSurface(tela);
		SDL_FreeSurface(recordes);
		SDL_FreeSurface(escolha);
		SDL_FreeSurface(perso);
		SDL_FreeSurface(escolha2);
		SDL_FreeSurface(fundo);
		SDL_FreeSurface(nave);
		SDL_FreeSurface(tiro);
		SDL_FreeSurface(explosao);
		SDL_FreeSurface(asteroid1);
		SDL_FreeSurface(asteroid2);
		SDL_FreeSurface(asteroid3);
		SDL_FreeSurface(vida);
		SDL_FreeSurface(integrantes);
		
		Mix_FreeMusic(theme);
		Mix_FreeMusic(jogando);
		Mix_FreeChunk(choice);
		Mix_FreeChunk(shotsound);
		Mix_FreeChunk(explode);
		Mix_FreeChunk(choice2);
		Mix_FreeChunk(explode2);
		Mix_FreeChunk(R2);
		
		Mix_CloseAudio();
		
		SDL_Quit();;
		
	return 0;
}

int colisao_nave(float x, float y, SDL_Rect B, SDL_Surface *C){

	int leftA = x; 
	int leftB = B.x;
	int rightA = x + C -> w;
	int rightB = B.x + B.w;
	int topA = y;
	int topB = B.y;
	int bottomA = y + C -> h; 
	int bottomB = B.y + B.h;
	
	if( topA >= bottomB)
		return 0;
	
	if(bottomA <= topB)
		return 0;
		
	if(rightA <= leftB)
		return 0;
		
	if(leftA >= rightB)
		return 0;
		
	return 1;	
}

int colisao_tiro(SDL_Rect A, SDL_Rect B){
	
	int leftA = A.x;
	int leftB = B.x;
	int rightA = A.x + A.w;
	int rightB = B.x + B.w;
	int topA = A.y;
	int topB = B.y;
	int bottomA = A.y + A.h;
	int bottomB = B.y + B.h;
	
	if( topA >= bottomB)
		return 0;
	
	if(bottomA <= topB)
		return 0;
		
	if(rightA <= leftB)
		return 0;
		
	if(leftA >= rightB)
		return 0;
		
	return 1;	
	
}

void retorna(float *x, float *y, float *vel, int *angle){
	
	*x = 400;
	*y = 300;
	*angle = 0;
	*vel = 0;
}

int geraAsteroidInicial(ASTEROID asteroides[]){
	
	int contador;
	int soma = 0;
	
		
	asteroides[0].quadAsteroid.x = 5;
	asteroides[0].quadAsteroid.y = 5;
	asteroides[0].anguloAsteroid = rand()%90 + 270;
	asteroides[0].tipo = 8;
	soma += asteroides[0].tipo;
	asteroides[0].destruido = 0;


	asteroides[1].quadAsteroid.x = 1;
	asteroides[1].quadAsteroid.y = 450;
	asteroides[1].anguloAsteroid = rand() % 90;
	asteroides[1].tipo = 8;
	soma += asteroides[1].tipo;
	asteroides[1].destruido = 0;
	
	
	asteroides[2].quadAsteroid.x = 650;
	asteroides[2].quadAsteroid.y = 1;
	asteroides[2].anguloAsteroid = rand()%90 + 180;
	asteroides[2].tipo = 8;
	soma += asteroides[2].tipo;
	asteroides[2].destruido = 0;
		
	asteroides[3].quadAsteroid.x = 650;
	asteroides[3].quadAsteroid.y = 450;
	asteroides[3].anguloAsteroid = rand()%90 + 90;
	asteroides[3].tipo = 8;
	soma += asteroides[3].tipo;
	asteroides[3].destruido = 0;
		
	
	for(contador = 4; contador < 24; contador++){
	
		asteroides[contador].tipo = 0;
		asteroides[contador].destruido = 1;
	}
	
	return soma;
}

int destroiAsteroid(ASTEROID asteroides[], int soma, int contador){
	
	int tipoDestruido;
	int tipoGerado;
	int posicao_x;
	int posicao_y;
	int posicao;
	int angulo;
	
	angulo = asteroides[contador].anguloAsteroid;

	tipoDestruido = asteroides[contador].tipo;
	
	soma -= tipoDestruido;
	
	asteroides[contador].destruido = 1;
	asteroides[contador].tipo = 0;
	
	posicao_x = asteroides[contador].quadAsteroid.x;
	posicao_y = asteroides[contador].quadAsteroid.y;
	
	tipoGerado = tipoDestruido/2;
	
	if(tipoDestruido != 2){

			contador = achar_vazio(asteroides);
			asteroides[contador].destruido = 0;
			asteroides[contador].tipo = tipoGerado;
			asteroides[contador].quadAsteroid.x = posicao_x;
			asteroides[contador].quadAsteroid.y = posicao_y;
			asteroides[contador].anguloAsteroid = angulo + 90;
			soma += tipoGerado;
			
			contador = achar_vazio(asteroides);
			asteroides[contador].destruido = 0;
			asteroides[contador].tipo = tipoGerado;
			asteroides[contador].quadAsteroid.x = posicao_x;
			asteroides[contador].quadAsteroid.y = posicao_y;
			asteroides[contador].anguloAsteroid = angulo + 180;
			soma += tipoGerado;
	}
	
	if(soma <= 16){
		
		while(soma < 24){

			contador = achar_vazio(asteroides);
			posicao = rand()%4;
		
			if(posicao == 0){
			
				asteroides[contador].quadAsteroid.x = 0;
				asteroides[contador].quadAsteroid.y = 0;
			
				asteroides[contador].anguloAsteroid = 290;
			}
			if(posicao == 1){
			
				asteroides[contador].quadAsteroid.x = 0;
				asteroides[contador].quadAsteroid.y = 450;
			
				asteroides[contador].anguloAsteroid = 45;
			}
			if(posicao == 2){
			
				asteroides[contador].quadAsteroid.x = 650;
				asteroides[contador].quadAsteroid.y = 0;
				
				asteroides[contador].anguloAsteroid = 230;
			}
			if(posicao == 3){
			
				asteroides[contador].quadAsteroid.x = 650;
				asteroides[contador].quadAsteroid.y = 450;
			
				asteroides[contador].anguloAsteroid = 135;
			}
			
			asteroides[contador].destruido = 0;
			asteroides[contador].tipo = 8;
			soma += 8;
		}
	 }
	
	return soma;
}

int achar_vazio(ASTEROID asteroides[]){
	
	int i;	
	
	for(i = 0; i < 24; i++){
		
		if(asteroides[i].destruido == 1)
			return i;
	}
	
	return i;
}

void animacao(SDL_Rect gif[]){
	
	int i;
	
	for(i = 0; i < 25; i++){
		
		gif[i].h = 64;
		gif[i].w = 64;
	}
	
	gif[0].x = 0;
	gif[0].y = 0;
	
	gif[1].x = 64;
	gif[1].y = 0;
	
	gif[2].x = 128;
	gif[2].y = 0;
	
	gif[3].x = 192;
	gif[3].y = 0;
	
	gif[4].x = 256;
	gif[4].y = 0;
	
	gif[5].x = 0;
	gif[5].y = 64;
	
	gif[6].x = 64;
	gif[6].y = 64;
	
	gif[7].x = 128;
	gif[7].y = 64;
	
	gif[8].x = 192;
	gif[8].y = 64;
	
	gif[9].x = 256;
	gif[9].y = 64;
	
	gif[10].x = 0;
	gif[10].y = 128;
	
	gif[11].x = 64;
	gif[11].y = 128;
	
	gif[12].x = 128;
	gif[12].y = 128;
	
	gif[13].x = 192;
	gif[13].y = 128;
	
	gif[14].x = 256;
	gif[14].y = 128;
	
	gif[15].x = 0;
	gif[15].y = 192;
	
	gif[16].x = 64;
	gif[16].y = 192;
	
	gif[17].x = 128;
	gif[17].y = 192;
	
	gif[18].x = 192;
	gif[18].y = 192;
	
	gif[19].x = 256;
	gif[19].y = 192;
	
	gif[20].x = 0;
	gif[20].y = 256;
	
	gif[21].x = 64;
	gif[21].y = 256;
	
	gif[22].x = 128;
	gif[22].y = 256;
	
	gif[23].x = 192;
	gif[23].y = 256;
	
	gif[24].x = 256;
	gif[24].y = 256;
}
