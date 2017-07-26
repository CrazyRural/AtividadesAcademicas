#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"


// Funcao que codifica a lista
// a partir da lista de arvores, esta função gera uma única arvore (que fica em lista->inicio)
// nesta arvore os caracteres de maior frequencia ficam mais proximos da raiz,
// assim usaremos menos bits para representa-los(Obs.: usamos 0 para indicar esquerda e 1 para direita)
void huffman(LISTA* lista);


int main(){
	
	int aux;
	printf("\n\n-------AA de ED1 - Algoritmo de Huffman-------\n\n");

	printf("Digite 1 para compactar ou 2 para descompactar:\n");
	scanf("%d", &aux);

	if (aux==1){

		printf("\n----------Compactar----------\n\nDigite o nome do arquivo a ser compactado:\n");
		char path[20];
		scanf("%s",path);
		LISTA *lista = lerArquivo(path);
		
//		printf("\n\nLista Gerada\n\n");
//		exibeListaComCaracter(lista);
//		printf("\n\n");
		

//		printf("Executando Algoritmo de huffman...\n\n");
		huffman(lista);


//		printf("\n\n");

		char *codigo = (char*)malloc(30*sizeof(char));//[30]; //= "abc";


		LISTA_CARACTERES* listaCodigos = criaListaCaracter();
		pegaFolhas(listaCodigos,lista->inicio->arvore,codigo,0);

//		exibir(listaCodigos);

		printf("\nDigite o nome do arquivo de saida:\n");
		char output[20];
		scanf ("%s",output);

		comprime(output,listaCodigos,path);

		printf("\nCompactação concluída.\n\n");
	
	}

	else if (aux==2){

		char nome1[20],nome2[20];

		printf("\n----------Descompactar----------\n\nDigite o nome do arquivo a ser descompactado:\n");
		scanf("%s",nome1);

		printf("\nDigite o nome do arquivo destino da descompactação:\n");
		scanf("%s",nome2);
		
		descomprime(nome1,nome2);

		printf("\nDescompactação concluída.\n\n");
	}

	return 0;
}


void huffman(LISTA* lista){

	//se a lista so contem um elemento retorna
	if(lista->inicio->prox == NULL )
		return;

	NO_ARVORE *no1 = removerInicio(lista);
	NO_ARVORE *no2 = removerInicio(lista);

	NO_ARVORE *no_arvore = criaArvore();
	incluiEsquerda(no_arvore,no1);
	incluiDireita(no_arvore,no2);

	no_arvore->valor = no1->valor + no2->valor;

	inserirOrdenado( lista, no_arvore );

//	exibeLista(lista);

	huffman(lista);
}