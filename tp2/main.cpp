#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>

#include "argumentos.h"
#include "aluno.h"
#include "converteBin.h"
#include "desempenho.h"
#include "fitas.h"
#include "quickSortExterno.h"

using namespace std;
using namespace std::chrono;

void geraBinario(Argumentos*, char**);
void imprimeRegistrosBinario(char*);

int main(int argc, char *argv[]) {


    Fita fita;

    srand(time(NULL));

    //Cria e inicializa as variáveis de controle
    Desempenho desempenho;
    // iniciaDesempenho(&desempenho);

    // Informa erro quando o número de argumentos é inválido
    if(argc < 4 || argc > 5) {
        cout << "Número de argumentos inválidos! São 4 ou 5.\n"
            << "Linha de execução: ./ordena <método> <quantidade> <situação> [-P]\n"
            << "\tExemplo 1 de execução: ./ordena 1 100 3\n"
            << "\tExemplo 2 de execução: ./ordena 2 100000 1 [-P]\n";
        return 0;
    }
    
    // Coloca os argumentos num TAD de Argumentos
    Argumentos argumentos;
    argumentos.metodoOrdenacao = atoi(argv[1]);
    argumentos.quantidadeAlunos = atoi(argv[2]);
    argumentos.tipoOrdenacao = atoi(argv[3]);


    // Verifica se a impressão dos registros foi requerida
    if(argc == 5 && !strcmp("-P", argv[4]))
        argumentos.p = true;

    else
        argumentos.p = false;

    // Informa erro quando o número do método é inválido
    if(argumentos.metodoOrdenacao < 1 || argumentos.metodoOrdenacao > 3) {
        cout << "Valor inválido. Os métodos são:\n"
            << "1 - Intercalação balanceada de vários caminhos (2f fitas), utilizando o mergesort para ordenação;\n"
            << "2 - Intercalação balanceada de vários caminhos (2f fitas), utilizando seleção por substituição.\n"
            << "3 - Quicksort externo;\n";
        return 0;
    }
    
    // Informa erro quando o número de alunos é inválido
    else if(argumentos.quantidadeAlunos < 100 || argumentos.quantidadeAlunos > 471705) {
        cout << "Quantidade de Alunos inválida.\n"
            << "Deve estar entre 100 e 471.705";
        return 0;
    }
    
    // Informa erro quando o número do tipo de ordenação é inválido
    else if(argumentos.tipoOrdenacao < 1 || argumentos.tipoOrdenacao > 3) {
        cout << "Situação inválida. A situação do aquivo pode ser:\n"
            << "1 - Arquivo ordenado ascendentemente;\n"
            << "2 - Arquivo ordenado descendentemente;\n"
            << "3 - Arquivo desordenado aleatoriamente.\n";
        return 0;
    }


    char *nomeArquivoBinario = NULL;
    geraBinario(&argumentos, &nomeArquivoBinario);

    switch(argumentos.metodoOrdenacao) {
        
        case 1:
            break;

        case 2:

            break;

        case 3:
            ordenaQuickSort(nomeArquivoBinario, argumentos);
            break;


    } 

    free(nomeArquivoBinario);
    return 0;
}

void geraBinario(Argumentos *argumentos, char **nomeArquivoBinario) {

    char *nomeArquivoTexto = (char*) malloc(50 * sizeof(char));

    switch(argumentos->tipoOrdenacao) {

        case 1:
            strcpy(nomeArquivoTexto, "provaoCrescente.txt");
            *nomeArquivoBinario = trocaExtensao(nomeArquivoTexto);
            break;
    
        case 2:
            strcpy(nomeArquivoTexto, "provaoDecrescente.txt");
            *nomeArquivoBinario = trocaExtensao(nomeArquivoTexto);
            break;
    
        case 3:
            strcpy(nomeArquivoTexto, "provaoAleatorio.txt");
            *nomeArquivoBinario = trocaExtensao(nomeArquivoTexto);
            break;
    }



    textoParaBinario(nomeArquivoTexto, *nomeArquivoBinario);
    imprimeRegistrosBinario(*nomeArquivoBinario);

    free(nomeArquivoTexto);
}

void imprimeRegistrosBinario(char *nomeArquivoBinario) {
    
    FILE *arquivoBinario;
    Aluno aluno;
    

    // Tenta abrir o arquivo binário e retorna erro caso não consiga
    if((arquivoBinario = fopen(nomeArquivoBinario, "rb")) == NULL) {
        cout << "Erro na abertura do arquivo binário para impressão dos registros.\n";
        return;
    }

    cout << "----------------------------" << endl;
    // Imprime os registros
    while(fread(&aluno, sizeof(Aluno), 1, arquivoBinario)) {
        cout << aluno.numeroInscricao << "|" << aluno.nota << "|" << aluno.estado << "|" << 
        aluno.cidade << "|" << aluno.curso << "|\n";
    }

    cout << "----------------------------" << endl;

    fclose(arquivoBinario);
    return;
}