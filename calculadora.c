#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <stdlib.h>
#include <unistd.h> // Para a função sleep()



struct calculadora {
    char historico[100][100]; 
    int historicoIndex;           
};

void adicionarAoHistorico(struct calculadora *calc, char *expressao, int resultado) {
    if (calc->historicoIndex < 100) {
        snprintf(calc->historico[calc->historicoIndex], sizeof(calc->historico[calc->historicoIndex]), 
                 "%s = %d", expressao, resultado);
        calc->historicoIndex++;
    } else {
        printf("Histórico cheio! Não foi possível salvar o cálculo.\n");
    }
}

void mostrarHistorico(struct calculadora *calc) {
    if (calc->historicoIndex == 0) {
        printf("O histórico está vazio.\n");
    } else {
        printf("\nHistórico de cálculos:\n");
        for (int i = 0; i < calc->historicoIndex; i++) {
            printf("%d: %s\n", i + 1, calc->historico[i]);
        }
    }
}

void Limpar() {
    for (int i = 2; i > 0; i--) {
        fflush(stdout); 
        sleep(1);     
    }
    system("clear");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    struct calculadora calc = {{0}, 0}; // Inicializa a estrutura com o histórico vazio
    char expr[100];
    int opcao;
           
    do {
             printf("################################A vida é dura calculadora################################\n");
             printf("\t\t\t\tSIXX THE CREATOR\n");
        printf("\nMenu da Calculadora:\n");
        printf("1 - Fazer um cálculo\n");
        printf("2 - Mostrar histórico\n");
        printf("3 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 
           
              
        if (opcao == 1) {
            printf("Informe o cálculo: ");
            fgets(expr, sizeof(expr), stdin);
                fflush(stdin);
            expr[strcspn(expr, "\n")] = '\0'; 
            
            int nums[12], numIndex = 0;
            char ops[11];
            int opIndex = 0;
            int num = 0;

            for (int i = 0; i < strlen(expr); i++) {
                if (isdigit(expr[i])) {
                    num = num * 10 + (expr[i] - '0');
                } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
                    nums[numIndex++] = num;
                    num = 0;
                    ops[opIndex++] = expr[i];
                }else{
                    printf("\nErro: Foram inseridas letras na expressão.Tente Novamente!.\n");
                      goto end_calculation; 
                }
            }
               if (numIndex > 12 || opIndex > 11)
                    {
                        printf("\nErro: O número de operandos ou operadores é superior ao permitido!\n");
                        goto end_calculation; 
                    }

            nums[numIndex++] = num; // número armazenado nesta vector

            for (int i = 0; i < opIndex; i++) {
                if (ops[i] == '*') {
                    nums[i] = nums[i] * nums[i + 1];
                    for (int j = i + 1; j < numIndex - 1; j++) {
                        nums[j] = nums[j + 1];
                    }
                    for (int j = i; j < opIndex - 1; j++) {
                        ops[j] = ops[j + 1];
                    }
                    numIndex--;
                    opIndex--;
                    i--;
                } else if (ops[i] == '/') {
                    if (nums[i + 1] == 0) { 
                        printf("Erro:Divisão por zero não é possível!.\n");
                        goto end_calculation; 
                    }
                    nums[i] = nums[i] / nums[i + 1];
                    for (int j = i + 1; j < numIndex - 1; j++) {
                        nums[j] = nums[j + 1];
                    }
                    for (int j = i; j < opIndex - 1; j++) {
                        ops[j] = ops[j + 1];
                    }
                    numIndex--;
                    opIndex--;
                    i--;
                }
            }
            int res = nums[0];
            for (int i = 0; i < opIndex; i++) {
                if (ops[i] == '+') {
                    res += nums[i + 1];
                } else if (ops[i] == '-') {
                    res -= nums[i + 1];
                }
            }
                Limpar();
            printf("Resultado: %d\n", res);
            adicionarAoHistorico(&calc, expr, res); 
        } else if (opcao == 2) {
            Limpar();
            mostrarHistorico(&calc);
        } else if (opcao == 3) {
            Limpar();
            printf("Saindo do programa. A Vida é dura Jovem!!!\n");
        } else {
            Limpar();
            printf("Opção inválida! Tente novamente.\n");
        }
        end_calculation:
            ;
                printf("\tSIXX THE CREATOR\n");
                    Limpar();
    } while (opcao != 3);

    return 0;

    
}
