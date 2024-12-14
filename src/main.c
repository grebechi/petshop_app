#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cliente.h"
#include "../include/pet.h"
#include "../include/servico.h"
#include "../include/utils.h"

//Cabeçalho das funções utilizadas na main
void capturarString(const char *mensagem, char *destino, int tamanho);
void menuPrincipal();
void menuCliente();
void menuPet();
void menuServico();

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
            case 1:{ //Menu Cliente
                menuCliente();
                break;
            }
            case 2:{ //Menu Pets
                menuPet();
                break;
            }
            case 3:{ //Menu Serviços
                menuServico();
                break;
            }
            case 4:{ //Menu Serviços Prestados
                printf("\n[MENU SERVIÇOS PRESTADOS] Ainda não foi implementado!\n");
                pausarTerminal();
                break;
            }
            case 0:{ //Sair do Sistema
                printf("\nSaindo do Sistema...\n");
                break;
            }
            default:{ //Opção Inválida
                printf("\nOpção inválida! Tente novamente.\n");
                pausarTerminal();
                break;
            }
        }
    } while (opcao != 0);

}

//função para acessar o menu do cliente
void menuCliente() {
    int opcao, quantidadeClientes;
    do {
        quantidadeClientes = contarClientes();
        limparTerminal();
        printf("\n=== Menu Cliente [%d no total] ===\n",quantidadeClientes);
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Listar Clientes\n");
        printf("3 - Atualizar Cliente\n");
        printf("4 - Excluir Cliente\n");
        if(quantidadeClientes == 0){
            printf("5 - Adicionar Clientes Padrão\n");
        }
        printf("0 - Voltar ao Menu Principal\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:{ //Cadastrar Cliente
                Cliente cliente;
                limparTerminal();
                printf("\n=== Cadastrar Novo Cliente ===\n");
                // Captura o Nome
                capturarString("\nDigite o Nome: ", cliente.nome, CLIENTE_MAX_NOME);  
                // Captura o telefone
                capturarString("\nDigite o Telefone: ", cliente.telefone, CLIENTE_MAX_TELEFONE);
                // Captura o CPF
                capturarString("\nDigite o CPF: ", cliente.cpf, CLIENTE_MAX_CPF);
                // Gerar o ID do cliente
                cliente.id = gerarProximoID();
                switch (salvarCliente(cliente)){
                    case 1:{
                        printf("\nCliente cadastrado com sucesso! ID: %d\n", cliente.id);
                        pausarTerminal();
                        break;
                        }
                    case 0:{
                        perror("\nErro ao abrir o arquivo original da base de dados");
                        pausarTerminal();
                        break;
                        }
                    default:{
                        perror("\nErro ao tentar cadastrar o cliente");
                        pausarTerminal();
                        break;
                        }
                }
                break;
            }
            case 2:{ //Listar Clientes
                int quantidade = contarClientes();
                if (quantidade > 0) {
                // Chama a função listarClientes
                Cliente *clientes = listarClientes(quantidade);
                if(clientes){
                        limparTerminal();
                        printf("\n=== Lista de Clientes [%d no total]===\n\n",quantidadeClientes);
                        for (int i = 0; i < quantidade; i++) {
                            printf("ID: %d, Nome: %s, Telefone: %s, CPF: %s\n",
                                clientes[i].id, clientes[i].nome,
                                clientes[i].telefone, clientes[i].cpf);
                        }
                        pausarTerminal();
                }else{
                    perror("\nErro ao abrir o banco de dados");
                    pausarTerminal();
                }
                free(clientes); // Libera a memória alocada
                }else {
                    printf("\nNenhum cliente encontrado.\n");
                    pausarTerminal();
                    }
                break;
            }
            case 3:{ //Atualizar Cliente
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
            case 4:{ //Excluir Cliente
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
            case 5:{ //Clientes Padrão
                if(quantidadeClientes == 0){
                    if(adicionarClientesPadrao() == 1){
                        printf("\nClientes padrão adicionados ao sistema.\n");
                        pausarTerminal();
                    }else{
                        printf("\nErro ao adicionar clientes padrão ao sistema.\n");
                        pausarTerminal();
                    }
                }else{
                    printf("Opção inválida! Tente novamente.\n");
                    pausarTerminal();
                }
                
                break;
                }
            case 0:{ //Voltar para o Menu Principal
                printf("\nVoltando para o Menu Principal...\n");
                pausarTerminal();
                break;
            }
            default:{ //Opção Inválida
                printf("Opção inválida! Tente novamente.\n");
                pausarTerminal();
            break;
            }
        }
    } while (opcao != 0);
    
}

//função para acessar o menu do pet
void menuPet() {
    int opcao, quantidadePets;
    do {
        quantidadePets = contarPets();
        limparTerminal();
        printf("\n=== Menu Pet [%d no total] ===\n",quantidadePets);
        printf("1 - Cadastrar Pet\n");
        printf("2 - Listar Pets\n");
        printf("3 - Atualizar Pet\n");
        printf("4 - Excluir Pet\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:{ //Cadastrar Pet
                int codCliente, confirmaCliente, repeteCliente;
                Pet pet;
                Cliente *cliente;
                limparTerminal();
                printf("\n=== Cadastrar Novo Pet ===\n");
                // Captura o Nome
                capturarString("\nDigite o Nome: ", pet.nome, PET_MAX_NOME);  
                // Captura a especie
                capturarString("\nDigite a Espécie do Pet: ", pet.especie, PET_MAX_ESPECIE);
                // Captura o Cliente
                do{
                    printf("\nDigite o ID do Cliente Responsável pelo Pet: %s: ",pet.nome);
                    scanf("%d", &codCliente);
                    fflush(stdin);
                    cliente = buscarClientePeloID(codCliente);
                    if(cliente){
                        printf("\n=== Cliente Localizado pelo [ID] -> [%d] ===",codCliente);
                        printf("\nID: %d, Nome: %s, Telefone: %s, CPF: %s\n",
                            cliente->id, cliente->nome,
                            cliente->telefone, cliente->cpf);
                        printf("\nDigite [1] para CONFIRMAR, [2] para ALTERAR o Cliente ou [0] para CANCELAR: ");
                        scanf("%d", &confirmaCliente);
                        fflush(stdin);
                        switch (confirmaCliente){
                            case 1:{
                                pet.codCliente = codCliente;
                                repeteCliente = 0;
                                break;
                            }
                            case 2:{
                                repeteCliente = 1;
                                break;
                            }
                            case 0:{
                                repeteCliente = 2;
                                printf("\nCancelando o Cadastro do Pet: %s\n",pet.nome);
                                pausarTerminal();
                                break;
                            }                                      
                            default:{
                                repeteCliente = 1;
                                printf("\nOpção inválida!");
                                pausarTerminal();
                                break;
                            }
                        }
                    }else{
                        printf("\nNão foi encontrado um cliente com [ID] -> [%d]\n",codCliente);
                        pausarTerminal();
                    }
                }while(repeteCliente != 0 && repeteCliente != 2);
                
                if(repeteCliente == 0){
                    // Gerar o ID do Pet
                    pet.id = gerarProximoIDPet();
                    switch (salvarPet(pet)){
                        case 1:{
                            printf("\nPet cadastrado com sucesso! ID: %d\n", pet.id);
                            pausarTerminal();
                            break;
                            }
                        case 0:{
                            perror("\nErro ao abrir o arquivo original da base de dados");
                            pausarTerminal();
                            break;
                            }
                        default:{
                            perror("\nErro ao tentar cadastrar o pet");
                            pausarTerminal();
                            break;
                            }
                    }
                }
                free(cliente);
                break;
            }
            case 2:{ //Listar Pets
                quantidadePets = contarPets();
                if (quantidadePets > 0) {
                    // Chama a função listarPets
                    Pet *pets = listarPets(quantidadePets);
                    if(pets){
                            Cliente *cliente;
                            limparTerminal();
                            printf("\n=== Lista de Pets [%d no total]===\n\n",quantidadePets);
                            for (int i = 0; i < quantidadePets; i++) {//listar também as informações do cliente...
                                cliente = buscarClientePeloID(pets[i].codCliente);
                                if(cliente){
                                    printf("ID: %d, Nome: %s, Espécie: %s, ID do Cliente: %d, Nome do Cliente: %s, Telefone: %s, CPF: %s\n",
                                    pets[i].id, pets[i].nome,
                                    pets[i].especie, pets[i].codCliente, cliente->nome, cliente->telefone, cliente->cpf);
                                }else{
                                    printf("ID: %d, Nome: %s, Espécie: %s, ID do Cliente: %d [CLIENTE NÃO ENCONTRADO]\n",
                                    pets[i].id, pets[i].nome,
                                    pets[i].especie, pets[i].codCliente);
                                }
                                
                            }
                            free(cliente);
                            pausarTerminal();
                    }else{
                        perror("\nErro ao abrir o banco de dados");
                        pausarTerminal();
                    }
                    free(pets); // Libera a memória alocada
                }else {
                    printf("\nNenhum pet encontrado.\n");
                    pausarTerminal();
                    }
                break;
            }
            case 3:{ //Atualizar Pet da pra melhorar, listando o cliente atual 
                int id, codCliente, confirmaCliente, repeteCliente;
                limparTerminal();
                printf("\n=== Atualizar Pet ===\n\n");
                printf("Digite o ID do pet a ser atualizado: ");
                scanf("%d", &id);
                Pet *petParaEnviar = buscarPetPeloID(id);
                if(petParaEnviar){
                    Cliente *cliente;
                    printf("\n=== Pet Localizado pelo [ID] -> [%d] ===",id);//falta os dados do cliente aqui
                    printf("\nID: %d, Nome: %s, Espécie: %s, ID do Cliente: %d\n",
                            petParaEnviar->id, petParaEnviar->nome,
                            petParaEnviar->especie, petParaEnviar->codCliente);
                    // Captura o Nome
                    printf("\nNome Atual: [%s] -> ",petParaEnviar->nome);
                    capturarString("Digite o novo Nome: ", petParaEnviar->nome, PET_MAX_NOME);  
                    // Captura a espécie
                    printf("\nEspécie Atual: [%s] -> ",petParaEnviar->especie);
                    capturarString("Digite a nova Espécie: ", petParaEnviar->especie, PET_MAX_ESPECIE);
                    // Captura o ID do cliente
                    do{
                        printf("\nID do Cliente Atual: [%d] -> ",petParaEnviar->codCliente);
                        printf("Digite o ID do Cliente Responsável pelo Pet: %s: ",petParaEnviar->nome);
                        scanf("%d", &codCliente);
                        fflush(stdin);
                        cliente = buscarClientePeloID(codCliente);
                        if(cliente){
                            printf("\n=== Cliente Localizado pelo [ID] -> [%d] ===",codCliente);
                            printf("\nID: %d, Nome: %s, Telefone: %s, CPF: %s\n",
                                cliente->id, cliente->nome,
                                cliente->telefone, cliente->cpf);
                            printf("\nDigite [1] para CONFIRMAR, [2] para ALTERAR o Cliente ou [0] para CANCELAR: ");
                            scanf("%d", &confirmaCliente);
                            fflush(stdin);
                            switch (confirmaCliente){
                                case 1:{
                                    petParaEnviar->codCliente = codCliente;
                                    repeteCliente = 0;
                                    break;
                                }
                                case 2:{
                                    repeteCliente = 1;
                                    break;
                                }
                                case 0:{
                                    repeteCliente = 2;
                                    printf("\nCancelando o Cadastro do Pet: %s\n",petParaEnviar->nome);
                                    pausarTerminal();
                                    break;
                                }                                      
                                default:{
                                    repeteCliente = 1;
                                    printf("\nOpção inválida!");
                                    pausarTerminal();
                                    break;
                                }
                            }
                        }else{
                            printf("\nNão foi encontrado um cliente com [ID] -> [%d]\n",codCliente);
                            pausarTerminal();
                        }
                    }while(repeteCliente != 0 && repeteCliente != 2);
                    
                    if(repeteCliente == 0){
                        switch (atualizarPet(petParaEnviar)){
                            case 0:
                                printf("\nSucesso ao atualizar pet com [ID] -> [%d]\n",id);
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
                                printf("\nNão foi encontrado um pet com [ID] -> [%d]\n",id);
                                pausarTerminal();
                                break;
                            default:
                                perror("\nErro ao tentar atualizar o pet");
                                pausarTerminal();
                                break;
                        }
                    }
                    free(cliente);   
                }else{
                    printf("\nNão foi encontrado um pet com [ID] -> [%d]\n",id);
                    pausarTerminal();
                }
                free(petParaEnviar);
                break;
            }
            case 4:{ //Excluir Pet da pra melhorar listando o cliente quando o pet for encontrado
                int id;
                limparTerminal();
                printf("\n=== Excluir Pet ===\n\n");
                printf("Digite o ID do pet a ser excluído: ");
                scanf("%d", &id);
                Pet *pet = buscarPetPeloID(id);
                if(pet){
                    int subOpcao;
                    printf("\n=== Pet Localizado pelo [ID] -> [%d] ===",id);
                    printf("\nID: %d, Nome: %s, Espécie: %s, ID do Cliente: %d\n",
                            pet->id, pet->nome,
                            pet->especie, pet->codCliente);
                    do{
                        printf("\nDigite [1] para CANCELAR ou [2] para EXCLUIR permanentemente: ");
                        scanf("%d", &subOpcao);
                        switch (subOpcao){
                            case 1:
                            printf("\n\nCancelando exclusão...");
                            pausarTerminal();
                            break;
                            case 2:
                                switch (excluirPet(id)){
                                    case 0:
                                        printf("\nSucesso ao excluir pet com [ID] -> [%d]\n",id);
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
                                        printf("\nNão foi encontrado um pet com [ID] -> [%d]\n",id);
                                        pausarTerminal();
                                        break;
                                    default:
                                        perror("\nErro ao tentar excluir o pet");
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
                    printf("\nNão foi encontrado um pet com [ID] -> [%d]\n",id);
                    pausarTerminal();
                }
                free(pet);
                break;
            }
            case 0:{ //Voltar para o Menu Principal
                printf("\nVoltando para o Menu Principal...\n");
                pausarTerminal();
                break;
            }
            default:{ //Opção Inválida
                printf("Opção inválida! Tente novamente.\n");
                pausarTerminal();
            break;
            }
        }
    } while (opcao != 0);
    
}

//função para acessar o menu de Servicos
void menuServico(){ 
    int opcao, quantidadeServicos;
    do {
        quantidadeServicos = contarServicos();
        limparTerminal();
        printf("\n=== Menu Serviços [%d no total] ===\n",quantidadeServicos);
        printf("1 - Cadastrar Serviço\n");
        printf("2 - Listar Serviços\n");
        printf("3 - Atualizar Serviço\n");
        printf("4 - Excluir Serviço\n");
        if(quantidadeServicos == 0){
            printf("5 - Adicionar Serviços Padrão\n");
        }
        printf("0 - Voltar ao Menu Principal\n");
        printf("======================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:{ //Cadastrar Servico
                Servico servico;
                limparTerminal();
                printf("\n=== Cadastrar Novo Serviço ===\n");
                // Captura o Nome
                capturarString("\nDigite o Nome: ", servico.nome, SERVICO_MAX_NOME);  
                // Captura o custo
                // Captura o valor cobrado
                do{
                    printf("\nDigite o Valor de Custo: ");
                    scanf("%f",&servico.valorCusto);
                    fflush(stdin);
                    printf("\nDigite o Valor de Cobrado: ");
                    scanf("%f",&servico.valorCobrado);
                    fflush(stdin);
                    if(servico.valorCusto > servico.valorCobrado){
                        printf("\nO Valor de Custo [R$ %.2f] não pode ser superior ao Valor Cobrado [R$ %.2f]\n",servico.valorCusto, servico.valorCobrado);
                        printf("\nInforme novamente os valores para o serviço: %s!\n",servico.nome);
                        pausarTerminal();
                    }
                }while(servico.valorCusto > servico.valorCobrado);
                // Gerar o ID do servico
                servico.id = gerarProximoIDServico();
                switch (salvarServico(servico)){
                    case 1:{
                        printf("\nServiço cadastrado com sucesso! ID: %d\n", servico.id);
                        pausarTerminal();
                        break;
                        }
                    case 0:{
                        perror("\nErro ao abrir o arquivo original da base de dados");
                        pausarTerminal();
                        break;
                        }
                    default:{
                        perror("\nErro ao tentar cadastrar o cliente");
                        pausarTerminal();
                        break;
                        }
                }
                break;
            }
            case 2:{ //Listar Servicos
                quantidadeServicos = contarServicos();
                if (quantidadeServicos > 0) {
                // Chama a função listarServicos
                Servico *servicos = listarServicos(quantidadeServicos);
                if(servicos){
                        limparTerminal();
                        printf("\n=== Lista de Serviços [%d no total]===\n\n",quantidadeServicos);
                        for (int i = 0; i < quantidadeServicos; i++) {
                            printf("\nID: %d, Nome: %s, Valor Cobrado: R$ %.2f | Custo: R$ %.2f | Lucro: R$ %.2f\n",
                                servicos[i].id, servicos[i].nome,
                                servicos[i].valorCobrado, servicos[i].valorCusto,
                                (servicos[i].valorCobrado - servicos[i].valorCusto));
                        }
                        pausarTerminal();
                }else{
                    perror("\nErro ao abrir o banco de dados");
                    pausarTerminal();
                }
                free(servicos); // Libera a memória alocada
                }else {
                    printf("\nNenhum serviço encontrado.\n");
                    pausarTerminal();
                    }
                break;
            }
            case 3:{ //Atualizar Serviço
                int id;
                limparTerminal();
                printf("\n=== Atualizar Serviço ===\n\n");
                printf("Digite o ID do serviço a ser atualizado: ");
                scanf("%d", &id);
                Servico *servicoParaEnviar = buscarServicoPeloID(id);
                if(servicoParaEnviar){
                    printf("\n=== Serviço Localizado pelo [ID] -> [%d] ===",id);
                    printf("\nID: %d, Nome: %s, Valor Cobrado: R$ %.2f | Custo: R$ %.2f | Lucro: R$ %.2f\n",
                            servicoParaEnviar->id, servicoParaEnviar->nome,
                            servicoParaEnviar->valorCobrado, servicoParaEnviar->valorCusto,
                            (servicoParaEnviar->valorCobrado - servicoParaEnviar->valorCusto));
                    // Captura o Nome
                    printf("\nNome Atual: [%s] -> ",servicoParaEnviar->nome);
                    capturarString("Digite o novo Nome: ", servicoParaEnviar->nome, SERVICO_MAX_NOME);  
                    do{
                        // Captura o custo
                        printf("\nValor de Custo Atual: [R$ %.2f] -> ",servicoParaEnviar->valorCusto);
                        printf("Digite o novo Valor de Custo: ");
                        scanf("%f",&servicoParaEnviar->valorCusto);
                        fflush(stdin);
                        // Captura o valor cobrado
                        printf("\nValor Cobrado Atualmente: [R$ %.2f] -> ",servicoParaEnviar->valorCobrado);
                        printf("Digite o novo Valor Cobrado: ");
                        scanf("%f",&servicoParaEnviar->valorCobrado);
                        fflush(stdin);
                        if(servicoParaEnviar->valorCusto > servicoParaEnviar->valorCobrado){
                            printf("\nO Valor de Custo [R$ %.2f] não pode ser superior ao Valor Cobrado [R$ %.2f]\n",servicoParaEnviar->valorCusto, servicoParaEnviar->valorCobrado);
                            printf("\nInforme novamente os valores para o serviço: %s!\n",servicoParaEnviar->nome);
                            pausarTerminal();
                        }
                    }while(servicoParaEnviar->valorCusto > servicoParaEnviar->valorCobrado);
                    switch (atualizarServico(servicoParaEnviar)){
                        case 0:
                            printf("\nSucesso ao atualizar servico com [ID] -> [%d]\n",id);
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
                             printf("\nNão foi encontrado um servico com [ID] -> [%d]\n",id);
                             pausarTerminal();
                            break;
                        default:
                            perror("\nErro ao tentar atualizar o servico");
                            pausarTerminal();
                            break;
                    }
                }else{
                    printf("\nNão foi encontrado um servico com [ID] -> [%d]\n",id);
                    pausarTerminal();
                }
                free(servicoParaEnviar);
                break;
            }
            case 4:{ //Excluir Serviço
                int id;
                limparTerminal();
                printf("\n=== Excluir Serviço ===\n\n");
                printf("Digite o ID do serviço a ser excluído: ");
                scanf("%d", &id);
                Servico *servico = buscarServicoPeloID(id);
                if(servico){
                    int subOpcao;
                    printf("\n=== Serviço Localizado pelo [ID] -> [%d] ===",id);
                    printf("ID: %d, Nome: %s, Valor Cobrado: R$ %.2f | Custo: R$ %.2f | Lucro: R$ %.2f\n",
                                servico->id, servico->nome,
                                servico->valorCobrado, servico->valorCusto,
                                (servico->valorCobrado - servico->valorCusto));
                    do{
                        printf("\nDigite [1] para CANCELAR ou [2] para EXCLUIR permanentemente: ");
                        scanf("%d", &subOpcao);
                        switch (subOpcao){
                            case 1:
                            printf("\n\nCancelando exclusão...");
                            pausarTerminal();
                            break;
                            case 2:
                                switch (excluirServico(id)){
                                    case 0:
                                        printf("\nSucesso ao excluir serviço com [ID] -> [%d]\n",id);
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
                                        printf("\nNão foi encontrado um serviço com [ID] -> [%d]\n",id);
                                        pausarTerminal();
                                        break;
                                    default:
                                        perror("\nErro ao tentar excluir o serviço");
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
                    printf("\nNão foi encontrado um serviço com [ID] -> [%d]\n",id);
                    pausarTerminal();
                }
                free(servico);
                break;
            }
            case 5:{ //Serviços Padrão
                if(quantidadeServicos == 0){
                    if(adicionarServicosPadrao() == 1){
                        printf("\nServiços padrão adicionados ao sistema.\n");
                        pausarTerminal();
                    }else{
                        printf("\nErro ao adicionar clientes padrão ao sistema.\n");
                        pausarTerminal();
                    }
                }else{
                    printf("Opção inválida! Tente novamente.\n");
                    pausarTerminal();
                }
                
                break;
                }
            case 0:{ //Voltar para o Menu Principal
                printf("\nVoltando para o Menu Principal...\n");
                pausarTerminal();
                break;
            }
            default:{ //Opção Inválida
                printf("Opção inválida! Tente novamente.\n");
                pausarTerminal();
            break;
            }
        }
    } while (opcao != 0);
    
}