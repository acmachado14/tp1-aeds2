#include "../hash/relevancia.h"
#include "../tree/patricia.h"
#include <stdbool.h>

bool leituraArquivoEntrada(char **arquivosTeste, int *N);

bool construirIndiceInvertidoHash(TabelaHash *tabelaHash, char **arquivosTeste,  int N);
bool construirIndiceInvertidoPatricia(TipoPatNo **raiz, char **arquivosTeste,  int N);
