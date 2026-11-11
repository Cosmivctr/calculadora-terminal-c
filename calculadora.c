#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

double lerNumero(const char *mensagem) {
    double valor;
    int lidos;

    while (1) {
        printf("%s", mensagem);
        lidos = scanf("%lf", &valor);

        if (lidos == EOF) {
            printf("\nEntrada encerrada.\n");
            exit(1);
        }

        if (lidos == 1) {
            limparBuffer();
            return valor;
        }

        printf("Entrada invalida! Digite apenas numeros.\n");
        limparBuffer();
    }
}

int main(void) {
    double num1, num2, resultado;
    char operacao;
    char continuar;

    do {
        num1 = lerNumero("Digite o primeiro numero: ");

        printf("Digite a operacao (+, -, *, /, %%, r para raiz): ");
        scanf(" %c", &operacao);
        limparBuffer();

        if (operacao != 'r') {
            num2 = lerNumero("Digite o segundo numero: ");
        }

        switch (operacao) {
            case '+':
                resultado = num1 + num2;
                printf("Resultado: %.2f\n", resultado);
                break;
            case '-':
                resultado = num1 - num2;
                printf("Resultado: %.2f\n", resultado);
                break;
            case '*':
                resultado = num1 * num2;
                printf("Resultado: %.2f\n", resultado);
                break;
            case '/':
                if (num2 == 0) {
                    printf("Erro: divisao por zero nao e permitida.\n");
                } else {
                    resultado = num1 / num2;
                    printf("Resultado: %.2f\n", resultado);
                }
                break;
            case 'r':
                if (num1 < 0) {
                    printf("Erro: nao existe raiz quadrada real de numero negativo.\n");
                } else {
                    resultado = sqrt(num1);
                    printf("Resultado: %.2f\n", resultado);
                }
                break;
            case '%':
                if (num2 == 0) {
                    printf("Erro: resto por zero nao e permitido.\n");
                } else {
                    resultado = fmod(num1, num2);
                    printf("Resultado: %.2f\n", resultado);
                }
                break;
            default:
                printf("Operacao invalida!\n");
        }

        printf("Deseja fazer outro calculo? (s/n): ");
        scanf(" %c", &continuar);
        limparBuffer();

    } while (continuar == 's' || continuar == 'S');

    printf("Programa encerrado.\n");
    return 0;
}
