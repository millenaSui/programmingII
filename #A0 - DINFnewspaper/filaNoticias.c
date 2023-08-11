#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "filaNoticias.h"

/*cria uma lista vazia e a retorna, 
se falhar retorna mensagem de erro*/
lista *criaLista() {
    lista *novaLista = malloc(sizeof(lista));
    if (novaLista) {
        novaLista -> tamanho = 0;
        novaLista -> init = NULL;
        novaLista -> fim = NULL;
        return novaLista;
    } else
        printf("Erro ao alocar memória.\n");
}

/*insere uma nova noticia no fim da lista*/
void insereNoticia(lista *listaNoticias) {
    nodo *noticia = malloc(sizeof(nodo));

    /*se for possivel alocar memoria, inicializa 
    o nodo, caso contrario, exibe erro*/
    if(noticia) {
        getchar();
        printf("\nInsira o título da notícia:\n");
        fgets(noticia -> titulo, 33, stdin);

        printf("\nInsira o conteúdo da notícia:\n");
        fgets(noticia -> corpo, 513, stdin);

        noticia -> idade = 0;
        noticia -> prox = NULL;

        /*se a fila estiver vazia insere nela a nova noticia,
        caso contrário, insere a noticia no final da fila*/
        if (listaNoticias -> tamanho == 0) {
            listaNoticias -> init = noticia;
            listaNoticias -> fim = noticia;
        } else {
            listaNoticias -> fim -> prox = noticia;
            listaNoticias -> fim = noticia;
        }
        listaNoticias -> tamanho++;
    } else
        printf("Erro ao alocar memória.\n");
}

/*remove noticia do inicio da lista em questao e a atualiza*/
void removeNoticia(lista *listaNoticias) {
    nodo *nodoAux = malloc(sizeof(nodo));

    if (nodoAux) {
        if (listaNoticias -> tamanho != 0) {
            nodoAux = listaNoticias -> init -> prox;
            free(listaNoticias -> init);
            listaNoticias -> init = nodoAux;
            listaNoticias -> tamanho--;        
        }
    } else 
        printf("Erro ao alocar memória.\n");
}

/*envelhece em um dia todas as noticias da lista*/
void envelheceNoticias(lista *listaNoticias) {
    nodo *nodoAux = malloc(sizeof(nodo));

    if (nodoAux) 
        nodoAux = listaNoticias -> init;
    else
        printf("Erro ao alocar memória.\n");

    while (nodoAux != NULL) {
        nodoAux -> idade++;
        nodoAux = nodoAux -> prox;
    }
}

/*verifica se, dentre as noticias da lista, ha alguma cuja 
idade ultrapasse tres dias e, se sim, a remove*/
void removeNoticiasVelhas(lista *listaNoticias) {
    if (listaNoticias -> tamanho != 0) {
        while (listaNoticias -> init -> idade > 3)
            removeNoticia(listaNoticias);
    }
}

/*remove todos os elementos de uma lista e libera sua alocacao*/
lista *destroiLista(lista *listaNoticias) {
    while (listaNoticias -> init != NULL) {
        removeNoticia(listaNoticias);
    }
    free(listaNoticias);
    return NULL;
}