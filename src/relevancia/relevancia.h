//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include <math.h>
#include "../indice/indiceInvertido.h"
#include "../tree/patricia.h"

typedef struct noRelevancia{
    float r;   // Relevancia de um documento
    int idDoc; // idDoc do documento em questão
    struct noRelevancia *esq, *dir;
}NoRelevancia;

typedef struct{
    NoRelevancia *no;
}ArvoreRelevancia;

void insercaoR(NoRelevancia **no, float r, int id);
void inicializaArvoreRelevancia(NoRelevancia **raiz);
void freeArvoreRelevancia(NoRelevancia **no);
void clearStdin(void);
void percursoRelevancia(NoRelevancia **no);

//HASH
void buscaPorTexto(TabelaHash *tabelaHash);
float relevanciaDocumento(TabelaHash *tabelaHash, char **termos, int idDoc, int q);

//PATRICIA
void buscaPorTextoPat(TipoPatNo *patricia, int N);
float relevanciaDocumentoPat(TipoPatNo *patricia, char **termos, int idDoc, int q, int N);
int numDistintosPat(TipoPatNo *patricia, int idDoc);
int numOcorrenciasTermoPat(TipoPatNo *patricia, char *termo, int idDoc);
int numeroDocumentosTermoPat(TipoPatNo *patricia, char *termo, int N);