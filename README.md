# Calculadora em C

Este é um dos meus primeiros projetos em linguagem C. Criei uma calculadora de terminal com as quatro operações básicas (soma, subtração, multiplicação e divisão) e, depois, evoluí o projeto adicionando a **raiz quadrada**. O objetivo é praticar os fundamentos da linguagem e documentar o que fui aprendendo no caminho.

Escrevi este README como um diário de estudo: além de mostrar como usar o programa, explico por que escrevi cada parte do código.

## Funcionalidades

- Soma (`+`), subtração (`-`), multiplicação (`*`) e divisão (`/`)
- Raiz quadrada (`r`), que usa apenas um número
- Suporte a números decimais (tipo `double`)
- Tratamento de divisão por zero
- Tratamento de raiz de número negativo
- Validação de operação inválida
- Repetição de cálculos sem precisar reiniciar o programa

## O que eu queria praticar

- Ler dados do teclado e mostrar resultados na tela
- Trabalhar com variáveis de tipos diferentes
- Tomar decisões no código com `switch` e `if/else`
- Repetir ações com um laço
- Proteger o programa contra entradas problemáticas
- Usar uma biblioteca externa (`math.h`) e compilar com ela

## Como o programa funciona

1. Pede o primeiro número.
2. Pede a operação (`+`, `-`, `*`, `/` ou `r` para raiz).
3. Pede o segundo número, **exceto** na raiz quadrada.
4. Calcula e mostra o resultado.
5. Pergunta se quero fazer outro cálculo. Se sim, volta ao passo 1.

## O que aprendi em cada parte do código

### Bibliotecas `stdio.h` e `math.h`

```c
#include <stdio.h>
#include <math.h>
```

O C não sabe, por conta própria, mostrar texto na tela nem ler o teclado. Essas funções (`printf` e `scanf`) vêm da `stdio.h`. Já a `math.h` traz funções matemáticas, como a `sqrt()` da raiz quadrada. Sem essas linhas, o compilador não reconhece as funções.

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
scanf("%lf", &num1);
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

Antes, o programa sempre pedia dois números. Para a raiz isso não faz sentido, então coloquei a leitura de `num2` dentro de um `if`:

```c
if (operacao != 'r') {
    printf("Digite o segundo numero: ");
    scanf("%lf", &num2);
}
```

O `!=` significa "diferente de". Assim, o segundo número só é pedido nas operações que precisam dele.

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
Digite a operacao (+, -, *, /, r para raiz): /
Digite o segundo numero: 4
Resultado: 2.50
Deseja fazer outro calculo? (s/n): n
Programa encerrado.
```

Raiz quadrada (note que o segundo número não é pedido):

```
Digite o primeiro numero: 16
Digite a operacao (+, -, *, /, r para raiz): r
Resultado: 4.00
Deseja fazer outro calculo? (s/n): n
Programa encerrado.
```

## Dificuldades que encontrei

- Entender por que o `scanf` pulava a leitura do caractere (resolvido com o espaço antes do `%c`).
- Lembrar do `break` em cada `case`.
- Diferenciar `=` de `==`.
- Entender por que o `scanf` precisa do `&`.
- Descobrir que a raiz quadrada exige a flag `-lm` na compilação.

## Próximos passos

- [x] Adicionar a raiz quadrada
- [ ] Adicionar a operação de resto (`%`)
- [ ] Validar o retorno do `scanf` para quando o usuário digitar letras no lugar de números
- [ ] Separar cada operação em funções (`somar`, `subtrair`, etc.)
- [ ] Adicionar potenciação com `pow()`

## Autor

**João Victor Ferreira Cosmi**

- GitHub: [@Cosmivctr](https://github.com/Cosmivctr)
