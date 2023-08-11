#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no {
    char titulo[33];
    char corpo[513];
    int idade;
    struct no *prox;
} nodo;

typedef struct filaNoticias {
    nodo *init;
    nodo *fim;
    int tamanho;
} lista;

/*cria uma lista vazia e a retorna, 
se falhar retorna mensagem de erro*/
lista *criaLista();

/*insere uma nova noticia no fim da lista*/
void insereNoticia(lista *listaNoticias);

/*remove noticia do inicio da lista em questao e a atualiza*/
void removeNoticia(lista *listaNoticias);

/*envelhece em um dia todas as noticias da lista*/
void envelheceNoticias(lista *listaNoticias);

/*verifica se, dentre as noticias da lista, ha alguma cuja 
idade ultrapasse tres dias e, se sim, a remove*/
void removeNoticiasVelhas(lista *listaNoticias);

/*remove todos os elementos de uma lista e libera sua alocacao*/
lista *destroiLista(lista *listaNoticias);