#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cliente.h"
#include "../include/utils.h"

void capturarString(const char *mensagem, char *destino, int tamanho);
void menuPrincipal();
void menuCliente();

//fazer a void do menu princial
int main() {
    menuPrincipal();
    return 0;
}

//função para capturar Strings com tamanho máximo para evitar problemas com o buffer
void capturarString(const char *mensagem, char *destino, int tamanho) {
    fflush(stdin);
    printf("%s", mensagem);
    if (fgets(destino, tamanho, stdin) != NULL) {
        // Remove o caractere de nova linha '\n', se existir
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    } else {
        // Garante que a string esteja limpa em caso de erro
        destino[0] = '\0';
    }
    fflush(stdin);
}

//função para acessar o menu principal
void menuPrincipal(){
     int opcao;
    do {
        limparTerminal();
        printf("\n=== Menu Principal ===\n");
        printf("1 - Gerenciar Clientes\n");
        printf("2 - Gerenciar Pets\n");
        printf("3 - Gerenciar Serviços\n");
        printf("4 - Gerenciar Serviços Prestados\n");
        printf("0 - Sair do Sistema\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1: 
                menuCliente();
                break;
            case 2:
                printf("\n[MENU PETS] Ainda não foi implementado!\n");
                pausarTerminal();
                break;
            case 3:
                printf("\n[MENU SERVIÇOS] Ainda não foi implementado!\n");
                pausarTerminal();
                break;
            case 4:
                printf("\n[MENU SERVIÇOS PRESTADOS] Ainda não foi implementado!\n");
                pausarTerminal();
                break;
            case 0:
                printf("\nSaindo do Sistema...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                pausarTerminal();
        }
    } while (opcao != 0);

}

//função para acessar o menu do cliente
void menuCliente() {
    int opcao;
    do {
        limparTerminal();
        printf("\n=== Menu Cliente ===\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Listar Clientes\n");
        printf("3 - Atualizar Cliente\n");
        printf("4 - Excluir Cliente\n");
        printf("5 - Adicionar Clientes Padrão\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1: {
                Cliente cliente;
                // Captura o Nome
                capturarString("Digite o Nome: ", cliente.nome, CLIENTE_MAX_NOME);  
                // Captura o telefone
                capturarString("Digite o Telefone: ", cliente.telefone, CLIENTE_MAX_TELEFONE);
                // Captura o CPF
                capturarString("Digite o CPF: ", cliente.cpf, CLIENTE_MAX_CPF);
                // Gerar o ID do cliente
                cliente.id = gerarProximoID();
                salvarCliente(cliente);
                printf("Cliente cadastrado com sucesso! ID: %d\n", cliente.id);
                pausarTerminal();
                break;
            }
            case 2: {
                int quantidade = contarClientes();
                // Chama a função listarClientes
                Cliente *clientes = listarClientes(quantidade);
                if(clientes){
                    if (quantidade > 0) {
                        limparTerminal();
                        printf("\n=== Lista de Clientes ===\n\n");
                        for (int i = 0; i < quantidade; i++) {
                            printf("ID: %d, Nome: %s, Telefone: %s, CPF: %s\n",
                                clientes[i].id, clientes[i].nome,
                                clientes[i].telefone, clientes[i].cpf);
                        }
                        pausarTerminal();
                    } else {
                        printf("Nenhum cliente encontrado.\n");
                        pausarTerminal();
                    }
                }else{
                    printf("Não foi possível ler o Banco de Dados.\n");
                    pausarTerminal();
                }
                free(clientes); // Libera a memória alocada
                break;
            }
            case 3:{
                int id;
                limparTerminal();
                printf("\n=== Atualizar Cliente ===\n\n");
                printf("Digite o ID do cliente a ser atualizado: ");
                scanf("%d", &id);
                Cliente *clienteParaEnviar = buscarClientePeloID(id);
                if(clienteParaEnviar){
                    printf("\n=== Cliente Localizado pelo [ID] -> [%d] ===",id);
                    printf("\nID: %d, Nome: %s, Telefone: %s, CPF: %s\n",
                            clienteParaEnviar->id, clienteParaEnviar->nome,
                            clienteParaEnviar->telefone, clienteParaEnviar->cpf);
                    // Captura o Nome
                    printf("\nNome Atual: [%s] -> ",clienteParaEnviar->nome);
                    capturarString("Digite o novo Nome: ", clienteParaEnviar->nome, CLIENTE_MAX_NOME);  
                    // Captura o telefone
                    printf("\nTelefone Atual: [%s] -> ",clienteParaEnviar->telefone);
                    capturarString("Digite o novo Telefone: ", clienteParaEnviar->telefone, CLIENTE_MAX_TELEFONE);
                    // Captura o CPF
                    printf("\nCPF Atual: [%s] -> ",clienteParaEnviar->cpf);
                    capturarString("Digite o novo CPF: ", clienteParaEnviar->cpf, CLIENTE_MAX_CPF);
                    switch (atualizarCliente(clienteParaEnviar)){
                        case 0:
                            printf("\nSucesso ao atualizar cliente com [ID] -> [%d]\n",id);
                            pausarTerminal();
                            break;
                        case 1:
                            perror("\nErro ao abrir o arquivo original da base de dados");
                            pausarTerminal();
                            break;
                        case 2:
                            perror("\nErro ao criar o arquivo temporário da base de dados");
                            pausarTerminal();
                            break;
                        case 3:
                             printf("\nNão foi encontrado um cliente com [ID] -> [%d]\n",id);
                             pausarTerminal();
                            break;
                        default:
                            perror("\nErro ao tentar atualizar o cliente");
                            pausarTerminal();
                            break;
                    }
                }else{
                    printf("\nNão foi encontrado um cliente com [ID] -> [%d]\n",id);
                    pausarTerminal();
                }
                free(clienteParaEnviar);
                break;
            }
            case 4: {
                int id;
                limparTerminal();
                printf("\n=== Excluir Cliente ===\n\n");
                printf("Digite o ID do cliente a ser excluído: ");
                scanf("%d", &id);
                Cliente *cliente = buscarClientePeloID(id);
                if(cliente){
                    int subOpcao;
                    printf("\n=== Cliente Localizado pelo [ID] -> [%d] ===",id);
                    printf("\nID: %d, Nome: %s, Telefone: %s, CPF: %s\n",
                            cliente->id, cliente->nome,
                            cliente->telefone, cliente->cpf);
                    do{
                        printf("\nDigite [1] para CANCELAR ou [2] para EXCLUIR permanentemente: ");
                        scanf("%d", &subOpcao);
                        switch (subOpcao){
                            case 1:
                            printf("\n\nCancelando exclusão...");
                            pausarTerminal();
                            break;
                            case 2:
                                switch (excluirCliente(id)){
                                    case 0:
                                        printf("\nSucesso ao excluir cliente com [ID] -> [%d]\n",id);
                                        pausarTerminal();
                                        break;
                                    case 1:
                                        perror("\nErro ao abrir o arquivo original da base de dados");
                                        pausarTerminal();
                                        break;
                                    case 2:
                                        perror("\nErro ao criar o arquivo temporário da base de dados");
                                        pausarTerminal();
                                        break;
                                    case 3:
                                        printf("\nNão foi encontrado um cliente com [ID] -> [%d]\n",id);
                                        pausarTerminal();
                                        break;
                                    default:
                                        perror("\nErro ao tentar excluir o cliente");
                                        pausarTerminal();
                                        break;
                                }
                            break;
                            default:
                            printf("\nOpção inválida!");
                            pausarTerminal();
                            break;
                        }
                    }while (subOpcao != 1 && subOpcao != 2);
                }else{
                    printf("\nNão foi encontrado um cliente com [ID] -> [%d]\n",id);
                    pausarTerminal();
                }
                free(cliente);
                break;
            }
            case 5:
                adicionarClientesPadrao();
                printf("Clientes padrão adicionados (se não duplicados).\n");
                pausarTerminal();
                break;
            case 0:
                printf("Voltando para o Menu Principal...\n");
                pausarTerminal();
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                pausarTerminal();
        }
    } while (opcao != 0);
    
}
