#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    char *Name, *Phone, *Course, *Grade1Str, *Grade2Str, *resultado;
    float Grade01, Grade02, FinalGrade;
};

void Resultado(struct student *student)
{
    // Media do aluno
    student->FinalGrade = (student->Grade01 + student->Grade02) / 2;

    // Definir resultado
    if (student->FinalGrade < 7)
    {
        student->resultado = "REPROVADO";
    }
    else
    {
        student->resultado = "APROVADO";
    }
}

void readcsv(FILE *Data, FILE *Data_Output)
{
    char Line[256];
    struct student student;

    // Pular a primeira linha e add cabeçalho arquivo de saida
    fgets(Line, sizeof(Line), Data);

    // Loop de leitura do arquivo de entrada
    while (fgets(Line, sizeof(Line), Data))
    {
        student.Name = strtok(Line, ",");
        student.Phone = strtok(NULL, ",");
        student.Course = strtok(NULL, ",");
        student.Grade1Str = strtok(NULL, ",");
        student.Grade2Str = strtok(NULL, ",");

        student.Grade01 = atof(student.Grade1Str);
        student.Grade02 = atof(student.Grade2Str);

        Resultado(&student);

        // Gravar os resultados no arquivo de saida
        fprintf(Data_Output, "%s,%f,%s\n", student.Name, student.FinalGrade, student.resultado);
        printf("%s, %f, %s\n", student.Name, student.FinalGrade, student.resultado);
    }
}

int main()
{
    FILE *Data;
    FILE *Data_Output;

    Data = fopen("DadosEntrada.csv", "r");
    Data_Output = fopen("SituacaoFinal.csv", "w");

    // Erros de Leitura | Escrita
    if (Data == NULL)
    {
        printf("Não foi possivel abrir o arquivo de entrada.");
        exit(1);
    }
    if (Data_Output == NULL)
    {
        printf("Não foi possivel abrir o arquivo de saida.");
        exit(1);
    }

    // colocar cabeçalho no arquivo
    fprintf(Data_Output, "Nome,Nota Final,Resultado\n");

    readcsv(Data, Data_Output);

    fclose(Data);
    fclose(Data_Output);
    return 0;
}