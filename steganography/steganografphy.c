#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECURE_START 33
#define SECURE_END 120

// Funções principais
void stegano(char *original_img, char *stegano_img, char *text);
void unstegano(char *stegano_img);

// Funções auxiliares
char *tag_text(char *text, int len);
unsigned char *str2bin(char *text, int len);

int main(int argc, char *argv[])
{
    if (argc != 5 && argc != 3)
    {
        printf("Modos de uso:\n");
        printf("Esteganografar: %s -e <imagem_entrada.jpg> <imagem_saida.jpg> <texto>\n", argv[0]);
        printf("Desesteganografar: %s -d <imagem_esteganografada.jpg>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-e") == 0)
    {
        char *original_img = argv[2];
        char *stegano_img = argv[3];
        char *text = argv[4];
        stegano(original_img, stegano_img, text);
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        char *stegano_img = argv[2];
        unstegano(stegano_img);
    }
    else
    {
        printf("Flag inválida\n");
        return 1;
    }

    return 0;
}

void stegano(char *original_img, char *stegano_img, char *text)
{
    if (strlen(text) > 10)
    {
        printf("Só é possível inserir uma plavra de até 10 caracteres\n");
        return;
    }

    FILE *input = fopen(original_img, "rb");
    FILE *output = fopen(stegano_img, "wb");

    if (input == NULL || output == NULL)
    {
        printf("Falha ao abrir arquivos\n");
        if (input) fclose(input);
        if (output) fclose(output);
        return;
    }

    int text_len = strlen(text);
    char *tagged_text = tag_text(text, text_len);
    if (!tagged_text)
    {
        fclose(input);
        fclose(output);
        return;
    }

    unsigned char *bin_text = str2bin(tagged_text, text_len + 2);
    if (!bin_text)
    {
        free(tagged_text);
        fclose(input);
        fclose(output);
        return;
    }

    int bin_len = (text_len + 2) * 8; 
    int pos = 0;
    int bin_index = 0;
    unsigned char byte;
    while (fread(&byte, 1, 1, input) == 1)
    {
        if (pos >= SECURE_START && pos <= SECURE_END && bin_index < bin_len)
        {
            byte &= 0b11111110;
            byte |= bin_text[bin_index];
            bin_index++;
        }

        fputc(byte, output);
        pos++;
    }

    free(tagged_text);
    free(bin_text);
    fclose(input);
    fclose(output);
}

void unstegano(char *stegano_img)
{
    FILE *input = fopen(stegano_img, "rb");
    if (input == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    fseek(input, 0, SEEK_END);
    long file_size = ftell(input);
    fseek(input, 0, SEEK_SET);

    unsigned char *image = (unsigned char*) malloc(file_size);
    if (image == NULL)
    {
        printf("Falha ao alocar memória\n");
        fclose(input);
        return;
    }

    fread(image, 1, file_size, input);
    fclose(input);

    char text[11];
    int text_index = 0;
    char current_char = 0;
    int bit_index = 0;
    bool found_start = false;

    for (int i = SECURE_START; i <= SECURE_END && i < file_size; i++)
    {
        unsigned char byte = image[i];
        int lsb = byte & 1;

        current_char = (current_char << 1) | lsb;
        bit_index++;

        if (bit_index == 8)
        {
            if (current_char == '$' && !found_start)
                found_start = true;
            else
            {
                if (found_start)
                {
                    if (current_char == '$')
                    {
                        text[text_index] = '\0';
                        break;
                    }
                    if (text_index < 10)
                    {
                        text[text_index++] = current_char;
                    }
                }
            }
            current_char = 0;
            bit_index = 0;
        }
    }

    if (found_start && text_index > 0)
        printf("Texto extraído: %s\n", text);
    else
        printf("Nenhum texto oculto encontrado ou formato inválido!\n");

    free(image);
}

char *tag_text(char *text, int len)
{
    char *tagged_text = (char *)malloc(len + 3);
    if (tagged_text == NULL)
    {
        printf("Falha ao alocar memória\n");
        return NULL;
    }

    tagged_text[0] = '$';
    strcpy(tagged_text + 1, text);
    tagged_text[len + 1] = '$';
    tagged_text[len + 2] = '\0';

    return tagged_text;
}

unsigned char *str2bin(char *text, int len) {
    unsigned char *bin = (unsigned char *)malloc(len * 8);
    if (!bin) {
        printf("Falha ao alocar memória\n");
        return NULL;
    }

    int bin_index = 0;
    for (int i = 0; i < len; i++) {
        unsigned char c = text[i];
        for (int j = 0; j < 8; j++) {
            unsigned char temp = c;
            for (int k = 0; k < 7 - j; k++) 
                temp /= 2;
            bin[bin_index + j] = temp % 2;
        }
        bin_index += 8;
    }
    return bin;
}