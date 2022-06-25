//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#ifndef TAD_PATRICIA_H
#define TAD_PATRICIA_H

typedef enum{
	interno, externo
}TipoDoNo;

typedef struct TipoPatNo{
    TipoDoNo notipo;
    char *chave;
    int idDoc;
    int qtde;
    union{
        struct{
            unsigned char indice;
            char compara;                 //essa variavel guarda qual o caracter diferente, presente no indice acima
            struct TipoPatNo *esquerda, *direita;
        }NoInterno;
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