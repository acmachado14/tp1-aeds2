//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree/patricia.h"

typedef char *String;

void LerDoc(String teste,String vetores[5000],int *tam){
    int i = 0;
    int j = 0;
    int numPalavras = 0;
    //String palavras[5000];
    char line[5000];
    FILE *arquivo;

    arquivo = fopen(teste, "r");
    if (arquivo == NULL){
        puts("y");
        return;
    }
    
    while(fgets(line, sizeof line, arquivo) != NULL)
    {
        //Adiciona cada palavra no vetor
        vetores[i] = strdup(line);

        i++;
        (*tam)++;

        //Conta a quantidade de palavras
        numPalavras++;
    }



    printf("\n\n");

    fclose(arquivo);
}

int main(int argc, char** argv) {
    //inicio

    int i;
    char teste[46];
    String vetores[5000];
    //scanf("%s",&teste);
    String str1 = "../tests/";
    String str2 = ".txt";
    char buffer[50];
    char buffer2[50];

    printf("Digite o nome do teste a ser executado na pasta de testes: \n");
    scanf("%s", &teste);

    strcat(strcpy(buffer, str1), teste);

    strcpy(buffer2, buffer);

    strcat(strcpy(buffer, buffer), str2);

    int tam = 0;
    LerDoc(buffer,vetores,&tam);
    for (i=0;i<tam;i++){
        printf("%s",vetores[i]);
    }
    return 0;
}
