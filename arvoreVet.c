//Heloísa Louzada Borchardt Gomes - V06 - Trabalho 4 (Árvore sequêncial)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Tab_arvore.h"

#define TAMANHO_NOME 100

//MANIPULAÇÃO DE ARQUIVO..............................
FILE * abrirArquivo(char * nomeArq, char * modo) {
    FILE * arq = fopen( nomeArq, modo );
    if ( arq == NULL) {
        printf("ERRO ao abrir o arquivo.");
    }

    return arq;
}


void carregarArquivo(Arvore* arvore, FILE *arq){ 
    char nome[TAMANHO_NOME];
    long long int matricula;

    while (fgets(nome, sizeof(nome), arq) != NULL){
        nome[strcspn(nome, "\n")] = '\0';  
        if (fscanf(arq, "%I64d\n", &matricula) == 1){  
            Aluno* aluno = pesquisar(arvore, matricula);
            if (aluno == NULL) { 
                inserir(arvore, nome, matricula);  
            }
        }    
    }

}


void gravarArquivo(FILE *arquivo, Arvore* arvore) {
    Aluno *atual = arvore[0].vetorAluno;
    int i;    
    for (i = 0; i < arvore->tamanho; i++){
        if (arvore->status[i] == 1) {  
            fprintf(arquivo, "%s\n", atual->nome);              
            fprintf(arquivo, "%I64d\n", atual->matricula);      
        }
    }
    fclose(arquivo);
}


//FUNÇÕES AUXILIARES
long quantidadeElementos(FILE *arq){
            
    char nome[TAMANHO_NOME];
    long long int matricula;    
    long quantidade = 0;   

    
    while (fgets(nome, sizeof(nome), arq) != NULL){  
        if (fscanf(arq, "%I64d\n", &matricula) == 1){  
            quantidade++;  
        }
    }
  
    printf("\n\n\t\tA quantidade de alunos é:%ld\n", quantidade);

    
    return quantidade;
}


void procurarIndice(Arvore* arvore, Aluno novoAluno, int index) {
    if (index >= arvore->tamanho) {
        printf("Error\n");
        return;
    }

    if (arvore->status[index] == 0) {
        arvore->vetorAluno[index] = novoAluno;
        arvore->status[index] = 1;  
        return;
    }
     
    if (novoAluno.matricula < arvore->vetorAluno[index].matricula) {
        
        procurarIndice(arvore, novoAluno, 2 * index + 1);  
    } else {
        
        procurarIndice(arvore, novoAluno, 2 * index + 2);  
    }
}


Arvore* criarVetor(long tamanho) {
    int i;
    Arvore* planta = (Arvore*)malloc(sizeof(Arvore));
    if (planta == NULL) {
        printf("Error\n");
        return NULL;
    }

    planta->tamanho = (tamanho * 100);
    planta->vetorAluno = (Aluno*)malloc((tamanho * 100) * sizeof(Aluno));
    if (planta->vetorAluno == NULL) {
        printf("Error\n");
        free(planta);
        return NULL;
    }

    planta->status = (long*)malloc((tamanho * 100) * sizeof(long));
    if (planta->status == NULL) {
        printf("Error\n");
        free(planta->vetorAluno);
        free(planta);
        return NULL;
    }

    for (i = 0; i < (tamanho * 100); i++) {
        planta->status[i] = 0;
    }

    return planta;
}


//FUNÇÕES PRINCIPAIS MENU
void inserir(Arvore* arvore, char* nome, long long int matricula) {
    Aluno novoAluno;
    strcpy(novoAluno.nome, nome);
    novoAluno.matricula = matricula;

    if (arvore->status[0] == 0) {
        arvore->vetorAluno[0] = novoAluno;
        arvore->status[0] = 1; 
    } else {
        procurarIndice(arvore, novoAluno, 0);
        
    }
}


Aluno* pesquisar(Arvore* arvore, long long int matricula){
    long i = 0;
    while (i < arvore->tamanho) {
        if (arvore->status[i] == 0) {
            return NULL;
        }
        if (arvore->status[i] == 1 && arvore->vetorAluno[i].matricula == matricula) {
            return &arvore->vetorAluno[i];
        }
        i++;
    }
    return NULL;
}


void imprimir (Arvore* arvore){
    int i;
    for (i = 0; i < arvore->tamanho; i++) {
        if (arvore->status[i] == 1) {
            printf("índice %d -> Nome: %s, Matrícula: %I64d\n", i, arvore->vetorAluno[i].nome, arvore->vetorAluno[i].matricula);
        }
    }
}


void contarTotal(Arvore* arvore){
    int i, total = 0;
    for (i = 0; i < arvore->tamanho; i++) {
        if (arvore->status[i] == 1) {  
            total++;
        }
    }
    printf("O total é: %d\n", total);
}


int encontrarMenorIndice(Arvore* arvore, int index) {
    while (arvore->status[2 * index + 1] == 1) {
        index = 2 * index + 1;
    }
    return index;
}


void remover(Arvore* arvore, long long int matricula, int index) {
    if (index >= arvore->tamanho || arvore->status[index] == 0) {
        printf("Matrícula não encontrada.\n");
        return;
    }

    if (matricula < arvore->vetorAluno[index].matricula) {
        remover(arvore, matricula, 2 * index + 1);  
    } else if (matricula > arvore->vetorAluno[index].matricula) {
        remover(arvore, matricula, 2 * index + 2);  
    } else {
        
        if (arvore->status[2 * index + 1] == 0 && arvore->status[2 * index + 2] == 0) {
            arvore->status[index] = 0;

        } else if (arvore->status[2 * index + 1] == 0) {
            arvore->vetorAluno[index] = arvore->vetorAluno[2 * index + 2];
            arvore->status[index] = 1;
            arvore->status[2 * index + 2] = 0;

        } else if (arvore->status[2 * index + 2] == 0) {
            arvore->vetorAluno[index] = arvore->vetorAluno[2 * index + 1];
            arvore->status[index] = 1;
            arvore->status[2 * index + 1] = 0;

        } else {
            int menorinIndex = encontrarMenorIndice(arvore, 2 * index + 2);
            arvore->vetorAluno[index] = arvore->vetorAluno[menorinIndex];
            remover(arvore, arvore->vetorAluno[menorinIndex].matricula, menorinIndex);
        }
    }
}


// FUNÇÃO PRINCIPAL
int main() {
    SetConsoleOutputCP(65001);
    FILE *arquivo;
    arquivo = abrirArquivo("nomes_matriculas.txt", "rt"); 

    long baseDados = quantidadeElementos(arquivo);
    
    Arvore* arvore = criarVetor(baseDados);
    rewind(arquivo);
    carregarArquivo(arvore, arquivo);

    int opcao;
    char nome[TAMANHO_NOME];
    long long int matricula;

    do{
        printf("\nMenu:\n");
        printf("1) Inserir nova matrícula\n");
        printf("2) Cancelar matrícula\n");
        printf("3) Pesquisar matrícula\n");
        printf("4) Total de matrículas\n");
        printf("5) Imprimir matrículas\n");
        printf("6) Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                printf("Digite o nome do aluno: ");
                scanf(" %99[^\n]s", nome);
               
                printf("Digite a matrícula: ");
                
                fflush(stdin);
            
                while (scanf("%I64d", &matricula) < 0){
                    printf("Entrada inválida. Digite a matrícula novamente: ");
                    fflush(stdin);
                }

                inserir(arvore, nome, matricula);
                break;

            case 2:
                printf("Digite a matrícula do aluno a ser removido: ");
                scanf("%I64d", &matricula);
                remover(arvore, matricula, 0);
                break;
                
            case 3:
                printf("Digite a matrícula do aluno: ");
                scanf("%I64d", &matricula);
                Aluno* aluno = pesquisar(arvore,matricula);
                if (aluno != NULL) {
                    printf("Aluno encontrado: Nome: %s, Matrícula: %I64d\n", aluno->nome, aluno->matricula);
                } else {
                    printf("Aluno não encontrado.\n");
                }
                break;
                
            case 4:
                contarTotal(arvore);
                break;
                
            case 5:
                imprimir(arvore);
                break;
                
            case 6:
                gravarArquivo(arquivo, arvore);
                break;
                
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 6);

    return 0;
}