#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "filaNoticias.h"

#define breakingNews = 0;
#define informes = 1;

/*lista de funcoes utilizadas*/
int defineOperacao();
int defineTipoNoticia();
void cadastraNoticia(lista *listaBreakingNews, lista *listaInformes);
void selecionaNoticias(lista *listaBreakingNews, lista *listaInformes, nodo *primeiraNoticia, nodo *segundaNoticia);
void imprimeNoticias(nodo *primeiraNoticia, nodo *segundaNoticia);
void fechaEdicao(lista *listaBreakingNews, lista *listaInformes);


/*funcoes desenvolvidas*/

/*consertar forma de ler strings*/
int defineOperacao() {
    int operacao;
    printf("\nQual operação você deseja realizar?\n");
    printf("(1) Cadastrar notícia\n(2) Fechar edição\n(3) Sair\n");
    scanf("%d", &operacao);
    return operacao;
}

int defineTipoNoticia() {
    int tipo;
    printf("\nA notícia a ser cadastrada é:\n(0) De alto interesse aos leitores\n(1) Informes gerais de menor interesse\n");
    scanf("%d", &tipo);
    return tipo;
}

void cadastraNoticia(lista *listaBreakingNews, lista *listaInformes) {
            
    int tipo = defineTipoNoticia();

    /*adiciona notícia na fila correspondente ao seu nível de interesse para os 
    leitores, caso usuário insira tipo inválido, requisita que insira novamente*/
    if (tipo == 0)
        insereNoticia(listaBreakingNews);
    else if (tipo == 1)
        insereNoticia(listaInformes);
    else {
        while (tipo != 0 && tipo != 1) {
            printf("\nVocê inseriu uma opção inválida, tente novamente.\n");
            tipo = defineTipoNoticia();
        }
    }
    printf("\nSua notícia foi cadastrada.\n");
}

void selecionaNoticias(lista *listaBreakingNews, lista *listaInformes, nodo *primeiraNoticia, nodo *segundaNoticia) {

    /*caso exista alguma notícia na lista breaking news, retorna
    a primeira da lista para ocupar a primeira noticia*/
    if (listaBreakingNews -> tamanho > 0) {
        primeiraNoticia = listaBreakingNews -> init;

        /*caso exista mais alguma notícia na lista breaking news, 
        imprime as duas breaking news e remove-as da lista*/
        if (listaBreakingNews -> tamanho-1 != 0) {
            segundaNoticia = listaBreakingNews -> init -> prox;
            imprimeNoticias(primeiraNoticia, segundaNoticia);
            removeNoticia(listaBreakingNews);
            removeNoticia(listaBreakingNews);

        /*caso não exista, verifica na lista informes e, caso exista algum informe, 
        imprime, tanto a primeira notícia da lista breaking news quanto a primeira 
        da lista informes e as remove de suas respectivas listas*/
        } else if (listaInformes -> tamanho > 0) {
            segundaNoticia = listaInformes -> init;
            imprimeNoticias(primeiraNoticia, segundaNoticia);
            removeNoticia(listaBreakingNews);
            removeNoticia(listaInformes);
        
        /*caso não exista nenhuma outra notícia, imprime apenas a primeira 
        e remove apenas a que foi impressa de sua lista*/
        } else {
            imprimeNoticias(primeiraNoticia, segundaNoticia);
            removeNoticia(listaBreakingNews);
        }
    
    /*caso não existam breaking news, mas exista algum informe, 
    retorna o primeiro da lista para ocupar a primeira notícia*/    
    } else if (listaInformes -> tamanho > 0) {
        primeiraNoticia = listaInformes -> init;

        /*caso exista mais algum informe, imprime os 
        dois informes e remove-os da lista*/
        if (listaInformes -> tamanho-1 != 0) {
            segundaNoticia = listaInformes -> init -> prox;
            imprimeNoticias(primeiraNoticia, segundaNoticia);
            removeNoticia(listaInformes);
            removeNoticia(listaInformes);
        
        /*caso não exista nenhuma outra notícia, imprime apenas a primeira 
        e remove apenas a que foi impressa de sua lista*/
        } else {
            imprimeNoticias(primeiraNoticia, segundaNoticia);
            removeNoticia(listaInformes);
        }
    
    /*caso não existam notícias disponiveis em nenhuma 
    das listas, exibe mensagem de edição pulada*/
    } else 
        printf("\nEsta edição foi pulada por falta de notícias!\n\n");

}

void imprimeNoticias(nodo *primeiraNoticia, nodo *segundaNoticia) {

    /*caso hajam duas notícias, imprime com a primeira formatação,
    caso contrário, imprime com a segunda formatação*/
    if (segundaNoticia) {
        printf("\n=======================================================\n");
        printf("%s\n\n", primeiraNoticia -> titulo);
        printf("%s", primeiraNoticia -> corpo);
        printf("\n\n==\n\n");
        printf("%s\n\n", segundaNoticia -> titulo);
        printf("%s", segundaNoticia -> corpo);
        printf("\n=======================================================\n\n");
    } else {
        printf("\n\n=======================================================\n");
        printf("%s\n\n", primeiraNoticia -> titulo);
        printf("%s", primeiraNoticia -> corpo);
        printf("=======================================================\n\n");
    }
}

void fechaEdicao(lista *listaBreakingNews, lista *listaInformes) {
    nodo *primeiraNoticia = malloc(sizeof(nodo));
    nodo *segundaNoticia = malloc(sizeof(nodo));

    /*seleciona e imprime noticias válidas*/
    if (primeiraNoticia && segundaNoticia)
        selecionaNoticias(listaBreakingNews, listaInformes, primeiraNoticia, segundaNoticia);

    else
        printf("Erro ao alocar memória.\n");
    
    /*atualiza as listas envelhecendo todas as suas notícias em um
    dia e removendo as que ultrapassaram a marca de três dias*/
    envelheceNoticias(listaBreakingNews);
    envelheceNoticias(listaInformes);
    removeNoticiasVelhas(listaBreakingNews);
    removeNoticiasVelhas(listaInformes);
}


/*programa principal*/
int main() {

    /*cria ambas as listas de classificacao das noticias*/
    lista *listaBreakingNews = criaLista();
    lista *listaInformes = criaLista();

    /*fornece as opções ao usuário para que defina a 
    operação a ser realizada no início do loop*/
    int operacao = defineOperacao();
    bool controleSwitchCase = true;
    
    while (controleSwitchCase) {
        switch (operacao) {
            
            /*requisita ao usuário que insira primeiramente o tipo de classifição
            de sua notícia para que seja inserida em uma das listas e, 
            posteriormente, o seu título e texto*/
            case 1:
                cadastraNoticia(listaBreakingNews, listaInformes);
                operacao = defineOperacao();
            break;

            /*realiza a seleção das notícias, imprime a edição do jornal com as notícias
            selecionadas e atualiza ambas as listas criadas para envelhecimento*/
            case 2:
                fechaEdicao(listaBreakingNews, listaInformes);
                operacao = defineOperacao(operacao);
            break;

            /*interrompe o loop de requisições e o funcionamento do programa, imprime 
            mensagem de encerramento e destrói as listas criadas*/
            case 3:
                controleSwitchCase = false;
            break;

            /*caso o usuário insira operação inválida, exibe mensagem de erro
            e requisita que insira uma operação válida*/
            default :
                printf("\nVocê inseriu uma opção inválida, tente novamente.\n");
                operacao = defineOperacao();
        }
    }
    printf("\nO programa foi encerrado.\n");
    destroiLista(listaBreakingNews);
    destroiLista(listaInformes);
    return 0;
}