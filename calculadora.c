#include <stdio.h>
#include <math.h>

int main(void) {
    double num1, num2, resultado;
    char operacao;
    char continuar;

    do {
        printf("Digite o primeiro numero: ");
        scanf("%lf", &num1);

        printf("Digite a operacao (+, -, *, /, r para raiz): ");
        scanf(" %c", &operacao);

        if (operacao != 'r') {
        printf("Digite o segundo numero: ");
        scanf("%lf", &num2);
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
            default:
                printf("Operacao invalida!\n");
        }

        printf("Deseja fazer outro calculo? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    printf("Programa encerrado.\n");
    return 0;
}