#ifndef SERVICO_H
#define SERVICO_H

// Tamanho máximo para os campos
#define SERVICO_MAX_NOME 100

// Estrutura do Servico
typedef struct {
    int id;
    char nome[SERVICO_MAX_NOME];
    float valorCobrado;
    float valorCusto;
} Servico;

// Declaração das funções
int gerarProximoIDServico();
int salvarServico(Servico servico);
int contarServicos();
Servico *listarServicos(int quantidade);
int atualizarServico(Servico *servicoRecebido);
int excluirServico(int id);
Servico *buscarServicoPeloID(int id);
int servicoJaExiste(const char *nome);
int adicionarServicosPadrao();

#endif




