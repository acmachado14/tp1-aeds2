//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include "manipulacaoArquivo.h"
#include <ctype.h>

// Função que lê o arquivo de entrada e guarda os nomes dos arquivos de teste em arquivosTeste,
//  é a quantidade de arquivos de teste em N
bool leituraArquivoEntrada(char **arquivosTeste, int *N){
    char arquivoEntrada[50];
    char *str1 = "tests/";
    char buffer[50];
    char buffer1[50];
    printf("Digite o nome do arquivo de entrada (exemplo: entrada.txt): ");
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

// Lê os arquivos de teste, e chama a função de inserir na tabela hash para cada palavra
bool construirIndiceInvertidoHash(TabelaHash *tabelaHash, char **arquivosTeste,  int N){
    char *str1 = "tests/";
    char buffer[50];
    char buffer1[50];
    char buffer2[50];
    int i, j;
    clock_t clockTabela, clockAux1;
    clockTabela = clock();

    int Memoria = 0;
    InicializaTabelaHash(tabelaHash, N, &Memoria);
    clockTabela = clock() - clockTabela;
    for(i = 0; i < N; i++){
        // Concatena o nome do arquivo de teste com o caminho da pasta onde ele está para que sejá possivel abrir ele
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
                buffer2[j] = tolower(buffer1[j]); // Função que converte um caractere maiusculo em minusculo
                j++;
            }
            buffer2[j] = '\0';
            clockAux1 = clock();
            InserirTabelaHash(tabelaHash, buffer2, i, &Memoria);
            clockAux1 = clock() - clockAux1;
            clockTabela = clockAux1 + clockTabela;
        }
        fclose(file);
    }
    printf("Tempo de execucao: %f ms\nMemoria alocada: %d bytes\n\n", ((float)(clockTabela) * 1000)/(CLOCKS_PER_SEC), Memoria);
    return false;
}

// Lê os arquivos de teste, e chama a função de inserir na arvore patrici para cada palavra
bool construirIndiceInvertidoPatricia(TipoPatNo **pat, char **arquivosTeste,  int N){
    char *str1 = "tests/";
    char buffer[50];
    char buffer1[50];
    char buffer2[50];
    int i, j;
    clock_t clockTabela, clockAux1;
    clockTabela = clock();
    clockTabela = clock() - clockTabela;

    int Memoria = 0;

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
            (*pat) = Insere(buffer2, pat, &Memoria, i);
            clockAux1 = clock() - clockAux1;
            clockTabela = clockAux1 + clockTabela;
        }
        fclose(file);
    }
    printf("Tempo de execucao: %f ms\nMemoria alocada: %d bytes\n\n", ((float)(clockTabela) * 1000)/(CLOCKS_PER_SEC), Memoria);
    return false;
}
