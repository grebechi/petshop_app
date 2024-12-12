#ifndef CLIENTE_H
#define CLIENTE_H

// Tamanho máximo para os campos
#define CLIENTE_MAX_NOME 50
#define CLIENTE_MAX_TELEFONE 15
#define CLIENTE_MAX_CPF 15

// Estrutura do Cliente
typedef struct {
    int id;
    char nome[CLIENTE_MAX_NOME];
    char telefone[CLIENTE_MAX_TELEFONE];
    char cpf[CLIENTE_MAX_CPF];
} Cliente;

// Declaração das funções
int gerarProximoID();
int salvarCliente(Cliente cliente);
int contarClientes();
Cliente *listarClientes(int quantidade);
int atualizarCliente(Cliente *clienteRecebido);
int excluirCliente(int id);
Cliente *buscarClientePeloID(int id);
int clienteJaExiste(const char *nome);
void adicionarClientesPadrao();

#endif
