//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include "tabelaHash.h"


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
    Dados *dadosAux;
    celula = lista->primeira;

    while (celula != NULL){
        if(! strcmp(celula->string, string)){
            dadosAux = celula->dados;
            while(dadosAux != NULL){
                if(dadosAux->idDoc == idDoc){
                    dadosAux->qtd += 1;
                    return;
                }
                dadosAux = dadosAux->prox;
            }
            dadosAux = (Dados*)malloc(sizeof(Dados));
            dadosAux->idDoc = idDoc;
            dadosAux->qtd = 1;
            dadosAux->prox = NULL;
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
    strcpy(lista->ultima->string, string);
    lista->ultima->dados = (Dados*)malloc(sizeof(Dados));
    lista->ultima->dados->idDoc = idDoc;
    lista->ultima->dados->qtd = 1;
    lista->ultima->prox = NULL;
    lista->ultima->dados->prox = NULL;
}

// A função M retorna o numero primo mais proximo da divisão da estimativa de chaves
// pelo fator de carga, numa faixa de valores da (divisao - 15) á (divisao + 15)
int tamanhoTabelaHash(int N){
    int m, a;        // a representa o fator de carga
    int totalChaves; // numero aproximado de palavras na tabela hash
    int i, j, soma;
    int primoAntecessor, primoSucessor;
    totalChaves = N * 50;
    a = 4;
    m = totalChaves / a;
    for(i = m ; i >=  m - 15; i--){
        soma = 0;
        for (j = 2; j <= i / 2; j++) {
            if (i % j == 0) {
                soma++;
                break;
            }
        }
        if(soma == 0){
            primoAntecessor = i;
            break;
        }
    }
    for(i = m ; i <= m + 15; i++){
        soma = 0;
        for (j = 2; j <= i / 2; j++) {
            if (i % j == 0) {
                soma++;
                break;
            }
        }
        if (soma == 0){
            primoSucessor = i;
            break;
        }
    }
    if(m - primoAntecessor <= primoSucessor - m){
        return primoAntecessor;
    }
    else{
        return primoSucessor;
    }
}


