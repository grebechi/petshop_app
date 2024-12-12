#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cliente.h"

#define ARQUIVO_CLIENTE "src/bin/clientes.bin"

int gerarProximoID() {
    FILE *file = fopen(ARQUIVO_CLIENTE, "rb");
    if (file == NULL) {
        return 1; // Arquivo inexistente, primeiro ID será 1
    }

    Cliente cliente;
    int maxID = 0;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.id > maxID) {
            maxID = cliente.id;
        }
    }

    fclose(file);
    return maxID + 1; // Retorna o próximo ID
}

int salvarCliente(Cliente cliente) {
    FILE *file = fopen(ARQUIVO_CLIENTE, "ab"); // Abre o arquivo no modo de adicionar binário
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    fwrite(&cliente, sizeof(Cliente), 1, file); // Escreve o cliente no arquivo
    fclose(file);
    return 1;
}

int contarClientes() {
    FILE *file = fopen(ARQUIVO_CLIENTE, "rb");
    if (file == NULL) {
        return 0; // Arquivo inexistente ou vazio
    }

    Cliente cliente;
    int count = 0;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        count++;
    }

    fclose(file);
    return count;
}

Cliente *listarClientes(int quantidade) {
    FILE *file = fopen(ARQUIVO_CLIENTE, "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    if (quantidade == 0) {
        fclose(file);
        return NULL;
    }

    Cliente *clientes = (Cliente *)malloc(quantidade * sizeof(Cliente));
    if (clientes == NULL) {
        perror("Erro ao alocar memória");
        fclose(file);
        return NULL;
    }

    fread(clientes, sizeof(Cliente), quantidade, file);
    fclose(file);

    return clientes;
}

int atualizarCliente(Cliente *clienteRecebido) {
    FILE *file = fopen(ARQUIVO_CLIENTE, "rb"); // Abre o arquivo original
    if (file == NULL) {
        return 1;
    }

    FILE *temp = fopen("src/bin/temp1.bin", "wb"); // Cria o arquivo temporário
    if (temp == NULL) {
        fclose(file);
        return 2;
    }

    Cliente cliente;
    int encontrado = 0;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.id == clienteRecebido->id) {
            encontrado = 1; // Encontrou o cliente a ser excluído
            fwrite(clienteRecebido, sizeof(Cliente), 1, temp); // Escreve o cliente recebido no arquivo temporário
        } else {
            fwrite(&cliente, sizeof(Cliente), 1, temp); // Escreve os demais clientes no arquivo temporário
        }
    }

    fclose(file);
    fclose(temp);

    if (encontrado == 1) {
        remove(ARQUIVO_CLIENTE);           // Remove o arquivo original
        rename("src/bin/temp1.bin", ARQUIVO_CLIENTE); // Renomeia o temporário para o original
        return 0;
    } else {
        remove("src/bin/temp1.bin");               // Remove o temporário
        return 3;
    }
}

int excluirCliente(int id) {
    FILE *file = fopen(ARQUIVO_CLIENTE, "rb"); // Abre o arquivo original
    if (file == NULL) {
        return 1;
    }

    FILE *temp = fopen("src/bin/temp.bin", "wb"); // Cria o arquivo temporário
    if (temp == NULL) {
        fclose(file);
        return 2;
    }

    Cliente cliente;
    int encontrado = 0;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.id == id) {
            encontrado = 1; // Encontrou o cliente a ser excluído
        } else {
            fwrite(&cliente, sizeof(Cliente), 1, temp); // Escreve no arquivo temporário
        }
    }

    fclose(file);
    fclose(temp);

    if (encontrado == 1) {
        remove(ARQUIVO_CLIENTE);           // Remove o arquivo original
        rename("src/bin/temp.bin", ARQUIVO_CLIENTE); // Renomeia o temporário para o original
        return 0;
    } else {
        remove("src/bin/temp.bin");               // Remove o temporário
        return 3;
    }
}

Cliente *buscarClientePeloID(int id) {
    FILE *file = fopen(ARQUIVO_CLIENTE, "rb");
    if (file == NULL) {
        return NULL; // Arquivo inexistente, cliente não existe
    }
    
    Cliente *cliente = (Cliente *)malloc(1 * sizeof(Cliente));
    while (fread(cliente, sizeof(Cliente), 1, file)) {
        if (cliente->id == id) {
            fclose(file);
            return cliente; // Cliente encontrado
            
        }
    }

    fclose(file);
    return NULL; // Cliente não encontrado
}

int clienteJaExiste(const char *nome) {
    FILE *file = fopen(ARQUIVO_CLIENTE, "rb");
    if (file == NULL) {
        return 0; // Arquivo inexistente, cliente não existe
    }

    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (strcmp(cliente.nome, nome) == 0) {
            fclose(file);
            return 1; // Cliente encontrado
        }
    }

    fclose(file);
    return 0; // Cliente não encontrado
}

void adicionarClientesPadrao() {
    // Lista de clientes padrão
    Cliente clientesPadrao[] = {
        {0, "Alice", "123456789", "123.456.789-00"},
        {0, "Bob", "987654321", "987.654.321-00"},
        {0, "Carlos", "111111111", "111.111.111-11"},
        {0, "Diana", "222222222", "222.222.222-22"},
        {0, "Eduardo", "333333333", "333.333.333-33"},
        {0, "Fátima", "444444444", "444.444.444-44"},
        {0, "Gabriel", "555555555", "555.555.555-55"},
        {0, "Helena", "666666666", "666.666.666-66"},
        {0, "Igor", "777777777", "777.777.777-77"},
        {0, "Juliana", "888888888", "888.888.888-88"}
    };

    for (int i = 0; i < 10; i++) {
        if (!clienteJaExiste(clientesPadrao[i].nome)) {
            clientesPadrao[i].id = gerarProximoID();
            salvarCliente(clientesPadrao[i]);
        }
    }
}
