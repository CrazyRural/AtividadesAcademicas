#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ITEM;
typedef int bool;

#define true  1
#define false 0


//-------Estruturas------

typedef struct NO_ARVORE {

	ITEM valor;
	char caracter;

	struct NO_ARVORE *esq;
	struct NO_ARVORE *dir;

}NO_ARVORE;


typedef struct CARACTER_CODIFICADO{

	char caracter;
	char *binario;

}CARACTER_CODIFICADO;


typedef struct NO_CARACTERES{
	CARACTER_CODIFICADO *valor;
	struct NO_CARACTERES *prox;
}NO_CARACTERES;

typedef struct LISTA_CARACTERES{
	int tamanho;
	NO_CARACTERES *inicio;	
}LISTA_CARACTERES;


typedef struct NO_LISTA {
	NO_ARVORE *arvore;
	struct NO_LISTA *prox;
} NO_LISTA;

typedef struct LISTA{
	NO_LISTA *inicio;
}LISTA;



//-------Funções--------

NO_ARVORE* criaArvore(){

	NO_ARVORE *raiz = (NO_ARVORE*)malloc(sizeof(NO_ARVORE));
	if(raiz != NULL){
		raiz->esq = NULL;
		raiz-> dir = NULL;

		return raiz;
	}
	printf("Erro de alocação de memória!\n");
	return NULL;
}


LISTA_CARACTERES* criaListaCaracter(){

	LISTA_CARACTERES* lista = (LISTA_CARACTERES*)malloc(sizeof(LISTA_CARACTERES));
	if(lista != NULL)
		lista->tamanho = 0;

	return lista;
}


void addInicio(LISTA_CARACTERES *lista, CARACTER_CODIFICADO *c){

	NO_CARACTERES *no = (NO_CARACTERES*)malloc(sizeof(NO_CARACTERES));
	no->valor = c;

	no->prox = lista->inicio;
	lista->inicio = no;

	lista->tamanho += 1;
}


void exibir(LISTA_CARACTERES *lista){

	NO_CARACTERES* no = lista->inicio;

	while(no != NULL){

		if(no->valor->caracter == ' ')
			printf("¬ %s\n",no->valor->binario );
		else if(no->valor->caracter == '\n')
			printf("` %s\n",no->valor->binario );
		else
			printf("%c %s\n",no->valor->caracter,no->valor->binario );
		
		no = no->prox;
	}

}


char* buscaCaracter(LISTA_CARACTERES* lista, char chave){

	NO_CARACTERES* no = lista->inicio;
	while(no!= NULL){

		if(no->valor->caracter == chave)
			return no->valor->binario;

		no = no->prox;
	}

	return NULL;
}


char buscaPorBinario(LISTA_CARACTERES* lista, char *chave){

	NO_CARACTERES* no = lista->inicio;
	while(no!= NULL){

		if(strcmp (chave, no->valor->binario) == 0)
			return no->valor->caracter;		

		no = no->prox;
	}

	return ' ';
}


//incluir no2 no filho da esquerda de no1
void incluiEsquerda(NO_ARVORE* no1,NO_ARVORE* no2){

	//no2->esq = no1->esq;
	no1->esq = no2;
}

void incluiDireita(NO_ARVORE* no1,NO_ARVORE* no2){
	//no2->dir = no1->dir;
	no1->dir = no2;	
}


void MostraFolhas(NO_ARVORE *arvore,char *codigo,int pos){

	if(arvore!=NULL){
		if(arvore->esq != NULL){
			codigo[pos] = '0';
			MostraFolhas(arvore->esq,codigo,pos+1);
		}
			
		if(arvore->dir != NULL){
			codigo[pos]= '1';
			MostraFolhas(arvore->dir,codigo,pos+1);
		}
			

		if( (arvore->esq == NULL) && (arvore->dir == NULL) ){
			printf("sou a folha do caracter %c ",arvore->caracter);
			codigo[pos] = '\0';
			printf("meu codigo = %s\n",codigo );
		}
	}

}


void pegaFolhas(LISTA_CARACTERES* lista,NO_ARVORE *arvore,char *codigo,int pos){

	if(arvore!=NULL){
		if(arvore->esq != NULL){
			codigo[pos] = '0';
			pegaFolhas(lista,arvore->esq,codigo,pos+1);
		}
			
		if(arvore->dir != NULL){
			codigo[pos]= '1';
			pegaFolhas(lista,arvore->dir,codigo,pos+1);
		}
			

		if( (arvore->esq == NULL) && (arvore->dir == NULL) ){
			//printf("sou a folha do caracter %c ",arvore->caracter);
			codigo[pos] = '\0';
			//printf("meu codigo = %s\n",codigo );

			CARACTER_CODIFICADO* c1 = (CARACTER_CODIFICADO*)malloc(sizeof(CARACTER_CODIFICADO));
			c1->caracter = arvore->caracter;
			char *bin = (char*) malloc(30*sizeof(char));
			strcpy(bin,codigo);
			c1->binario = bin;

			addInicio(lista,c1);
		}
	}

}


int vazia(LISTA* lista){
	return lista->inicio == NULL;
}


LISTA* criaLista(){

	LISTA* lista = (LISTA*)malloc(sizeof(LISTA));
	if(lista != NULL){
		lista->inicio = NULL;
		return lista;
	}

	printf("Erro de alocação de memória\n");
	return NULL;
}


void inserirInicio(LISTA* lista, NO_ARVORE *arvore){

	NO_LISTA *no = (NO_LISTA*)malloc(sizeof(NO_LISTA));
	no->arvore = arvore;

	no->prox = lista->inicio;
	lista->inicio = no;
}

NO_ARVORE* removerInicio(LISTA* lista){

	NO_LISTA *no_remove = lista->inicio;
	lista->inicio = lista->inicio->prox;

	NO_ARVORE* arvore = no_remove->arvore;
	free(no_remove);

	return arvore;
}


void inserirOrdenado(LISTA *lista, NO_ARVORE *arvore){

	NO_LISTA *no = (NO_LISTA*)malloc(sizeof(NO_LISTA));
	no->arvore = arvore;

	if( lista->inicio == NULL || lista->inicio->arvore->valor > no->arvore->valor){
		no->prox = lista->inicio;
		lista->inicio = no;

		return;
	}
	// 5.5
	// 1 4 5 6
	NO_LISTA *temp = lista->inicio->prox;
	NO_LISTA *anterior = lista->inicio;
	for( ; temp != NULL && (no->arvore->valor > temp->arvore->valor) ; temp= temp->prox,anterior = anterior->prox);

	anterior->prox = no;
	no->prox = temp;
}


void exibeLista(LISTA *lista){
	NO_LISTA *temp = lista->inicio;
	for(;temp!=NULL;temp=temp->prox)
		printf("%d ",temp->arvore->valor );

	printf("\n");
}

void exibeListaComCaracter(LISTA *lista){
	NO_LISTA *temp = lista->inicio;

	for(temp = lista->inicio;temp!=NULL;temp=temp->prox)
		printf("%3c",temp->arvore->caracter );

	printf("\n");
	for(temp = lista->inicio;temp!=NULL;temp=temp->prox)
		printf("%3d",temp->arvore->valor );
	

	printf("\n");
}


NO_ARVORE* busca(LISTA *lista,char caracter){

	NO_LISTA* temp;
	for(temp = lista->inicio; temp != NULL; temp= temp->prox){
		if(temp->arvore->caracter == caracter){
			//printf("encontrei o caracter %c \n",caracter );
			return temp->arvore;
		}
			
	}

	return NULL;
}


LISTA* lerArquivo(char* path){

	FILE *file = fopen(path,"r");

	if(file == NULL){
		printf("Arquivo não existe!\n");
		return NULL;
	}

	LISTA* lista = criaLista();
	char c;
	while((c = getc(file) ) != EOF){

		NO_ARVORE *arvore = busca(lista,c);
		//se ainda nao existe o caracter na lista
		if(arvore == NULL){
			arvore = criaArvore();
			arvore->caracter = c;
			arvore->valor = 1;
			inserirInicio(lista,arvore);

			//printf("\n");
			//exibeListaComCaracter(lista);
			//printf("\n");
		}
		else{

			//se ja existe entao soma 1 a frequencia
			arvore->valor = arvore->valor+1;

		}
	}


	LISTA* listaOrdenada = criaLista();

	//NO_ARVORE* no;
	//NO_LISTA* temp;
	//for (temp = lista->inicio; temp != NULL ; temp = lista->inicio)
	while(!vazia(lista))
	{
		//no = removerInicio(lista);
		//printf("%c\n",no->caracter );
		inserirOrdenado(listaOrdenada,removerInicio(lista));
	}


	return listaOrdenada;
}


void comprime(char* outputFile,LISTA_CARACTERES *caracteres,char* inputFile){


	FILE *input = fopen(inputFile,"r");
	FILE *output = fopen(outputFile,"w");

	if(input == NULL){
		printf("Arquivo não existe!\n");
		return;
	}

	// escrever a lista no arquivo de saida para descompressao
	NO_CARACTERES *no = caracteres->inicio;
	fprintf(output, "%d\n", caracteres->tamanho);
	while(no != NULL){

		if(no->valor->caracter == '\n')
			fprintf(output, "` %s\n",  no->valor->binario);

		else if(no->valor->caracter == ' ')
			fprintf(output, "¬ %s\n", no->valor->binario);

		else
			fprintf(output, "%c %s\n", no->valor->caracter, no->valor->binario);

		no = no->prox;
	}


	char c;
	while((c = getc(input) ) != EOF){
		char *bin = buscaCaracter(caracteres,c); // bin contem o codigo binario para c
		fprintf(output, "%s ",  bin);
	}	
}


void descomprime(char* inputFile,char* outputFile){

	LISTA_CARACTERES *caracteres = criaListaCaracter();

	FILE *input = fopen(inputFile,"r");
	FILE *output = fopen(outputFile,"w");

	int tam;
	fscanf(input,"%d\n",&tam);
	caracteres->tamanho = tam;
//	printf("%d\n", caracteres->tamanho);

	int i;
	for (i = 0; i < tam+1; i++){

		CARACTER_CODIFICADO* c1 = (CARACTER_CODIFICADO*)malloc(sizeof(CARACTER_CODIFICADO));
		addInicio(caracteres,c1);
		char c;
		char *str = (char*) malloc(20*sizeof(char));
		fscanf(input,"%c %s\n",&c,str);
		c1->caracter = c;
		c1->binario = str;
		

//		printf("%c %s\n",c1->caracter,c1->binario);

		
	}

	while(! feof(input)){
		char bin[20];
		fscanf(input,"%s ",bin);

		char c = buscaPorBinario(caracteres,bin);
		if(c == '¬')
			fprintf(output,"%c" , ' ');
		else if(c == '`')
			fprintf(output,"%c" , '\n');
		else
			fprintf(output,"%c" , c);
	}

	//printf("Buscar por b %c\n",buscaPorBinario(caracteres,"000000") );
//	exibir(caracteres);
}