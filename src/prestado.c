#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/prestado.h"

#define ARQUIVO_PRESTADOS "src/bin/prestados.bin"

int gerarProximoIDPrestado() {
    FILE *file = fopen(ARQUIVO_PRESTADOS, "rb");
    if (file == NULL) {
        return 1; // Arquivo inexistente, primeiro ID será 1
    }

    Prestado prestado;
    int maxID = 0;

    while (fread(&prestado, sizeof(Prestado), 1, file)) {
        if (prestado.id > maxID) {
            maxID = prestado.id;
        }
    }

    fclose(file);
    return maxID + 1; // Retorna o próximo ID
}

int salvarPrestado(Prestado prestado) {
    FILE *file = fopen(ARQUIVO_PRESTADOS, "ab"); // Abre o arquivo no modo de adicionar binário
    if (file == NULL) {
        return 0;
    }

    fwrite(&prestado, sizeof(Prestado), 1, file); // Escreve o serviço prestado no arquivo
    fclose(file);
    return 1;
}

int contarPrestados() {
    FILE *file = fopen(ARQUIVO_PRESTADOS, "rb");
    if (file == NULL) {
        return 0; // Arquivo inexistente ou vazio
    }

    // Move o ponteiro para o final do arquivo
    fseek(file, 0, SEEK_END);

    // Calcula o tamanho do arquivo em bytes
    long tamanhoArquivo = ftell(file);

    // Calcula o número de registros dividindo o tamanho total pelo tamanho de um struct de Serviço Prestado
    int totalPrestados = tamanhoArquivo / sizeof(Prestado);

    fclose(file);

    return totalPrestados;
}

Prestado *listarPrestados(int quantidade) {
    FILE *file = fopen(ARQUIVO_PRESTADOS, "rb");
    if (file == NULL) {
        return NULL;
    }

    if (quantidade == 0) {
        fclose(file);
        return NULL;
    }

    Prestado *prestados = (Prestado *)malloc(quantidade * sizeof(Prestado));
    if (prestados == NULL) {
        fclose(file);
        return NULL;
    }

    fread(prestados, sizeof(Prestado), quantidade, file);
    fclose(file);

    return prestados;
}

int atualizarPrestado(Prestado *prestadoRecebido) {
    FILE *file = fopen(ARQUIVO_PRESTADOS, "rb"); // Abre o arquivo original
    if (file == NULL) {
        return 1;
    }

    FILE *temp = fopen("src/bin/temp_prestado1.bin", "wb"); // Cria o arquivo temporário
    if (temp == NULL) {
        fclose(file);
        return 2;
    }

    Prestado prestado;
    int encontrado = 0;

    while (fread(&prestado, sizeof(Prestado), 1, file)) {
        if (prestado.id == prestadoRecebido->id) {
            encontrado = 1; // Encontrou o serviço prestado a ser atualizado
            fwrite(prestadoRecebido, sizeof(Prestado), 1, temp); // Escreve o serviço prestado recebido no arquivo temporário
        } else {
            fwrite(&prestado, sizeof(Prestado), 1, temp); // Escreve os demais serviços prestados no arquivo temporário
        }
    }

    fclose(file);
    fclose(temp);

    if (encontrado == 1) {
        remove(ARQUIVO_PRESTADOS);           // Remove o arquivo original
        rename("src/bin/temp_prestado1.bin", ARQUIVO_PRESTADOS); // Renomeia o temporário para o original
        return 0;
    } else {
        remove("src/bin/temp_prestado1.bin");               // Remove o temporário
        return 3;
    }
}

int excluirPrestado(int id) {
    FILE *file = fopen(ARQUIVO_PRESTADOS, "rb"); // Abre o arquivo original
    if (file == NULL) {
        return 1;
    }

    FILE *temp = fopen("src/bin/temp_prestado2.bin", "wb"); // Cria o arquivo temporário
    if (temp == NULL) {
        fclose(file);
        return 2;
    }

    Prestado prestado;
    int encontrado = 0;

    while (fread(&prestado, sizeof(Prestado), 1, file)) {
        if (prestado.id == id) {
            encontrado = 1; // Encontrou o serviço prestado a ser excluído
        } else {
            fwrite(&prestado, sizeof(Prestado), 1, temp); // Escreve no arquivo temporário
        }
    }

    fclose(file);
    fclose(temp);

    if (encontrado == 1) {
        remove(ARQUIVO_PRESTADOS);           // Remove o arquivo original
        rename("src/bin/temp_prestado2.bin", ARQUIVO_PRESTADOS); // Renomeia o temporário para o original
        return 0;
    } else {
        remove("src/bin/temp_prestado2.bin");               // Remove o temporário
        return 3;
    }
}

Prestado *buscarPrestadoPeloID(int id) {
    FILE *file = fopen(ARQUIVO_PRESTADOS, "rb");
    if (file == NULL) {
        return NULL; // Arquivo inexistente, serviço prestado não existe
    }
    
    Prestado *prestado = (Prestado *)malloc(1 * sizeof(Prestado));
    while (fread(prestado, sizeof(Prestado), 1, file)) {
        if (prestado->id == id) {
            fclose(file);
            return prestado; // Serviço prestado encontrado
            
        }
    }

    fclose(file);
    return NULL; // Serviço prestado não encontrado
}

Prestado *listarPrestadosPorPet(int idPet, int *qtdPrestadosVinculados) { 
    FILE *file = fopen(ARQUIVO_PRESTADOS, "rb");
    if (file == NULL) {
        return NULL; // Arquivo inexistente
    }

    Prestado prestado;
    int total = 0;

    // Contar quantos Serviços Prestados estão vinculados ao idPet
    while (fread(&prestado, sizeof(Prestado), 1, file)) {
        if (prestado.codPet == idPet) {
            total++;
        }
    }

    // Se não há Serviços prestados vinculados, encerra
    if (total == 0) {
        fclose(file);
        *qtdPrestadosVinculados = 0;
        return NULL;
    }

    // Aloca memória para armazenar os pets vinculados
    Prestado *prestados = (Prestado *)malloc((total) * sizeof(Prestado));
    if (prestados == NULL) {
        fclose(file);
        return NULL; // Falha na alocação de memória
    }

    rewind(file); // Volta ao início do arquivo para ler novamente
    int index = 0;

    // Lê os serviços prestados vinculados ao idPet
    while (fread(&prestado, sizeof(Prestado), 1, file)) {
        if (prestado.codPet == idPet) {
            prestados[index++] = prestado;
        }
    }
    *qtdPrestadosVinculados = total;

    fclose(file);

    return prestados; // Retorna a lista de serviços prestados encontrados
}