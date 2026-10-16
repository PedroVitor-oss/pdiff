# pdiff

Um utilitário de diff de arquivos em C, inspirado no comportamento do `git diff`. Compara dois arquivos de texto linha a linha e mostra as operações necessárias para transformar um no outro.

## Como funciona

O programa usa o algoritmo **LCS (Longest Common Subsequence)** para encontrar a maior sequência de linhas que aparece em ambos os arquivos **na mesma ordem**. Tudo que não faz parte dessa sequência vira uma operação:

- `+` → linha **adicionada** (existe no arquivo 2, não no arquivo 1)
- `-` → linha **removida** (existe no arquivo 1, não no arquivo 2)
- Linhas sem prefixo → **inalteradas**

Como o LCS é simétrico, a lista de operações lida ao contrário (trocando `+` por `-`) transforma o arquivo 2 de volta no arquivo 1.
## Exemplo completo

Suponha que você tem duas versões de um mesmo arquivo C.

### `v1.c`

```c
#incldue <stdio.h>

void main(){
    printf("ola mundo");
}
```

### `v2.c`

```c
#include <stdio.h>

void greet() {
    printf("ola mundo");
}

int main() {
    greet();
    return 0;
}
```

### Rodando o diff

```bash
./pdiff 
```

### Saída (teorica)

```
arquivo 1(v1.c) tem 6 linhas
arquivo 2(v2.c) tem 9 linhas

=== Diff (transformar 'v1.c' em 'v2.c') ===
+ void greet() {
+     printf("Hello\n");
+ }
+
+     greet();

Resumo: 5 adicao(oes), 0 remocao(oes)
```

### Lendo o resultado

As linhas com `+` são o que precisa ser **inserido** em `v1.c` para chegar em `v2.c`:

- A função `greet()` foi adicionada antes da `main`.
- A chamada `greet();` foi adicionada dentro da `main`.

Se você **inverter a leitura** (aplicar as operações ao contrário, trocando `+` por `-`), o mesmo resultado transforma `v2.c` de volta em `v1.c`.

## Compilação

```bash
gcc pdiff.c -o pdiff