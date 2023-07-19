#ifndef _QUICK_SORT_EXTERNO_
#define _QUICK_SORT_EXTERNO_

#include "aluno.h"
#include "argumentos.h"

// typedef Aluno Area[20];
#define TAM_AREA 20
typedef struct {
    Aluno alunos[TAM_AREA];
    int numero_alunos = 0;
} Area;

void ordenaQuickSort(char*, Argumentos);


//ArqLEs gerencia o Ls(Limite Superior) e o Es (Escrita Superior)
//ArqLi gerencia o Li ( Limite Inferior)
//ArqEi gerencia o Ei ( Escrita Inferior)
void QuickSortExterno(FILE **, FILE **, FILE**, int, int);
//FazAreaVazia
void FAVazia(Area*);

//A partição vai retornar os valores de I e J, para eu poder realizar o QuickSort
void particao(FILE **, FILE **, FILE**, Area, int, int, int*, int*);

void leSuperior(FILE**, Aluno*, int*, bool*);

void leInferior(FILE**, Aluno*, int*, bool*);

//insere o Aluno de forma ordenada na Área
void inserirArea(Area*, Aluno*, int*);

//Insere item ordenadamente na área.
void insereItem(Aluno *, Area*);

int obterNumCelOcupadas(Area *);

//escreve do lado superior
void escreveMax(FILE **, Aluno, int *);

//escreve do lado inferior
void escreveMin(FILE **, Aluno, int *);

void retiraMax(Area *, Aluno *, int *);

void retiraMin(Area *, Aluno *, int *);

void retiraUltimo(Area *, Aluno *);

void retiraPrimeiro(Area *, Aluno *);


#endif