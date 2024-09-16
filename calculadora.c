#include <stdio.h>

int main() {
    float valor1, valor2, resultado;
    char operacao, continuar = 's', usar_resultado_anterior;

    // Primeiro cálculo
    printf("Digite o primeiro valor: ");
    scanf("%f", &valor1);

    printf("Escolha a operacao (+, -, *, /): ");
    scanf(" %c", &operacao);

    printf("Digite o segundo valor: ");
    scanf("%f", &valor2);

    // Realiza o cálculo inicial
    switch (operacao) {
        case '+':
            resultado = valor1 + valor2;
            break;
        case '-':
            resultado = valor1 - valor2;
            break;
        case '*':
            resultado = valor1 * valor2;
            break;
        case '/':
            if (valor2 != 0) {
                resultado = valor1 / valor2;
            } else {
                printf("Erro: Divisao por zero!\n");
                return 1;  // Encerra o programa se houver divisão por zero
            }
            break;
        default:
            printf("Operacao invalida!\n");
            return 1;  // Encerra o programa se a operação for inválida
    }

    // Mostra o resultado
    printf("Resultado: %.2f\n", resultado);

    // Loop para continuar calculando
    do {
        // Pergunta se o usuário deseja continuar
        printf("Deseja continuar? (s/n): ");
        scanf(" %c", &continuar);

        if (continuar == 's') {
            // Pergunta se deseja usar o resultado anterior
            printf("Deseja usar o resultado anterior? (s/n): ");
            scanf(" %c", &usar_resultado_anterior);

            if (usar_resultado_anterior == 's') {
                valor1 = resultado;  // Usa o resultado anterior como primeiro valor
            } else {
                printf("Digite o primeiro valor: ");
                scanf("%f", &valor1);
            }

            // Escolhe a operação
            printf("Escolha a operacao (+, -, *, /): ");
            scanf(" %c", &operacao);

            // Pede o segundo valor
            printf("Digite o segundo valor: ");
            scanf("%f", &valor2);

            // Realiza o cálculo
            switch (operacao) {
                case '+':
                    resultado = valor1 + valor2;
                    break;
                case '-':
                    resultado = valor1 - valor2;
                    break;
                case '*':
                    resultado = valor1 * valor2;
                    break;
                case '/':
                    if (valor2 != 0) {
                        resultado = valor1 / valor2;
                    } else {
                        printf("Erro: Divisao por zero!\n");
                        continue;  // Volta ao início do loop se houver erro
                    }
                    break;
                default:
                    printf("Operação invalida!\n");
                    continue;  // Volta ao início do loop se a operação for inválida
            }

            // Mostra o resultado
            printf("Resultado: %.2f\n", resultado);
        }

    } while (continuar == 's');

    printf("Programa encerrado.\n");
    return 0;
}
