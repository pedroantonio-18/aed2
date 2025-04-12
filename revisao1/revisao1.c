#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 3
#define COLS 10
#define LIST_SIZE 30

// Versão 1 - Matriz
typedef struct
{
    char nome[100];
    char matricula[10];
    float nota;
    float frequencia;
} AlunoMatriz;

void scan_alunos_matriz(AlunoMatriz alunos[ROWS][COLS]);
void check_alunos_matriz(AlunoMatriz alunos[ROWS][COLS]);

// Versão 2 - Lista Encadeada
typedef struct Aluno
{
    char nome[100];
    char matricula[10];
    float nota;
    float frequencia;
    struct Aluno *next;
} AlunoLista;

AlunoLista* create_aluno(char *nome, char *matricula, float nota, float frequencia);
void append(AlunoLista **head, char *nome, char *matricula, float nota, float frequencia);
void scan_alunos_lista(AlunoLista **head);
void check_alunos_lista(AlunoLista *head);
void free_list(AlunoLista *head);

int main(void)
{
    int opcao;
    printf("Escolha a versão:\n");
    printf("1 - Matriz\n");
    printf("2 - Lista Encadeada\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
        case 1:
        {
            AlunoMatriz alunos[ROWS][COLS];
            scan_alunos_matriz(alunos);
            check_alunos_matriz(alunos);
            break;
        }
        case 2:
        {
            AlunoLista *head = NULL;
            scan_alunos_lista(&head);
            check_alunos_lista(head);
            free_list(head);
            break;
        }
        default:
            printf("Opção inválida\n");
    }

    return 0;
}

// Versão 1 - Matriz
void scan_alunos_matriz(AlunoMatriz alunos[ROWS][COLS])
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

void check_alunos_matriz(AlunoMatriz alunos[ROWS][COLS])
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

// Versão 2 - Lista Encadeada
AlunoLista* create_aluno(char *nome, char *matricula, float nota, float frequencia)
{
    AlunoLista *new_aluno = (AlunoLista*) malloc(sizeof(AlunoLista));
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

void append(AlunoLista **head, char* nome, char *matricula, float nota, float frequencia)
{
    AlunoLista *aluno = create_aluno(nome, matricula, nota, frequencia);
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
        AlunoLista *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = aluno;
    }
}

void scan_alunos_lista(AlunoLista **head)
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

void check_alunos_lista(AlunoLista *head)
{
    AlunoLista *current = head;
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

void free_list(AlunoLista *head)
{
    AlunoLista *current = head;
    AlunoLista *next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}
