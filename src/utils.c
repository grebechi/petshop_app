#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"

void limparTerminal() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls"); // Comando para Windows
#elif defined(__linux__)
    system("clear"); // Comando para Linux
#elif defined(__APPLE__) && defined(__MACH__)
    system("clear"); // Comando para macOS
#elif defined(__unix__)
    system("clear"); // Comando para sistemas Unix
#else
    printf("\nSistema operacional não suportado para limpar a tela.\n");
#endif
}

void pausarTerminal() {
#if defined(_WIN32) || defined(_WIN64)
    system("pause"); // Comando para Windows
    fflush(stdin);
#elif defined(__linux__) || (defined(__APPLE__) && defined(__MACH__)) || defined(__unix__)
    printf("\nPressione Enter para continuar...");
    fflush(stdin);
    getchar(); // Aguarda o usuário pressionar Enter
#else
    printf("\nSistema operacional não suportado para pausar o terminal.\n");
#endif
}
