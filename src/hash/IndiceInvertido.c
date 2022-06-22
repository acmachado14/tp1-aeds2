//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include "IndiceInvertido.h"


void ImprimirIndiceInvertidoHash(TabelaHash *tabelaHash){
    Lista *lista;
    ApontadorCelula celula;
    ArvoreIndiceInvertido raiz;
    inicializaArvoreIndice(&raiz.no);
    int i, M;
    M = tabelaHash->M;

    for(i = 0; i < M; i++){
        lista = &tabelaHash->tabela_hash[i];
        celula = lista->inicio;
        while(celula != NULL){
            insercaoArvore(&raiz.no, celula);
            celula = celula->prox;
        }
    }
    percursoOrdem(&raiz.no);
    freeArvoreIndice(&raiz.no);
}

int comparaString(char *stringInserir, char *stringInserida){
    int indice;
    indice = strcmp(stringInserir, stringInserida);
    return indice;
}

void inicializaArvoreIndice(NoIndiceInvertido **raiz){
    *raiz = NULL;
}

void insercaoArvore(NoIndiceInvertido **no, ApontadorCelula celula){
    if (*no == NULL){
        (*no) = (NoIndiceInvertido*)malloc(sizeof(NoIndiceInvertido));
        (*no)->celula = celula;
        (*no)->dir = NULL;
        (*no)->esq = NULL;
    }
    else{
        int indice;
        indice = comparaString(celula->string, (*no)->celula->string);
        if (indice < 0){
            insercaoArvore(&(*no)->esq, celula);
        }
        if(indice > 0){
            insercaoArvore(&(*no)->dir, celula);
        }
    } 
}

void percursoOrdem(NoIndiceInvertido **no){
    if((*no) != NULL){
        ApontadorDados dados;
        percursoOrdem(&(*no)->esq);
        printf("%-15s  ", (*no)->celula->string);
        dados = (*no)->celula->dados;
        while(dados != NULL){
            printf("<%d,%d> ", dados->qtde, dados->idDoc);
            dados = dados->prox;
        }
        printf("\n");
        percursoOrdem(&(*no)->dir);
    }
}

void freeArvoreIndice(NoIndiceInvertido **no){
    if((*no) != NULL){
        freeArvoreIndice(&(*no)->esq);
        freeArvoreIndice(&(*no)->dir);
        free((*no));
        (*no) = NULL;
    }
}
