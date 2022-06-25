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
}TipoDoNo; //essa enumera��o serve pra identificar se o n� � Externo ou Interno

typedef struct TipoPatNo{
    TipoDoNo notipo;
    //int conta; eu implementei uma forma de contar quantas vezes uma palavra foi encontrada no texto, creio que o tp n�o exige isso, ent�o tudo relacionado a essa fun��o vai estar comentado, mas caso for ajudar em algo, t� a�
    union{
        struct{
            unsigned char indice;          //essa vari�vel guarda o indice em que o no interno se difere
            char compara;                  //essa var�avel guarda qual o caracter diferente, presente no indice acima
            struct TipoPatNo *esquerda, *direita;
        }NoInterno;
        struct{
            char *chave;  //ponteiro pra char que aponta para a string que estamos armazenando, se o n� for externo
            ApontadorDadosPat dados;
        }NoExterno;
    }PatNo;
}TipoPatNo;


char Bit(unsigned char i, char k[]);

short NoEExterno(TipoPatNo *no);

TipoPatNo *CriaNoInt(int i, char c, TipoPatNo **esq, TipoPatNo **dir, int *Memoria);

TipoPatNo *CriaNoExt(char *ch, int *Memoria, int idDoc);

void BuscaPat (char k[], TipoPatNo *no);

TipoPatNo *InsereEntre (char k[], char compara, TipoPatNo **no, int i, int *Memoria, int idDoc);

TipoPatNo *Insere(char k[], TipoPatNo **no, int *Memoria, int idDoc);

int ContaPalavras(TipoPatNo *no);

void ImprimePalavras(TipoPatNo *no);

#endif // TAD_PATRICIA_H