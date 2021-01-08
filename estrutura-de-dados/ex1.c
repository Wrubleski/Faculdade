#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Primeiramente, criei a estruct que simboliza cada musica da playlist.
// Decidi usar uma lista encadeada dupla, pois é a que faz mais sentido
// no contexto de uma playlist, tendo em vista que temos facil acesso ao próximo elemento e ao anterior

typedef struct dadosMusica {
    char nome[50];
    char artista[50];
    float duracao;
    int isHead;
    struct dadosMusica *prox, *ant; // prox = próxima musica, ant = música anterior

} Musica; // Cada novo registro é uma nova música


// Declaração padrão das fuções que irei usar no programa
int menu();
void flush();
void inserirMusica(Musica **Head);
void listaMusicas(Musica **Head);
void tocar(Musica **Head);


int main() {
    // A primeira música é NULL. Eu só aloco memória pra ela quando o programa é executado e a primeira música inserida.
    Musica *Head = NULL;
    int opcao;
    
    // Menu padrão para cada funcionalidade do programa
    while (1)
    {
        opcao = menu();
        switch (opcao)
        {
        case 1: 
            // Inseri uma musica na playlist através da funcão InserirMusica()
            inserirMusica(&Head);
            break;

        case 2:
            // List as músicas da playlist através da função listaMusicas()
            listaMusicas(&Head);
            break;

        case 3:
            // Simula a execucao de um dispositivo de audio através da funcao tocar()
            tocar(&Head);
            break;
            
        case 4:
            // Finaliza o programa
            return 0;

        default:
            printf("Opcao nao encontada!\n");
            break;
        }
    }
    

    return 0;
}

int menu() {
    // Um menu padrão, não tem segredo aqui
    int opcao;

    printf("\n1. Inserir musica\n");
    printf("2. Listar as musicas da playlist\n");
    printf("3. Tocar playlist\n");
    printf("4. Sair\n");
    printf("Digite sua escolha: ");
    scanf("%d", &opcao);
    flush();

    return opcao;
}

void flush() {
    // Limpa o buffer do teclado
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return;
}

void inserirMusica(Musica **Head) {
    // Aqui que realmente começa a mágica
    // Caso o Head seja NULL, então essa é a primeira música a ser adicionada.
    // Com isso, eu aloco memoria, seto suas propriedades e inicio o isHead, que será usado como ponto de parada na
    // função de visualização

    if (*Head == NULL) {
        *Head = (Musica *)malloc(sizeof(Musica));
        printf("Informe o nome da musica: ");
        gets((*Head)->nome);
        printf("Informe o nome do artista: ");
        gets((*Head)->artista);
        printf("Informe a duracao da musica: \n(Parte inteira = minutos, parte decimal = segundos. \nEx: 3.14 = uma musica de duracao 03:14)\n");
        scanf("%f", &(*Head)->duracao);
        flush();

        (*Head)->isHead = 1; 

        // Eu decidi usar uma lista dupla circular, para poder facilmente ir da última
        // música para a primeira, e vice versa.
        // Como essa é a primeira e única música, ela aponta
        // para sí mesma em ambas as direções (prox e ant)

        (*Head)->prox = *Head;
        (*Head)->ant = *Head;

        return;

    } else {
        // Caso não seja a primeira música, crio uma nova música e aloco memória para ela

        Musica *novaMusica = NULL;
        novaMusica = (Musica *)malloc(sizeof(Musica));
        printf("\nInforme o nome da musica: ");
        gets(novaMusica->nome);
        printf("Informe o nome do artista: ");
        gets(novaMusica->artista);
        printf("Informe a duracao da musica: \nParte inteira = minutos, parte decimal = segundos. Ex: 3.14 = uma musica de duracao 03:14)\n");
        scanf("%f", &novaMusica->duracao);
        flush();

        // Aqui finalmente defini como os ponteiros irão se comportar.
        // Toda música é inserida no final da nossa lista, como normalmente acontece em ferramentas similares.

        // Primeiro, defino pra onde os ponteiros da nova música irão apontar.
        // Como a lista é dupla circular, e a nova música sempre vai no final da lista,
        // o ponteiro prox aponta para o Head.
        // Da mesma forma, o ponteiro ant aponta para a música que era a última da lista, nesse caso,
        // a ant do Head.

        novaMusica->prox = *Head;
        novaMusica->ant = (*Head)->ant;

        // Agora, com os ponteiros da nova música prontos, preciso apenas corrigir os ponteiros do Head e o da anteriormente última musica.

        // O prox da ant do Head deve apontar para a nova música.
        // Com isso, a penultima música agora está apontando para a última música
        (*Head)->ant->prox = *(&novaMusica);

        // E o ant do Head deve apontar, também, para a nova música, terminando a manipulação dos ponteiros da lista encadeada dupla circular.
        (*Head)->ant = *(&novaMusica);

        return;
    }

}

void listaMusicas(Musica **Head) {
    // Sempre tem aquele usuário que quer listar a playlist sem ter nada nela...
    if (*Head == NULL) {
        printf("Voce ainda nao possui musicas na playlist!\n");
        return;
    }

    // Aloco o Head em uma variável, a qual utilizo para iterar até parar no Head novamente
    Musica current = **Head;
    int i = 1, min, seg;

    // Usando um do - while, consigo visualizar a primeira musica, 
    // iniciando no Head, e parando quando chego nele novamente.
    do {
        printf("\n\n");
        printf("Musica #%d\n", i);
        printf("Nome: %s\n", (&current)->nome);
        printf("Artista: %s\n", (&current)->artista);

        // Estou utilizando um float para capturar a duracao da musica.
        // A parte inteira são os minutos, e os segundos são a parte decimal * 100

        min = floor((&current)->duracao);
        seg = (((&current)->duracao - min) * 100);
        printf("duracao: %d:%d\n\n", min, seg);

        // Partindo para a próxima música
        current = *(&current)->prox;
        i++;
    } while ((&current)->isHead != 1); // Quando o isHead == 1, o laço termina, pois deu uma volta completa na lista, finalizando a vizualização.
    return;
}

void tocar(Musica **Head) {
    // Aqui eu simulo a execução da música.
    // Ficou bacana para navegar através da lista usando os ponteiros de ant e prox

    if (*Head == NULL) {
        printf("Voce ainda nao possui musicas cadastradas!\n");
        return;
    }

    Musica current = **Head;
    int opcao;

    while (1)
    {
        printf("\n\nTocando a musica %s, do artista %s.\n", (&current)->nome, (&current)->artista);
        printf("\n1: Proxima Musica\n2: Musica Anterior\n3: Sair do modo de execucao.\n...");
        scanf("%d" ,&opcao);
        flush();
        
        switch (opcao)
        {
        case 1:
            current = *(&current)->prox;
            break;
        
        case 2:
            current = *(&current)->ant;
            break;
        case 3:
            return;    
        default:
            printf("Opcao nao encontrada!\n");
            break;
        }
    }
    
}