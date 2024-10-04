Relatório Árvore Binária (Implementação Sequencial)<br/>
Heloísa Louzada Borchardt Gomes<br/>

1. Explicação sobre a estratégia utilizada.<br/> 
O código implementa uma árvore binária de busca utilizando um vetor para armazenar as informações dos alunos e simular a estrutura da árvore.
2. Descrição do algoritmo e das estruturas utilizadas.<br/>
 
Para o pleno funcionamento do código, foi importado as seguintes bibliotecas:<br/> 
•	stdio.h: Biblioteca padrão de entrada e saída.
•	stdlib.h: Biblioteca padrão de funções utilitárias, como alocação de memória.
•	string.h: Biblioteca para manipulação de strings.
•	windows.h: Biblioteca específica do Windows para manipulação de console e outras funcionalidades.
•	Tab_arvore.h: Cabeçalho personalizado (presumivelmente contém definições e declarações de funções do programa. As funções serão explanadas posteriormente e podem ser divididas em três categorias: Manipulação de arquivo, funções base do menu e funções auxiliares. Segue a foto da “Tab_arvore.h”.


FUNÇÕES MANIPULAÇÃO DE ARQUIVO <br/>
É um grupo de funções responsáveis por ler e retirar as informações do arquivo “nome_matriculas.txt”.
A função “abrirArquivo” abre o arquivo com o nome e modo especificado e retorna um ponteiro para o arquivo, ou exibe uma mensagem de erro caso não consiga abrir o arquivo.

A função “carregarArquivo” lê os nomes e números de matrícula de um arquivo e insere esses dados na árvore binária usando a função pesquisar para verificar se a matrícula do aluno já existe no vetor antes de inseri-lo na árvore.
 
A função “gravarArquivo” tem como utilidade gravar os dados da árvore no arquivo, apenas para os alunos com status ativo (status == 1), e ao final fecha o arquivo.
FUNÇÕES AUXILIARES
A função “quantidadeElementos” conta o número de alunos no arquivo e retorna a quantidade de entradas no arquivo que será utilizada para a criação estática do vetor.

A função “procurarIndice” insere o aluno na posição correta da árvore usando o índice do vetor verificando se o espaço no índice está livre e, se não, decide se deve descer à esquerda ou à direita da árvore, baseado na matrícula.

A função “criarVetor” cria e inicializa uma árvore com um vetor de alunos e um vetor de status para controle das posições ocupadas. Para isso, a alocação de memória para a árvore depende da quantidade de alunos obtida pela função “quantidadeElementos” multiplicada por 100.


FUNÇÕES PRINCIPAIS DO MENU<br/>
A função “inserir” insere um novo aluno na árvore e verifica se a raiz está vazia. Caso contrário, usa “procurarIndice” para encontrar a posição correta.
 
A função “pesquisar” pesquisa um aluno na árvore linearmente, percorrendo o vetor e retorna o aluno se a matrícula for encontrada, ou null se não for.

A função “imprimir” imprime todos os alunos da árvore que possuem status ativo, exibindo nome e matrícula.

A função “contarTotal” conta e exibe o número total de alunos inseridos na árvore (com status ativo).

A função “encontrarMenorIndice” encontra o índice do menor valor em uma subárvore a partir de um determinado nó. Essa função auxilia o processo de remoção de uma matrícula. 

A função “remover” remove um aluno da árvore tratando os possíveis casos.
Em caso de não encontrar a matrícula: Se o índice for maior que o tamanho da árvore ou se o nó não estiver ocupado (status == 0), a função exibe uma mensagem que a matrícula não foi encontrada e retorna.
Se a matrícula que queremos remover for menor que a do nó atual, a função desce à esquerda (subárvore da esquerda). Se a matrícula for maior, desce à direita (subárvore da direita).
1°- Nó sem filho: Se o nó encontrado não possui filhos, simplesmente marca o nó como vazio (status[index] = 0), removendo o aluno.
2°- Nó com um filho: substitui o nó atual pelo filho e atualiza o status, removendo o nó original. Se o nó tiver apenas um filho à direita, substitui pelo filho da direita. Se o nó tiver apenas um filho à esquerda, substitui pelo filho da esquerda.
3°- Nó tiver dois filhos: Se o nó tem dois filhos, o algoritmo encontra o sucessor imediato na subárvore direita, ou seja, o menor nó da subárvore à direita usando a função “encontrarMenorIndice”. O nó atual é substituído pelo sucessor, e o sucessor é então removido recursivamente da árvore. 
