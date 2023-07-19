#include <iostream>

#include <limits.h>

#include "quickSortExterno.h"

using namespace std;

void ordenaQuickSort(char *nomeArquivoBinario, Argumentos argumentos){

    cout << nomeArquivoBinario << endl;

    FILE *ArqLi, *ArqEi, *ArqLEs;

    if((ArqLi = fopen(nomeArquivoBinario, "rb+")) == NULL) {
        cout << "Erro na abertura do arquivo binário.\n";
        return;
    }

    if((ArqEi = fopen(nomeArquivoBinario, "rb+")) == NULL) {
        cout << "Erro na abertura do arquivo binário.\n";
        return;
    }

    if((ArqLEs = fopen(nomeArquivoBinario, "rb+")) == NULL) {
        cout << "Erro na abertura do arquivo binário.\n";
        return;
    }

    QuickSortExterno(&ArqLi, &ArqEi, &ArqLEs, 1, argumentos.quantidadeAlunos);
    
    fflush(ArqLi);

    fclose(ArqEi);
    fclose(ArqLEs);

    fseek(ArqLi, 0, SEEK_SET);
    Aluno aluno;
    int contador = 0;

    while(fread(&aluno, sizeof(Aluno), 1 ,ArqLi) && contador < argumentos.quantidadeAlunos){
        // cout << "Nota: " << aluno.nota << " -Inscricao Aluno: " << aluno.numeroInscricao << endl;
        contador++;
    }

    fclose(ArqLi);

    return;
}


void QuickSortExterno(FILE **ArqLi, FILE **ArqEi, FILE**ArqLEs, int esq, int dir){

    int i,j;
    
    Area area; // Area de armazenamento interna

    cout << "AAAAAAAAAAAAA" << endl;
    if (dir - esq < 1){
        cout << "i : " << i << " j: " << j << endl;
        return;
    } // Significa que não existe elementos, encerro o quicksort


    particao(ArqLi, ArqEi, ArqLEs, area, esq, dir, &i, &j);


    //Ordena primeiro o menor subarquivo. O 1 subarquivo, vai de esq a i, e a segunda partição vai de j a dir

    //ordena primeiro o subarquivo menor através de recursão
    if(i - esq < dir - j){
        QuickSortExterno(ArqLi, ArqEi, ArqLEs, esq, i);
        QuickSortExterno(ArqLi, ArqEi, ArqLEs, j, dir);
    } else {
        QuickSortExterno(ArqLi, ArqEi, ArqLEs, j, dir);
        QuickSortExterno(ArqLi, ArqEi, ArqLEs, esq, i);
    }
}

void particao(FILE **ArqLi, FILE **ArqEi, FILE**ArqLEs, Area area, int esq, int dir, int *i, int *j){

    int Ls = dir, Es = dir, Li = esq, Ei = esq, NRArea = 0, Linf = INT_MIN, Lsup = INT_MAX;
    bool ondeLer = true;
    //aluno vai ser o que será retirado da area
    Aluno ultimoAlunoLido, aluno;

    fseek(*ArqLi, (Li - 1) * sizeof(Aluno), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(Aluno), SEEK_SET);

    *i = esq - 1;
    *j = dir + 1;

    while(Ls >= Li){

        if(NRArea < TAM_AREA - 1){

            if(ondeLer)
                leSuperior(ArqLEs, &ultimoAlunoLido, &Ls, &ondeLer);
            else
                leInferior(ArqLi, &ultimoAlunoLido, &Li, &ondeLer);
                
            inserirArea(&area, &ultimoAlunoLido, &NRArea);
            continue;
        }

        if(Ls == Es)
            leSuperior(ArqLEs, &ultimoAlunoLido, &Ls, &ondeLer);

        else if (Li == Ei)
            leInferior(ArqLi, &ultimoAlunoLido, &Li, &ondeLer);

        else if (ondeLer)
            leSuperior(ArqLEs, &ultimoAlunoLido, &Ls, &ondeLer);

        else
            leInferior(ArqLi, &ultimoAlunoLido, &Li, &ondeLer);

        //funcao comparar alunos seria interessante!
        if(ultimoAlunoLido.nota > Lsup){
            *j = Es;
            escreveMax(ArqLEs, ultimoAlunoLido, &Es);
            continue;
        }

        if(ultimoAlunoLido.nota < Linf){
            *i = Ei;
            escreveMin(ArqEi, ultimoAlunoLido, &Ei);
            continue;
        }

        inserirArea(&area, &ultimoAlunoLido, &NRArea);

        if(Ei - esq < dir - Es){
            retiraMin(&area, &aluno, &NRArea);
            escreveMin(ArqEi, aluno, &Ei);
            Linf = aluno.nota;
        } else {
            retiraMax(&area, &aluno, &NRArea);
            escreveMax(ArqLEs, aluno, &Es);
            Lsup = aluno.nota;
        }
    }

    while(Ei <= Es){
        retiraMin(&area, &aluno, &NRArea);
        escreveMin(ArqEi, aluno, &Ei);
    }


}

void FAVazia(Area *area){
    area->numero_alunos = 0;
}

int obterNumCelOcupadas(Area *area){
    return area->numero_alunos;
}

//ondeLer é responsável por controlar a leitura alternada
//se for true le a parte superior

void leSuperior(FILE **ArqLEs, Aluno *aluno, int *Ls, bool *ondeLer){
    fseek(*ArqLEs, (*Ls -1) * sizeof(Aluno), SEEK_SET);
    fread(aluno, sizeof(Aluno), 1, *ArqLEs);
    (*Ls)--;
    *ondeLer = false;
}

//ondeLer é responsável por controlar a leitura alternada
//se for true le a parte superior
void leInferior(FILE **ArqLi, Aluno *aluno, int *Li, bool *ondeLer){
    fread(aluno, sizeof(Aluno), 1, *ArqLi);
    (*Li)++;
    *ondeLer = true;

}

//
void inserirArea(Area *area, Aluno *aluno, int *NRArea){
    cout << "Inserindo aluno:" << endl;
    imprimeAluno(aluno);

    cout << "------------------------" << endl;

    insereItem(aluno, area);
    *NRArea = obterNumCelOcupadas(area);

    // cout << "Tamanho Area: " << area->numero_alunos << endl;
    for(int i = 0; i < area->numero_alunos; i++){
        imprimeAluno(&(area->alunos[i]));
    }
    cout << "------------------------" << endl;

}

void insereItem(Aluno *aluno, Area *area){
    
    if(area->numero_alunos >= TAM_AREA)
        return;

    int insert_index = 0;

    for (int i = 0; i < area->numero_alunos; i++){
        if(aluno->nota > area->alunos[i].nota){
            insert_index++;
        } else 
            break;
    }

    for( int i = area->numero_alunos - 1; i >= insert_index; i--){
        area->alunos[i + 1] = area->alunos[i];
    }

    area->alunos[insert_index] = *aluno;
    (area->numero_alunos)++;
}


void escreveMax(FILE **ArqLEs, Aluno aluno, int *Es){
    fseek(*ArqLEs, (*Es - 1) * sizeof(Aluno), SEEK_SET);
    fwrite(&aluno, sizeof(Aluno), 1, *ArqLEs);
    (*Es)--;
}

void escreveMin(FILE **ArqEi, Aluno aluno, int *Ei){
    fwrite(&aluno, sizeof(Aluno), 1, *ArqEi);
    (*Ei)++;
}

void retiraMax(Area *area, Aluno *aluno, int *NRArea){
    retiraUltimo(area, aluno);
    *NRArea = obterNumCelOcupadas(area);
}

void retiraMin(Area *area, Aluno *aluno, int *NRArea){
    retiraPrimeiro(area, aluno);
    *NRArea = obterNumCelOcupadas(area);
}

void retiraUltimo(Area *area, Aluno *aluno){
    (area->numero_alunos)--;
}

void retiraPrimeiro(Area *area, Aluno *aluno){
    for(int i = 0; i < area->numero_alunos - 1; i++){
        area->alunos[i] = area->alunos[i + 1];
    }
    (area->numero_alunos)--;
}




