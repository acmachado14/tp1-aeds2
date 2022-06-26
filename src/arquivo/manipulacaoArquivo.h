//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include "../tree/patricia.h"
#include "../relevancia/relevancia.h"
#include <stdbool.h>

bool leituraArquivoEntrada(char **arquivosTeste, int *N);

bool construirIndiceInvertidoHash(TabelaHash *tabelaHash, char **arquivosTeste,  int N);
bool construirIndiceInvertidoPatricia(TipoPatNo **raiz, char **arquivosTeste,  int N);
