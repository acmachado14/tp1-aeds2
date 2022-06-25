//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include <math.h>
#include "indiceInvertido.h"

typedef struct noRelevancia{
    float r;   // Relevancia de um documento 
    int idDoc; // idDoc do documento em questão
    struct noRelevancia *esq, *dir;
}NoRelevancia;

typedef struct{
    NoRelevancia *no;
}ArvoreRelevancia;


void inicializaArvoreRelevancia(NoRelevancia **raiz);
void insercaoR(NoRelevancia **no, float r, int id);
void percursoRelevancia(NoRelevancia **no);
void buscaPorTexto(TabelaHash *tabelaHash);
float relevanciaDocumento(TabelaHash *tabelaHash, char **termos, int idDoc, int q);
void freeArvoreRelevancia(NoRelevancia **no);
void clearStdin(void);