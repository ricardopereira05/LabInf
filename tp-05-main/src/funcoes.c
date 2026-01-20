#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

/**
 * @brief  Função para exibir o menu principal
 * 
 */
void menu() {
    printf("\n========================================================\n");
    printf("        Aplicação de Gestão do Espaço Social\n");
    printf("========================================================\n");
    printf("1. Carregar Dados dos Funcionarios\n");
    printf("2. Carregar Ementa Semanal\n");
    printf("3. Carregar Escolhas para a Semana dos Utentes\n");
    printf("4. Apresentar Refeições de um dia\n");
    printf("5. Listar os Utentes e Calcular as Despesas\n");
    printf("6. Listar Refeições e Calorias de um Utente\n");
    printf("7. Calcular média de Calorias por Refeição de todo Espaço\n");
    printf("8. Gerar tabela da Ementa Semanal\n");
    printf("9. Sair\n");
    printf("Escolha uma opção:");
}

void mostrarAjuda() {
    printf("Uso: programa [opções] [ficheiros]\n");
    printf("Opções:\n");
    printf("  -ajuda       Mostra esta mensagem de ajuda\n");
    printf("  -tab         Usa ficheiros de texto separados por tabulação\n");
    printf("  -bin         Usa ficheiros em modo binário\n");
    printf("Ficheiros:\n");
    printf("  funcionarios.txt ementas.txt escolhas.txt\n");
}

/**
 * @brief  Função para carregar os dados dos funcionários a partir de um ficheiro
 * 
 * @param nomeFicheiro   Nome do ficheiro
 * @param funcionario  Array de funcionários
 * @return int  Retorna o total de funcionários carregados
 */
int carregarFuncionarios(char* nomeFicheiro, Funcionario funcionario[]) {
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro: %s\n", nomeFicheiro);
        return 0;
    }

    int totalFuncionarios = 0;
    while (totalFuncionarios < MAX_FUNCIONARIOS) {

        // Lê os dados do ficheiro e atribui aos campos da estrutura
        if (fscanf(ficheiro, "%d;%99[^;];%14[^;];%14[^\n]\n",
                   &funcionario[totalFuncionarios].numero,
                   funcionario[totalFuncionarios].nome,
                   funcionario[totalFuncionarios].nif,
                   funcionario[totalFuncionarios].telefone) == 4) {
            totalFuncionarios++;
        } else {
            break; // Encerra a leitura caso ocorra erro ou final do arquivo
        }
    }

    fclose(ficheiro);

    printf("Carregamento dos dados dos funcionários foi realizado com sucesso!\n");
    printf("Total de funcionários carregados: %d\n", totalFuncionarios);
    return totalFuncionarios;
}


/**
 * @brief  Função para carregar a ementa semanal a partir de um ficheiro
 * 
 * @param nomeficheiro  Nome do ficheiro
 * @param ementas  Array de ementas
 * @return int   ]Retorna o total de ementas carregadas
 */
int carregarEmenta(char* nomeficheiro, Ementa ementas[]) {
    FILE* ficheiro = fopen(nomeficheiro, "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir ficheiro de ementa\n");
        return 0;
    }
    
    int totalEmentas = 0; 
    while (fscanf(ficheiro, "%9[^;];%11[^;];%99[^;];%d;%99[^;];%d;%99[^;];%d;%99[^;];%d\n", 
                    ementas[totalEmentas].diaSemana,
                    ementas[totalEmentas].data,    
                    ementas[totalEmentas].pratoPeixe, &ementas[totalEmentas].caloriasPeixe,
                    ementas[totalEmentas].pratoCarne, &ementas[totalEmentas].caloriasCarne, 
                    ementas[totalEmentas].pratoDieta, &ementas[totalEmentas].caloriasDieta, 
                    ementas[totalEmentas].pratoVegetariano, &ementas[totalEmentas].caloriasVegetariano) == 10) {
                totalEmentas++;
        if (totalEmentas >= 5) {
            break;
        }
    }

    fclose(ficheiro);
    printf("Carregamento de ementa semanal foi realizado com sucesso!\n");
    return totalEmentas; 
}

/**
 * @brief  Função para carregar as escolhas dos utentes a partir de um ficheiro
 * 
 * @param nomeFicheiro  Nome do ficheiro
 * @param escolhas  Array de escolhas
 * @return int  Retorna o total de escolhas carregadas
 */
int carregarEscolhas(char* nomeFicheiro, Escolha escolhas[]) {
    FILE* ficheiro = fopen(nomeFicheiro, "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro!");
        return 0; 
    }

    int totalEscolhas = 0;
    while (fscanf(ficheiro, "%19[^;];%d;%19[^\n]\n", 
                  escolhas[totalEscolhas].diaSemana, 
                  &escolhas[totalEscolhas].numeroFuncionario, 
                  escolhas[totalEscolhas].tipoPrato) == 3) {
        totalEscolhas++;
        if (totalEscolhas >= MAX_ESCOLHAS) { // Limita ao número máximo de escolhas
            printf("Limite máximo de refeições atingido %d \n", MAX_ESCOLHAS);
            break;
        }
    }
    fclose(ficheiro);

    printf("Carregamento das escolhas realizado com sucesso!\n");
    return totalEscolhas;
    
}


/**
 * @brief  Função para carregar os dados dos funcionários a partir de um ficheiro binário
 * 
 * @param nomeFicheiro   Nome do ficheiro
 * @param funcionarios  Array de funcionários
 * @param totalFuncionarios  Ponteiro para o total de funcionários carregados
 */
void carregarFuncionariosBin(const char *nomeFicheiro, Funcionario *funcionarios, int *totalFuncionarios) {
    FILE *ficheiro = fopen(nomeFicheiro, "rb");
    if (!ficheiro) {
        printf("Erro ao abrir o ficheiro: %s\n", nomeFicheiro);
        *totalFuncionarios = 0;
        return;
    }

    size_t lidos = fread(funcionarios, sizeof(Funcionario), MAX_FUNCIONARIOS, ficheiro);
    *totalFuncionarios = (int)lidos;

    if (ferror(ficheiro)) {
        printf("Erro ao ler o ficheiro: %s\n", nomeFicheiro);
    } else {
        printf("Carregamento dos funcionários em binário foi bem-sucedido!\n");
        printf("Total de funcionários carregados: %d\n", *totalFuncionarios);
    }
    fclose(ficheiro);
}

/**
 * @brief  Função para carregar a ementa semanal a partir de um ficheiro binário
 * 
 * @param nomeFicheiro  Nome do ficheiro
 * @param ementas  Array de ementas
 * @param totalEmentas  Ponteiro para o total de ementas carregadas
 */
void carregarEmentasBin(const char *nomeFicheiro, Ementa *ementas, int *totalEmentas) {
    FILE *ficheiro = fopen(nomeFicheiro, "rb");
    if (ficheiro == NULL) {
        printf("Erro ao abrir ficheiro de ementa\n");
        *totalEmentas = 0;
        return;
    }

    *totalEmentas = fread(ementas, sizeof(Ementa), 5, ficheiro); // Ajuste conforme a quantidade máxima de ementas
    fclose(ficheiro);

    printf("Carregamento das ementas em modo binário foi realizado com sucesso!\n");
    printf("Total de ementas carregadas: %d\n", *totalEmentas);
}

/**
 * @brief  Função para carregar as escolhas dos utentes a partir de um ficheiro binário
 * 
 * @param nomeFicheiro  Nome do ficheiro
 * @param escolhas  Array de escolhas
 * @param totalEscolhas  Ponteiro para o total de escolhas carregadas
 */
void carregarEscolhasBin(const char *nomeFicheiro, Escolha *escolhas, int *totalEscolhas) {
    FILE *ficheiro = fopen(nomeFicheiro, "rb");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro!");
        *totalEscolhas = 0;
        return;
    }

    *totalEscolhas = fread(escolhas, sizeof(Escolha), MAX_ESCOLHAS, ficheiro);
    fclose(ficheiro);

    printf("Carregamento das escolhas em modo binário foi realizado com sucesso!\n");
    printf("Total de escolhas carregadas: %d\n", *totalEscolhas);
}

/**
 * @brief  Função para carregar os dados dos funcionários a partir de um ficheiro de texto separado por tabulação
 * 
 * @param nomeFicheiro   Nome do ficheiro
 * @param funcionarios  Array de funcionários
 * @param totalFuncionarios  Ponteiro para o total de funcionários carregados
 */
void carregarFuncionariosTab(const char *nomeFicheiro, Funcionario *funcionarios, int *totalFuncionarios) {
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    if (!ficheiro) {
        printf("Erro ao abrir o ficheiro: %s\n", nomeFicheiro);
        *totalFuncionarios = 0;
        return;
    }

    *totalFuncionarios = 0;
    while (*totalFuncionarios < MAX_FUNCIONARIOS) {
        if (fscanf(ficheiro, "%d\t%99[^\t]\t%14[^\t]\t%14[^\n]",
                   &funcionarios[*totalFuncionarios].numero,
                   funcionarios[*totalFuncionarios].nome,
                   funcionarios[*totalFuncionarios].nif,
                   funcionarios[*totalFuncionarios].telefone) == 4) {
            (*totalFuncionarios)++;
        } else if (feof(ficheiro)) {
            break;
        } else {
            printf("Erro ao ler dados no ficheiro tabulado.\n");
            break;
        }
    }

    printf("Carregamento dos funcionários em modo tabulação foi realizado com sucesso!\n");
    printf("Total de funcionários carregados: %d\n", *totalFuncionarios);
    fclose(ficheiro);
}

/**
 * @brief  Função para carregar a ementa semanal a partir de um ficheiro de texto separado por tabulação
 * 
 * @param nomeFicheiro  Nome do ficheiro
 * @param ementas  Array de ementas
 * @param totalEmentas  Ponteiro para o total de ementas carregadas
 */
void carregarEmentasTab(const char *nomeFicheiro, Ementa *ementas, int *totalEmentas) {
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir ficheiro de ementa\n");
        *totalEmentas = 0;
        return;
    }

    *totalEmentas = 0;
    while (*totalEmentas < 5) { // Ajuste conforme a quantidade máxima de ementas
        if (fscanf(ficheiro, "%9[^\t]\t%11[^\t]\t%49[^\t]\t%d\t%49[^\t]\t%d\t%49[^\t]\t%d\t%49[^\t]\t%d\n",
                   ementas[*totalEmentas].diaSemana,
                   ementas[*totalEmentas].data,
                   ementas[*totalEmentas].pratoPeixe,
                   &ementas[*totalEmentas].caloriasPeixe,
                   ementas[*totalEmentas].pratoCarne,
                   &ementas[*totalEmentas].caloriasCarne,
                   ementas[*totalEmentas].pratoDieta,
                   &ementas[*totalEmentas].caloriasDieta,
                   ementas[*totalEmentas].pratoVegetariano,
                   &ementas[*totalEmentas].caloriasVegetariano) == 10) {
            (*totalEmentas)++;
        } else {
            break; // Encerra a leitura caso ocorra erro ou final do arquivo
        }
    }

    fclose(ficheiro);

    printf("Carregamento das ementas em modo tabulação foi realizado com sucesso!\n");
    printf("Total de ementas carregadas: %d\n", *totalEmentas);
}

/**
 * @brief  Função para carregar as escolhas dos utentes a partir de um ficheiro de texto separado por tabulação
 * 
 * @param nomeFicheiro  Nome do ficheiro
 * @param escolhas  Array de escolhas
 * @param totalEscolhas  Ponteiro para o total de escolhas carregadas
 */
void carregarEscolhasTab(const char *nomeFicheiro, Escolha *escolhas, int *totalEscolhas) {
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro!");
        *totalEscolhas = 0;
        return;
    }

    *totalEscolhas = 0;
    while (fscanf(ficheiro, "%19[^\t]\t%d\t%19[^\n]\n", 
                  escolhas[*totalEscolhas].diaSemana, 
                  &escolhas[*totalEscolhas].numeroFuncionario, 
                  escolhas[*totalEscolhas].tipoPrato) == 3) {
        (*totalEscolhas)++;
        if (*totalEscolhas >= MAX_ESCOLHAS) { // Limita ao número máximo de escolhas
            printf("Limite máximo de refeições atingido %d \n", MAX_ESCOLHAS);
            break;
        }
    }
    fclose(ficheiro);

    printf("Carregamento das escolhas em modo tabulação foi realizado com sucesso!\n");
}

/**
 * @brief  Função para listar as refeições de um dia específico
 * 
 * @param escolhas  Array de escolhas
 * @param totalEscolhas  Total de escolhas
 * @param funcionarios  Array de funcionários
 * @param totalFuncionarios  Total de funcionários
 * @param diaSemana  Dia da semana
 */
void listarRefeicoesDia(Escolha* escolhas, int totalEscolhas, Funcionario* funcionarios, int totalFuncionarios, const char* diaSemana) {
    printf("Refeições para o dia %s:\n", diaSemana);
    printf("----------------------------------------------------\n");
    printf("| Nº Funcionário | Nome            | Prato         |\n");
    printf("----------------------------------------------------\n");

    int encontrado = 0; // Flag para indicar se alguma refeição foi encontrada

    for (int i = 0; i < totalEscolhas; i++) {
        if (strcmp(escolhas[i].diaSemana, diaSemana) == 0) {
            // Encontra o nome do funcionário correspondente
            for (int j = 0; j < totalFuncionarios; j++) {
                if (funcionarios[j].numero == escolhas[i].numeroFuncionario) {
                    printf(" |%15d|%-15s|%-15s| \n",
                           funcionarios[j].numero,
                           funcionarios[j].nome,
                           escolhas[i].tipoPrato);
                    encontrado = 1; // Marca que encontramos pelo menos uma refeição
                    break; // Para de procurar o funcionário correspondente
                }
            }
        }
    }

    if (!encontrado) {
        printf("Nenhuma refeição foi registrada para o dia de %s.\n", diaSemana);
    }
}

/**
 * @brief Função para listar os utentes em ordem decrescente de número de funcionário
 * 
 * @param escolhas Array de escolhas
 * @param totalEscolhas Total de Escolhas Possivel
 * @param funcionarios  Array de funcionários
 * @param totalFuncionarios  Total de Funcionários
 */
void listarUtentesOrdemDecrescente(Escolha* escolhas, int totalEscolhas, Funcionario* funcionarios, int totalFuncionarios) {
    // Arrays para armazenar refeições e despesas por funcionário
    int refeicoes[totalFuncionarios];
    float despesas[totalFuncionarios];

    // Inicializa os contadores
    for (int i = 0; i < totalFuncionarios; i++) {
        refeicoes[i] = 0;
        despesas[i] = 0.0f;
    }

    // Calcula o número de refeições e a despesa total para cada funcionário
    for (int i = 0; i < totalEscolhas; i++) {
        for (int j = 0; j < totalFuncionarios; j++) {
            if (escolhas[i].numeroFuncionario == funcionarios[j].numero) {
                refeicoes[j]++;
                despesas[j] += 6.00;
            }
        }
    }

    // Ordena os funcionários em ordem decrescente de número de funcionário
    for (int i = 0; i < totalFuncionarios - 1; i++) {
        for (int j = i + 1; j < totalFuncionarios; j++) {
            if (funcionarios[i].numero< funcionarios[j].numero) {
                // Troca os funcionários
                Funcionario tempFuncionario = funcionarios[i];
                funcionarios[i] = funcionarios[j];
                funcionarios[j] = tempFuncionario;

                // Troca os dados correspondentes
                int tempRefeicoes = refeicoes[i];
                refeicoes[i] = refeicoes[j];
                refeicoes[j] = tempRefeicoes;

                float tempDespesas = despesas[i];
                despesas[i] = despesas[j];
                despesas[j] = tempDespesas;
            }
        }
    }

    // Exibe os dados ordenados
    printf("Relatório de Utentes - Recursos Humanos\n");
    printf("-------------------------------------------------------------\n");
    printf("| Nº Funcionário | Nome            | Refeições | Total (€) |\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < totalFuncionarios; i++) {
        printf("| %-15d | %-15s | %-10d | %-10.2f |\n",
               funcionarios[i].numero,
               funcionarios[i].nome,
               refeicoes[i],
               despesas[i]);
    }
}


/**
 * @brief  Funcao para converter o dia da semana em número
 * 
 * @param dia  Dia da semana
 * @return int  Retorna o número correspondente ao dia da semana
 */
int diaSemanaParaNumero(char* dia) {
    if (strcmp(dia, "Segunda") == 0) return 0;
    if (strcmp(dia, "Terça") == 0) return 1;
    if (strcmp(dia, "Quarta") == 0) return 2;
    if (strcmp(dia, "Quinta") == 0) return 3;
    if (strcmp(dia, "Sexta") == 0) return 4;
    return -1; // Dia inválido
}


/**
 * @brief Função para verificar se um dia está dentro de um intervalo
 * 
 * @param diaAtual  Dia atual
 * @param numeroInicio  Número do dia de início
 * @param numeroFim Número do dia de fim
 * @return int  Retorna 1 se o dia está no intervalo, 0 caso contrário
 */
int estaNoIntervalo(int diaAtual, int numeroInicio, int numeroFim) {
    if (numeroInicio <= numeroFim) {
        // Intervalo direto (ex: Segunda a Sexta)
        return (diaAtual >= numeroInicio && diaAtual <= numeroFim);
    } else {
        // Intervalo circular (ex: Quinta a Terça)
        return (diaAtual >= numeroInicio || diaAtual <= numeroFim);
    }
}


/**
 * @brief  Função para listar as refeições e calorias de um utente durante um período
 * 
 * @param escolhas  Array de escolhas
 * @param totalEscolhas  Total de escolhas
 * @param ementas  Array de ementas
 * @param totalFuncionarios  Total de funcionários
 * @param totalEmentas  Total de ementas
 */
void listarRefeicoesUtente(Escolha* escolhas, int totalEscolhas, Ementa* ementas, int totalFuncionarios, int totalEmentas) {
    int numeroFuncionario;
    printf("Escreva o número do funcionário: ");
    scanf("%d", &numeroFuncionario);

    // Verifica se o número do funcionário é válido antes de pedir os dias
    if (numeroFuncionario <= 0 || numeroFuncionario > totalFuncionarios) {
        printf("Erro: Número de funcionário %d não existe.\n", numeroFuncionario);
        return;  // Sai da função e retorna ao menu
    }

    char DiaInicio[20], DiaFim[20];
    printf("Escreva o dia de início (ex: Segunda): ");
    scanf("%s", DiaInicio);
    printf("Escreva o dia de fim (ex: Sexta): ");
    scanf("%s", DiaFim);
    
    int numeroInicio = diaSemanaParaNumero(DiaInicio);
    int numeroFim = diaSemanaParaNumero(DiaFim);

   
    if (numeroInicio == -1 || numeroFim == -1) {
        printf("Erro: Dia de início ou fim inválido.\n");
        return;
    }

    printf("Refeições e calorias do funcionário %d durante o período de %s a %s:\n", numeroFuncionario, DiaInicio, DiaFim);
    printf("---------------------------------------------------------\n");
    printf("|  Dia da Semana  |   Tipo de Prato    |   Calorias   |\n");
    printf("---------------------------------------------------------\n");

    int numeroRefeicoes = 0;
    int totalCalorias = 0;

    // Passa pelas escolhas e buscar correspondências na ementa
    for (int i = 0; i < totalEscolhas; i++) {
        if (escolhas[i].numeroFuncionario == numeroFuncionario) {
            for (int j = 0; j < totalEmentas; j++) {
                if (strcmp(escolhas[i].diaSemana, ementas[j].diaSemana) == 0) {
                    int indiceAtual = diaSemanaParaNumero(ementas[j].diaSemana);

                    if (estaNoIntervalo(indiceAtual, numeroInicio, numeroFim)) {
                        // Determinar as calorias do prato específico
                        int calorias = 0;

                        if (strcmp(escolhas[i].tipoPrato, "Peixe") == 0) {
                            calorias = ementas[j].caloriasPeixe;
                        } else if (strcmp(escolhas[i].tipoPrato, "Carne") == 0) {
                            calorias = ementas[j].caloriasCarne;
                        } else if (strcmp(escolhas[i].tipoPrato, "Dieta") == 0) {
                            calorias = ementas[j].caloriasDieta;
                        } else if (strcmp(escolhas[i].tipoPrato, "Vegetariano") == 0) {
                            calorias = ementas[j].caloriasVegetariano;
                        }

                        // Atualizar valores e exibir o prato específico
                        totalCalorias += calorias; // Acumular calorias
                        printf("| %16s | %15s | %5d |\n", ementas[j].diaSemana, escolhas[i].tipoPrato, calorias);
                        numeroRefeicoes++;
                    }
                }
            }
        }
    }

    printf("---------------------------------------------------------\n");
    if (numeroRefeicoes > 0) {
        printf("Total de refeições: %d\n", numeroRefeicoes);
        printf("Total de calorias consumidas no período: %d\n", totalCalorias);
    } else {
        printf("Nenhuma refeição registrada para o funcionário %d durante o período de %s a %s.\n", numeroFuncionario, DiaInicio, DiaFim);
    }
}


/**
 * @brief  Função para calcular a média de calorias consumidas no período
 * 
 * @param ementas  Array de ementas
 * @param totalEmentas  Total de ementas
 * @param escolhas  Array de escolhas
 * @param totalEscolhas  Total de escolhas
 * @param diainicio  Dia de início
 * @param diafim  Dia de fim
 */
// Função para calcular a média de calorias consumidas no período
void calcularMediaCaloriasEspaco(Ementa* ementas, int totalEmentas, Escolha* escolhas, int totalEscolhas, char* diainicio, char* diafim) {
    // Converte os dias de início e fim em números
    int numeroDiaInicio = diaSemanaParaNumero(diainicio);
    int numeroDiaFim = diaSemanaParaNumero(diafim);

    if (numeroDiaInicio == -1 || numeroDiaFim == -1) {
        printf("Erro: Dia de início ou fim inválido.\n");
        return;
    }

    // Inicializa as variáveis para somar as calorias por dia
    int caloriasDia[5] = {0};  // 0: Segunda, 1: Terça, 2: Quarta, 3: Quinta, 4: Sexta
    int numeroRefeicoesPorDia[5] = {0};
    int CaloriasPrato = 0;

    // Percorre todas as escolhas de refeição
    for (int i = 0; i < totalEscolhas; i++) {
        // Obtém o número do dia da escolha
        int numeroDiaEscolha = diaSemanaParaNumero(escolhas[i].diaSemana);

        // Verifica se o dia da escolha está dentro do intervalo de dias
        if (numeroDiaEscolha >= numeroDiaInicio && numeroDiaEscolha <= numeroDiaFim) {
            // Percorre as ementas para verificar a correspondência dos pratos
            for (int y = 0; y < totalEmentas; y++) {
                if (numeroDiaEscolha == diaSemanaParaNumero(ementas[y].diaSemana)) {
                    // Verifica o tipo de prato e calcula as calorias
                    if (strcmp(escolhas[i].tipoPrato, "Peixe") == 0) {
                        CaloriasPrato = ementas[y].caloriasPeixe;
                    } else if (strcmp(escolhas[i].tipoPrato, "Carne") == 0) {
                        CaloriasPrato = ementas[y].caloriasCarne;
                    } else if (strcmp(escolhas[i].tipoPrato, "Dieta") == 0) {
                        CaloriasPrato = ementas[y].caloriasDieta;
                    } else if (strcmp(escolhas[i].tipoPrato, "Vegetariano") == 0) {
                        CaloriasPrato = ementas[y].caloriasVegetariano;
                    }

                    // Adiciona as calorias do prato escolhido ao total de calorias do dia correspondente
                    caloriasDia[numeroDiaEscolha] += CaloriasPrato;
                    numeroRefeicoesPorDia[numeroDiaEscolha]++;
                    break; // Interrompe o loop de ementas, pois encontramos o prato para o dia
                }
            }
        }
    }

    // Exibe as médias de calorias consumidas por refeição para cada dia da semana
    printf("Média de calorias consumidas por refeição de cada dia da semana no período de %s a %s:\n", diainicio, diafim);
    printf("-------------------------------------------------------------\n");

    // Array com os dias da semana
    const char* diasSemana[] = {"Segunda", "Terça", "Quarta", "Quinta", "Sexta"};

    for (int k = 0; k < 5; k++) {
        if (numeroRefeicoesPorDia[k] > 0) {
            float media = (float)caloriasDia[k] / numeroRefeicoesPorDia[k];
            printf("%s:  %d refeições, média: %.2f calorias por refeição.\n",
                diasSemana[k], numeroRefeicoesPorDia[k], media);
        }
    }
}


/**
 * @brief  Função para gerar uma tabela de ementa para um utente
 * 
 * @param escolhas  Array de escolhas
 * @param totalEscolhas  Total de escolhas
 * @param ementas  Array de ementas
 * @param totalEmentas  Total de ementas
 * @param numeroFuncionario  Número do funcionário
 */
void gerarTabelaEmentaUtente(Escolha* escolhas, int totalEscolhas, Ementa* ementas, int totalEmentas, int numeroFuncionario) {
    printf("| Dia Semana | Prato Escolhido | Calorias |\n");
    printf("==============================================\n");

    // Percorre todos os dias da semana para verificar se o funcionário fez escolha
    for (int i = 0; i < totalEmentas; i++) {
        char* refeicaoEscolhida = 0;
        int calorias = 0;

        // Verifica se o funcionário fez uma escolha para aquele dia
        for (int j = 0; j < totalEscolhas; j++) {
            if (escolhas[j].numeroFuncionario == numeroFuncionario && 
                strcmp(escolhas[j].diaSemana, ementas[i].diaSemana) == 0) {
                
    
                // Atribui as calorias conforme o prato escolhido
                if (strcmp(escolhas[j].tipoPrato, "Peixe") == 0) {
                    calorias = ementas[i].caloriasPeixe;
                } else if (strcmp(escolhas[j].tipoPrato, "Carne") == 0) {
                    calorias = ementas[i].caloriasCarne;
                } else if (strcmp(escolhas[j].tipoPrato, "Dieta") == 0) {
                    calorias = ementas[i].caloriasDieta;
                } else if (strcmp(escolhas[j].tipoPrato, "Vegetariano") == 0) {
                    calorias = ementas[i].caloriasVegetariano;
                }

                // Imprime os dados na tabela
                printf("| %15s | %15s | %-5d |\n", 
                       ementas[i].diaSemana, escolhas[j].tipoPrato , calorias);
                break;  
            }
        }
    }
}
