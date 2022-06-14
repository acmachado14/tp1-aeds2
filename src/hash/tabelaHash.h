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


typedef struct celula{
    char *string;
    // Cada posição i do vetor qtde armazena a quantidade de vezes que a string aparece
    // no documento i
    int *qtde;
    struct celula *prox;
}Celula;

typedef struct{
    Celula *primeira; // Primeira posição da lista linear encadiada
    Celula *ultima;   // Ultima posição da lista linear encadeada
}Lista;

typedef struct{
    Lista *tabela_hash;
    Pesos pesos;
    int N;
    int M;
}TabelaHash;

void GerarPesos(Pesos *pesos);
void Inicializa(TabelaHash *tabelaHash, int M, int N);
void FazListaVazia(Lista *lista);
void Inserir(TabelaHash *tabelaHash, char *string, int idDoc);
void IInseri(Lista *lista, char *string, int idDoc, int N);
int HashFunction(Pesos pesos, char *string, int M);
void Imprimir(TabelaHash *tabelaHash);
void IImprimir(Lista *lista, int N);
//void set_string(Dados *dados, char *string);
//void set_idDoc(Dados *dados, int idDoc);