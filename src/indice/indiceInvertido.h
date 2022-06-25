//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include "../hash/tabelaHash.h"
#include "../tree/patricia.h"

typedef struct noIndice{
    ApontadorCelula celula;
    struct noIndice *esq, *dir;
}NoIndiceInvertido;

typedef struct{
    NoIndiceInvertido *no;
}ArvoreIndiceInvertido;

void ImprimirIndiceInvertidoHash(TabelaHash *tabelaHash);
int comparaString(char *stringInserir, char *stringInserida);
void inicializaArvoreIndice(NoIndiceInvertido **raiz);
void insercaoArvore(NoIndiceInvertido **no, ApontadorCelula celula);
void percursoOrdem(NoIndiceInvertido **no);
void freeArvoreIndice(NoIndiceInvertido **no);

typedef struct noIndicePat{
    TipoPatNo *patNo;
    struct noIndicePat *esq, *dir;
}NoIndiceInvertidoPat;

typedef struct{
    NoIndiceInvertidoPat *no;
}ArvoreIndiceInvertidoPat;

void inicializaArvoreIndicePat(NoIndiceInvertidoPat **raiz);
void ImprimirIndiceInvertidoPat(TipoPatNo *pat);
void insercaoArvorePat(NoIndiceInvertidoPat **no, TipoPatNo *patNo);
void percursoOrdemPat(NoIndiceInvertidoPat **no);
void freeArvoreIndicePat(NoIndiceInvertidoPat **no);
void percrusaoPatricia(ArvoreIndiceInvertidoPat *raiz, TipoPatNo *pat);