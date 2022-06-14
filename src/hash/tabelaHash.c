//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include "TabelaHash.h"


void GerarPesos(Pesos *pesos){
    pesos->pesos = (int*)malloc(100 * sizeof(int));
    int i;
    srand(time(NULL));
    for( i = 0; i < 100; i++){
        pesos->pesos[i] =  rand() % 1000 + 1;
    }
}

void Inicializa(TabelaHash *tabelaHash, int M, int N){
    int i;
    GerarPesos(&tabelaHash->pesos);
    tabelaHash->N = N;
    tabelaHash->M = M;
    tabelaHash->tabela_hash = (Lista*)malloc(M * sizeof(Lista));
    for(i = 0; i < M; i++){
        FazListaVazia(&tabelaHash->tabela_hash[i]);
    } 
}

void FazListaVazia(Lista *lista){
    lista->primeira = NULL;
    lista->ultima = NULL;
}

int HashFunction(Pesos pesos, char *string, int M){
    int i, K = 0;
    int tamanhoString;
    tamanhoString = strlen(string);
    for(i = 0; i < tamanhoString; i++){
        K += string[i] * pesos.pesos[i];
    }
    return K % M;
}

void Inserir(TabelaHash *tabelaHash, char *string, int idDoc){
    int hashCode;
    int N, M;
    N = tabelaHash->N;
    M = tabelaHash->M;
    hashCode = HashFunction(tabelaHash->pesos, string, M);
    IInseri(&tabelaHash->tabela_hash[hashCode], string, idDoc, N);
}

void IInseri(Lista *lista, char *string, int idDoc, int N){
    Celula *celula;
    celula = lista->primeira;

    while (celula != NULL){
        if(! strcmp(celula->string, string)){
            celula->qtde[idDoc] += 1;
            return;
        }
        celula = celula->prox;
    }
    
    if(lista->ultima == NULL){
        lista->ultima = (Celula*)malloc(sizeof(Celula));
        lista->primeira = lista->ultima;
    }
    else{
        lista->ultima->prox = (Celula*)malloc(sizeof(Celula));
        lista->ultima = lista->ultima->prox;
    }
    lista->ultima->qtde = (int*)calloc(N, sizeof(int));
    lista->ultima->qtde[idDoc] += 1;
    strcpy(lista->ultima->string, string);
    lista->ultima->prox = NULL;
}

