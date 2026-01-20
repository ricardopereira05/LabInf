#define FUNCOES_H

#define MAX_FUNCIONARIOS 200 // Número máximo de funcionários
#define MAX_ESCOLHAS 200 // Número máximo de refeições

/**
 * @brief  Estrutura para armazenar os dados dos funcionários
 * 
 */
typedef struct {
    
    int numero;
    char nome[100];
    char nif[15];
    char telefone[15];
} Funcionario;

/**
 * @brief  Estrutura para armazenar os dados das ementas
 * 
 */
typedef struct {
    char diaSemana[10];
    char data[12];
    char pratoPeixe[50];
    int caloriasPeixe;
    char pratoCarne[50];
    int caloriasCarne;
    char pratoDieta[50];
    int caloriasDieta;
    char pratoVegetariano[50];
    int caloriasVegetariano;
} Ementa;

/**
 * @brief  Estrutura para armazenar as escolhas
 * 
 */
typedef struct {
    char diaSemana[20];
    int numeroFuncionario;
    char tipoPrato[20];
} Escolha;

// Declarar as funções que serão usadas
int carregarFuncionarios(char* nomeFicheiro, Funcionario funcionario[]);
int carregarEmenta(char* nomeficheiro, Ementa ementas[]);
int carregarEscolhas(char* nomeficheiro, Escolha escolhas[]);
void carregarFuncionariosBin(const char *nomeFicheiro, Funcionario *funcionarios, int *totalFuncionarios);
void carregarEmentasBin(const char *nomeFicheiro, Ementa *ementas, int *totalEmentas);
void carregarEscolhasBin(const char *nomeFicheiro, Escolha *escolhas, int *totalEscolhas);
void carregarFuncionariosTab(const char *nomeFicheiro, Funcionario *funcionarios, int *totalFuncionarios);
void carregarEmentasTab(const char *nomeFicheiro, Ementa *ementas, int *totalEmentas);
void carregarEscolhasTab(const char *nomeFicheiro, Escolha *escolhas, int *totalEscolhas);
void listarRefeicoesDia(Escolha* escolhas, int totalEscolhas, Funcionario* funcionarios, int totalFuncionarios, const char* diaSemana);
void listarUtentesOrdemDecrescente(Escolha* escolhas, int totalEscolhas, Funcionario* funcionarios, int totalFuncionarios);
void listarRefeicoesUtente(Escolha* escolhas, int totalEscolhas, Ementa* ementas, int totalFuncionarios, int totalEmentas);
void calcularMediaCaloriasEspaco (Ementa* ementas, int totalEmentas, Escolha* escolhas, int totalEscolhas, char* diainicio, char* diafim);
void gerarTabelaEmentaUtente(Escolha* escolhas, int totalEscolhas, Ementa* ementas, int totalEmentas, int numeroFuncionario);
void mostrarAjuda();
void menu();