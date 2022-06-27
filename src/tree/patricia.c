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
    no = malloc(sizeof(TipoPatNo));
    (*Memoria) += sizeof(*no);
    no->notipo = externo;
    no->PatNo.NoExterno.chave = malloc(30*sizeof(char));
    (*Memoria) += sizeof(no->PatNo.NoExterno.chave);
    strcpy(no->PatNo.NoExterno.chave, ch);

    no->PatNo.NoExterno.dados = (ApontadorDadosPat)malloc(sizeof(DadosPat));
    (*Memoria) += sizeof(*no->PatNo.NoExterno.dados);
    no->PatNo.NoExterno.dados->idDoc = idDoc;
    no->PatNo.NoExterno.dados->qtde = 1;
    no->PatNo.NoExterno.dados->prox = NULL;
    return no;
};

TipoPatNo *InsereEntre (char k[], char compara, TipoPatNo **no, int i, int *Memoria, int idDoc){
    TipoPatNo *Pno;
    if (NoEExterno(*no)){
        Pno = CriaNoExt(k, Memoria, idDoc);
        if (Bit(i, k) > Bit (i, (*no)->PatNo.NoExterno.chave)){
            return CriaNoInt(i, k[i], no, &Pno, Memoria);
        }else{
            return CriaNoInt(i, (*no)->PatNo.NoExterno.chave[i], &Pno, no, Memoria);
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
    ApontadorDadosPat dadosAux;
    int i;
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
        i=0;
        while (Bit((int)i, k) == Bit((int)i, Pno->PatNo.NoExterno.chave) && i < strlen(k)) i++;
        if (strcmp(k, Pno->PatNo.NoExterno.chave) == 0){
            dadosAux = Pno->PatNo.NoExterno.dados;
            while(dadosAux != NULL){
                if(dadosAux->idDoc == idDoc){
                    dadosAux->qtde += 1;
                    return (*no);
                }
                else{
                    if(dadosAux->prox == NULL){
                        dadosAux->prox = (ApontadorDadosPat)malloc(sizeof(DadosPat));
                        dadosAux = dadosAux->prox;
                        dadosAux->idDoc = idDoc;
                        dadosAux->qtde = 1;
                        dadosAux->prox = NULL;
                        return (*no);
                    }
                }
                dadosAux = dadosAux->prox;
            }
            printf("A palavra %s ja esta na arvore.\n\n", k);
            return (*no);
        }else{
        return (InsereEntre(k, Pno->PatNo.NoExterno.chave[i], no, i, Memoria, idDoc));}
    }
};

void ImprimePalavras(TipoPatNo *no){
    ApontadorDadosPat dados;
    if (no->notipo == externo) {
        printf("%-15s ",no->PatNo.NoExterno.chave);
        dados = no->PatNo.NoExterno.dados;
        while(dados != NULL){
            printf("<%d,%d> ", dados->qtde, dados->idDoc);
            dados = dados->prox;
        }
        printf("\n");
    }
    else{
        ImprimePalavras(no->PatNo.NoInterno.esquerda);
        ImprimePalavras(no->PatNo.NoInterno.direita);
    }
}