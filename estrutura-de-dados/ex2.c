#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define SIZE 27
// Tamanho da minha lista de hash. Foi interessante mudar esse valor e observar como a distribuição acontece atravéz da lista.
// Irei usar um load factor de 0.75 
// Como nossos dados serão 20 entradas, irei assumir o tamanho de 27 para a tabela (dados esperados / load factor)
// Custa um pouco mais de memoria, porem temos um desempenho elevado. 
#define MEURU 1984779

// Irei usar no exercício uma tabela de hash, pois é o metodo mais eficiente de busca, considerando
// um caso com uma tabela grande o suficiente (e uma função de hash boa o suficiente) para evitar ao máximo as colisões, 
// tendo em vista que caso seu número seja elevado, a tabela hash perde sua eficiência.

// Aqui defino como será cada item da minha hash.
// Alêm dos dados necessários para o exercício, também adiciono um ponteiro para
// o próximo item da lista, tendo em vista que irei fazer uma tabela de hash
// com endereçamento em cadeia.

typedef struct cadastroAluno {
    char nome[100];
    char email[100];
    int ru;
    struct cadastroAluno *prox;    
} Aluno;


// Minha tabela de hash vai ser um vetor de ponteiros do tipo aluno.
Aluno *tabelaHash[SIZE];


// Declaração das funções que serão usadas no programa.
void inicializaTabela();
int funcaoHash(int ru);
void inserirAluno(Aluno *aluno);
void printaTabela();
void busca(int ru);
void flush();
int menu();

int main() {
    int opcao, RU;
    inicializaTabela(); // Inicia todos os itens da minha lista com NULL, o qual servirá de "ground" para a minha lista.


    // Adicionei 20 alunos ao total na lista.
    // Os nomes e os RU's foram gerados aleatoriamente, exceto o meu, devido a exigências do exercício.

    Aluno Andre = {.nome="Andre", .email="Andre@gmail.com", .ru=1262886};
    inserirAluno(&Andre);
    Aluno Eduardo = {.nome="Eduardo", .email="Eduardo@gmail.com", .ru=6891757};
    inserirAluno(&Eduardo);
    Aluno luizHenrique = {.nome="Luiz Henrique Hipolito", .email="henrike.hip@live.com", .ru=MEURU};
    inserirAluno(&luizHenrique);
    Aluno Murilo = {.nome="Murilo", .email="Murilo@gmail.com", .ru=5340205};
    inserirAluno(&Murilo);
    Aluno Theo = {.nome="Theo", .email="Theo@gmail.com", .ru=4383538};
    inserirAluno(&Theo);
    Aluno Enrico = {.nome="Enrico", .email="Enrico@gmail.com", .ru=1878604};
    inserirAluno(&Enrico);
    Aluno Agatha = {.nome="Agatha", .email="Agatha@gmail.com", .ru=3096112};
    inserirAluno(&Agatha);
    Aluno Camila = {.nome="Camila", .email="Camila@gmail.com", .ru=7684435};
    inserirAluno(&Camila);
    Aluno Larissa = {.nome="Larissa", .email="Larissa@gmail.com", .ru=1559792};
    inserirAluno(&Larissa);
    Aluno Rebeca = {.nome="Rebeca", .email="Rebeca@gmail.com", .ru=1235434};
    inserirAluno(&Rebeca);
    Aluno Sara = {.nome="Sara", .email="Sara@gmail.com", .ru=1283497};
    inserirAluno(&Sara);
    Aluno Isabel = {.nome="Isabel", .email="Isabel@gmail.com", .ru=7228244};
    inserirAluno(&Isabel);
    Aluno Milena = {.nome="Milena", .email="Milena@gmail.com", .ru=3953993};
    inserirAluno(&Milena);
    Aluno Giovanna = {.nome="Giovanna", .email="Giovanna@gmail.com", .ru=9972785};
    inserirAluno(&Giovanna);
    Aluno Lorena = {.nome="Lorena", .email="Lorena@gmail.com", .ru=4370968};
    inserirAluno(&Lorena);
    Aluno Kaique = {.nome="Kaique", .email="Kaique@gmail.com", .ru=8321573};
    inserirAluno(&Kaique);
    Aluno Yuri = {.nome="Yuri", .email="Yuri@gmail.com", .ru=8867555};
    inserirAluno(&Yuri);
    Aluno Benedito = {.nome="Benedito", .email="Benedito@gmail.com", .ru=4211716};
    inserirAluno(&Benedito);
    Aluno Guilhermo = {.nome="Guilhermo", .email="Guilhermo@gmail.com", .ru=1507127};
    inserirAluno(&Guilhermo);
    Aluno Anastasia = {.nome="Anastasia", .email="Anastasia@gmail.com", .ru=5475262};
    inserirAluno(&Anastasia);
    
    // Menu padrão para as funcionalidades
    while (1)
    {
        opcao = menu();

        switch (opcao)
        {
        case 1: // Efetua a busca da tabela hash
            printf("Informe o RU a ser buscado: ");
            scanf("%d", &RU);
            flush();
            busca(RU);
            break;

        case 2: // Printa todos os dados da tabela.
            printaTabela();
            break;

        case 3: // Sai do programa
            return 0;
        default:
            printf("Opcao nao encontada!\n");
            break;
        }
    }
    

    
    return 0;
}

void flush() {
    // Limpa o buffer do teclado
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return;
}

void inicializaTabela() {
    // Inicia todos os itens da minha lista de hash com NULL, os quais servirão de "ground" para a minha lista.
    for (int i = 0; i < SIZE; i++) {
        tabelaHash[i] = NULL;
    }
    return;
}

void inserirAluno(Aluno *aluno) {
    // Criei essa função para facilitar a inserção dos alunos "dummy" na tabela hash.

    if (aluno == NULL) return; // Essa linha está aqui apenas para ter certeza de que não será inserido um NULL na lista.

    int posicao = funcaoHash(aluno->ru); // Usando minha função de hash, determino em qual posição da lista devo adicionar o aluno.

    // Se nao houver nada na posicao, aluno->prox = NULL, pois a tabela foi, anteriormente, populada com NULL. 
    // Caso tenha, aluno->prox = a lista encadeada já existente na posição.
    aluno->prox = tabelaHash[posicao];

    // Abaixo, o novo aluno se torna o head da lista encadeada. 
    tabelaHash[posicao] = aluno;
    return;
}

void printaTabela() {
    // Não foi solicitado no exercício, porém fiz uma função para visualizar a lista.
    // Interessante notar como fiz o simbolo de qual elemento aponta para qual, através de setas impressas.

    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        if (tabelaHash[i] == NULL) {
            printf("-NULL-\n");
        } else {
            // Crio um aluno temporário apenas para poder iterar sobre ele usando o ponteiro de prox, que aponta para o próximo item da lista encadeada.
            Aluno *current = tabelaHash[i];

            printf("%s", current->nome);

            while(current->prox != NULL) {
                printf(" --> %s", current->prox->nome);
                current = current->prox;
            }
            printf(" --> NULL\n");
        }
    }
    printf("\n");
}

int funcaoHash(int ru) {
    // Usei o método da multiplicação como minha função de hash, tendo em vista que
    // já havia usado o da divisão no exemplo da aula prática.

    // Citando o material impresso da aula 6, "Esse método apresenta como desvantagem o fato de ser mais lento para
    // execução em relação ao método da divisão, pois temos mais cálculos envolvidos
    // no processo, porém tem a vantagem de que o valor de m não é crítico, não
    // importando o valor escolhido"

    float A = 0.618; // Valor recomendado de A, segundo Knuth (1998)
    return floor(SIZE * ((ru * A) - floor(ru * A)));  
}

void busca(int ru) {

    int posicao = funcaoHash(ru); // Novamente, meu index é calculado pela função hash

    // Se o RU que estou procurando é igual ao RU do primeiro item da lista na posição calculada,
    // eu apenas apresento os dados do aluno, pois já o encontramos.
    if (tabelaHash[posicao]->ru == ru) {
            printf("\nNome do aluno:  %s\n", tabelaHash[posicao]->nome);
            printf("Email do aluno: %s\n", tabelaHash[posicao]->email);
            return;
    } 

    // Caso ele não seja o primeiro item da lista,
    // preciso iterar sobre a lista encadeada, e percorrer linearmente até encontrar o
    // aluno buscado. Idealmente, essa parte do código nunca deveria ser executada, significando
    // que o aluno sempre estaria no head da posição calculada no hash.
    

    // Crio novamente um aluno temporário, para poder iterar sobre ele.
    Aluno *current = tabelaHash[posicao];

    while(current != NULL) {
        // Se o RU do aluno que estamos iterando sobre a lista encadeada é o RU buscado,
        // então encontramos o aluno e devolvemos seus dados. 
        if(current->ru == ru) {
            printf("\nNome do aluno: %s\n", current->nome);
            printf("Email do aluno: %s\n", current->email);
            return;
        }

        // Caso contrario, passamos para o próximo item da lista.
        current = current->prox;
    }

    
    // Caso o RU passe por ambas as buscas, significa que ele não foi cadastrado no sistema.
    printf("ERRO! RU nao cadastrado no sistema!\n");
    return;
    
}

int menu() {
    // Um menu padrão, não tem segredo aqui
    int opcao;

    printf("\n1. Buscar por RU\n");
    printf("2. Listar dados\n");
    printf("3. Sair\n");
    printf("Digite sua escolha: ");
    scanf("%d", &opcao);
    flush();

    return opcao;
}

