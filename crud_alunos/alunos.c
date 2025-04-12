#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno
{
    char nome[100];
    int matricula;
    struct Aluno *next;
} Aluno;

void menu(int option, Aluno **head);
Aluno* create_aluno(char *nome, int matricula);
void insert_ordered(Aluno **head, char *nome, int matricula);
int remove_aluno(Aluno **head, int matricula);
int update_aluno(Aluno *head, int matricula, char *new_nome, int new_matricula);
void print_list(Aluno *head);
void free_list(Aluno *head);

int main(void)
{
    Aluno *head = NULL;

    int option;
    do
    {
        printf("Escolha uma opção:\n[ 0 ] - Sair\n[ 1 ] - Adicionar estudante\n[ 2 ] - Remover estudante\n[ 3 ] - Atualizar dados de um estudante\n[ 4 ] - Mostrar lista de estudante\n");
        scanf("%d", &option);
        printf("\n");
        menu(option, &head);
    }
    while (option != 0);
}

void menu(int option, Aluno **head)
{
    switch (option)
    {
        int matricula, new_matricula;
        char nome[100], new_nome[100];

        case 0:
            free_list(*head);
            return;
            break;

        case 1:
            printf("Insira os dados do aluno:\n");
            printf("Nome: ");
            getchar();
            fgets(nome, 100, stdin);
            nome[strcspn(nome, "\n")] = '\0';
            printf("Matrícula: ");
            scanf("%d", &matricula);
            printf("\n");
            insert_ordered(head, nome, matricula);
            break;

        case 2:
            printf("Insira a matrícula do aluno a ser removido: ");
            scanf("%d", &matricula);
            printf("\n");
            remove_aluno(head, matricula);
            break;

        case 3:
            printf("Insira a matrícula atual do estudante a ser modificado: ");
            scanf("%d", &matricula);
            printf("Insira o nome atualizado: ");
            scanf("%s", new_nome);
            printf("Insira a matrícula atualizada: ");
            scanf("%d", &new_matricula);
            printf("\n");
            update_aluno(*head, matricula, new_nome, new_matricula);
            break;

        case 4:
            print_list(*head);
            printf("\n");
            break;
        
        default:
            printf("Insira uma opção válida\n");
            break;
    }
}

Aluno* create_aluno(char *nome, int matricula)
{
    Aluno *new_aluno = (Aluno*) malloc(sizeof(Aluno));

    if (new_aluno == NULL)
    {
        return NULL;
    }

    strcpy(new_aluno->nome, nome);
    new_aluno->matricula = matricula;
    new_aluno->next = NULL;

    return new_aluno;
}

void insert_ordered(Aluno **head, char *nome, int matricula)
{
    Aluno *new_aluno = create_aluno(nome, matricula);

    if (*head == NULL)
    {
        *head = new_aluno;
        return;
    }

    if (new_aluno->matricula < (*head)->matricula)
    {
        new_aluno->next = *head;
        *head = new_aluno;
        return;
    }

    Aluno *prev = *head;
    Aluno *current = *head;
    while ((current != NULL) && (current->matricula < new_aluno->matricula))
    {
        prev = current;
        current = current->next;
    }
    
    prev->next = new_aluno;
    new_aluno->next = current;
}

int remove_aluno(Aluno **head, int matricula)
{
    if (head == NULL) return 0;

    Aluno *prev = NULL;
    Aluno *current = *head;
    while ((current != NULL) &&  (current->matricula != matricula))
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return 0;

    if (prev == NULL)
    {
        (*head) = current->next;
    }
    else
    {
        prev->next = current->next;
    }

    free(current);

    return 1;
}

int update_aluno(Aluno *head, int matricula, char *new_nome, int new_matricula)
{
    Aluno *current = head;
    while ((current != NULL) && (current->matricula != matricula))
    {
        current = current->next;
    }

    if (current == NULL) return 0;

    strcpy(current->nome, new_nome);
    current->matricula = new_matricula;

    return 1;
}

void print_list(Aluno *head)
{
    Aluno *current = head;
    while (current != NULL)
    {
        printf("( Nome: %s | Matrícula: %d )\n", current->nome, current->matricula);
        current = current->next;
    }
}

void free_list(Aluno *head)
{
    Aluno *current = head;
    while (current != NULL)
    {
        Aluno *tmp = current->next;
        free(current);
        current = tmp;
    }
}