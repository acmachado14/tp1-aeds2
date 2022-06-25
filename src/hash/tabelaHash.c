//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include "tabelaHash.h"

//Funcao que gera os pessos usados para achar o hash code de uma string
void GerarPesos(Pesos *pesos){
    pesos->pesos = (int*)malloc(100 * sizeof(int));
    int i;
    srand(time(NULL));
    for( i = 0; i < 100; i++){
        pesos->pesos[i] =  rand() % 1000 + 1;
    }
}

// Função para inicializar a tabela hash 
void InicializaTabelaHash(TabelaHash *tabelaHash, int N){
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

// Função que auxilia na inicializaçao da tabela hash
void FazListaVazia(Lista *lista){
    lista->inicio = NULL;
    lista->ultima = NULL;
}

// Função que gera o hash code usado para indicar a posição na tabela hash que uma string vai ser inserir,
//ou na buscar a posição na tabela hash que a string pode estar
int HashFunction(Pesos pesos, char *string, int M){
    int i, K = 0;
    int tamanhoString;
    tamanhoString = strlen(string);
    for(i = 0; i < tamanhoString; i++){
        K += string[i] * pesos.pesos[i];
    }
    return K % M;
}

void InserirTabelaHash(TabelaHash *tabelaHash, char *string, int idDoc){
    int hashCode;
    int N, M;
    M = tabelaHash->M;
    hashCode = HashFunction(tabelaHash->pesos, string, M);
    IInseri(&tabelaHash->tabela_hash[hashCode], string, idDoc);
}

// Função que realmente inseri na tabela hash
void IInseri(Lista *lista, char *string, int idDoc){
    ApontadorDados dadosAux;
    ApontadorCelula celula;

    celula = lista->inicio;
    // O while e o primeiro if verifica se a string a ser inserida já estar na tabela hash
    while (celula != NULL){
        if(! strcmp(celula->string, string)){
            dadosAux = celula->dados;
            // Caso a string já esteja na tabela hash, o próximo while é if verificão se a string já apareceu
            // alguma vez no documento que esta sendo lido, por meio do idDoc. Se ela ja tiver aparecido alguma vez, 
            // incrementa 1 na quantidade de vez que a string aparece naquele documento
            while(dadosAux != NULL){
                if(dadosAux->idDoc == idDoc){
                    dadosAux->qtde += 1;
                    return;
                }
                
                else{
                    // Caso a string não tenha aparecido ainda no documento que esta sendo lido, aloca-se memoria para uma
                    // struct que guarda o idDoc do documento que esta sendo lido, bem como a variavel que guarda a quantidade
                    // de vezes que a string aparece naquele documento recebe 1
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

    // Caso o algoritimo passe pelas verificações anteriores, indica que a string ainda não apareceu em 
    // nenhum documento e criase uma nova celula que guarda a string em questão e os dados passados com ela
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

// A função retorna o primeiro primo maior da divisão da estimativa de chaves pelo fator de carga
int tamanhoTabelaHash(int N){
    int m, a;        // a representa o fator de carga
    int totalChaves; // numero aproximado de palavras na tabela hash
    int i, j, soma;
    int primoAntecessor, primoSucessor;
    totalChaves = N * 25; // Se desejar almentar ou diminuir o tamanho da tabela hash deve almentar ou diminuir
                          // o número que multiplica N. Ele representa o numero aproximado de palavras diferentes por arquivo
    a = 4;
    m = totalChaves / a;
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
    return primoSucessor;
}

// Função para liberar memoria alocada na construção da tabela hash
void freeTabelaHash(TabelaHash *tabelaHash){
    ApontadorCelula celula;
    ApontadorDados dados;
    ApontadorCelula celulaAux;
    ApontadorDados dadosAux;
    Lista * lista;
    int M = tabelaHash->M;
    int i;
    for(i = 0; i < M; i++){
        lista = &tabelaHash->tabela_hash[i];
        celula = lista->inicio;
        while(celula != NULL){
            dados = celula->dados;
            while(dados != NULL){
                dadosAux = dados;
                dados = dados->prox;
                free(dadosAux);
            }
            celulaAux = celula;
            celula = celula->prox;
            free(celulaAux->string);
            free(celulaAux);
        }
    }
    free(tabelaHash->tabela_hash);
}
