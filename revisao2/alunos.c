#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno
{
    char nome[30];
    char matricula[10];
    float notas[2];
    float frequencia;
    struct Aluno *next;
} Aluno;

Aluno* create_aluno(char *nome, char *matricula, float *notas, float frequencia);
void append(Aluno **head, char *nome, char *matricula, float *notas, float frequencia);
void scan_alunos(Aluno **head);
void table_alunos(Aluno *head);
void free_list(Aluno *head);

int main(void)
{
    Aluno *head = NULL;
    scan_alunos(&head);
    table_alunos(head);
    free_list(head);
}

Aluno* create_aluno(char *nome, char *matricula, float *notas, float frequencia)
{
    Aluno *new_aluno = (Aluno*) malloc(sizeof(Aluno));
    if (new_aluno == NULL)
    {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    strcpy(new_aluno->nome, nome);
    strcpy(new_aluno->matricula, matricula);
    new_aluno->notas[0] = notas[0];
    new_aluno->notas[1] = notas[1];
    new_aluno->frequencia = frequencia;
    new_aluno->next = NULL;

    return new_aluno;
}

void append(Aluno **head, char* nome, char *matricula, float *notas, float frequencia)
{
    Aluno *aluno = create_aluno(nome, matricula, notas, frequencia);
    if (aluno == NULL)
    {
        return;
    }

    if (*head == NULL)
    {
        *head = aluno;
    }
    else
    {
        Aluno *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = aluno;
    }
}

void scan_alunos(Aluno **head)
{
    int list_size;
    printf("Digite quantos alunos serão adicionados à lista: ");
    scanf("%d", &list_size);
    getchar();

    printf("Digite os dados dos alunos:");

    for (int i = 0; i < list_size; i++)
    {
        char nome[100], mat[10];
        float notas[2], freq;

        printf("\nAluno %d:\n", i + 1);

        printf("Nome: ");
        if (i != 0) while (getchar() != '\n'); 
        fgets(nome, 100, stdin);
        nome[strcspn(nome, "\n")] = '\0';

        printf("Matrícula: ");
        scanf("%s", mat);

        for (int j = 0; j < 2; j++)
        {
            do
            {
                printf("Nota %d: ", (j + 1));
                scanf("%f", &notas[j]);
            } while (notas[j] < 0 || notas[j] > 10);
        }

        do
        {
            printf("Presença (em %%): ");
            scanf("%f", &freq);
        } while (freq < 0 || freq > 100);

        append(head, nome, mat, notas, freq);
    }
}

void table_alunos(Aluno *head)
{
    Aluno *current = head;
    int i = 0;

    printf("\n%-7s | %-25s | %-6s | %-6s | %-13s | %-10s | %-25s\n",
        "Seq", "Nome", "Nota 1", "Nota 2", "Média Final", "Frequência", "Situação");
    printf("--------------------------------------------------------------------------------------------------------------------\n");

    while (current != NULL)
    {
        float mf = (current->notas[0] + current->notas[1]) / 2.0;
        char situacao[40];

        if (mf >= 6 && current->frequencia >= 75)
            strcpy(situacao, "Aprovado");
        else if (mf < 6 && current->frequencia < 75)
            strcpy(situacao, "Reprovado por nota e por falta");
        else if (mf < 6)
            strcpy(situacao, "Reprovado por nota");
        else
            strcpy(situacao, "Reprovado por falta");

        printf("%-7d | %-25s | %6.1f | %6.1f | %12.1f | %9.1f%% | %-25s\n",
                i + 1, current->nome,
                current->notas[0], current->notas[1], mf,
                current->frequencia, situacao);

        current = current->next;
        i++;
    }
}

void free_list(Aluno *head)
{
    Aluno *current = head;
    Aluno *next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}