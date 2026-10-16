# pdiff

Um utilitário de diff de arquivos em C, inspirado no comportamento do `git diff`. Compara dois arquivos de texto linha a linha e mostra as operações necessárias para transformar um no outro.

## Como funciona

O programa usa o algoritmo **LCS (Longest Common Subsequence)** para encontrar a maior sequência de linhas que aparece em ambos os arquivos **na mesma ordem**. Tudo que não faz parte dessa sequência vira uma operação:

- `+` → linha **adicionada** (existe no arquivo 2, não no arquivo 1)
- `-` → linha **removida** (existe no arquivo 1, não no arquivo 2)
- Linhas sem prefixo → **inalteradas**

Como o LCS é simétrico, a lista de operações lida ao contrário (trocando `+` por `-`) transforma o arquivo 2 de volta no arquivo 1.

## Compilação

```bash
gcc pdiff.c -o pdiff