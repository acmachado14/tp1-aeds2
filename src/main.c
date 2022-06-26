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
    TipoPatNo *pat = NULL;
    int escolha;
    bool continuar, arquivoEntrada, construirIndiceTabela, construirIndicePatricia;
    bool erroAbrirArquivo;

    continuar = true;
    arquivoEntrada = false;
    construirIndiceTabela = false;
    construirIndicePatricia = false;

    char *arquivosTeste[100];
    int N;

    while(continuar){
        printf("------------------------------------------------------------------------------\n");
        printf("Digite um dos numeros para escolher uma das opcoes:\n");
        printf("1 - Para receber o arquivo de entrada: \n");
        printf("2 - Para construir o indice invertido pela Tabela Hash: \n");
        printf("3 - Para construir o indice invertido pela Arvore Patricia: \n");
        printf("4 - Para imprimir o indice invertido construido pela Tabela Hash: \n");
        printf("5 - Para imprimir o indice invertido construido pela Arvore Patricia:\n");
        printf("6 - Para realizar buscas por textos pela Tabela Hash: \n");
        printf("7 - Para realizar buscas por textos pela Arvore Patricia:\n");
        printf("8 - Para finalizar o programa: \n\n");
        printf("Digite um numero: ");
        scanf("%d", &escolha);
        clearStdin();
        printf("\n");

        switch (escolha){
            case 1:{
                if(arquivoEntrada){
                    printf("O arquivo de entrada ja foi recebido.\n");
                    printf("Deseja receber outro arquivo de entrada. Voce tera que reconstruir os"
                          " incices invertidos, casso tenha construidos.\n");
                    int opcao;
                    printf("1 - Sim\n2 - Nao:\nDigite: ");
                    scanf("%d", &opcao);
                    clearStdin();
                    while(opcao < 1 || opcao > 2){
                        printf("1 - Sim\n2 - Nao:\nDigite: ");
                        scanf("%d", &opcao);
                    }
                    if(opcao == 2){
                        break;
                    }
                    arquivoEntrada = false;
                    construirIndiceTabela = false;
                    construirIndicePatricia = false;

                }
                erroAbrirArquivo =  leituraArquivoEntrada(arquivosTeste, &N);
                if(erroAbrirArquivo){
                    printf("Digite um nome de arquivo valido.\n");
                    break;
                }
                arquivoEntrada = true;
                break;
            }

            case 2:{
                if(construirIndiceTabela){
                    printf("O indice invertido da Tabela Hash ja foi construido.\n");
                    printf("Escolha outra opcao\n");
                    break;
                }
                if(arquivoEntrada){
                    erroAbrirArquivo =  construirIndiceInvertidoHash(&tabelaHash, arquivosTeste, N);
                    if(erroAbrirArquivo){
                        printf("Voce sera redirecionado ao menu.\n");
                        break;
                    }
                    construirIndiceTabela = true;
                    printf("Indice invertido criado para a Tabela Hash\n");
                }
                else{
                    printf("Precisa escolher a opcao de numero 1 primeiro para selecionar esta opcao.\n");
                }
                break;
            }

            case 3:{
                if(construirIndicePatricia){
                    printf("O indice invertido da Arvore Patricia ja foi construido.\n");
                    printf("Escolha outra opcao\n");
                    break;
                }
                if(arquivoEntrada){
                    // deve passar os parametros necessarisos para inserir na arvore patricia
                    erroAbrirArquivo =  construirIndiceInvertidoPatricia(&pat, arquivosTeste, N);
                    if(erroAbrirArquivo){
                        printf("Voce sera redirecionado ao menu.\n");
                        break;
                    }
                    construirIndicePatricia = true;
                    printf("Indice invertido criado para a Arvore Patricia\n");
                }
                else{
                    printf("Precisa escolher a opcao de numero 1 primeiro para selecionar esta opcao.\n");
                }
                break;
            }

            case 4:{
                if(arquivoEntrada && construirIndiceTabela){
                    ImprimirIndiceInvertidoHash(&tabelaHash);
                }
                else{
                    if(!arquivoEntrada){
                        printf("Precisa escolher a opcao de numero 1 primeiro, depois a opcao de numero 2 para selecionar esta opcao.\n");
                    }
                    else if(arquivoEntrada && !construirIndiceTabela){
                        printf("Precisa escolher a opcao de numero 2 primeiro para selecionar esta opcao.\n");
                    }
                }
                break;
            }

            case 5:{
                if(arquivoEntrada && construirIndicePatricia){
                    ImprimePalavras(pat);
                }
                else{
                    if(!arquivoEntrada){
                        printf("Precisa escolher a opcao de numero 1 primeiro, depois a opcao de numero 3 para selecionar esta opcao.\n");
                    }
                    else if(arquivoEntrada && !construirIndicePatricia){
                        printf("Precisa escolher a opcao de numero 3 primeiro para selecionar esta opcao.\n");
                    }
                }
                break;
            }

            case 6:{
                if(arquivoEntrada && construirIndiceTabela){
                    int Memoria = 0;
                    clock_t tempo = clock();
                    buscaPorTexto(&tabelaHash, &Memoria);
                    tempo = clock() - tempo;
                    printf("Tempo de execucao: %f ms\nMemoria alocada: %d bytes\n\n", ((float)(tempo) * 1000)/(CLOCKS_PER_SEC), Memoria);
                }
                else{
                    if(!arquivoEntrada){
                        printf("Precisa escolher a opcao de numero 1 primeiro, depois a opcao de numero 2 para selecionar esta opcao.\n");
                    }
                    else if(arquivoEntrada && !construirIndiceTabela){
                        printf("Precisa escolher a opcao de numero 2 primeiro para selecionar esta opcao.\n");
                    }

                }
                break;
            }

            case 7:{
                if(arquivoEntrada && construirIndicePatricia){
                    int Memoria = 0;
                    clock_t tempo = clock();
                    buscaPorTextoPat(pat, N, &Memoria);
                    tempo = clock() - tempo;
                    printf("Tempo de execucao: %f ms\nMemoria alocada: %d bytes\n\n", ((float)(tempo) * 1000)/(CLOCKS_PER_SEC), Memoria);
                }
                else{
                    if(!arquivoEntrada){
                        printf("Precisa escolher a opcao de numero 1 primeiro, depois a opcao de numero 3 para selecionar esta opcao.\n");
                    }
                    else if(arquivoEntrada && !construirIndicePatricia){
                        printf("Precisa escolher a opcao de numero 3 primeiro para selecionar esta opcao.\n");
                    }

                }
                break;
            }

            case 8:{
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
    //system("pause");
    return 0;
}
