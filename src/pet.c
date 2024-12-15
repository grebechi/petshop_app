#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/pet.h"

#define ARQUIVO_PET "src/bin/pets.bin"

int gerarProximoIDPet() {
    FILE *file = fopen(ARQUIVO_PET, "rb");
    if (file == NULL) {
        return 1; // Arquivo inexistente, primeiro ID será 1
    }

    Pet pet;
    int maxID = 0;

    while (fread(&pet, sizeof(Pet), 1, file)) {
        if (pet.id > maxID) {
            maxID = pet.id;
        }
    }

    fclose(file);
    return maxID + 1; // Retorna o próximo ID
}

int salvarPet(Pet pet) {
    FILE *file = fopen(ARQUIVO_PET, "ab"); // Abre o arquivo no modo de adicionar binário
    if (file == NULL) {
        return 0;
    }

    fwrite(&pet, sizeof(Pet), 1, file); // Escreve o pet no arquivo
    fclose(file);
    return 1;
}

int contarPets() {
    FILE *file = fopen(ARQUIVO_PET, "rb");
    if (file == NULL) {
        return 0; // Arquivo inexistente ou vazio
    }

    Pet pet;
    int count = 0;

    while (fread(&pet, sizeof(Pet), 1, file)) {
        count++;
    }

    fclose(file);
    return count;
}

Pet *listarPets(int quantidade) {
    FILE *file = fopen(ARQUIVO_PET, "rb");
    if (file == NULL) {
        return NULL;
    }

    if (quantidade == 0) {
        fclose(file);
        return NULL;
    }

    Pet *pets = (Pet *)malloc(quantidade * sizeof(Pet));
    if (pets == NULL) {
        fclose(file);
        return NULL;
    }

    fread(pets, sizeof(Pet), quantidade, file);
    fclose(file);

    return pets;
}

int atualizarPet(Pet *petRecebido) {
    FILE *file = fopen(ARQUIVO_PET, "rb"); // Abre o arquivo original
    if (file == NULL) {
        return 1;
    }

    FILE *temp = fopen("src/bin/temp_pet1.bin", "wb"); // Cria o arquivo temporário
    if (temp == NULL) {
        fclose(file);
        return 2;
    }

    Pet pet;
    int encontrado = 0;

    while (fread(&pet, sizeof(Pet), 1, file)) {
        if (pet.id == petRecebido->id) {
            encontrado = 1; // Encontrou o pet a ser atualizado
            fwrite(petRecebido, sizeof(Pet), 1, temp); // Escreve o pet recebido no arquivo temporário
        } else {
            fwrite(&pet, sizeof(Pet), 1, temp); // Escreve os demais pets no arquivo temporário
        }
    }

    fclose(file);
    fclose(temp);

    if (encontrado == 1) {
        remove(ARQUIVO_PET);           // Remove o arquivo original
        rename("src/bin/temp_pet1.bin", ARQUIVO_PET); // Renomeia o temporário para o original
        return 0;
    } else {
        remove("src/bin/temp_pet1.bin");               // Remove o temporário
        return 3;
    }
}

int excluirPet(int id) {
    FILE *file = fopen(ARQUIVO_PET, "rb"); // Abre o arquivo original
    if (file == NULL) {
        return 1;
    }

    FILE *temp = fopen("src/bin/temp_pet2.bin", "wb"); // Cria o arquivo temporário
    if (temp == NULL) {
        fclose(file);
        return 2;
    }

    Pet pet;
    int encontrado = 0;

    while (fread(&pet, sizeof(Pet), 1, file)) {
        if (pet.id == id) {
            encontrado = 1; // Encontrou o pet a ser excluído
        } else {
            fwrite(&pet, sizeof(Pet), 1, temp); // Escreve no arquivo temporário
        }
    }

    fclose(file);
    fclose(temp);

    if (encontrado == 1) {
        remove(ARQUIVO_PET);           // Remove o arquivo original
        rename("src/bin/temp_pet2.bin", ARQUIVO_PET); // Renomeia o temporário para o original
        return 0;
    } else {
        remove("src/bin/temp_pet2.bin");               // Remove o temporário
        return 3;
    }
}

Pet *buscarPetPeloID(int id) {
    FILE *file = fopen(ARQUIVO_PET, "rb");
    if (file == NULL) {
        return NULL; // Arquivo inexistente, pet não existe
    }
    
    Pet *pet = (Pet *)malloc(1 * sizeof(Pet));
    while (fread(pet, sizeof(Pet), 1, file)) {
        if (pet->id == id) {
            fclose(file);
            return pet; // Pet encontrado
            
        }
    }

    fclose(file);
    return NULL; // Pet não encontrado
}

Pet *listarPetsPorCliente(int idCliente) { //falta implementar na main
    FILE *file = fopen(ARQUIVO_PET, "rb");
    if (file == NULL) {
        return NULL; // Arquivo inexistente
    }

    Pet pet;
    int total = 0;

    // Contar quantos pets estão vinculados ao idCliente
    while (fread(&pet, sizeof(Pet), 1, file)) {
        if (pet.codCliente == idCliente) {
            total++;
        }
    }

    // Se não há pets vinculados, encerra
    if (total == 0) {
        fclose(file);
        return NULL;
    }

    // Aloca memória para armazenar os pets vinculados
    Pet *pets = (Pet *)malloc((total + 1) * sizeof(Pet)); //adiciona 1 pet a mais para definir o final do array
    if (pets == NULL) {
        fclose(file);
        return NULL; // Falha na alocação de memória
    }

    rewind(file); // Volta ao início do arquivo para ler novamente
    int index = 0;

    // Lê os pets vinculados ao idCliente
    while (fread(&pet, sizeof(Pet), 1, file)) {
        if (pet.codCliente == idCliente) {
            pets[index++] = pet;
        }
    }

    // Configura o marcador de término
    pets[index].id = -1;
    pets[index].nome[0] = '\0';
    pets[index].especie[0] = '\0';

    fclose(file);

    return pets; // Retorna a lista de pets encontrados
}
