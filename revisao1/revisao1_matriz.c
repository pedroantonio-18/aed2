#include <stdio.h>
#include <string.h>

#define ROWS 3
#define COLS 10

typedef struct
{
    char nome[100];
    char matricula[10];
    float nota;
    float frequencia;
} Aluno;

void scan_alunos(Aluno alunos[ROWS][COLS]);
void check_alunos(Aluno alunos[ROWS][COLS]);

int main(void)
{
    Aluno alunos[ROWS][COLS];
    scan_alunos(alunos);
    check_alunos(alunos);
}

void scan_alunos(Aluno alunos[ROWS][COLS])
{
    printf("Digite os dados dos alunos:\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("\nAluno %d:\n", i * COLS + j + 1);

            printf("Nome: ");
            scanf("%s", alunos[i][j].nome);

            printf("Matrícula: ");
            scanf("%s", alunos[i][j].matricula);

            do
            {
                printf("Nota: ");
                scanf("%f", &alunos[i][j].nota);
            } while (alunos[i][j].nota < 0 || alunos[i][j].nota > 10);

            do
            {
                printf("Frequência (em %%): ");
                scanf("%f", &alunos[i][j].frequencia);
            } while (alunos[i][j].frequencia < 0 || alunos[i][j].frequencia > 100);
        }
    }
}

void check_alunos(Aluno alunos[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("\nAluno %d: %s - ", i * COLS + j + 1, alunos[i][j].nome);
            if (alunos[i][j].nota >= 6 && alunos[i][j].frequencia >= 75)
            {
                printf("Aprovado\n");
            }
            else if (alunos[i][j].nota < 6 && alunos[i][j].frequencia < 75)
            {
                printf("Reprovado por nota e por falta\n");
            }
            else if (alunos[i][j].nota < 6)
            {
                printf("Reprovado por nota\n");
            }
            else
            {
                printf("Reprovado por falta\n");
            }
        }
    }
}
