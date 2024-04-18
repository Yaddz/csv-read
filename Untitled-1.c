#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Portuguese");
    char line[256], *Name, *Phone, *Course, *Grade1Str, *Grade2Str, *resultado;
    float Grade1, Grade2, Final_grade;
    FILE *Data;
    FILE *Data_Output;

    Data = fopen("DadosEntrada.csv", "r");
    Data_Output = fopen("SituacaoFinal.csv", "w");

    //Erros de abertura do arquivo
    if (Data == NULL){
        printf("Não foi possivel abrir o arquivo de entrada.");
        exit(1);
    }

    if (Data_Output == NULL){
        printf("Não foi possivel abrir o arquivo de saida.");
        exit(1);
    }

    //Pular a primeira linha
    fgets(line, sizeof(line), Data);

    //Loop de leitura do arquivo de dados
    fprintf(Data_Output, "Nome,Media,Resultado\n");
    while (fgets(line, sizeof(line), Data)) {
        Name = strtok(line, ",");
        Phone = strtok(NULL, ",");
        Course = strtok(NULL, ",");
        Grade1Str = strtok(NULL, ",");
        Grade2Str = strtok(NULL, ",");

        Grade1 = atof(Grade1Str);
        Grade2 = atof(Grade2Str);

        //Media do aluno
        Final_grade = (Grade1 + Grade2) / 2;

        //Definir resultado
        if (Final_grade < 7 ){
          resultado = "REPROVADO";  
        } else{
            resultado = "APROVADO";
        }

        //Gravar os resultados no arquivo de saida
        fprintf(Data_Output, "%s,%f,%s\n", Name, Final_grade, resultado);
        printf("%f, %s\n", Final_grade, resultado);
    }

    fclose(Data);
    fclose(Data_Output);

    return 0;
}
