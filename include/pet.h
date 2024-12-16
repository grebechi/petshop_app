#ifndef PET_H
#define PET_H

// Tamanho máximo para os campos
#define PET_MAX_NOME 50
#define PET_MAX_ESPECIE 35

// Estrutura do Pet
typedef struct {
    int id;
    char nome[PET_MAX_NOME];
    char especie[PET_MAX_ESPECIE];
    int codCliente;
} Pet;

// Declaração das funções
int gerarProximoIDPet();
int salvarPet(Pet pet);
int contarPets();
Pet *listarPets(int quantidade);
int atualizarPet(Pet *petRecebido);
int excluirPet(int id);
Pet *buscarPetPeloID(int id);
Pet *listarPetsPorCliente(int idCliente, int *qtdPetsVinculados);

#endif
