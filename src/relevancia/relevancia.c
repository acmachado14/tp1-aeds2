//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include "relevancia.h"

// Função que de acordo com os termos inseridos pelo usuario, retorna para o usuario os arquivos inseridos
// de acordo com sua relevancia
void buscaPorTexto(TabelaHash *tabelaHash, int *Memoria){
    int q = 0; // q representa a quantidade de termos a serem buscados
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
    (*Memoria) += sizeof(**termos);
    for(i = 0; i < q; i++){
        printf("Termo %d: ", i + 1);
        scanf("%s", termos[i]);
        clearStdin();
    }
    int N;
    N = tabelaHash->N;
    float r;
    // A arvore BST ArvoreRelevancia guarda a relevancia os dos documentos
    ArvoreRelevancia raiz;
    inicializaArvoreRelevancia(&raiz.no);
    for(i = 0; i < N; i++){
        r = relevanciaDocumento(tabelaHash, termos, i, q);
        insercaoR(&raiz.no, r, i);
        (*Memoria) += sizeof(NoRelevancia*);
    }
    printf("\nRelevancia dos textos:\n\n");
    percursoRelevancia(&raiz.no);
    freeArvoreRelevancia(&raiz.no);
}


// Função que calcula a relevancia de um documento atravez do TF-IDF dos termos em um documento
float relevanciaDocumento(TabelaHash *tabelaHash, char **termos, int idDoc, int q){
    ApontadorDados dados;
    ApontadorCelula celula;
    Lista *lista;

    int i, M;
    double N;
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
    double logN;
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
                continue;
            }
        }
        else{
            printf("O termo %s nao esta na tabela hash.\n", termos[i]);
            continue;
        }
        logN = log2(N);
        w = f * logN / dj;
        r += w;
    }
    r = r / ni;
    return r;
}

// AS próximas três funções servem para inicializar a arvore BST, inserir as relevancias dos documentos na arvore
// e imprimir os nomes dos arquivos de acordo com sua relevancia, do arquivo de maior relevancia para o de menor relevancia
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

// Função para liberar memória
void freeArvoreRelevancia(NoRelevancia **no){
    if((*no) != NULL){
        freeArvoreRelevancia(&(*no)->esq);
        freeArvoreRelevancia(&(*no)->dir);
        free((*no));
        (*no) = NULL;
    }
}

// Funcão de limpar buffer
void clearStdin(void){
    int c = getchar();
    while( c != '\n' && c != EOF){
        c = getchar();
    }
}

//Patricia-------------------------------------------------------------------------------------------

void buscaPorTextoPat(TipoPatNo *patricia, int N, int *Memoria){
    int q = 0; // q representa a quantidade de termos a serem buscados
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
    (*Memoria) += sizeof(**termos);
    for(i = 0; i < q; i++){
        printf("Termo %d: ", i + 1);
        scanf("%s", termos[i]);
        clearStdin();
    }

    float r; //relevancia

    ArvoreRelevancia raiz;
    inicializaArvoreRelevancia(&raiz.no);
    for(i = 0; i < N; i++){
        r = relevanciaDocumentoPat(patricia, termos, i, q, N);
        insercaoR(&raiz.no, r, i);
        (*Memoria) += sizeof(NoRelevancia*);
    }
    printf("\nRelevancia dos textos:\n\n");
    percursoRelevancia(&raiz.no);
    freeArvoreRelevancia(&raiz.no);
}


// Função que calcula a relevancia de um documento atravez do TF-IDF dos termos em um documento
float relevanciaDocumentoPat(TipoPatNo *patricia, char **termos, int idDoc, int q, int N){

    //q = quantidade de palavras a serem pesquisadas OK

    //ni = número de termos distintos do documento i OK

    //w = peso do termo tj no documento i

    //f = número de ocorrências do termo tj no documento i OK

    //dj = número de documentos na coleção que contém o termo tj OK

    //N = número de documentos na coleção. OK

    int ni, dj, f;
    float w, r;
    r = 0.0;
    double logN;
    logN = log2(N);

    ni = numDistintosPat(patricia,idDoc);
    for(int i = 0; i<q; i++){
        f = 0;
        f = numOcorrenciasTermoPat(patricia, termos[i],idDoc);
        dj = numeroDocumentosTermoPat(patricia, termos[i],N);
    
        if (dj == 0){
            dj = 1;
        }

        w = f * logN / dj;
        r += w;
    }
    r = r / ni;
    return r;
}

int numDistintosPat(TipoPatNo *patricia, int idDoc){
    if (patricia->notipo == externo) {
        ApontadorDadosPat dados;
        dados = patricia->PatNo.NoExterno.dados;
        while (dados != NULL){
            if(dados->idDoc == idDoc){
                return 1;
            }
            dados = dados->prox;
        }
        return 0;
    }
    return numDistintosPat(patricia->PatNo.NoInterno.esquerda, idDoc) + numDistintosPat(patricia->PatNo.NoInterno.direita, idDoc);
}

int numOcorrenciasTermoPat(TipoPatNo *patricia, char *termo, int idDoc){
    if (patricia->notipo == externo) {
        if (!strcmp(patricia->PatNo.NoExterno.chave, termo)){
            ApontadorDadosPat dados;
            dados = patricia->PatNo.NoExterno.dados;
            while (dados != NULL){
                if(dados->idDoc == idDoc){
                    return dados->qtde;
                }
                dados = dados->prox;
            }
        }
        return 0;
    }
    return numOcorrenciasTermoPat(patricia->PatNo.NoInterno.esquerda, termo, idDoc) + numOcorrenciasTermoPat(patricia->PatNo.NoInterno.direita, termo, idDoc);
}

int numeroDocumentosTermoPat(TipoPatNo *patricia, char *termo, int N){
    int resultado = 0;
    int aux = 0;
    for (int i = 0; i < N; i++){
        aux = numOcorrenciasTermoPat(patricia, termo, i);
        if (aux > 1){
            resultado += 1;
        }
    }
    return resultado;
}