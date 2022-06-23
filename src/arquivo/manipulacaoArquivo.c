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
        printf("Erro na abertura do arquivo de entrada\n");
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

void leituraTextos(TabelaHash *tabelaHash, char **arquivosTeste,  int N){
    char *str1 = "../TP1-AEDS2/tests/";
    char buffer[50];
    char buffer1[50];
    char buffer2[50];
    int i, j;
    Inicializa(tabelaHash, N);
    for(i = 0; i < N; i++){
        strcat(strcpy(buffer, str1), arquivosTeste[i]);
        FILE *file;
        file = fopen(buffer, "r");
        if(file == NULL){
            printf("Erro na abertura do arquivo de teste: %s\n", buffer);
            continue;
        }
        while (!feof(file)){
            fscanf(file,"%s ", buffer1);
            j = 0;
            while(buffer1[j] != '\0'){
                buffer2[j] = tolower(buffer1[j]);
                j++;
            }
            buffer2[j] = '\0';
            Inserir(tabelaHash, buffer2, i);
        }
        fclose(file);
    }
}
