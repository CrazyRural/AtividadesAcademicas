#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

#define TRUE  1
#define FALSE 0

#define MAX_ARRAY 10
#define MAX_NOME 50

SDL_Surface* ttf[10][3];

SDL_Surface *screen;

typedef struct
{
    char nome[MAX_NOME];
    int pontuacao;
} RECORDE;

typedef struct
{
    RECORDE vetor[MAX_ARRAY];
    int n;

} ARRAY;

RECORDE elemento(ARRAY *, int);
int tamanho(ARRAY *);
void insere(ARRAY *, RECORDE);

void remove_posicao(ARRAY *, int);
void imprime(ARRAY *,TTF_Font *,SDL_Color);
void sort(ARRAY *);
void bubble_sort(RECORDE *, int);

int tempo = 0;
int vida = 0;

int colisao(SDL_Rect quad1, SDL_Rect quad2)
{
	 if(quad2.x + quad2.w < quad1.x) 
	    return 0;
	 if(quad2.x > quad1.x + quad1.w) 
	    return 0;
	 if(quad2.y + quad2.h < quad1.y) 
	    return 0;
	 if(quad2.y > quad1.y + quad1.h) 
	    return 0;

	 return 1; 
}

typedef struct explosao{
        
        SDL_Rect rect;
        int ativa;
        
}Explosao;

typedef struct bomba{

       SDL_Rect destbomba;
       int ativa;
       int colocar;
       Explosao cima[2];
       Explosao baixo[2];
       Explosao esquerda[2];
       Explosao direita[2];
       
}Bomba;

int main(int argc,char** argv){

	char *nome_arquivo = "recordes.dat";
	FILE *p_arquivo;

	ARRAY array;
	array.n = 0;

	time_t inicio, fim2;

	RECORDE reco1;

	SDL_Init(SDL_INIT_EVERYTHING);

	if(TTF_Init() == -1)
    	{
        	return -1;
    	}
	
	screen = SDL_SetVideoMode(1280,720,16,SDL_SWSURFACE);
	
	SDL_WM_SetCaption("The Simpsons : Donutsman",NULL);	
	
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	
	SDL_Surface *tela = IMG_Load("menu.png");
	SDL_Surface *recordes = IMG_Load("recordes.png");
	SDL_Surface *escolha = IMG_Load("seletor.png");
	SDL_Surface *creditos = IMG_Load("creditos.png");
	
	SDL_Surface *bombaimagem = IMG_Load( "bomba3.png" );
	SDL_Surface *fundo = IMG_Load( "fundo.png" );
	SDL_Surface *barradireita = IMG_Load( "barravertical.png" );
	SDL_Surface *barraesquerda = IMG_Load( "barravertical.png" );
	SDL_Surface *barrasuperior = IMG_Load( "barrahorizontal.png" );
	SDL_Surface *barrainferior = IMG_Load( "barrahorizontal.png" );
	SDL_Surface *parede = IMG_Load( "parede.png" );
	SDL_Surface *parederemovivel2 = IMG_Load( "parederemovivel2.png" );
	SDL_Surface *parederemovivel1 = IMG_Load( "parederemovivel1.png" );

	SDL_Surface* ttf;
	SDL_Surface* ttfvida;
	SDL_Surface* ttftraco;
	SDL_Surface* dignome;
	SDL_Surface* ttfnome;
	SDL_Surface* gameover;
	SDL_Surface* sair1 = NULL;

	sair1 = IMG_Load("sair1.png");

	SDL_Surface *cabecalho = IMG_Load( "cabecalho.png" );
	
	SDL_Surface *down1 = IMG_Load( "P1down1.png" );

	SDL_Surface *down2 = IMG_Load( "P1down2.png" );

	SDL_Surface *down3  = IMG_Load( "P1down3.png" );

	SDL_Surface *down4  = IMG_Load( "P1down4.png" );

	SDL_Surface *down5  = IMG_Load( "P1down5.png" );

	SDL_Surface *down6  = IMG_Load( "P1down6.png" );

	SDL_Surface *down7  = IMG_Load( "P1down7.png" );

	SDL_Surface *down8 = IMG_Load( "P1down8.png" );

	SDL_Surface *parado  = IMG_Load( "parado.png" );

	SDL_Surface *left1  = IMG_Load( "P1left1.png" );

	SDL_Surface *left2  = IMG_Load( "P1left2.png" );

	SDL_Surface *left3  = IMG_Load( "P1left3.png" );

	SDL_Surface *left4  = IMG_Load( "P1left4.png" );

	SDL_Surface *left5  = IMG_Load( "P1left5.png" );

	SDL_Surface *left6 = IMG_Load( "P1left6.png" );

	SDL_Surface *right1 = IMG_Load( "P1right1.png" );

	SDL_Surface *right2 = IMG_Load( "P1right2.png" );

	SDL_Surface *right3 = IMG_Load( "P1right3.png" );

	SDL_Surface *right4 = IMG_Load( "P1right4.png" );

	SDL_Surface *right5 = IMG_Load( "P1right5.png" );

	SDL_Surface *right6 = IMG_Load( "P1right6.png" );
	
	SDL_Surface *centro1 = IMG_Load( "centro1.png" );

	SDL_Surface *cima1 = IMG_Load( "cima1.png" );

	SDL_Surface *baixo1 = IMG_Load( "baixo1.png" );

	SDL_Surface *direita1 = IMG_Load( "direita1.png" );

	SDL_Surface *esquerda1 = IMG_Load( "esquerda1.png" );

	SDL_Surface *buraco = IMG_Load( "buraco.png" );

	SDL_Surface *monstro1 = IMG_Load( "monstro1.png" );

	SDL_Surface *monstro3 = IMG_Load( "monstro3.png" );

	SDL_Surface *tempo4;

	dignome = IMG_Load( "dignome.png" );
	gameover = IMG_Load( "gameover.png" );
	
	Mix_Music *theme = Mix_LoadMUS("SIMPT.mp3");
	Mix_Chunk *choice = Mix_LoadWAV("DOH.wav");
	Mix_Music *jogando = Mix_LoadMUS("TSIMPT.mp3");
	
		
	
	int i,j;
	int numpad[37];
	int bombax;
	int bombay;
	int buracox;
	int buracoy;
	int monstro10x;
	int monstro10y;
	int monstro20x;
	int monstro20y;
	int monstro30x;
	int monstro30y;
	int monstro40x;
	int monstro40y;
	int monstro50x;
	int monstro50y;
	int n;
	int fase = 0;
	int contdown = 0;
	int contleft = 0;
	int contright = 0;
	int k = 0;
	int lol = 0;
	int colide = 0;
	int xpad = 82;
	int ypad = 82;
	int vetor1[37] = {3,7,11,13,17,20,21,24,29,30,34,36,38,40,42,43,47,50,52,54,61,63,70,73,75,79,80,83,87,90,94,99,102,105,110,107,112};
	int vetor2[37] = {4,6,8,12,14,15,16,18,19,23,25,27,28,31,32,37,38,45,46,50,51,62,64,71,72,74,81,82,90,91,92,95,97,100,103,106,110};
	int vetor3[37] = {3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,60,63,66,69,72,75,79,81,84,87,90,93,96,99,102,105,108,111};

    SDL_Rect quade  = {81,81};
    SDL_Rect bomb = {2000,2000};
	SDL_Rect buracoo;
    
    int passo = 1;
    int incx  = 0;
    int incy  = 0;
	int mov1 = 1;
	int mov2 = 1;
	int mov3 = 1;
	int mov4 = 1;
	int mov5 = 1;

	int x;
	int y;
	int bombx;
	int bomby;
	int casa;
	int FPS = 30;
	int credits = 0;
	int record = 0;
	int jogar = 0;
	int menu = 1;


	SDL_Rect barra1 = {40,40};
	SDL_Rect barra2 = {80,40};
	SDL_Rect barra3 = {600,40};
	SDL_Rect barra4 = {80,520};

	SDL_Rect fogocima;
	SDL_Rect fogobaixo;
	SDL_Rect fogocentro;
	SDL_Rect fogodireita;
	SDL_Rect fogoesquerda;
	SDL_Rect recttf = {160, 8, 0, 0};

	SDL_Rect monstro10;
	SDL_Rect monstro20;
	SDL_Rect monstro30;
	SDL_Rect monstro40;
	SDL_Rect monstro50;
	SDL_Rect reccabecalho = {40,0};
	SDL_Rect vid = {100,8};
	SDL_Rect tempo3 = {380,600};

	SDL_Rect paredee[30];

	paredee[0].x = 120;
	paredee[0].y = 120;
	paredee[1].x = 120;
	paredee[1].y = 200;
	paredee[2].x = 120;
	paredee[2].y = 280;
	paredee[3].x = 120;
	paredee[3].y = 360;
	paredee[4].x = 120;
	paredee[4].y = 440;
	paredee[5].x = 200;
	paredee[5].y = 120;
	paredee[6].x = 200;
	paredee[6].y = 200;
	paredee[7].x = 200;
	paredee[7].y = 280;
	paredee[8].x = 200;
	paredee[8].y = 360;
	paredee[9].x = 200;
	paredee[9].y = 440;
	paredee[10].x = 280;
	paredee[10].y = 120;
	paredee[11].x = 280;
	paredee[11].y = 200;
	paredee[12].x = 280;
	paredee[12].y = 280;
	paredee[13].x = 280;
	paredee[13].y = 360;
	paredee[14].x = 280;
	paredee[14].y = 440;
	paredee[15].x = 360;
	paredee[15].y = 120;
	paredee[16].x = 360;
	paredee[16].y = 200;
	paredee[17].x = 360;
	paredee[17].y = 280;
	paredee[18].x = 360;
	paredee[18].y = 360;
	paredee[19].x = 360;
	paredee[19].y = 440;
	paredee[20].x = 440;
	paredee[20].y = 120;
	paredee[21].x = 440;
	paredee[21].y = 200;
	paredee[22].x = 440;
	paredee[22].y = 280;
	paredee[23].x = 440;
	paredee[23].y = 360;
	paredee[24].x = 440;
	paredee[24].y = 440;
	paredee[25].x = 520;
	paredee[25].y = 120;
	paredee[26].x = 520;
	paredee[26].y = 200;
	paredee[27].x = 520;
	paredee[27].y = 280;
	paredee[28].x = 520;
	paredee[28].y = 360;
	paredee[29].x = 520;
	paredee[29].y = 440;

	SDL_Rect padremov[113];

	SDL_Rect rec1;
	rec1.x = 200;
	rec1.y = 50;
	SDL_Rect rec5;
	rec5.x = 340;
	rec5.y = 410;
	SDL_Rect rec6;
	rec6.x = 340;
	rec6.y = 480;
	SDL_Rect recdig;
	recdig.x = 200;
	recdig.y = 340;

	SDL_Color cor = {255, 0, 0};

	TTF_Font *fonte;
	TTF_Font *fontenome;

	fonte = TTF_OpenFont("fonte.ttf", 20);
	fontenome = TTF_OpenFont("fonte.ttf", 40);
	TTF_SetFontStyle(fonte, TTF_STYLE_ITALIC);
	


    	Bomba bomba;

	for(i = 0;i < 6;i++)
	{
		for(j = 0;j<13;j++)
		{
			padremov[k].x = xpad;
			padremov[k].y = ypad;
			padremov[k].w = 40;
			padremov[k].h = 40;
			xpad += 40;
			k++;
		}
		xpad = 82;
		ypad += 80;
	}
	
	xpad = 82;
	ypad = 122;

	for(i = 0;i < 5;i++)
	{
		for(j = 0;j < 7;j++)
		{
			padremov[k].x = xpad;
			padremov[k].y = ypad;
			padremov[k].w = 40;
			padremov[k].h = 40;
			xpad += 80;
			k++;
		}
		xpad = 82;
		ypad += 80;
	}

	srand(time(NULL));
	n = rand()%3;

	printf("n = %d\n",n);

	if(n == 0)
	{
		monstro10x = padremov[14].x;
		monstro10y = padremov[14].y;		

		monstro10.x = monstro10x;
		monstro10.y = monstro10y;

		monstro20x = padremov[22].x;
		monstro20y = padremov[22].y;		

		monstro20.x = monstro20x;
		monstro20.y = monstro20y;

		monstro30x = padremov[31].x;
		monstro30y = padremov[31].y;		

		monstro30.x = monstro30x;
		monstro30.y = monstro30y;

		monstro40x = padremov[44].x;
		monstro40y = padremov[44].y;		

		monstro40.x = monstro40x;
		monstro40.y = monstro40y;

		monstro50x = padremov[55].x;
		monstro50y = padremov[55].y;		

		monstro50.x = monstro50x;
		monstro50.y = monstro50y;
	}

	if(n == 1)
	{
		monstro10x = padremov[9].x;
		monstro10y = padremov[9].y;		

		monstro10.x = monstro10x;
		monstro10.y = monstro10y;

		monstro20x = padremov[21].x;
		monstro20y = padremov[21].y;		

		monstro20.x = monstro20x;
		monstro20.y = monstro20y;

		monstro30x = padremov[33].x;
		monstro30y = padremov[33].y;		

		monstro30.x = monstro30x;
		monstro30.y = monstro30y;

		monstro40x = padremov[39].x;
		monstro40y = padremov[39].y;		

		monstro40.x = monstro40x;
		monstro40.y = monstro40y;

		monstro50x = padremov[65].x;
		monstro50y = padremov[65].y;		

		monstro50.x = monstro50x;
		monstro50.y = monstro50y;
	}

	if(n == 2)
	{
		monstro10x = padremov[10].x;
		monstro10y = padremov[10].y;		

		monstro10.x = monstro10x;
		monstro10.y = monstro10y;

		monstro20x = padremov[22].x;
		monstro20y = padremov[22].y;		

		monstro20.x = monstro20x;
		monstro20.y = monstro20y;

		monstro30x = padremov[34].x;
		monstro30y = padremov[34].y;		

		monstro30.x = monstro30x;
		monstro30.y = monstro30y;

		monstro40x = padremov[49].x;
		monstro40y = padremov[49].y;		

		monstro40.x = monstro40x;
		monstro40.y = monstro40y;

		monstro50x = padremov[67].x;
		monstro50y = padremov[67].y;		

		monstro50.x = monstro50x;
		monstro50.y = monstro50y;
	}

	for(i = 0;i < 37;i++)
	{
		if(n == 0)
		numpad[i] = vetor1[i];

		if(n == 1)
		numpad[i] = vetor2[i];

		if(n == 2)
		numpad[i] = vetor3[i];
		
	}

	bomba.ativa = 1;
			
	SDL_Rect quad = {0,0};
	SDL_Rect seletor = {200,140};

	casa = rand()%37;
	
	
	Uint32 start;
	Mix_PlayMusic(theme, 1);

	SDL_Event event;	
	
	while(menu != FALSE)
	{
	
		char nome1[10];
		int w = 0;
		char letra[10];
		int selecao = 0;
		int fim = 0;
		int pontuacao1 = 0;
		char vidaa[10];
		int vidda;
		char tempo5[10];
		int tempo2 = 0;
	if(n == 0)
	{
		monstro10x = padremov[14].x;
		monstro10y = padremov[14].y;		

		monstro10.x = monstro10x;
		monstro10.y = monstro10y;

		monstro20x = padremov[22].x;
		monstro20y = padremov[22].y;		

		monstro20.x = monstro20x;
		monstro20.y = monstro20y;

		monstro30x = padremov[31].x;
		monstro30y = padremov[31].y;		

		monstro30.x = monstro30x;
		monstro30.y = monstro30y;

		monstro40x = padremov[44].x;
		monstro40y = padremov[44].y;		

		monstro40.x = monstro40x;
		monstro40.y = monstro40y;

		monstro50x = padremov[55].x;
		monstro50y = padremov[55].y;		

		monstro50.x = monstro50x;
		monstro50.y = monstro50y;
	}

	if(n == 1)
	{
		monstro10x = padremov[9].x;
		monstro10y = padremov[9].y;		

		monstro10.x = monstro10x;
		monstro10.y = monstro10y;

		monstro20x = padremov[21].x;
		monstro20y = padremov[21].y;		

		monstro20.x = monstro20x;
		monstro20.y = monstro20y;

		monstro30x = padremov[33].x;
		monstro30y = padremov[33].y;		

		monstro30.x = monstro30x;
		monstro30.y = monstro30y;

		monstro40x = padremov[39].x;
		monstro40y = padremov[39].y;		

		monstro40.x = monstro40x;
		monstro40.y = monstro40y;

		monstro50x = padremov[65].x;
		monstro50y = padremov[65].y;		

		monstro50.x = monstro50x;
		monstro50.y = monstro50y;
	}

	if(n == 2)
	{
		monstro10x = padremov[10].x;
		monstro10y = padremov[10].y;		

		monstro10.x = monstro10x;
		monstro10.y = monstro10y;

		monstro20x = padremov[22].x;
		monstro20y = padremov[22].y;		

		monstro20.x = monstro20x;
		monstro20.y = monstro20y;

		monstro30x = padremov[34].x;
		monstro30y = padremov[34].y;		

		monstro30.x = monstro30x;
		monstro30.y = monstro30y;

		monstro40x = padremov[49].x;
		monstro40y = padremov[49].y;		

		monstro40.x = monstro40x;
		monstro40.y = monstro40y;

		monstro50x = padremov[67].x;
		monstro50y = padremov[67].y;		

		monstro50.x = monstro50x;
		monstro50.y = monstro50y;
	}
		
		for(j = 0;j < 10;j++)
		{
			nome1[w] = ' ';
		}
		
		while(SDL_PollEvent(&event))
		{
					
			switch(event.type)
			{
				
				case SDL_QUIT:
					
					menu = FALSE;
					break;

				case SDL_KEYDOWN:
				
					switch(event.key.keysym.sym)
					{
					
						case SDLK_ESCAPE:
							
							menu = FALSE;
							break;
							
						case SDLK_DOWN:
							if(seletor.y < 320)
								seletor.y += 90;
							else
								seletor.y = 140;
							break;
						
						case SDLK_UP:
							if(seletor.y > 140)
								seletor.y -= 90;
							else
								seletor.y = 320;
							break;
								
						case SDLK_RETURN:
							selecao = TRUE;
							break;
							
						default:
							break;
					}
						default:
						break;
				}
			}
			
		if(selecao == TRUE)
		{
			
			if(seletor.y == 140)
			{
				Mix_PlayChannel(-1,choice,1);
				inicio= time(NULL);
				jogar = TRUE;
				}
			else if(seletor.y == 230)
			{
				record = TRUE;
			}
			else if(seletor.y == 320)
				credits = TRUE;	
		}	
		
	while (jogar == 1 )
    {
	start=SDL_GetTicks();
       
        while(SDL_PollEvent(&event))
        {
              
              if (event.type == SDL_QUIT)
	      {
					jogar = FALSE; 
					menu = FALSE;
					break ;
              } 		
              else if( event.type == SDL_KEYDOWN )
              {
                  
			switch( event.key.keysym.sym )
                   {
                      
                      case SDLK_UP:
                           incy = -passo;
				contdown = 0;
                           break;
                      case SDLK_DOWN:
                           incy = passo;
				contdown = 0;
                           break;
                      case SDLK_LEFT: 
                           incx = -passo;
				contdown = 0;
                           break;
                      case SDLK_RIGHT:
                           incx = passo;
				contdown = 0;
                           break;
				case SDLK_ESCAPE:
				jogar  = FALSE;
				menu = TRUE;
				vida = 0;
				srand(time(NULL));
				n = rand()%3;
				casa = rand()%37;

				for(i = 0;i < 37;i++)
				{
					if(n == 0)
					numpad[i] = vetor1[i];

					if(n == 1)
					numpad[i] = vetor2[i];

					if(n == 2)
					numpad[i] = vetor3[i];
		
				}

				bomb.x = 2000;
				bomb.y = 2000;
				quade.x = 81;
				quade.y = 81;
				bomba.ativa = 1;
				lol = 0;
				fase = 0;
				mov1 = 1;
				mov2 = 1;
				mov3 = 1;
				mov4 = 1;
				mov5 = 1;
				break;
			case SDLK_SPACE:
			if(bomba.ativa != 2)
			{
				bomba.colocar = 1;
				
			}
                    break;
			default:
				break;
                   }

 
               } 
               else if( event.type == SDL_KEYUP )
              {
			switch( event.key.keysym.sym )
			{
		              case SDLK_UP:
		                   incy = 0;
		                   break;
		              case SDLK_DOWN:
		                   incy = 0;
		                   break;
		              case SDLK_LEFT:
		                   incx = 0;
		                   break;
		              case SDLK_RIGHT: 
		                   incx = 0;
		                   break;
				default:
				break;
			}
              }
        }

	fim2 = time(NULL);
	printf("tempo = %.2f\n",difftime(inicio,fim2)+180);
	if(difftime(inicio,fim2)+(180) == 0)
	{
		fim = 1;
		vida = 0;
		srand(time(NULL));
		n = rand()%3;
		casa = rand()%37;

		for(i = 0;i < 37;i++)
		{
			if(n == 0)
			numpad[i] = vetor1[i];

			if(n == 1)
			numpad[i] = vetor2[i];

			if(n == 2)
			numpad[i] = vetor3[i];
		
		}

		bomb.x = 2000;
		bomb.y = 2000;
		quade.x = 81;
		quade.y = 81;
		bomba.ativa = 1;
		lol = 0;
		fase = 0;
		mov1 = 1;
		mov2 = 1;
		mov3 = 1;
		mov4 = 1;
		mov5 = 1;
	}

	if(vida == 0)
	{
		vidda = 3;
	}
	if(vida == 1)
	{
		vidda = 2;
	}
	if(vida == 2)
	{
		vidda = 1;
	}

	sprintf(letra,"%i",pontuacao1);

	ttf = TTF_RenderText_Blended(fonte, letra, cor);

	sprintf(vidaa,"%i",vidda);

	ttfvida = TTF_RenderText_Blended(fonte, vidaa, cor);

	if(fase == 2)
	{
		jogar  = FALSE;
		menu = TRUE;
		vida = 0;
		srand(time(NULL));
		n = rand()%3;
		casa = rand()%37;

		for(i = 0;i < 37;i++)
		{
			if(n == 0)
			numpad[i] = vetor1[i];

			if(n == 1)
			numpad[i] = vetor2[i];

			if(n == 2)
			numpad[i] = vetor3[i];
		
		}

		bomb.x = 2000;
		bomb.y = 2000;
		quade.x = 81;
		quade.y = 81;
		bomba.ativa = 1;
		lol = 0;
		fase = 0;
	}

	if(mov1 == 1)
	{
		monstro10.x += 2;
		for(i = 0;i < 37;i++)
		{
			if(colisao(monstro10, padremov[numpad[i]]) == 1)
			{
			mov1 = 2;
			}

			else if(colisao(monstro10, barra3) == 1)
			{
			mov1 = 2;
			}
		}

		if(colisao(monstro10, bomb) == 1)
		{
		mov1 = 0;
		}
	}

	if(mov1 == 2)
	{
		monstro10.x -= 2;
		for(i = 0;i < 37;i++)
		{
			if(colisao(monstro10, padremov[numpad[i]]) == 1)
			{
			mov1 = 1;
			}

			else if(colisao(monstro10, barra1) == 1)
			{
			mov1 = 1;
			}
		}

		if(colisao(monstro10, bomb) == 1)
		{
		mov1 = 1;
		}
	}

	if(mov2 == 1)
	{
		monstro20.x += 2;
		for(i = 0;i < 37;i++)
		{
			if(colisao(monstro20, padremov[numpad[i]]) == 1)
			{
			mov2 = 2;
			}

			else if(colisao(monstro20, barra3) == 1)
			{
			mov2 = 2;
			}
		}

		if(colisao(monstro20, bomb) == 1)
		{
		mov2 = 0;
		}
	}

	if(mov2 == 2)
	{
		monstro20.x -= 2;
		for(i = 0;i < 37;i++)
		{
			if(colisao(monstro20, padremov[numpad[i]]) == 1)
			{
			mov2 = 1;
			}

			else if(colisao(monstro20, barra1) == 1)
			{
			mov2 = 1;
			}
		}

		if(colisao(monstro20, bomb) == 1)
		{
		mov2 = 1;
		}
	}

	if(mov3 == 1)
	{
		monstro30.x += 2;
		for(i = 0;i < 37;i++)
		{
			if(colisao(monstro30, padremov[numpad[i]]) == 1)
			{
			mov3 = 2;
			}

			else if(colisao(monstro30, barra3) == 1)
			{
			mov3 = 2;
			}
		}

		if(colisao(monstro30, bomb) == 1)
		{
		mov3 = 0;
		}
	}

	if(mov3 == 2)
	{
		monstro30.x -= 2;
		for(i = 0;i < 37;i++)
		{
			if(colisao(monstro30, padremov[numpad[i]]) == 1)
			{
			mov3 = 1;
			}

			else if(colisao(monstro30, barra1) == 1)
			{
			mov3 = 1;
			}
		}

		if(colisao(monstro30, bomb) == 1)
		{
		mov3 = 1;
		}
	}

	if(mov4 == 1)
	{
		monstro40.x += 2;
		for(i = 0;i < 37;i++)
		{
			if(colisao(monstro40, padremov[numpad[i]]) == 1)
			{
			mov4 = 2;
			}

			else if(colisao(monstro40, barra3) == 1)
			{
			mov4 = 2;
			}
		}

		if(colisao(monstro40, bomb) == 1)
		{
		mov4 = 0;
		}
	}

	if(mov4 == 2)
	{
		monstro40.x -= 2;
		for(i = 0;i < 37;i++)
		{
			if(colisao(monstro40, padremov[numpad[i]]) == 1)
			{
			mov4 = 1;
			}

			else if(colisao(monstro40, barra1) == 1)
			{
			mov4 = 1;
			}
		}

		if(colisao(monstro40, bomb) == 1)
		{
		mov4 = 1;
		}
	}

	if(mov5 == 1)
	{
		monstro50.x += 2;
		for(i = 0;i < 37;i++)
		{
			if(colisao(monstro50, padremov[numpad[i]]) == 1)
			{
			mov5 = 2;
			}

			else if(colisao(monstro50, barra3) == 1)
			{
			mov5 = 2;
			}
		}

		if(colisao(monstro50, bomb) == 1)
		{
		mov5 = 0;
		}
	}

	if(mov5 == 2)
	{
		monstro50.x -= 2;
		for(i = 0;i < 37;i++)
		{
			if(colisao(monstro50, padremov[numpad[i]]) == 1)
			{
			mov5 = 1;
			}

			else if(colisao(monstro50, barra1) == 1)
			{
			mov5 = 1;
			}
		}

		if(colisao(monstro50, bomb) == 1)
		{
		mov5 = 1;
		}
	}

	if(colisao(quade, barra3) == 1)
	{
	incx = 0;
	incy = 0;
	quade.x = x;
	quade.y = y;
	}

	if(colisao(quade, barra2) == 1)
	{
	incx = 0;
	incy = 0;
	quade.x = x;
	quade.y = y;
	}

	if(colisao(quade, barra1) == 1)
	{
	incx = 0;
	incy = 0;
	quade.x = x;
	quade.y = y;
	}

	if(colisao(quade, barra4) == 1)
	{
		incx = 0;
		incy = 0;
		quade.x = x;
		quade.y = y;
	}

	if(colisao(quade, monstro10) == 1)
	{
		vida++;
		quade.x = 81;
		quade.y = 81;
	}

	if(colisao(quade, monstro20) == 1)
	{
		vida++;
		quade.x = 81;
		quade.y = 81;
	}

	if(colisao(quade, monstro30) == 1)
	{
		vida++;
		quade.x = 81;
		quade.y = 81;
	}

	if(colisao(quade, monstro40) == 1)
	{
		vida++;
		quade.x = 81;
		quade.y = 81;
	}

	if(colisao(quade, monstro50) == 1)
	{
		vida++;
		quade.x = 81;
		quade.y = 81;
	}

	if(colisao(quade, buracoo) == 1)
	{
		srand(time(NULL));
		n = rand()%3;
		casa = rand()%37;
		inicio= time(NULL);

		for(i = 0;i < 37;i++)
		{
			if(n == 0)
			numpad[i] = vetor1[i];

			if(n == 1)
			numpad[i] = vetor2[i];

			if(n == 2)
			numpad[i] = vetor3[i];
		
		}

	if(n == 0)
	{
		monstro10x = padremov[14].x;
		monstro10y = padremov[14].y;		

		monstro10.x = monstro10x;
		monstro10.y = monstro10y;

		monstro20x = padremov[22].x;
		monstro20y = padremov[22].y;		

		monstro20.x = monstro20x;
		monstro20.y = monstro20y;

		monstro30x = padremov[31].x;
		monstro30y = padremov[31].y;		

		monstro30.x = monstro30x;
		monstro30.y = monstro30y;

		monstro40x = padremov[44].x;
		monstro40y = padremov[44].y;		

		monstro40.x = monstro40x;
		monstro40.y = monstro40y;

		monstro50x = padremov[55].x;
		monstro50y = padremov[55].y;		

		monstro50.x = monstro50x;
		monstro50.y = monstro50y;
	}

	if(n == 1)
	{
		monstro10x = padremov[9].x;
		monstro10y = padremov[9].y;		

		monstro10.x = monstro10x;
		monstro10.y = monstro10y;

		monstro20x = padremov[21].x;
		monstro20y = padremov[21].y;		

		monstro20.x = monstro20x;
		monstro20.y = monstro20y;

		monstro30x = padremov[33].x;
		monstro30y = padremov[33].y;		

		monstro30.x = monstro30x;
		monstro30.y = monstro30y;

		monstro40x = padremov[39].x;
		monstro40y = padremov[39].y;		

		monstro40.x = monstro40x;
		monstro40.y = monstro40y;

		monstro50x = padremov[65].x;
		monstro50y = padremov[65].y;		

		monstro50.x = monstro50x;
		monstro50.y = monstro50y;
	}

	if(n == 2)
	{
		monstro10x = padremov[10].x;
		monstro10y = padremov[10].y;		

		monstro10.x = monstro10x;
		monstro10.y = monstro10y;

		monstro20x = padremov[22].x;
		monstro20y = padremov[22].y;		

		monstro20.x = monstro20x;
		monstro20.y = monstro20y;

		monstro30x = padremov[34].x;
		monstro30y = padremov[34].y;		

		monstro30.x = monstro30x;
		monstro30.y = monstro30y;

		monstro40x = padremov[49].x;
		monstro40y = padremov[49].y;		

		monstro40.x = monstro40x;
		monstro40.y = monstro40y;

		monstro50x = padremov[67].x;
		monstro50y = padremov[67].y;		

		monstro50.x = monstro50x;
		monstro50.y = monstro50y;
	}

		bomb.x = 2000;
		bomb.y = 2000;
		quade.x = 81;
		quade.y = 81;
		bomba.ativa = 1;
		lol = 0;
		mov1 = 1;
		mov2 = 1;
		mov3 = 1;
		mov4 = 1;
		mov5 = 1;
		fase++;
	}
	for(i = 0;i < 37;i++)
	{
		if(colisao(quade, padremov[numpad[i]]) == 1)
		{
		incx = 0;
		incy = 0;
		quade.x = x;
		quade.y = y;
		}
	}
	if(bomba.ativa == 1)
	{
	if(colide == 1)
	{			
		if(colisao(quade, bomb) == 1)
		{
			incx = 0;
			incy = 0;
			quade.x = x;
			quade.y = y;
		}
	}

	if(colisao(quade, bomb) == 0 && (quade.x > (bomb.x + bomb.w) || quade.y > (bomb.y + bomb.h))) 
	{
		colide = 1;	
	}
	
	else if(colisao(quade, bomb) == 0 && ((quade.x + quade.w) > bomb.x  || (quade.y + quade.h) > bomb.y )) 
	{
		colide = 1;	
	}
	}	

	for(i = 0;i < 30;i++)
	{
		if(colisao(quade, paredee[i]) == 1)
		{
			incx = 0;
			incy = 0;
			quade.x = x;
			quade.y = y;
		}
	}
	

	x = quade.x;
	y = quade.y;

	if(incy == -1)
	{
		quade.y -= 5;
		contdown++;
		if(contdown == 8)
		{
		contdown = 0;
		}
	}

	if(incy == 1)
	{
		quade.y += 5;
		contdown++;
		if(contdown == 8)
		{
		contdown = 0;
		}
	}

	if(incx == -1)
	{
		quade.x -= 5;
		contleft++;
		if(contleft == 6)
		{
		contleft = 0;
		}
	}

	if(incx == 1)
	{
		quade.x += 5;
		contright++;
		if(contright == 6)
		{
		contright = 0;
		}
	}

       SDL_FillRect(screen, NULL, 0);

	SDL_BlitSurface( fundo, NULL, screen, NULL);

	SDL_BlitSurface( cabecalho, NULL, screen, &reccabecalho);

	SDL_BlitSurface( ttf, NULL, screen, &recttf);

	SDL_BlitSurface( ttfvida, NULL, screen, &vid);

	tempo2 = difftime(inicio,fim2)+(180);
	sprintf(tempo5,"%i",tempo2);
	tempo4 = TTF_RenderText_Blended(fonte, tempo5, cor);
	
	SDL_BlitSurface( tempo4, NULL, screen, &tempo3);

	if(bomba.ativa == 0)
	{
      if(bomba.colocar == 1)
        {
        
		for(k = 0;k < 113;k++)
		{
			if(colisao(quade, padremov[k]) == 1)
			{
				bombx = padremov[k].x;
				bomby = padremov[k].y;
				bomb.x = bombx;
				bomb.y = bomby;
			}
		}

	bomba.ativa = 1;
	bomba.colocar = 2;
	}
	}

	if(bomba.ativa == 1)
	{	
		
	SDL_BlitSurface(bombaimagem,NULL,screen,&bomb);
		

		tempo++;
		bomba.colocar = 0;
	}

	if(incy != 0)
	{
		if(contdown == 0)
		{
		SDL_BlitSurface( down1, NULL, screen, &quade);
		}
		if(contdown == 1)
		{
		SDL_BlitSurface( down2, NULL, screen, &quade);
		}
		if(contdown == 2)
		{
		SDL_BlitSurface( down3, NULL, screen, &quade);
		}
		if(contdown == 3)
		{
		SDL_BlitSurface( down4, NULL, screen, &quade);
		}
		if(contdown == 4)
		{
		SDL_BlitSurface( down5, NULL, screen, &quade);
		}
		if(contdown == 5)
		{
		SDL_BlitSurface( down6, NULL, screen, &quade);
		}
		if(contdown == 6)
		{
		SDL_BlitSurface( down7, NULL, screen, &quade);
		}
		if(contdown == 7)
		{
		SDL_BlitSurface( down8, NULL, screen, &quade);
		}
	}

	if(incx == -1)
	{
		if(contleft == 0)
		{
		SDL_BlitSurface( left1, NULL, screen, &quade);
		}
		if(contleft == 1)
		{
		SDL_BlitSurface( left2, NULL, screen, &quade);
		}
		if(contleft == 2)
		{
		SDL_BlitSurface( left3, NULL, screen, &quade);
		}
		if(contleft == 3)
		{
		SDL_BlitSurface( left4, NULL, screen, &quade);
		}
		if(contleft == 4)
		{
		SDL_BlitSurface( left5, NULL, screen, &quade);
		}
		if(contleft == 5)
		{
		SDL_BlitSurface( left6, NULL, screen, &quade);
		}
	}

	if(incx == 1)
	{
		if(contright == 0)
		{
		SDL_BlitSurface( right1, NULL, screen, &quade);
		}
		if(contright == 1)
		{
		SDL_BlitSurface( right2, NULL, screen, &quade);
		}
		if(contright == 2)
		{
		SDL_BlitSurface( right3, NULL, screen, &quade);
		}
		if(contright == 3)
		{
		SDL_BlitSurface( right4, NULL, screen, &quade);
		}
		if(contright == 4)
		{
		SDL_BlitSurface( right5, NULL, screen, &quade);
		}
		if(contright == 5)
		{
		SDL_BlitSurface( right6, NULL, screen, &quade);
		}
	}

	

	if(incy == 0 && incx == 0)
	{
		SDL_BlitSurface( parado, NULL, screen, &quade);
	}

	if(mov1 != 0)
	{
		if(mov1 == 1)
		{
			SDL_BlitSurface( monstro1, NULL, screen, &monstro10 );
		}

		if(mov1 == 2)
		{
			SDL_BlitSurface( monstro3, NULL, screen, &monstro10 );
		}
	}

	if(mov2 != 0)
	{
		if(mov2 == 1)
		{
			SDL_BlitSurface( monstro1, NULL, screen, &monstro20 );
		}

		if(mov2 == 2)
		{
			SDL_BlitSurface( monstro3, NULL, screen, &monstro20 );
		}
	}

	if(mov3 != 0)
	{
		if(mov3 == 1)
		{
			SDL_BlitSurface( monstro1, NULL, screen, &monstro30 );
		}

		if(mov3 == 2)
		{
			SDL_BlitSurface( monstro3, NULL, screen, &monstro30 );
		}
	}

	if(mov4 != 0)
	{
		if(mov4 == 1)
		{
			SDL_BlitSurface( monstro1, NULL, screen, &monstro40 );
		}

		if(mov4 == 2)
		{
			SDL_BlitSurface( monstro3, NULL, screen, &monstro40 );
		}
	}

	if(mov5 != 0)
	{
		if(mov5 == 1)
		{
			SDL_BlitSurface( monstro1, NULL, screen, &monstro50 );
		}

		if(mov5 == 2)
		{
			SDL_BlitSurface( monstro3, NULL, screen, &monstro50 );
		}
	}

	if(lol == 0)
	{
		buracox = padremov[numpad[casa]].x;
		buracoy = padremov[numpad[casa]].y;
		buracoo.x = buracox + 8;
		buracoo.y = buracoy + 8;
		lol = 1;
	}

	SDL_BlitSurface( buraco, NULL, screen, &buracoo );

	if(fase == 0)
	{
		for(i = 0;i < 37;i++)
		{
			if(numpad[i]!=114)
			{
			SDL_BlitSurface( parederemovivel2, NULL, screen, &padremov[numpad[i]] );
			}
		}
	}

	if(fase == 1)
	{
		for(i = 0;i < 37;i++)
		{
			if(numpad[i]!=114)
			{
			SDL_BlitSurface( parederemovivel1, NULL, screen, &padremov[numpad[i]] );
			}
		}
	}

	if(tempo == 40)
	{
		tempo = 0;
		bomba.ativa = 0;
		colide = 0;
		bombax = bomb.x;
		bombay = bomb.y;
		fogocentro.x = bombax;
		fogocentro.y = bombay;
		fogocima.x = bombax;
		fogocima.y = bombay-40;
		fogobaixo.x = bombax;
		fogobaixo.y = bombay+40;
		fogodireita.x = bombax+40;
		fogodireita.y = bombay;
		fogoesquerda.x = bombax-40;
		fogoesquerda.y = bombay;

		for(i = 0;i < 37;i++)
		{
			if(colisao(fogocima, padremov[numpad[i]]) == 1)
			{
				numpad[i] = 114;
			}

			if(colisao(fogobaixo, padremov[numpad[i]]) == 1)
			{
				numpad[i] = 114;
			}
			if(colisao(fogoesquerda, padremov[numpad[i]]) == 1)
			{
				numpad[i] = 114;
			}
			if(colisao(fogodireita, padremov[numpad[i]]) == 1)
			{
				numpad[i] = 114;
			}
		}

			SDL_BlitSurface(centro1,NULL,screen,&fogocentro);
			SDL_BlitSurface(cima1,NULL,screen,&fogocima);
			SDL_BlitSurface(baixo1,NULL,screen,&fogobaixo);
			SDL_BlitSurface(esquerda1,NULL,screen,&fogoesquerda);
			SDL_BlitSurface(direita1,NULL,screen,&fogodireita);

			if(colisao(fogocima, monstro10) == 1)
			{
			monstro10.x = 800;
			pontuacao1 += 100;
			mov1 = 0;
			}
			if(colisao(fogobaixo, monstro10) == 1)
			{
			monstro10.x = 800;
			pontuacao1 += 100;
			mov1 = 0;
			}
			if(colisao(fogodireita, monstro10) == 1)
			{
			monstro10.x = 800;
			pontuacao1 += 100;
			mov1 = 0;
			}
			if(colisao(fogoesquerda, monstro10) == 1)
			{
			monstro10.x = 800;
			pontuacao1 += 100;
			mov1 = 0;
			}

			if(colisao(fogocima, monstro20) == 1)
			{
			monstro20.x = 800;
			pontuacao1 += 100;
			mov2 = 0;
			}
			if(colisao(fogobaixo, monstro20) == 1)
			{
			monstro20.x = 800;
			pontuacao1 += 100;
			mov2 = 0;
			}
			if(colisao(fogodireita, monstro20) == 1)
			{
			monstro20.x = 800;
			pontuacao1 += 100;
			mov2 = 0;
			}
			if(colisao(fogoesquerda, monstro20) == 1)
			{
			monstro20.x = 800;
			pontuacao1 += 100;
			mov2 = 0;
			}

			if(colisao(fogocima, monstro30) == 1)
			{
			monstro30.x = 800;
			pontuacao1 += 100;
			mov3 = 0;
			}
			if(colisao(fogobaixo, monstro30) == 1)
			{
			monstro30.x = 800;
			pontuacao1 += 100;
			mov3 = 0;
			}
			if(colisao(fogodireita, monstro30) == 1)
			{
			monstro30.x = 800;
			pontuacao1 += 100;
			mov3 = 0;
			}
			if(colisao(fogoesquerda, monstro30) == 1)
			{
			monstro30.x = 800;
			pontuacao1 += 100;
			mov3 = 0;
			}

			if(colisao(fogocima, monstro40) == 1)
			{
			monstro40.x = 800;
			pontuacao1 += 100;
			mov4 = 0;
			}
			if(colisao(fogobaixo, monstro40) == 1)
			{
			monstro40.x = 800;
			pontuacao1 += 100;
			mov4 = 0;
			}
			if(colisao(fogodireita, monstro40) == 1)
			{
			monstro40.x = 800;
			pontuacao1 += 100;
			mov4 = 0;
			}
			if(colisao(fogoesquerda, monstro40) == 1)
			{
			monstro40.x = 800;
			pontuacao1 += 100;
			mov4 = 0;
			}

			if(colisao(fogocima, monstro50) == 1)
			{
			monstro50.x = 800;
			pontuacao1 += 100;
			mov5 = 0;
			}
			if(colisao(fogobaixo, monstro50) == 1)
			{
			monstro50.x = 800;
			pontuacao1 += 100;
			mov5 = 0;
			}
			if(colisao(fogodireita, monstro50) == 1)
			{
			monstro50.x = 800;
			pontuacao1 += 100;
			mov5 = 0;
			}
			if(colisao(fogoesquerda, monstro50) == 1)
			{
			monstro50.x = 800;
			pontuacao1 += 100;
			mov5 = 0;
			}		

		if(colisao(fogocentro, quade) == 1)
		{
			vida++;
			quade.x = 81;
			quade.y = 81;
		}
		
		else if(colisao(fogodireita, quade) == 1)
		{
			vida++;
			quade.x = 81;
			quade.y = 81;
		}
		else if(colisao(fogoesquerda, quade) == 1)
		{
			vida++;
			quade.x = 81;
			quade.y = 81;
		}
		else if(colisao(fogocima, quade) == 1)
		{
			vida++;
			quade.x = 81;
			quade.y = 81;
		}
		else if(colisao(fogobaixo, quade) == 1)
		{
			vida++;
			quade.x = 81;
			quade.y = 81;
		}
		bomb.x = 800;
		bomb.y = 600;
	}

	if(vida == 3)
	{
		jogar = FALSE;
		menu = TRUE;
		vida = 0;
		fim = 1;

	srand(time(NULL));
	n = rand()%3;
	casa = rand()%37;

	for(i = 0;i < 37;i++)
	{
		if(n == 0)
		numpad[i] = vetor1[i];

		if(n == 1)
		numpad[i] = vetor2[i];

		if(n == 2)
		numpad[i] = vetor3[i];
		
	}

	bomb.x = 2000;
	bomb.y = 2000;
	quade.x = 81;
	quade.y = 81;
	bomba.ativa = 1;
	lol = 0;
	mov1 = 1;
	mov2 = 1;
	mov3 = 1;
	mov4 = 1;
	mov5 = 1;
	}

	for(i = 0;i < 30;i++)
	{
	SDL_BlitSurface( parede, NULL, screen, &paredee[i] );
	}

	SDL_BlitSurface( barradireita, NULL, screen, &barra3 );
	SDL_BlitSurface( barraesquerda, NULL, screen, &barra1 );
	SDL_BlitSurface( barrasuperior, NULL, screen, &barra2 );
	SDL_BlitSurface( barrainferior, NULL, screen, &barra4 );

        SDL_Flip(screen);

		if(1000.0/30>(SDL_GetTicks()-start))
		{
			SDL_Delay(1000.0/30>(SDL_GetTicks()-start));
		}

		while(fim == 1)
		{
			while(SDL_PollEvent(&event))
			{

				if (event.type == SDL_QUIT)
				{
					fim = 0;
				}

				else if( event.type == SDL_KEYDOWN )
				{
					switch( event.key.keysym.sym )
					{

					case SDLK_ESCAPE:
						fim = 0;
						break;
					case SDLK_RETURN:
						if((p_arquivo = fopen(nome_arquivo, "r")) != NULL)
						{
							fread(&array, sizeof(ARRAY), 1, p_arquivo);
							fclose(p_arquivo);
						}
						for(j = 0;j < 7;j++)
						{
							reco1.nome[j] = nome1[j];
						}
						reco1.pontuacao = pontuacao1;
						insere(&array, reco1);
						if((p_arquivo = fopen(nome_arquivo, "w")) == NULL)
						{
							perror("fopen:");
						}
						fwrite(&array, sizeof(ARRAY), 1, p_arquivo);
						fclose(p_arquivo);
						fim = 0;
						break;
					case SDLK_a:
						if(w<7)
						{
							nome1[w] = 'a';
							w++;
						}
						break;
					case SDLK_b:
						if(w<7)
						{
							nome1[w] = 'b';
							w++;
						}
						break;
					case SDLK_c:
						if(w<7)
						{
							nome1[w] = 'c';
							w++;
						}
						break;
					case SDLK_d:
						if(w<7)
						{
							nome1[w] = 'd';
							w++;
						}
						break;
					case SDLK_e:
						if(w<7)
						{
							nome1[w] = 'e';
							w++;
						}
						break;
					case SDLK_f:
						if(w<7)
						{
							nome1[w] = 'f';
							w++;
						}
						break;
					case SDLK_g:
						if(w<7)
						{
							nome1[w] = 'g';
							w++;
						}
						break;
					case SDLK_h:
						if(w<7)
						{
							nome1[w] = 'h';
							w++;
						}
						break;
					case SDLK_i:
						if(w<7)
						{
							nome1[w] = 'i';
							w++;
						}
						break;
					case SDLK_j:
						if(w<7)
						{
							nome1[w] = 'j';
							w++;
						}
						break;
					case SDLK_k:
						if(w<7)
						{
							nome1[w] = 'k';
							w++;
						}
						break;
					case SDLK_l:
						if(w<7)
						{
							nome1[w] = 'l';
							w++;
						}
						break;
					case SDLK_m:
						if(w<7)
						{
							nome1[w] = 'm';
							w++;
						}
						break;
					case SDLK_n:
						if(w<7)
						{
							nome1[w] = 'n';
							w++;
						}
						break;
					case SDLK_o:
						if(w<7)
						{
							nome1[w] = 'o';
							w++;
						}
						break;
					case SDLK_p:
						if(w<7)
						{
							nome1[w] = 'p';
							w++;
						}
						break;
					case SDLK_q:
						if(w<7)
						{
							nome1[w] = 'q';
							w++;
						}
						break;
					case SDLK_r:
						if(w<7)
						{
							nome1[w] = 'r';
							w++;
						}
						break;
					case SDLK_s:
						if(w<7)
						{
							nome1[w] = 's';
							w++;
						}
						break;
					case SDLK_t:
						if(w<7)
						{
							nome1[w] = 't';
							w++;
						}
						break;
					case SDLK_u:
						if(w<7)
						{
							nome1[w] = 'u';
							w++;
						}
						break;
					case SDLK_v:
						if(w<7)
						{
							nome1[w] = 'v';
							w++;
						}
						break;
					case SDLK_w:
						if(w<7)
						{
							nome1[w] = 'w';
							w++;
						}
						break;
					case SDLK_x:
						if(w<7)
						{
							nome1[w] = 'x';
							w++;
						}
						break;
					case SDLK_y:
						if(w<7)
						{
							nome1[w] = 'y';
							w++;
						}
						break;
					case SDLK_z:
						if(w<7)
						{
							nome1[w] = 'z';
							w++;
						}
						break;
					case SDLK_BACKSPACE:
						if(w>0)
						{
							w--;
							nome1[w]=' ';
						}
						break;
					default:
						break;
					}
				}		       
			}

			SDL_FillRect(screen, NULL, 0);
			SDL_BlitSurface( fundo, NULL, screen, NULL );
			ttfnome = TTF_RenderText_Blended(fontenome, nome1, cor);
			ttftraco = TTF_RenderText_Blended(fontenome, "_______", cor);
			SDL_BlitSurface( ttfnome, NULL, screen, &rec5);
			SDL_BlitSurface( ttftraco, NULL, screen, &rec5);
			SDL_BlitSurface( dignome, NULL, screen, &recdig );
			SDL_BlitSurface( sair1, NULL, screen, &rec6 );
			SDL_BlitSurface( gameover, NULL, screen, &rec1 );
			SDL_Flip(screen);
		}
	
    }
		while(record == TRUE)
		{
			
			SDL_Event event;
	
			while(SDL_PollEvent(&event))
			{
			
				switch(event.type)
				{
				
					case SDL_QUIT:
						record = FALSE;
						menu = FALSE;
						break;

					case SDL_KEYDOWN:
				
						switch(event.key.keysym.sym)
						{
					
							case SDLK_ESCAPE:
								record = FALSE;
								break;
							
							default:
								break;
					}
					default:
						break;
				
				}
			}
			SDL_FillRect(screen,NULL,0);
			if((p_arquivo = fopen(nome_arquivo, "r")) != NULL)
			{
				fread(&array, sizeof(ARRAY), 1, p_arquivo);
				fclose(p_arquivo);
			}
			SDL_BlitSurface(recordes, NULL, screen, &quad);	
			imprime(&array,fonte,cor);
			SDL_Flip(screen);
		
			if(1000/FPS > SDL_GetTicks() - start)
			{
				SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
		}
	}
		

	while(credits == TRUE)
		{
			
			SDL_Event event;
	
			while(SDL_PollEvent(&event))
			{
			
				switch(event.type)
				{
				
					case SDL_QUIT:
						credits = FALSE;
						menu = FALSE;
						break;

					case SDL_KEYDOWN:
				
						switch(event.key.keysym.sym)
						{
					
							case SDLK_ESCAPE:
								credits = FALSE;
								break;
							
							default:
								break;
					}
					default:
						break;
				
				}
			}
			SDL_FillRect(screen,NULL,0);
			
			SDL_BlitSurface(creditos, NULL, screen, &quad);	
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
			
		
	
	
	Mix_FreeChunk(choice);
	Mix_FreeMusic(theme);
	Mix_FreeMusic(jogando);
	Mix_CloseAudio();
	return 0;
}

RECORDE elemento(ARRAY *array, int posicao)
{
	return array->vetor[posicao];
}

int tamanho(ARRAY *array)
{
	return array->n;
}

void insere(ARRAY *array, RECORDE recorde)
{
    if(tamanho(array) < MAX_ARRAY)
    {
        array->vetor[tamanho(array)] = recorde;
        array->n += 1;
    }
    else
    {
        RECORDE menor_recorde;
        menor_recorde = elemento(array, MAX_ARRAY - 1);
        
        if(menor_recorde.pontuacao >= recorde.pontuacao)
        {
            return;
        }
        else
        {
            remove_posicao(array, MAX_ARRAY - 1);
            insere(array, recorde);
            return;
        }
    }
    
    sort(array);
}

void remove_posicao(ARRAY *array, int posicao)
{
	if(tamanho(array) == 0)
	{
		return;
	}
	else if(tamanho(array) == 1)
	{
		array->n -= 1;
		return;
	}
	else
	{
		array->n -= 1;
		array->vetor[posicao] = array->vetor[tamanho(array)];
	}
    
    sort(array);
}

void imprime(ARRAY *array,TTF_Font *fonte,SDL_Color cor)
{
	int i,j;
	char nome[tamanho(array)][10];
	char num[tamanho(array)][10];

	RECORDE recorde;

	SDL_Rect rec[tamanho(array)][3];
	int x;
	int y;
	
	y = 200;

	for(j = 0;j < tamanho(array);j++)
	{
		x = 600;

		for(i = 0;i < 3;i++)
		{
			rec[j][i].x = x;
			rec[j][i].y = y;
			x +=100;
		}
		y+=25;
	}

	for(i = 0; i < tamanho(array); i++)
	{
		recorde = elemento(array, i);
		sprintf(nome[i],"%i",recorde.pontuacao);
		sprintf(num[i],"%i",i+1);
	}

	for(j = 0;j < 3;j++)
	{
		for(i = 0; i < tamanho(array); i++)
		{
			recorde = elemento(array, i);
			if(j == 0)
			{
				ttf[i][j] = TTF_RenderText_Blended(fonte,num[i] , cor);
				SDL_BlitSurface( ttf[i][j], NULL, screen, &rec[i][j]);
			}
			if(j == 1)
			{
				ttf[i][j] = TTF_RenderText_Blended(fonte,recorde.nome , cor);
				SDL_BlitSurface( ttf[i][j], NULL, screen, &rec[i][j]);
			}
			if(j == 2)
			{
				ttf[i][j] = TTF_RenderText_Blended(fonte,nome[i] , cor);
				SDL_BlitSurface( ttf[i][j], NULL, screen, &rec[i][j]);
				
			}
		}
	}
}

void sort(ARRAY *array)
{
	bubble_sort(array->vetor, array->n);
}

void bubble_sort(RECORDE list[], int n)
{
	int i, j;
    RECORDE swap;

	for(i = 0 ; i < ( n - 1 ); i++)
	{
		for(j = 0 ; j < n - i - 1; j++)
		{
			if(list[j].pontuacao < list[j+1].pontuacao)
			{ 
				swap = list[j];
				list[j] = list[j+1];
				list[j+1] = swap;
			}
		}
	}
}
