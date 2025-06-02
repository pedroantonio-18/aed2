#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000

typedef struct Node
{
    int key;
    struct Node *next;
} Node;

typedef struct Hash
{
    Node *table[TABLE_SIZE];
    int occupied;
} Hash;

int hash_function(int key);
void initialize_hash(Hash *ht);
Node *create_node(int key);
void insert_key(Hash *ht, int key);
int search_key(Hash *ht, int key);
void free_hash(Hash *ht);
void diagnosis(Hash *ht);

int main(void)
{
    Hash ht;
    initialize_hash(&ht);
    
    FILE *f = fopen("data.txt", "r");
    if (f == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }
    
    int key;
    int count = 0;
    while (count < 3000 && fscanf(f, "%d", &key) == 1)
    {
        insert_key(&ht, key);
        count++;
    }
    fclose(f);
    
    char input[100];
    printf("Opções:\n");
    printf("1. Digite uma chave para buscar\n");
    printf("2. Digite 'd' para diagnóstico\n");
    printf("3. Digite 'q' para sair\n");

    while (1)
    {
        printf("Chave: ");
        fgets(input, sizeof(input), stdin);
        
        if (input[0] == 'q')
            break;
        if (input[0] == 'd')
        {
            diagnosis(&ht);
            continue;
        }

        key = atoi(input);
        if (key == 0 && input[0] != '0')
        {
            printf("Entrada inválida.\n");
            continue;
        }

        int steps = search_key(&ht, key);
        if (steps == -1)
            printf("Chave %d não encontrada\n", key);
        else
            printf("Chave %d encontrada em %d passos\n", key, steps);
    }
    
    printf("Posições ocupadas: %d\n", ht.occupied);
    printf("Posições vazias: %d\n", TABLE_SIZE - ht.occupied);
    
    free_hash(&ht);
    return 0;
}

int hash_function(int key)
{
    unsigned int prime1 = 73;
    unsigned int prime2 = 911;
    unsigned int prime3 = 131;
    unsigned int fibo_mix = 2584;
    
    unsigned int h = (unsigned int)key;

    h = (h * prime1 + fibo_mix) ^ (h >> 9) ^ (h << 13);
    h = (h * prime2 + prime1) ^ (h >> 15) ^ (h << 7);
    h = (h * prime3) ^ (h >> 11);

    return h % TABLE_SIZE;
}

void initialize_hash(Hash *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
        ht->table[i] = NULL;
    ht->occupied = 0;
}

Node *create_node(int key)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}

void insert_key(Hash *ht, int key)
{
    int index = hash_function(key);

    Node *current = ht->table[index];
    while (current != NULL)
    {
        if (current->key == key)
            return;
        current = current->next;
    }

    Node *new_node = create_node(key);
    new_node->next = ht->table[index];
    ht->table[index] = new_node;

    if (new_node->next == NULL)
        ht->occupied++;
}

int search_key(Hash *ht, int key)
{
    int index = hash_function(key);
    int steps = 1;

    Node *current = ht->table[index];

    while (current != NULL)
    {
        if (current->key == key)
            return steps;
        current = current->next;
        steps++;
    }

    return -1;
}

void free_hash(Hash *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node *current = ht->table[i];
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

void diagnosis(Hash *ht)
{
    FILE *f = fopen("data.txt", "r");
    if (f == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    int key;
    int total_steps = 0;
    int max_steps = 0;

    for (int i = 0; i < 3000 && fscanf(f, "%d", &key) == 1; i++)
    {
        int steps = search_key(ht, key);
        if (steps != -1)
        {
            total_steps += steps;
            if (steps > max_steps)
                max_steps = steps;
        }
    }
    fclose(f);

    double avg_steps = (double)total_steps / 3000;
    printf("Média de passos por busca: %.2lf\n", avg_steps);
    printf("Máximo de passos em uma busca: %d\n", max_steps);
}