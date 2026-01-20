
/**
 * @file main.c
 * @author n-05  (a31502@alunos.ipca.pt, a31517@alunos.ipca.pt, a31505@alunos.ipca.pt)
 * @brief  Programa para gerir as refeições de um refeitório
 * @version 0.1
 * @date 05-01-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


/**
 * @brief  Função para exibir o menu principal
 *
 * case 1 Carregar funcionários
 * case 2 Carregar ementas
 * case 3 Carregar escolhas
 * case 4 Listar refeições de um dia
 * case 5 Listar utentes por ordem decrescente
 * case 6 Listar refeições de um utente
 * case 7 Calcular média de calorias de um espaço
 * case 8 Gerar tabela de ementa semanal de um utente
 * case 9 Sair
 *@return int Retorna a opção escolhida pelo utilizador
 */

int main(int argc, char *argv[]) {
    
    Funcionario funcionarios[MAX_FUNCIONARIOS];
    Ementa ementas[5]; // Pode ser ajustado conforme a quantidade máxima de ementas
    Escolha escolhas[MAX_FUNCIONARIOS * 5]; // Ajuste conforme o número de escolhas possíveis
    int totalFuncionarios = 0, totalEmentas = 0, totalEscolhas = 0;
    int opcao;
    char nomeFicheiroFuncionarios[100] = "funcionarios.txt";
    char nomeFicheiroEmentas[100] = "ementas.txt";
    char nomeFicheiroEscolhas[100] = "escolhas.txt";
    int modoTab = 0;
    int modoBin = 0;
    char DiaInicio[10];
    char DiaFim[10];
     
      // Processa os argumentos da linha de comando
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-ajuda") == 0) {
            mostrarAjuda();
            return 0;
        } else if (strcmp(argv[i], "-tab") == 0) {
            modoTab = 1;
        } else if (strcmp(argv[i], "-bin") == 0) {
            modoBin = 1;
        } else if (i == argc - 3) {
            strcpy(nomeFicheiroFuncionarios, argv[i]);
            strcpy(nomeFicheiroEmentas, argv[i + 1]);
            strcpy(nomeFicheiroEscolhas, argv[i + 2]);
            break;
        }
    }

     // Carregar dados dos ficheiros
    if (modoBin) {
        // Carregar ficheiros em modo binário
        carregarFuncionariosBin(nomeFicheiroFuncionarios, funcionarios, &totalFuncionarios);
        carregarEmentasBin(nomeFicheiroEmentas, ementas, &totalEmentas);
        carregarEscolhasBin(nomeFicheiroEscolhas, escolhas, &totalEscolhas);
    } else if (modoTab) {
        // Carregar ficheiros de texto separados por tabulação
        carregarFuncionariosTab(nomeFicheiroFuncionarios, funcionarios, &totalFuncionarios);
        carregarEmentasTab(nomeFicheiroEmentas, ementas, &totalEmentas);
        carregarEscolhasTab(nomeFicheiroEscolhas, escolhas, &totalEscolhas);
    } else {
        totalFuncionarios = carregarFuncionarios(nomeFicheiroFuncionarios, funcionarios);
        totalEmentas = carregarEmenta(nomeFicheiroEmentas, ementas);
        totalEscolhas = carregarEscolhas(nomeFicheiroEscolhas, escolhas);
    }


         while (1) {
        /**
         * @brief Menu principal
         * 
         */
        menu(); // Mostra o menu
        scanf("%d", &opcao); // Lê a opção do utilizador

        /**
         * @brief Switch case para as opções do menu
         * 
         */
        switch (opcao) {
            
            case 1: {
                totalFuncionarios=carregarFuncionarios("funcionarios.txt", funcionarios);
                break;
            }
            case 2: {
                totalEmentas=carregarEmenta("ementas.txt", ementas);
                break;
            }
             case 3: {
                totalEscolhas=carregarEscolhas("escolhas.txt", escolhas);
                break;
            }
             case 4: {
                char diaSemana[10];
                printf("Escreva o dia da semana para listar as refeições (ex: Segunda): ");
                scanf("%s", diaSemana);
                listarRefeicoesDia(escolhas, totalEscolhas, funcionarios, totalFuncionarios, diaSemana);
                break;
            }

            case 5: {
                listarUtentesOrdemDecrescente(escolhas, totalEscolhas, funcionarios, totalFuncionarios);
                break;
            }

            case 6: {
                listarRefeicoesUtente(escolhas, totalEscolhas,  ementas, totalFuncionarios, totalEmentas);
                break;
            }
            case 7: {
                printf("Escreva o dia de início para calcular a média de calorias (ex: Segunda): ");
                scanf("%s", DiaInicio);
                printf("Escreva o dia de fim para calcular a média de calorias (ex: Sexta): ");
                scanf("%s", DiaFim);
                calcularMediaCaloriasEspaco (ementas, totalEmentas, escolhas, totalEscolhas, DiaInicio, DiaFim);
                break;
            }
            case 8: {
                printf("Escreva o número do funcionário para gerar a tabela de ementa semanal: ");
                int numeroFuncionario;
                scanf("%d", &numeroFuncionario);
                gerarTabelaEmentaUtente(escolhas, totalEscolhas, ementas, totalEmentas, numeroFuncionario);
                break;
            }
            case 9: {
                printf("A sair do programa...\n");
                exit (0);
            }

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        printf("\n");
    }

    return 0;
}
