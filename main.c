#include <stdio.h>
#include <string.h>

void RenderFile(const char* path){
    FILE *file = fopen(path,"r");

    if(file == NULL){
        printf("Erro ao abrir arquivo\n");
        return;
    }

    // render file 
    printf("Render file: %s\n\n",path);

    char linha[100];

    while (fgets(linha,sizeof(linha),file))
    {
        printf("%s",linha);
    }
    fclose(file);
}

void main(){
    //leitura dos arquivos
    RenderFile("files exemple/code1.txt");

    return;
}