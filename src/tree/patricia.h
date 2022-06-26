//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#ifndef TAD_PATRICIA_H
#define TAD_PATRICIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct dadosPat* ApontadorDadosPat;
typedef struct dadosPat{
    int idDoc;
    int qtde;
    ApontadorDadosPat prox;
}DadosPat;

typedef enum{
	interno, externo
}TipoDoNo;

typedef struct TipoPatNo{
    TipoDoNo notipo;
    union{
        struct{
            unsigned char indice;
            char compara;
            struct TipoPatNo *esquerda, *direita;
        }NoInterno;
        struct{
            char *chave;
            ApontadorDadosPat dados;
        }NoExterno;
    }PatNo;
}TipoPatNo;


char Bit(unsigned char i, char k[]);

short NoEExterno(TipoPatNo *no);

TipoPatNo *CriaNoInt(int i, char c, TipoPatNo **esq, TipoPatNo **dir, int *Memoria);

TipoPatNo *CriaNoExt(char *ch, int *Memoria, int idDoc);

TipoPatNo *InsereEntre (char k[], char compara, TipoPatNo **no, int i, int *Memoria, int idDoc);

TipoPatNo *Insere(char k[], TipoPatNo **no, int *Memoria, int idDoc);

void ImprimePalavras(TipoPatNo *no);

#endif // TAD_PATRICIA_H