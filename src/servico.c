#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/servico.h"

#define ARQUIVO_SERVICO "src/bin/servicos.bin"

int gerarProximoIDServico() { 
    FILE *file = fopen(ARQUIVO_SERVICO, "rb");
    if (file == NULL) {
        return 1; // Arquivo inexistente, primeiro ID será 1
    }

    Servico servico;
    int maxID = 0;

    while (fread(&servico, sizeof(Servico), 1, file)) {
        if (servico.id > maxID) {
            maxID = servico.id;
        }
    }

    fclose(file);
    return maxID + 1; // Retorna o próximo ID
}

int salvarServico(Servico servico) {
    FILE *file = fopen(ARQUIVO_SERVICO, "ab"); // Abre o arquivo no modo de adicionar binário
    if (file == NULL) {
        return 0;
    }

    fwrite(&servico, sizeof(Servico), 1, file); // Escreve o servico no arquivo
    fclose(file);
    return 1;
}

int contarServicos() {
    FILE *file = fopen(ARQUIVO_SERVICO, "rb");
    if (file == NULL) {
        return 0; // Arquivo inexistente ou vazio
    }

    // Move o ponteiro para o final do arquivo
    fseek(file, 0, SEEK_END);

    // Calcula o tamanho do arquivo em bytes
    long tamanhoArquivo = ftell(file);

    // Calcula o número de registros dividindo o tamanho total pelo tamanho de um struct de Servico
    int totalServico = tamanhoArquivo / sizeof(Servico);

    fclose(file);

    return totalServico;
}

Servico *listarServicos(int quantidade) {
    FILE *file = fopen(ARQUIVO_SERVICO, "rb");
    if (file == NULL) {
        return NULL;
    }

    if (quantidade == 0) {
        fclose(file);
        return NULL;
    }

    Servico *servicos = (Servico *)malloc(quantidade * sizeof(Servico));
    if (servicos == NULL) {
        fclose(file);
        return NULL;
    }

    fread(servicos, sizeof(Servico), quantidade, file);
    fclose(file);

    return servicos;
}

int atualizarServico(Servico *servicoRecebido) {
    FILE *file = fopen(ARQUIVO_SERVICO, "rb"); // Abre o arquivo original
    if (file == NULL) {
        return 1;
    }

    FILE *temp = fopen("src/bin/temp_servico1.bin", "wb"); // Cria o arquivo temporário
    if (temp == NULL) {
        fclose(file);
        return 2;
    }

    Servico servico;
    int encontrado = 0;

    while (fread(&servico, sizeof(Servico), 1, file)) {
        if (servico.id == servicoRecebido->id) {
            encontrado = 1; // Encontrou o servico a ser excluído
            fwrite(servicoRecebido, sizeof(Servico), 1, temp); // Escreve o servico recebido no arquivo temporário
        } else {
            fwrite(&servico, sizeof(Servico), 1, temp); // Escreve os demais servicos no arquivo temporário
        }
    }

    fclose(file);
    fclose(temp);

    if (encontrado == 1) {
        remove(ARQUIVO_SERVICO);           // Remove o arquivo original
        rename("src/bin/temp_servico1.bin", ARQUIVO_SERVICO); // Renomeia o temporário para o original
        return 0;
    } else {
        remove("src/bin/temp_servico1.bin");               // Remove o temporário
        return 3;
    }
}

int excluirServico(int id) {
    FILE *file = fopen(ARQUIVO_SERVICO, "rb"); // Abre o arquivo original
    if (file == NULL) {
        return 1;
    }

    FILE *temp = fopen("src/bin/temp_servico2.bin", "wb"); // Cria o arquivo temporário
    if (temp == NULL) {
        fclose(file);
        return 2;
    }

    Servico servico;
    int encontrado = 0;

    while (fread(&servico, sizeof(Servico), 1, file)) {
        if (servico.id == id) {
            encontrado = 1; // Encontrou o servico a ser excluído
        } else {
            fwrite(&servico, sizeof(Servico), 1, temp); // Escreve no arquivo temporário
        }
    }

    fclose(file);
    fclose(temp);

    if (encontrado == 1) {
        remove(ARQUIVO_SERVICO);           // Remove o arquivo original
        rename("src/bin/temp_servico2.bin", ARQUIVO_SERVICO); // Renomeia o temporário para o original
        return 0;
    } else {
        remove("src/bin/temp_servico2.bin");               // Remove o temporário
        return 3;
    }
}

Servico *buscarServicoPeloID(int id) {
    FILE *file = fopen(ARQUIVO_SERVICO, "rb");
    if (file == NULL) {
        return NULL; // Arquivo inexistente, servico não existe
    }
    
    Servico *servico = (Servico *)malloc(1 * sizeof(Servico));
    while (fread(servico, sizeof(Servico), 1, file)) {
        if (servico->id == id) {
            fclose(file);
            return servico; // Servico encontrado
            
        }
    }

    fclose(file);
    return NULL; // Servico não encontrado
}

int servicoJaExiste(const char *nome) {
    FILE *file = fopen(ARQUIVO_SERVICO, "rb");
    if (file == NULL) {
        return 0; // Arquivo inexistente, servico não existe
    }

    Servico servico;
    while (fread(&servico, sizeof(Servico), 1, file)) {
        if (strcmp(servico.nome, nome) == 0) {
            fclose(file);
            return 1; // Servico encontrado
        }
    }

    fclose(file);
    return 0; // Servico não encontrado
}

int adicionarServicosPadrao() {
    // Lista de servicos padrão
    Servico servicosPadrao[] = {
        {0, "Banho e Tosa Completo", 99.90, 30.00},
        {0, "Vacinação Antirrábica", 70.00, 15.00},
        {0, "Consulta Veterinária", 150.00, 50.00},
        {0, "Higienização Bucal", 85.90, 25.00},
        {0, "Banho Simples", 50.00, 20.00},
        {0, "Corte de Unhas", 20.00, 5.00},
        {0, "Tratamento de Pulgas e Carrapatos", 120.00, 40.00},
        {0, "Check-up Geral", 200.00, 70.00},
        {0, "Consulta Dermatológica", 160.00, 60.00},
        {0, "Consulta Cardiológica", 180.00, 70.00},
        {0, "Hospedagem Diária", 120.00, 40.00},
        {0, "Aplicação de Medicamentos", 25.00, 10.00},
        {0, "Corte Estilizado", 75.00, 25.00},
        {0, "Tosa Higiênica", 40.00, 15.00},
        {0, "Hidratação e Escovação de Pelos", 90.00, 30.00},
        {0, "Remoção de Tártaro", 110.00, 50.00},
        {0, "Exame de Sangue", 180.00, 80.00},
        {0, "Raio-X Veterinário", 250.00, 100.00},
        {0, "Ultrassom", 300.00, 120.00},
        {0, "Consulta Odontológica", 140.00, 60.00}
    };

    for (int i = 0; i < 10; i++) {
        if (!servicoJaExiste(servicosPadrao[i].nome)) {
            servicosPadrao[i].id = gerarProximoIDServico();
            if(salvarServico(servicosPadrao[i]) == 0){
                return 0;
            }
        }
    }
    return 1;
}
