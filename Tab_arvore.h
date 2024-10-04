#define TAMANHO 100

typedef struct {
    char nome[TAMANHO];
    long long int matricula;
}Aluno;

typedef struct {
    Aluno *vetorAluno;
    long tamanho;
    long *status;
}Arvore;

FILE * abrirArquivo(char * nomeArq, char * modo);

void carregarArquivo(Arvore* arvore, FILE *arq);

void gravarArquivo(FILE *arquivo, Arvore* arvore);

long quantidadeElementos(FILE *arq);

void procurarIndice(Arvore* arvore, Aluno novoAluno, int index); 

Arvore* criarVetor(long tamanho);

void inserir(Arvore* arvore, char* nome, long long int matricula);

Aluno* pesquisar(Arvore* arvore, long long int matricula);

void imprimir (Arvore* arvore);

void contarTotal(Arvore* arvore);

Aluno* buscar(Arvore* arvore, long long int matricula, int index);

int encontrarMenorIndice(Arvore* arvore, int index);

void remover(Arvore* arvore, long long int matricula, int index);