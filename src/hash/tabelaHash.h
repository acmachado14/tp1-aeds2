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

typedef struct dados{
    int idDoc;
    int qtde;
    struct dados *prox;
}Dados;

typedef struct celula{
    char *string;
    Dados *dados;
    struct celula *prox;
}Celula;

typedef struct{
    Celula *inicio; // Primeira posição da lista linear encadiada
    Celula *ultima;   // Ultima posição da lista linear encadeada
}Lista;

typedef struct{
    Lista *tabela_hash;
    Pesos pesos;
    int N;
    int M;
}TabelaHash;

typedef struct lista_aux{
    Celula *celula;
    struct lista_aux *prox;
}ListaAux;


void GerarPesos(Pesos *pesos);
void Inicializa(TabelaHash *tabelaHash, int M, int N);
void FazListaVazia(Lista *lista);
void Inserir(TabelaHash *tabelaHash, char *string, int idDoc);
void IInseri(Lista *lista, char *string, int idDoc, int N);
int HashFunction(Pesos pesos, char *string, int M);
int tamanhoTabelaHash(int N);
void ImprimirIndiceInvertidoHash(TabelaHash *tabelaHash);
void criaListaAuxOrdenada(ListaAux *inicio, Lista *lista);
int comparaString(char *stringInserir, char *stringInserida);
