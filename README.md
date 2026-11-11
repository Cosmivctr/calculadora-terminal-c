# Calculadora em C

Este é um dos meus primeiros projetos em linguagem C. Comecei com uma calculadora de terminal com as quatro operações básicas e fui evoluindo o projeto aos poucos: adicionei a **raiz quadrada**, o **resto da divisão** e a **validação de entradas inválidas**. O objetivo é praticar os fundamentos da linguagem e documentar o que fui aprendendo no caminho.

Escrevi este README como um diário de estudo: além de mostrar como usar o programa, explico por que escrevi cada parte do código.

## Funcionalidades

- Soma (`+`), subtração (`-`), multiplicação (`*`) e divisão (`/`)
- Resto da divisão (`%`), com suporte a números decimais
- Raiz quadrada (`r`), que usa apenas um número
- Suporte a números decimais (tipo `double`)
- Tratamento de divisão por zero, resto por zero e raiz de número negativo
- Validação de entrada: se o usuário digitar letras no lugar de números, o programa pede de novo
- Validação de operação inválida
- Repetição de cálculos sem precisar reiniciar o programa

## O que eu queria praticar

- Ler dados do teclado e mostrar resultados na tela
- Trabalhar com variáveis de tipos diferentes
- Tomar decisões no código com `switch` e `if/else`
- Repetir ações com um laço
- Proteger o programa contra entradas problemáticas
- Usar uma biblioteca externa (`math.h`) e compilar com ela
- Criar minhas próprias funções para não repetir código

## Como o programa funciona

1. Pede o primeiro número (e só aceita se for um número válido).
2. Pede a operação (`+`, `-`, `*`, `/`, `%` ou `r` para raiz).
3. Pede o segundo número, **exceto** na raiz quadrada.
4. Calcula e mostra o resultado.
5. Pergunta se quero fazer outro cálculo. Se sim, volta ao passo 1.

## O que aprendi em cada parte do código

### Bibliotecas

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
```

- `stdio.h`: traz `printf` e `scanf`. O C não sabe, por conta própria, mostrar texto na tela nem ler o teclado.
- `stdlib.h`: traz o `exit()`, que uso para encerrar o programa quando a entrada acaba.
- `math.h`: traz funções matemáticas, como `sqrt()` (raiz quadrada) e `fmod()` (resto com decimais).

Sem essas linhas, o compilador não reconhece as funções.

### Função `main`

```c
int main(void) {
```

Todo programa em C começa por aqui. O `int` indica que a função devolve um número ao sistema operacional (usei `return 0` no final, que significa "terminou sem erros"). O `void` indica que ela não recebe parâmetros.

### Variáveis

```c
double num1, num2, resultado;
char operacao;
char continuar;
```

Usei `double` para os números porque ele aceita casas decimais. Com `int`, a conta `7 / 2` daria `3` em vez de `3.5`. Para guardar o símbolo da operação e a resposta `s/n`, usei `char`, que armazena um único caractere.

### Laço `do...while`

```c
do {
    ...
} while (continuar == 's' || continuar == 'S');
```

Escolhi o `do...while` porque ele executa o bloco **pelo menos uma vez** antes de testar a condição. Isso combina com a calculadora: sempre faço um cálculo e só depois decido se quero outro. O `||` significa "ou", então o programa aceita `s` e `S`.

### Leitura de dados com `scanf`

```c
scanf(" %c", &operacao);
```

Aprendi três detalhes importantes aqui:

- `%lf` é o formato para ler um `double`, e `%c` lê um caractere.
- O `&` passa o **endereço de memória** da variável, para o `scanf` saber onde guardar o valor.
- O **espaço antes do `%c`** é essencial. Quando digito um número e aperto Enter, o Enter fica sobrando no buffer do teclado. Sem o espaço, o `scanf` lê esse Enter como se fosse a operação, e o programa quebra.

### Decisão com `switch`

```c
switch (operacao) {
    case '+':
        resultado = num1 + num2;
        printf("Resultado: %.2f\n", resultado);
        break;
    ...
    default:
        printf("Operacao invalida!\n");
}
```

Usei `switch` porque estou comparando **uma mesma variável** com vários valores fixos. Fica mais limpo do que vários `if` seguidos. Pontos que anotei:

- Caractere usa aspas simples (`'+'`). Aspas duplas (`"+"`) criam uma string, que é outra coisa.
- O `break` é obrigatório. Sem ele, o `switch` "cai" para o caso seguinte e executa várias operações.
- O `default` captura qualquer símbolo inválido e avisa o usuário.
- No `printf`, `%.2f` mostra o número com 2 casas decimais e `\n` quebra a linha.

### Proteção contra divisão por zero

```c
case '/':
    if (num2 == 0) {
        printf("Erro: divisao por zero nao e permitida.\n");
    } else {
        resultado = num1 / num2;
        printf("Resultado: %.2f\n", resultado);
    }
    break;
```

Dividir por zero é indefinido e gera resultados inválidos no programa. Por isso verifico o divisor **antes** de dividir. Aqui também reforcei a diferença entre `=` (atribuição) e `==` (comparação), um dos erros mais comuns de quem está começando.

## Adicionando a raiz quadrada

A raiz quadrada foi a primeira operação que usa **só um número**, então não bastou criar um `case` novo. Precisei mudar mais de um ponto do código.

### 1. Incluir a `math.h`

A função `sqrt()` não faz parte da linguagem C pura. Ela vem da biblioteca matemática, por isso adicionei `#include <math.h>`.

### 2. Escolher o símbolo `r`

Como o símbolo √ é difícil de digitar no terminal, escolhi a letra `r`. A mensagem que pede a operação também foi atualizada para o usuário saber da opção.

### 3. Pedir o segundo número só quando necessário

Antes, o programa sempre pedia dois números. Para a raiz isso não faz sentido, então só peço o segundo número quando a operação não é a raiz:

```c
if (operacao != 'r') {
    num2 = lerNumero("Digite o segundo numero: ");
}
```

O `!=` significa "diferente de".

### 4. Novo `case 'r'` com validação

```c
case 'r':
    if (num1 < 0) {
        printf("Erro: nao existe raiz quadrada real de numero negativo.\n");
    } else {
        resultado = sqrt(num1);
        printf("Resultado: %.2f\n", resultado);
    }
    break;
```

Não existe raiz quadrada real de número negativo. Sem a checagem, `sqrt(-9)` devolveria `nan` (*not a number*). Foi o mesmo raciocínio da divisão por zero: **validar a entrada antes de calcular**.

### 5. Compilar com `-lm`

O `#include <math.h>` apenas avisa ao compilador que a `sqrt` existe. O código dela fica em outra biblioteca, que precisa ser ligada na compilação com a flag `-lm`. Esquecer essa flag gera o erro `undefined reference to 'sqrt'`.

## Adicionando o resto da divisão (%)

O resto trouxe duas pegadinhas novas.

### 1. O operador `%` só funciona com `int`

Se eu escrevesse `num1 % num2` com variáveis `double`, o compilador daria erro. Para manter os números decimais, usei a função `fmod()` da `math.h`:

```c
case '%':
    if (num2 == 0) {
        printf("Erro: resto por zero nao e permitido.\n");
    } else {
        resultado = fmod(num1, num2);
        printf("Resultado: %.2f\n", resultado);
    }
    break;
```

Com `fmod`, `10.5` e `3` dão resto `1.5`. Se eu tivesse convertido para `int` (um *cast*), as casas decimais seriam descartadas e perderia precisão. Também aprendi que, em C, o resto leva o **sinal do primeiro número**: `-7` e `3` dão `-1`.

### 2. O `%` tem significado especial no `printf`

Dentro do texto de um `printf`, o `%` é o início de um formato (como `%lf`). Para mostrar um `%` de verdade na tela, preciso escrever **dois**:

```c
printf("Digite a operacao (+, -, *, /, %%, r para raiz): ");
```

Já dentro das aspas simples do `case '%':` não preciso duplicar, porque ali é só um caractere.

## Validando a entrada do usuário

Esta foi a parte em que mais aprendi. Antes, se eu digitasse `abc` onde era esperado um número, o programa quebrava: a variável ficava com lixo de memória e o texto inválido continuava preso no buffer do teclado, fazendo os próximos `scanf` falharem também.

### O retorno do `scanf`

Descobri que o `scanf` **devolve um valor**: a quantidade de itens lidos com sucesso. Eu nunca tinha usado esse retorno.

| Retorno | Significado |
|---|---|
| `1` | Leu o número com sucesso |
| `0` | A entrada não era um número (ex.: `abc`) |
| `EOF` | A entrada acabou (ex.: Ctrl+D) |

### Função `limparBuffer`

```c
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}
```

Ela lê e descarta caracteres do teclado até chegar ao Enter. Uso `int` em vez de `char` porque o `EOF` não cabe com segurança em um `char`. O bloco `{ }` fica vazio porque todo o trabalho acontece na condição do `while`.

### Função `lerNumero`

```c
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
```

Como preciso ler dois números, criei uma função para não repetir a validação:

- Mostra a pergunta e tenta ler.
- Se a entrada acabou (`EOF`), encerra o programa com `exit(1)`, senão o laço ficaria preso para sempre.
- Se leu um número (`1`), limpa o resto da linha e devolve o valor com `return`.
- Se não era número, avisa, limpa o buffer e pergunta de novo.

O `while (1)` é um laço infinito de propósito: ele só termina quando a função devolve um valor válido ou encerra o programa. No `main`, cada leitura virou uma linha só:

```c
num1 = lerNumero("Digite o primeiro numero: ");
```

Também passei a chamar `limparBuffer()` depois de ler a operação e a resposta `s/n`, para que letras extras (como `ab`) não atrapalhem a próxima leitura.

### Uma limitação que ainda existe

Se eu digitar `12abc`, o `scanf` lê o `12` com sucesso e o programa aceita sem avisar. Para rejeitar isso também, teria que ler a linha inteira com `fgets` e converter com `strtod`. Deixei como desafio para uma próxima versão.

## Como compilar e executar

É preciso ter o [GCC](https://gcc.gnu.org/) instalado.

```bash
gcc calculadora.c -o calculadora -lm
./calculadora
```

No Windows, execute com `calculadora.exe`.

## Exemplos de uso

Divisão:

```
Digite o primeiro numero: 10
Digite a operacao (+, -, *, /, %, r para raiz): /
Digite o segundo numero: 4
Resultado: 2.50
Deseja fazer outro calculo? (s/n): n
Programa encerrado.
```

Resto da divisão:

```
Digite o primeiro numero: 10.5
Digite a operacao (+, -, *, /, %, r para raiz): %
Digite o segundo numero: 3
Resultado: 1.50
Deseja fazer outro calculo? (s/n): n
Programa encerrado.
```

Raiz quadrada (o segundo número não é pedido):

```
Digite o primeiro numero: 16
Digite a operacao (+, -, *, /, %, r para raiz): r
Resultado: 4.00
Deseja fazer outro calculo? (s/n): n
Programa encerrado.
```

Entrada inválida (o programa pede de novo):

```
Digite o primeiro numero: abc
Entrada invalida! Digite apenas numeros.
Digite o primeiro numero: 5
Digite a operacao (+, -, *, /, %, r para raiz): +
Digite o segundo numero: 3
Resultado: 8.00
Deseja fazer outro calculo? (s/n): n
Programa encerrado.
```

## Dificuldades que encontrei

- Entender por que o `scanf` pulava a leitura do caractere (resolvido com o espaço antes do `%c`).
- Lembrar do `break` em cada `case`.
- Diferenciar `=` de `==`.
- Entender por que o `scanf` precisa do `&`.
- Descobrir que a raiz quadrada exige a flag `-lm` na compilação.
- Perceber que o `%` não funciona com `double` e que, no `printf`, precisa ser escrito `%%`.
- Entender por que o texto inválido ficava preso no buffer e como limpá-lo.

## Próximos passos

- [x] Adicionar a raiz quadrada
- [x] Adicionar a operação de resto (`%`)
- [x] Validar o retorno do `scanf` para quando o usuário digitar letras no lugar de números
- [ ] Rejeitar entradas como `12abc` usando `fgets` e `strtod`
- [ ] Separar cada operação em funções (`somar`, `subtrair`, etc.)
- [ ] Adicionar potenciação com `pow()`

## Autor

**João Victor Ferreira Cosmi**

- GitHub: [@Cosmivctr](https://github.com/Cosmivctr)
