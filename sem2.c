#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <string.h> // Necessário para usar strcmp

// Função para simular a contagem de tempo
void contarTempo(int segundos, char *cor, int *sairManutencao, int *pularAmarelo) {
    for (int i = 0; i < segundos; i++) {
        printf("\rSemaforo: %s - %d segundos", cor, i);
        fflush(stdout);
        sleep(1); // Aguarda 1 segundo

        if (kbhit()) { // Detecta se uma tecla foi pressionada
            char tecla = getch();
            if (tecla == 'p') {
                printf("\nFazer manutencao? (m - Sim, e - Encerrar): ");
                tecla = getch();
                if (tecla == 'm') {
                    // Modo de manutenção
                    printf("\nModo de manutencao: Luz amarela piscando\n");
                    while (1) {
                        printf("\rLuz amarela ON ");
                        fflush(stdout);
                        sleep(1);
                        printf("\rLuz amarela OFF");
                        fflush(stdout);
                        sleep(1);
                        if (kbhit()) {
                            tecla = getch();
                            if (tecla == 'c') {
                                printf("\nFim da manutencao e volta a luz verde\n");
                                *sairManutencao = 1; // Indica que é para sair da manutenção e voltar ao verde
                                return; // Sai da manutenção e volta ao loop principal
                            } else if (tecla == 'e') {
                                printf("\nFim do processo...\n");
                                exit(0); // Sai do programa
                            }
                        }
                    }
                } else if (tecla == 'e') {
                    printf("\nFim do processo...\n");
                    exit(0); // Sai do programa
                }
            } else if (tecla == 'v' && strcmp(cor, "Verde") == 0) {
                // Se a tecla 'v' for pressionada e estamos na cor verde
                *pularAmarelo = 1; // Sinaliza para pular para a luz amarela
                return;
            }
        }
    }
}

int main() {
    char tecla;
    int sairManutencao = 0; // Flag para controlar quando sair da manutenção
    int pularAmarelo = 0;   // Flag para controlar se deve pular diretamente para o amarelo
    int pularVermelho = 0;  // Flag para pular diretamente para o vermelho após pular para o amarelo

    printf("Iniciar semaforo? (s - Sim, e - Encerrar): ");
    tecla = getch();

    if (tecla == 'e') {
        printf("\nFim do processo...\n");
        return 0;
    }

    // Loop principal do semáforo
    while (1) {
        // Quando sair da manutenção, começa sempre na luz verde
        if (sairManutencao) {
            sairManutencao = 0; // Reseta a flag
        }

        printf("\nSemaforo Verde\n");
        contarTempo(30, "Verde", &sairManutencao, &pularAmarelo);
        if (sairManutencao) continue; // Se saiu da manutenção, reinicia o ciclo a partir da luz verde
        if (pularAmarelo) { // Se a tecla 'v' foi pressionada
            pularAmarelo = 0; // Reseta a flag
            pularVermelho = 1; // Sinaliza para pular o segundo ciclo amarelo
            printf("\nSemaforo Amarelo\n");
            contarTempo(5, "Amarelo", &sairManutencao, &pularAmarelo);
            if (sairManutencao) continue; // Se saiu da manutenção, reinicia o ciclo a partir da luz verde
        }

        if (!pularVermelho) {
            printf("\nSemaforo Amarelo\n");
            contarTempo(5, "Amarelo", &sairManutencao, &pularAmarelo);
            if (sairManutencao) continue; // Se saiu da manutenção, reinicia o ciclo a partir da luz verde
        } else {
            pularVermelho = 0; // Reseta a flag para o próximo ciclo
        }

        printf("\nSemaforo Vermelho\n");
        contarTempo(20, "Vermelho", &sairManutencao, &pularAmarelo);
        if (sairManutencao) continue; // Se saiu da manutenção, reinicia o ciclo a partir da luz verde
    }

    return 0;
}
