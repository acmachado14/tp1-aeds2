#define TADPATRICIA_H

#define TRUE 1
#define FALSE !TRUE
#define D 8

typedef  char *String;
typedef  short boolean;

typedef enum
{
  Interno, Externo
} TipoNo;

typedef struct TipoPatNo *TArvore;
typedef struct TipoPatNo
{
    TipoNo nt;
    union
    {
        struct
        {
            short Index;
            char Caractere;
            TArvore Esq, Dir;
        } NInterno ;
        String Chave;
    } NO;
} TipoPatNo;

