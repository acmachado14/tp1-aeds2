//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#ifndef TAD_PATRICIA_H
#define TAD_PATRICIA_H

typedef enum{
	interno, externo
}TipoDoNo; //essa enumeracao serve pra identificar se o no e Externo ou Interno

typedef struct TipoPatNo{
    TipoDoNo notipo;
    union{
        struct{
            unsigned char indice;          //essa variavel guarda o indice em que o no interno se difere
            char compara;                  //essa variavel guarda qual o caracter diferente, presente no indice acima
            struct TipoPatNo *esquerda, *direita;
        }NoInterno;
        char *chave;  //ponteiro pra char que aponta para a string que estamos armazenando, se o nao for externo
    }PatNo;
}TipoPatNo;


char Bit(unsigned char i, char k[]);

short NoEExterno(TipoPatNo *no);

TipoPatNo *CriaNoInt(int i, char c, TipoPatNo **esq, TipoPatNo **dir, int *Memoria);

TipoPatNo *CriaNoExt(char *ch, int *Memoria);

void BuscaPat (char k[], TipoPatNo *no, int *Comparacoes);

TipoPatNo *InsereEntre (char k[], char compara, TipoPatNo **no, int i, int *Comparacoes, int *Memoria);

TipoPatNo *Insere(char k[], TipoPatNo **no, int *Comparacoes, int *Memoria);

int ContaPalavras(TipoPatNo *no);

void ImprimePalavras(TipoPatNo *no);

#endif // TAD_PATRICIA_H