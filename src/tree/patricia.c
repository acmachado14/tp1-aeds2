//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patricia.h"

char Bit(unsigned char i, char k[]){
    return (k[i]);
};

short NoEExterno(TipoPatNo *no){
    return (no->notipo == externo);
};

TipoPatNo *CriaNoInt(int i, char c, TipoPatNo **esq, TipoPatNo **dir, int *Memoria){
    TipoPatNo *no;
    no = malloc(sizeof(TipoPatNo));
    (*Memoria) += sizeof(*no);
    no->notipo = interno;
    no->PatNo.NoInterno.esquerda = *esq;
    no->PatNo.NoInterno.direita = *dir;
    no->PatNo.NoInterno.indice = i;
    no->PatNo.NoInterno.compara = c;
    return no;
};

TipoPatNo *CriaNoExt(char *ch, int *Memoria, int idDoc){
    TipoPatNo *no;
    no = (TipoPatNo*)malloc(sizeof(TipoPatNo));
    (*Memoria) += sizeof(*no);
    no->notipo = externo;
    no->idDoc = idDoc;
    no->qtde = 1;
    no->chave = (char*)malloc(strlen(ch) * sizeof(char));

    (*Memoria) += sizeof(*no);
    strcpy(no->chave, ch);
    return no;
};


void BuscaPat(char k[], TipoPatNo *no){
    if (NoEExterno(no)){
        if(strcmp(k,no->chave) == 0){
            printf("Elemento encontrado: %s\n", no->chave);
        }
        else{
            printf("Elemento %s nao encontrado\n", k);
        }
        return;
    }
    if (Bit(no->PatNo.NoInterno.indice, k) < no->PatNo.NoInterno.compara){
        BuscaPat(k, no->PatNo.NoInterno.esquerda);
    }
    else{
        BuscaPat(k, no->PatNo.NoInterno.direita);
    }
};

TipoPatNo *InsereEntre (char k[], char compara, TipoPatNo **no, int i, int *Memoria, int idDoc){
    TipoPatNo *Pno;
    if (NoEExterno(*no)){
        Pno = CriaNoExt(k, Memoria, idDoc);
        if (Bit(i, k) > Bit (i, (*no)->chave)){
            return CriaNoInt(i, k[i], no, &Pno, Memoria);
        }else{
            return CriaNoInt(i, (*no)->chave, &Pno, no, Memoria);
        }
    }

    else if (i == (*no)->PatNo.NoInterno.indice){
        Pno = CriaNoExt(k, Memoria, idDoc);
        if (Bit(i, k) > (*no)->PatNo.NoInterno.compara) {
            return CriaNoInt(i, k[i], no, &Pno, Memoria);
        }else{
            (*no)->PatNo.NoInterno.esquerda = InsereEntre(k, compara, &(*no)->PatNo.NoInterno.esquerda, i, Memoria, idDoc);
            return (*no);
        }
    }

    else if (i < (*no)->PatNo.NoInterno.indice){
        Pno = CriaNoExt(k, Memoria, idDoc);
        if (Bit(i, k) > compara){
            return CriaNoInt(i, k[i], no, &Pno, Memoria);
        }else{
            return CriaNoInt(i, compara, &Pno, no, Memoria);
        }
    }

    else {
        if (Bit((*no)->PatNo.NoInterno.indice, k) == (*no)->PatNo.NoInterno.compara){
            (*no)->PatNo.NoInterno.direita = InsereEntre(k, compara, &(*no)->PatNo.NoInterno.direita, i, Memoria, idDoc);
        }else{
            (*no)->PatNo.NoInterno.esquerda = InsereEntre(k, compara, &(*no)->PatNo.NoInterno.esquerda, i, Memoria, idDoc);
        }
        return (*no);
    }
};

TipoPatNo *Insere(char k[], TipoPatNo **no, int *Memoria, int idDoc){
    TipoPatNo *Pno;
    if (*no == NULL){
        return CriaNoExt(k, Memoria, idDoc);
    }else{
        Pno = *no;
        while (!NoEExterno(Pno)){
            if (Bit(Pno->PatNo.NoInterno.indice, k) == Pno->PatNo.NoInterno.compara){
                Pno = Pno->PatNo.NoInterno.direita;
            }else{
                Pno = Pno->PatNo.NoInterno.esquerda;
            }
        }

        if (!strcmp(k, Pno->chave) && Pno->idDoc == idDoc && Pno->notipo == externo){
            printf("teste: %d \n", (Pno)->qtde);
            (Pno)->qtde += 1;
            return (*no);
        }else{
            int i=0;
            while (Bit((int)i, k) == Bit((int)i, Pno->chave) && i < strlen(k)) i++;
            return (InsereEntre(k, Pno->chave[i], no, i, Memoria, idDoc));
        }
    }
};

int ContaPalavras(TipoPatNo *no){
    if (no->notipo == externo) return 1;
    else return ContaPalavras(no->PatNo.NoInterno.esquerda) + ContaPalavras(no->PatNo.NoInterno.direita);
};

void ImprimePalavras(TipoPatNo *no){
    if (no->notipo == externo) {
        printf("palavra: %s\n",no->chave);
        printf("idDoc: %d\n",no->idDoc);
        printf("qtde: %d\n",no->qtde);
        puts("----------------------");
    }else{
        ImprimePalavras(no->PatNo.NoInterno.esquerda);
        ImprimePalavras(no->PatNo.NoInterno.direita);
    }
}