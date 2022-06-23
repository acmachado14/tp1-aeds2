//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree/patricia.h"
#include "hash/relevancia.h"

typedef char *String;

void LerDoc(String teste,String vetores[5000],int *tam){
    int i = 0;
    int numPalavras = 0;
    char line[5000];
    FILE *arquivo;

    arquivo = fopen(teste, "r");
    if (arquivo == NULL){
        puts("\nArquivo nao Encontrado\n");
        return;
    }
    
    while(fgets(line,sizeof line, arquivo) != NULL){
        vetores[i] = strdup(line);
    
        i++;
        (*tam)++;
        numPalavras++;
    }

    fclose(arquivo);
}


int main(){
    TArvore raiz = NULL;

    int escolha;
    bool continuar, arquivoEntrada, construirIndice;

    continuar = true;
    arquivoEntrada = false;
    construirIndice = false;

    char **arquivosTeste;
    int *N;
    while(continuar){
        printf("------------------------------------------------------------------------------\n");
        printf("Digite um dos numeros para escolher uma das opcoes:\n");
        printf("1 - Para receber o arquivo de entrada: \n");
        printf("2 - Para construir o indice invertido: \n");
        printf("3 - Para imprimir o indice invertido construido pela Tabela Hash: \n");
        printf("4 - Para imprimir o indice invertido construido pela Arvore Patricia:\n");
        printf("5 - Para realizar buscas por textos pela Tabela Hash: \n");
        printf("6 - Para realizar buscas por textos pela Arvore Patricia:\n");
        printf("7 - Para finalizar o programa: \n");
        printf("Digite um numero: ");
        scanf("%d", &escolha);
        //clearStdin();
        printf("\n");
        
        switch (escolha){
            case 1:{
                // chama aqui a função para ler o arquivo de entrada, e os arquivos de teste
                arquivoEntrada = true;

                int i;
                char teste[46];
                String vetores[5000];
                String str1 = "tests/";
                String str2 = ".txt";
                char buffer[50];
                char buffer2[50];

                printf("Digite o nome do teste a ser executado na pasta de testes: \n");
                scanf("%s", &teste);

                strcat(strcpy(buffer, str1), teste);

                strcpy(buffer2, buffer);

                strcat(strcpy(buffer, buffer), str2);
                int tam = 0;
                String *palavra;

                LerDoc(buffer,vetores,&tam);
                for (i=0;i<tam;i++){
                    palavra = (String)malloc(sizeof(char)*30);

                    palavra = vetores[i];
                    //printf("%s", palavra);
                    raiz = Insere(palavra, &raiz);
                }
                Ordem(raiz);

                break;
            }

            case 2:{
                if(arquivoEntrada){
                    // chama aqui a função Para construir o indice invertido:
                    construirIndice = true;
                }
                else{
                    printf("Precisa escolher a opcao de numero 1 primeiro para selecionar esta opcao.\n");
                }
                break;
            }

            case 3:{
                if(arquivoEntrada && construirIndice){
                    // chama aqui a função Para imprimir o indice invertido construido pela Tabela Hash:
                }
                else{
                    if(!arquivoEntrada){
                        printf("Precisa escolher a opcao de numero 1 primeiro, depois a opcao de numero 2 para selecionar esta opcao.\n");
                    }
                    else if(arquivoEntrada && !construirIndice){
                        printf("Precisa escolher a opcao de numero 2 primeiro para selecionar esta opcao.\n");
                    } 
                }
                break;
            }

            case 4:{
                if(arquivoEntrada && construirIndice){
                    // chama aqui a função Para imprimir o indice invertido construido pela Arvore Patricia:
                }
                else{
                    if(!arquivoEntrada){
                        printf("Precisa escolher a opcao de numero 1 primeiro, depois a opcao de numero 2 para selecionar esta opcao.\n");
                    }
                    else if(arquivoEntrada && !construirIndice){
                        printf("Precisa escolher a opcao de numero 2 primeiro para selecionar esta opcao.\n");
                    }
                }
                break;
            }

            case 5:{
                if(arquivoEntrada && construirIndice){
                    // chama aqui a função Para realizar buscas por textos pela Tabela Hash:
                }
                else{
                    if(!arquivoEntrada){
                        printf("Precisa escolher a opcao de numero 1 primeiro, depois a opcao de numero 2 para selecionar esta opcao.\n");
                    }
                    else if(arquivoEntrada && !construirIndice){
                        printf("Precisa escolher a opcao de numero 2 primeiro para selecionar esta opcao.\n");
                    }
                    
                }
                break;
            }

            case 6:{
                if(arquivoEntrada && construirIndice){
                    // chama aqui a função Para realizar buscas por textos pela Arvore Patricia:
                }
                else{
                    if(!arquivoEntrada){
                        printf("Precisa escolher a opcao de numero 1 primeiro, depois a opcao de numero 2 para selecionar esta opcao.\n");
                    }
                    else if(arquivoEntrada && !construirIndice){
                        printf("Precisa escolher a opcao de numero 2 primeiro para selecionar esta opcao.\n");
                    }
                    
                }
                break;
            }

            case 7:{
                continuar = false;
                printf("Saindo do programa...\n");
                break;
            }

            default:{
                printf("Digite um numero valido\n");
                break;
            }

        }
        printf("------------------------------------------------------------------------------\n\n");

    }
    return 0;
}
