#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RenderFile(const char *path)
{
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    // render file
    printf("Render file: %s\n\n", path);

    char linha[100];

    while (fgets(linha, sizeof(linha), file))
    {

        printf("%s", linha);
    }
    fclose(file);
}

int FileToArray(const char *path, char *linhas[])
{
    int maxLine = 100; // ate 100 linhas
    // contadores de linhas
    int n = 0;

    // lendo o primeiro arquivo
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return -1;
    }

    // render file
    // printf("adicionando em array linhas do  arquivo: %s\n\n",path);

    char linha[100];

    while (fgets(linha, sizeof(linha), file) && n < maxLine)
    {
        // push em linhasF1
        linha[strcspn(linha, "\n")] = '\0'; // remove o \n se existir

        linhas[n] = malloc(strlen(linha) + 1); // tamnho da linha + \n
        if (linhas[n] == NULL)
        {
            printf("Erro de memorio seila oque fazer");
            break;
        }
        strcpy(linhas[n], linha);
        n++;
    }
    fclose(file);
    return n;
}

void diff(const char *path1, const char *path2)
{
    // tentar fazer aquela porra de LCS
    char *linhasF1[100]; // ate 100 linhas
    char *linhasF2[100];
    const int n1 = FileToArray(path1, linhasF1);
    const int n2 = FileToArray(path2, linhasF2);
    int fullAdd = 0;

    printf("arquivo 1(%s) tem %d linhas\n", path1, n1);
    printf("arquivo 2(%s) tem %d linhas\n", path2, n2);

    // se arquivo 1 estiver vazio, tudo que esta no arquivo 2 é adição.
    if( n1 ==0 && n2 > 0){
        fullAdd = 1;
    }

    // matriz bidimendcional de comparação
    /* a regra do porjeto
    linha  vazia significa que temos uma REMOÇÂO
    coluna vazia significa que temo uma ADIÇÃO
    linha e coluna vazia temos um MODIFICAÇÂO
    */
    int comparation[100][100] = {0};
    int colUsed[100] = {0}; // para evitar repetição desnecessaria

    for (int y = 0; y < n1; y++)
    { // para cada linha de A
        for (int x = 0; x < n2; x++)
        { 
            if (!colUsed[x] && strcmp(linhasF1[y], linhasF2[x]) == 0)
            {
                comparation[y][x] = 1;
                colUsed[x] = 1;
                break;
            }
        }
    }
    // retorar resultado da comparçaõ
    printf("\n\n");
    for (int y = 0; y < n1; y++)
    {
        for (int x = 0; x < n2; x++)
        {
            printf("%d ", comparation[y][x]);
        }
        printf("\n");
    }

    if(fullAdd == 1){
        printf("todas as linhas do arquivo '%s' eh adicao", path2);
    }

    // rederizar oque foi adicionado e removido
    //exemplos dizem pra começar de baixo pta cim então ta 
    char ops[100 * 2];      // '+' ou '-'
    char *textos[100 * 2];  // ponteiro pra linha correspondente
    int nOps = 0;

    int i = n1, j = n2;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && strcmp(linhasF1[i - 1], linhasF2[j - 1]) == 0) {
            // linha igual → não gera operação
            i--; j--;
        } else if (j > 0 && (i == 0 || comparation[i][j - 1] >= comparation[i - 1][j])) {
            // adição (veio de B)
            ops[nOps] = '+';
            textos[nOps] = linhasF2[j - 1];
            nOps++;
            j--;
        } else {
            // remoção (veio de A)
            ops[nOps] = '-';
            textos[nOps] = linhasF1[i - 1];
            nOps++;
            i--;
        }
    }

    // ---- 3) Imprime o diff ----
    printf("=== Diff (transformar '%s' em '%s') ===\n", path1, path2);
    for (int k = nOps - 1; k >= 0; k--) {
        printf("%c %s\n", ops[k], textos[k]);
    }


    
}

void main()
{
    // leitura dos arquivos
    //  RenderFile("files exemple/code1.txt");
    diff("files exemple/code1.txt", "files exemple/code2.txt");

    return;
}