#include "manipulacaoArquivo.h"
#include <ctype.h>

bool leituraArquivoEntrada(char **arquivosTeste, int *N){
    char arquivoEntrada[50];
    char *str1 = "../TP1-AEDS2/tests/";
    char buffer[50];
    char buffer1[50];
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", arquivoEntrada);
    clearStdin();

    strcat(strcpy(buffer, str1), arquivoEntrada);
    FILE *file;
    file = fopen(buffer, "r");
    if(file == NULL){
        printf("Erro na abertura do arquivo de entrada !!!!!!!!\n");
        return true;
    }
    int n, i;
    fscanf(file, "%d ", &n);
    *N = n;
    i = 0;
    while (!feof(file)){
        fscanf(file,"%s ", buffer1);
        arquivosTeste[i] = strdup(buffer1);
        i++;
    }
    fclose(file);
    return false;
}

bool construirIndiceInvertidoHash(TabelaHash *tabelaHash, char **arquivosTeste,  int N){
    char *str1 = "../TP1-AEDS2/tests/";
    char buffer[50];
    char buffer1[50];
    char buffer2[50];
    int i, j;
    clock_t clockTabela, clockAux1;
    clockTabela = clock();
    Inicializa(tabelaHash, N);
    clockTabela = clock() - clockTabela;
    for(i = 0; i < N; i++){
        strcat(strcpy(buffer, str1), arquivosTeste[i]);
        FILE *file;
        file = fopen(buffer, "r");
        if(file == NULL){
            printf("Erro na abertura do arquivo de teste: %s\n", buffer);
            return true;
        }
        while (!feof(file)){
            fscanf(file,"%s ", buffer1);
            j = 0;
            while(buffer1[j] != '\0'){
                buffer2[j] = tolower(buffer1[j]);
                j++;
            }
            buffer2[j] = '\0';
            clockAux1 = clock();
            Inserir(tabelaHash, buffer2, i);
            clockAux1 = clock() - clockAux1;
            clockTabela = clockAux1 + clockTabela;
        }
        fclose(file);
    }
    printf("Tempo de construcao do indice invertido pela Tabela Hash: %f segundos\n", ((float)(clockTabela))/(float)CLOCKS_PER_SEC);
    return false;
}

bool construirIndiceInvertidoPatricia(TArvore *raiz, char **arquivosTeste,  int N){
    char *str1 = "../TP1-AEDS2/tests/";
    char buffer[50];
    char buffer1[50];
    char buffer2[50];
    int i, j;
    clock_t clockArvore, clockAux1;
    clockArvore = clock();
    // Chama aqui alguma função para inicializar a arvore, se precisar
    clockArvore = clock() - clockArvore;

    for(i = 0; i < N; i++){
        strcat(strcpy(buffer, str1), arquivosTeste[i]);
        FILE *file;
        file = fopen(buffer, "r");
        if(file == NULL){
            printf("Erro na abertura do arquivo de teste: %s\n", buffer);
            return true;
        }
        while (!feof(file)){
            fscanf(file,"%s ", buffer1);
            j = 0;
            while(buffer1[j] != '\0'){
                buffer2[j] = tolower(buffer1[j]);
                j++;
            }
            buffer2[j] = '\0';
            clockAux1 = clock();

            // Chama aqui a função de inserir na arvore patricia, passando a string que esta em buffer2
            // e o idDoc como sendo o indice i
        
            clockAux1 = clock() - clockAux1;
            clockArvore = clockAux1 + clockArvore;
        }
        fclose(file);
    }
    printf("Tempo de construcao do indice invertido pela Arvore Patricia: %f segundos\n", ((float)(clockArvore))/(float)CLOCKS_PER_SEC);
    return false;
}
