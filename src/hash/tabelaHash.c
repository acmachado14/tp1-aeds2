//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include "tabelaHash.h"


void GerarPesos(Pesos *pesos){
    pesos->pesos = (int*)malloc(100 * sizeof(int));
    int i;
    srand(time(NULL));
    for( i = 0; i < 100; i++){
        pesos->pesos[i] =  rand() % 1000 + 1;
    }
}

void Inicializa(TabelaHash *tabelaHash, int N){
    int i;
    int M;
    M = tamanhoTabelaHash(N);
    GerarPesos(&tabelaHash->pesos);
    tabelaHash->N = N;
    tabelaHash->M = M;
    tabelaHash->tabela_hash = (Lista*)malloc(M * sizeof(Lista));
    for(i = 0; i < M; i++){
        FazListaVazia(&tabelaHash->tabela_hash[i]);
    } 
}

void FazListaVazia(Lista *lista){
    lista->inicio = NULL;
    lista->ultima = NULL;
}

int HashFunction(Pesos pesos, char *string, int M){
    int i, K = 0;
    int tamanhoString;
    tamanhoString = strlen(string);
    for(i = 0; i < tamanhoString; i++){
        K += string[i] * pesos.pesos[i];
    }
    return K % M;
}

void Inserir(TabelaHash *tabelaHash, char *string, int idDoc){
    int hashCode;
    int N, M;
    M = tabelaHash->M;
    hashCode = HashFunction(tabelaHash->pesos, string, M);
    IInseri(&tabelaHash->tabela_hash[hashCode], string, idDoc);
}

void IInseri(Lista *lista, char *string, int idDoc){
    ApontadorDados dadosAux;
    ApontadorCelula celula;

    celula = lista->inicio;

    while (celula != NULL){
        if(! strcmp(celula->string, string)){
            dadosAux = celula->dados;
            while(dadosAux != NULL){
                if(dadosAux->idDoc == idDoc){
                    dadosAux->qtde += 1;
                    return;
                }
                
                else{
                    if(dadosAux->prox == NULL){
                        dadosAux->prox = (ApontadorDados)malloc(sizeof(Dados));
                        dadosAux = dadosAux->prox;
                        dadosAux->idDoc = idDoc;
                        dadosAux->qtde = 1;
                        dadosAux->prox = NULL;
                        return;
                    }
                }
                dadosAux = dadosAux->prox;
            }
        }
        celula = celula->prox;
    }
    if(lista->ultima == NULL){
        lista->ultima = (ApontadorCelula)malloc(sizeof(Celula));
        lista->inicio = lista->ultima;
    }
    else{
        lista->ultima->prox = (ApontadorCelula)malloc(sizeof(Celula));
        lista->ultima = lista->ultima->prox;
    }
    lista->ultima->prox = NULL;
    lista->ultima->string = (char*)malloc(strlen(string) * sizeof(char));
    strcpy(lista->ultima->string, string);
    
    lista->ultima->dados = (ApontadorDados)malloc(sizeof(Dados));
    lista->ultima->dados->idDoc = idDoc;
    lista->ultima->dados->qtde = 1;
    lista->ultima->dados->prox = NULL;
    
}

// A função tamanhoTabelaHash retorna o numero primo mais proximo da
// divisão da estimativa de chaves pelo fator de carga
int tamanhoTabelaHash(int N){
    int m, a;        // a representa o fator de carga
    int totalChaves; // numero aproximado de palavras na tabela hash
    int i, j, soma;
    int primoAntecessor, primoSucessor;
    totalChaves = N * 50;
    a = 4;
    m = totalChaves / a;
    for(i = m ; i >= 0; i--){
        soma = 0;
        for (j = 2; j <= i / 2; j++) {
            if (i % j == 0) {
                soma++;
                break;
            }
        }
        if(soma == 0){
            primoAntecessor = i;
            break;
        }
    }
    for(i = m ; i <= m + 1000; i++){
        soma = 0;
        for (j = 2; j <= i / 2; j++) {
            if (i % j == 0) {
                soma++;
                break;
            }
        }
        if (soma == 0){
            primoSucessor = i;
            break;
        }
    }
    if(m - primoAntecessor < primoSucessor - m){
        return primoAntecessor;
    }
    else{
        return primoSucessor;
    }
}

void ImprimirIndiceInvertidoHash(TabelaHash *tabelaHash){
    ListaAux *inicio;
    ListaAux *aux;
    ApontadorDados dados;
    inicio = NULL;
    int i, M;
    M = tabelaHash->M;
    for(i = 0; i < M; i++){
        inicio = criaListaAuxOrdenada(inicio, &tabelaHash->tabela_hash[i]);
    }
    aux = inicio;

    while(aux != NULL){
        printf("%s  ", aux->celula->string);
        dados = aux->celula->dados;
        while(dados != NULL){
            printf("<%d,%d> ", dados->qtde, dados->idDoc);
            dados = dados->prox;
        }
        printf("\n");
        aux = aux->prox;
    }
}

ApontadorListaAux criaListaAuxOrdenada(ListaAux *inicio, Lista *lista){
    int indice;
    ApontadorListaAux novo;
    ApontadorListaAux auxInicio;
    ApontadorListaAux aux;
    ApontadorCelula celula;
    celula = lista->inicio;
    int i = 0;
    celula = lista->inicio;
    auxInicio = inicio;
    if(celula == NULL){
        return auxInicio;
    }
    int p = 0;
    if(inicio == NULL){
        novo = (ApontadorListaAux)malloc(sizeof(ListaAux));
        novo->celula = celula;
        novo->prox = NULL;
        inicio = novo;
        auxInicio = novo;
        novo = novo->prox;
        celula = celula->prox;
        p++;
    }
    auxInicio = inicio;

    while(celula != NULL){
        novo = (ApontadorListaAux)malloc(sizeof(ListaAux));
        novo->celula = celula;
        aux = auxInicio;
        indice = comparaString(celula->string, auxInicio->celula->string);
        if(indice < 0){
            novo->prox = auxInicio;
            auxInicio = novo;
        }

        else{
            int k = 0;
            while(aux != NULL){
                if(aux->prox != NULL){
                    indice = comparaString(celula->string, aux->prox->celula->string);
                    if(indice < 0){
                        novo->prox = aux->prox;
                        aux->prox = novo;
                        break;
                    }
                }
                else{
                    novo->prox = NULL;
                    aux->prox = novo;
                    aux = aux->prox;
                }
                aux = aux->prox;
                k++;
            }
        }
        celula = celula->prox;
        p++;
    }
    return auxInicio;
}

int comparaString(char *stringInserir, char *stringInserida){
    int indice;
    indice = strcmp(stringInserir, stringInserida);
    return indice;
}
