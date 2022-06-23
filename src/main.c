//Angelo - 4695
//Arthur - 4679
//Iury - 4671

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "arquivo/manipulacaoArquivo.h"


int main(){
    TabelaHash tabelaHash;
    TArvore raiz = NULL;
    int escolha;
    bool continuar, arquivoEntrada, construirIndice;
    bool erroAbrirArquivo;

    continuar = true;
    arquivoEntrada = false;
    construirIndice = false;
    char *arquivosTeste[100];
    int N;
    int i;

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
        clearStdin();
        printf("\n");
        
        switch (escolha){
            case 1:{
                // chama aqui a função para ler o arquivo de entrada, e os arquivos de teste
                erroAbrirArquivo =  leituraArquivoEntrada(arquivosTeste, &N);
                if(erroAbrirArquivo){
                    system("pause");
                    return 0;
                }
                arquivoEntrada = true;
                break;
            }

            case 2:{
                if(arquivoEntrada){
                    leituraTextos(&tabelaHash, arquivosTeste, N);
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
                    ImprimirIndiceInvertidoHash(&tabelaHash);
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
                    buscaPorTexto(&tabelaHash);
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
    
    system("pause");
    return 0;
}
