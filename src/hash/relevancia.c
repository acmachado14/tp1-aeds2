//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include "relevancia.h"

void buscaPorTexto(TabelaHash *tabelaHash){
    int q = 0; // q representa a quantidade de termos 
    printf("Digite a quantidade de termo(s) de busca: ");
    scanf("%d", &q);
    clearStdin();
    while(q < 1){
        printf("Digite um numero maior ou igual a 1: ");
        scanf("%d", &q);
        clearStdin();
    }

    int i, j;
    char **termos;
    termos = (char**)malloc(q * sizeof(char*));
    for(i = 0; i < q; i++){
        termos[i] = (char*)malloc(50 * sizeof(char));
    }
    for(i = 0; i < q; i++){
        printf("Termo %d: ", i + 1);
        scanf("%s", termos[i]);
        clearStdin();
    }
    int N;
    N = tabelaHash->N;
    float r;
    ArvoreRelevancia raiz;
    inicializaArvoreRelevancia(&raiz.no);
    for(i = 0; i < N; i++){
        r = relevanciaDocumento(tabelaHash, termos, i, q);
        insercaoR(&raiz.no, r, i);
    }
    printf("\nRelevancia dos textos:\n\n");
    percursoRelevancia(&raiz.no);
    freeArvoreRelevancia(&raiz.no);
}

float relevanciaDocumento(TabelaHash *tabelaHash, char **termos, int idDoc, int q){
    ApontadorDados dados;
    ApontadorCelula celula;
    Lista *lista;

    int i, M, N;
    M = tabelaHash->M;
    N = tabelaHash->N;
    int ni = 0;
    for(i = 0; i < M; i++){
        lista = &tabelaHash->tabela_hash[i];
        if(lista->inicio != NULL){
            celula = lista->inicio;
            while(celula != NULL){
                dados = celula->dados;
                while(dados != NULL){
                    if(dados->idDoc == idDoc){
                        ni += 1;
                    }
                    dados = dados->prox;
                }
                celula = celula->prox;
            }
        }
    }
    float r, w;
    r = 0.0;
    int hashCode, f, dj;
    for(i = 0; i < q; i++){
        f = 0;
        dj = 0;
        hashCode = HashFunction(tabelaHash->pesos, termos[i], M);
        lista = &tabelaHash->tabela_hash[hashCode];
        if(lista->inicio != NULL){
            celula = lista->inicio;
            while(celula != NULL){
                if(! strcmp(termos[i], celula->string)){
                    dados = celula->dados;
                    while(dados != NULL){
                        if(dados->idDoc == idDoc){
                            f = dados->qtde;
                        }
                        dj += 1;
                        dados = dados->prox;
                    }
                    break;
                }
                celula = celula->prox;
            }
            if(celula == NULL){
                printf("O termo %s nao esta na tabela hash.\n", termos[i]);
            }
        }
        else{
            printf("O termo %s nao esta na tabela hash.\n", termos[i]);
            continue;
        }
        w = f * log2(2) / dj;
        r += w; 
    }
    r = r / ni;
    return r;
}

void inicializaArvoreRelevancia(NoRelevancia **raiz){
    *raiz = NULL;
}

void insercaoR(NoRelevancia **no, float r, int idDoc){
    if (*no == NULL){
        (*no) = (NoRelevancia*)malloc(sizeof(NoRelevancia));
        (*no)->idDoc = idDoc;
        (*no)->r = r;
        (*no)->dir = NULL;
        (*no)->esq = NULL;
    }
    else{
        if (r <= (*no)->r){
            insercaoR(&(*no)->esq, r, idDoc);
        }
        if(r > (*no)->r){
            insercaoR(&(*no)->dir, r, idDoc);
        }
    } 
}

void percursoRelevancia(NoRelevancia **no){
    if((*no) != NULL){
        percursoRelevancia(&(*no)->dir);
        printf("Texto %d (arquivo%d.txt)\n", (*no)->idDoc + 1, (*no)->idDoc + 1);
        percursoRelevancia(&(*no)->esq);
    }
}

void freeArvoreRelevancia(NoRelevancia **no){
    if((*no) != NULL){
        freeArvoreRelevancia(&(*no)->esq);
        freeArvoreRelevancia(&(*no)->dir);
        free((*no));
        (*no) = NULL;
    }
}

void clearStdin(void){
    int c = getchar();
    while( c != '\n' && c != EOF){
        c = getchar();
    }
}
