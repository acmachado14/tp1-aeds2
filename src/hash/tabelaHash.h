//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    int *pesos;
}Pesos;

typedef struct dados* ApontadorDados;
typedef struct dados{
    int idDoc;
    int qtde;
    ApontadorDados prox;
}Dados;

typedef struct celula* ApontadorCelula;
typedef struct celula{
    char *string;
    ApontadorDados dados;
    ApontadorCelula prox;
}Celula;

typedef struct{
    ApontadorCelula inicio; // Primeira posição da lista linear encadiada
    ApontadorCelula ultima;   // Ultima posição da lista linear encadeada
}Lista;

typedef struct{
    Lista *tabela_hash;
    Pesos pesos;
    int N;
    int M;
}TabelaHash;


void GerarPesos(Pesos *pesos);
void InicializaTabelaHash(TabelaHash *tabelaHash, int N);
void FazListaVazia(Lista *lista);
void InserirTabelaHash(TabelaHash *tabelaHash, char *string, int idDoc);
void IInseri(Lista *lista, char *string, int idDoc);
int HashFunction(Pesos pesos, char *string, int M);
int tamanhoTabelaHash(int N);
void freeTabelaHash(TabelaHash *tabelaHash);
