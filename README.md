# Projeto PetShop

Este repositório contém o código-fonte de um sistema de gestão de PetShop desenvolvido em linguagem C como parte da disciplina de Algoritmos e Programação II, ministrada pelo professor Marcelo Paravisi no IFRS - Campus Osório. O projeto tem como objetivo aplicar conceitos fundamentais de programação, como manipulação de structs, alocação dinâmica de memória e organização modular do código.

## Funcionalidades Principais

O sistema possui as seguintes funcionalidades:

### Entidades Gerenciadas

- **Cliente**: Cadastro, listagem, busca, atualização e exclusão de clientes.
- **Pet**: Vinculação de pets a clientes, listagem de pets e controle de exclusão ao remover um cliente.
- **Serviço**: Cadastro de serviços, atualização de valores e listagem de serviços cadastrados.
- **Serviços Prestados**: Registro de serviços realizados para os pets, vinculando o cliente, o pet e o serviço.

### Relatórios e Estatísticas

- Exibição do lucro por serviço prestado.
- Listagem dos pets e clientes que mais trouxeram lucro para a pet shop.
- Análise de serviços prestados com totalização do lucro.

### Armazenamento de Dados

- Os dados das entidades são armazenados em arquivos binários, permitindo persistência após a execução do programa.

## Estrutura do Projeto

O projeto segue uma organização modular, com separação de responsabilidades em arquivos .c e .h:

- **main.c**: Ponto de entrada do programa. Gerencia o menu principal e chama as funções das outras módulos.
- **Cliente.c / Cliente.h**: Funções para gerenciar clientes.
- **Pet.c / Pet.h**: Funções para gerenciar pets.
- **Servico.c / Servico.h**: Funções para gerenciar serviços.
- **Prestados.c / Prestados.h**: Funções para gerenciar serviços prestados.
- **Utils.c / Utils.h**: Funções utilitárias compartilhadas entre os módulos.

## Tecnologias e Ferramentas

- **Linguagem**: C
- **IDE**: VSCode, configurado com tasks para compilação e execução automática.
- **Compilador**: GCC

## Como Executar o Projeto

1. Clone este repositório:

   ```bash
   git clone https://github.com/grebechi/petshop_app
   cd petshop_app


2. Compile o projeto:

   ```bash
   gcc *.c -o petshop_app

3. Execute o programa:

    ```bash
    ./petshop_app

## Instruções de Uso

Navegue pelo menu principal para acessar as opções de cada entidade (Clientes, Pets, Serviços, etc.).
Realize as operações desejadas, como cadastro, listagem, atualização ou exclusão.
Gere relatórios e estatísticas para avaliar os serviços prestados.

## Desafios e Aprendizados

Este projeto foi uma oportunidade de explorar conceitos de:

- Manipulação de arquivos binários para persistência de dados.

- Segregação de responsabilidades por meio de organização modular.

- Tratamento de dados e validação em sistemas interativos.

## Licença
Este projeto está licenciado sob a Licença MIT.

Desenvolvido por Gabriel Rebechi e Benício Reinehr Dal Forno do curso de Tecnologia em Análise e Desenvolvimento de Sistemas.
