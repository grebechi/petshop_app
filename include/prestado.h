#ifndef PRESTADO_H
#define PRESTADO_H

// Tamanho máximo para os campos
#define PRESTADO_MAX_DATA 11

// Estrutura do Serviço Prestado
typedef struct {
    int id;
    int codPet;
    int codServico;
    char data[PRESTADO_MAX_DATA]; // Formato: "DD/MM/AAAA"
    float lucro;
} Prestado;

// Declaração das funções
int gerarProximoIDPrestado();
int salvarPrestado(Prestado prestado);
int contarPrestados();
Prestado *listarPrestados(int quantidade);
int atualizarPrestado(Prestado *prestadoRecebido);
int excluirPrestado(int id);
Prestado *buscarPrestadoPeloID(int id);
Prestado *listarPrestadosPorPet(int idPet, int *qtdPrestadosVinculados);

#endif

