#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LIST_SIZE 30

typedef struct Aluno
{
    char nome[100];
    char matricula[10];
    float nota;
    float frequencia;
    struct Aluno *next;
} Aluno;

Aluno* create_aluno(char *nome, char *matricula, float nota, float frequencia);
void append(Aluno **head, char *nome, char *matricula, float nota, float frequencia);
void scan_alunos(Aluno **head);
void check_alunos(Aluno *head);
void free_list(Aluno *head);

int main(void)
{
    Aluno *head = NULL;
    scan_alunos(&head);
    check_alunos(head);
    free_list(head);
}

Aluno* create_aluno(char *nome, char *matricula, float nota, float frequencia)
{
    Aluno *new_aluno = (Aluno*) malloc(sizeof(Aluno));
    if (new_aluno == NULL)
    {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    strcpy(new_aluno->nome, nome);
    strcpy(new_aluno->matricula, matricula);
    new_aluno->nota = nota;
    new_aluno->frequencia = frequencia;
    new_aluno->next = NULL;

    return new_aluno;
}

void append(Aluno **head, char* nome, char *matricula, float nota, float frequencia)
{
    Aluno *aluno = create_aluno(nome, matricula, nota, frequencia);
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
    printf("Digite os dados dos alunos:");
    for (int i = 0; i < LIST_SIZE; i++)
    {
        char nome[100], mat[10];
        float nota, freq;

        printf("\nAluno %d:\n", i + 1);

        printf("Nome: ");
        scanf("%s", nome);

        printf("Matrícula: ");
        scanf("%s", mat);

        do
        {
            printf("Nota: ");
            scanf("%f", &nota);
        } while (nota < 0 || nota > 10);

        do
        {
            printf("Presença (em %%): ");
            scanf("%f", &freq);
        } while (freq < 0 || freq > 100);

        append(head, nome, mat, nota, freq);
    }
}

void check_alunos(Aluno *head)
{
    Aluno *current = head;
    int i = 0;
    while (current != NULL)
    {
        printf("\nAluno %d: %s - ", i + 1, current->nome);
        if (current->nota >= 6 && current->frequencia >= 75)
        {
            printf("Aprovado\n");
        }
        else if (current->nota < 6 && current->frequencia < 75)
        {
            printf("Reprovado por nota e por falta\n");
        }
        else if (current->nota < 6) {
            printf("Reprovado por nota\n");
        }
        else
        {
            printf("Reprovado por falta\n");
        }

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