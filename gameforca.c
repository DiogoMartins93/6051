#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TENTATIVAS 5
#define TAMANHO_PALAVRA 20

// Função para mostrar a forca com base nas tentativas restantes
void mostrar_forca(int tentativas) {
    printf(" +---+\n");
    printf(" |   |\n");
    printf(" %s   |\n", tentativas <= 4 ? "O" : " ");
    printf("%s%s%s  |\n", tentativas <= 3 ? "/" : " ", tentativas <= 2 ? "|" : " ", tentativas <= 3 ? "\\" : " ");
    printf(" %s   |\n", tentativas <= 2 ? "|" : " ");
    printf("%s %s  |\n", tentativas <= 1 ? "/" : " ", tentativas == 0 ? "\\" : " ");
    printf("     |\n");
    printf("=========\n");
    if (tentativas == 0) {
        printf(" X_X\n");
    }
}

// Função para escolher uma palavra aleatória de um grupo
char* escolher_palavra(char grupo) {
    static char palavra[TAMANHO_PALAVRA];

    const char* animais[] = {"crocodilo", "panda", "elefante", "zebra", "leao"};
    const char* filmes[] = {"matrix", "titanic", "avatar", "rocky", "joker"};
    const char* objetos[] = {"mesa", "cadeira", "computador", "telefone", "garrafa"};

    int indice;
    switch (grupo) {
        case 'a':  // Animais
            indice = rand() % 5;
            strcpy(palavra, animais[indice]);
            break;
        case 'b':  // Filmes
            indice = rand() % 5;
            strcpy(palavra, filmes[indice]);
            break;
        case 'c':  // Objetos
            indice = rand() % 5;
            strcpy(palavra, objetos[indice]);
            break;
        default:
            strcpy(palavra, "erro");
    }

    return palavra;
}

// Função para verificar se a letra já foi escolhida
int letra_ja_escolhida(char letra, char letras_usadas[], int contador) {
    for (int i = 0; i < contador; i++) {
        if (letras_usadas[i] == letra) {
            return 1; // Letra já foi usada
        }
    }
    return 0; // Letra ainda não foi usada
}

// Função principal do jogo
void jogar_forca(char* palavra) {
    int tentativas = MAX_TENTATIVAS;
    int tamanho_palavra = strlen(palavra);
    char palavra_oculta[TAMANHO_PALAVRA];
    int acertou = 0;
    int i;

    for (i = 0; i < tamanho_palavra; i++) {
        palavra_oculta[i] = '_';
    }
    palavra_oculta[tamanho_palavra] = '\0';

    char letras_erradas[26] = "";
    char letras_usadas[26] = ""; // Armazena todas as letras escolhidas
    int erros = 0;
    int usadas_contador = 0; // Contador para o número de letras usadas

    while (tentativas > 0 && !acertou) {
        printf("\n");
        mostrar_forca(tentativas);

        // Mostra a palavra oculta
        printf("\nPalavra: ");
        for (i = 0; i < tamanho_palavra; i++) {
            printf("%c ", palavra_oculta[i]);
        }
        printf("\n");

        // Mostra letras erradas
        printf("Letras erradas: %s\n", letras_erradas);

        // Solicita uma letra
        printf("Digite uma letra: ");
        char letra;
        scanf(" %c", &letra);

        // Verifica se a letra já foi escolhida
        if (letra_ja_escolhida(letra, letras_usadas, usadas_contador)) {
            printf("Ja escolheu essa letra! Tente outra.\n");
            continue; // Não desconta uma tentativa
        }

        // Adiciona a letra à lista de letras usadas
        letras_usadas[usadas_contador++] = letra;

        // Verifica se a letra está na palavra
        int acertou_letra = 0;
        for (i = 0; i < tamanho_palavra; i++) {
            if (palavra[i] == letra) {
                palavra_oculta[i] = letra;
                acertou_letra = 1;
            }
        }

        if (!acertou_letra) {
            letras_erradas[erros++] = letra;
            tentativas--;
        }

        // Verifica se a palavra foi completamente descoberta
        if (strcmp(palavra_oculta, palavra) == 0) {
            acertou = 1;
        }
    }

    // Exibe o resultado final
    printf("\n");
    mostrar_forca(tentativas);

    if (acertou) {
        printf("\033[1;32m");  // Verde
        printf("Parabens! acertou na palavra: %s\n", palavra);
        printf("\033[0m");
    } else {
        printf("\033[1;31m");  // Vermelho
        printf("Perdeu! A palavra era: %s\n", palavra);
        printf("\033[0m");
    }
}

// Função para jogar sozinho
void jogar_sozinho() {
    char grupo;

    // Escolher grupo de palavras
    printf("Escolha o grupo de palavras: Animais (a), Filmes (b), Objetos (c): ");
    scanf(" %c", &grupo);

    // Escolhe a palavra aleatória
    char* palavra = escolher_palavra(grupo);

    if (strcmp(palavra, "erro") == 0) {
        printf("Grupo invalido!\n");
        return;
    }

    // Inicia o jogo
    jogar_forca(palavra);
}

// Função para jogar acompanhado (onde um jogador escolhe a palavra)
void jogar_acompanhado() {
    char palavra_escolhida[TAMANHO_PALAVRA];

    // Pedir para um jogador digitar a palavra (sem mostrar)
    printf("Jogador 1, digite a palavra (sem acentos, max %d letras): ", TAMANHO_PALAVRA - 1);
    scanf("%s", palavra_escolhida);

    // Verifica se o tamanho da palavra é válido
    if (strlen(palavra_escolhida) >= TAMANHO_PALAVRA) {
        printf("Palavra muito longa! Máximo de %d letras.\n", TAMANHO_PALAVRA - 1);
        return;
    }

    // Limpar a tela para que o jogador 2 não veja a palavra (simulação de limpeza)
    for (int i = 0; i < 100; i++) printf("\n");

    // Iniciar o jogo com a palavra escolhida pelo jogador 1
    jogar_forca(palavra_escolhida);
}

// Função para o jogo da forca
void iniciar_jogo() {
    int opcao;
    char jogar_novamente;

    srand(time(NULL)); // Inicializa a semente aleatória aqui

    do {
        printf("Bem-vindo ao Jogo da Forca!\n");
        printf("Escolha a opcao: Jogar sozinho (1), Jogar acompanhado (2): ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            jogar_sozinho();
        } else if (opcao == 2) {
            jogar_acompanhado();
        } else {
            printf("Opcao invalida!\n");
        }

        // Pergunta se deseja jogar novamente
        printf("Deseja jogar novamente? (s/n): ");
        scanf(" %c", &jogar_novamente);

    } while (jogar_novamente == 's');

    printf("Programa encerrado.\n");
}

int main() {
    iniciar_jogo();
    return 0;
}
