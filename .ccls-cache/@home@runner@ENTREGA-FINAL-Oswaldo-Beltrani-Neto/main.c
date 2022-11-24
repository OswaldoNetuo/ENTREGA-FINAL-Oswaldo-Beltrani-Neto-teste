// bibliotecas e definições

#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLUE "\e[0;34m"
#define RED "\e[0;31m"
#define WHITE "\e[0;37m"
#define CYAN "\e[0;36m"
#define YELLOW "\e[0;33m"
#define GREEN "\e[0;32m"
#define MAG "\x1B[35m"


int main() {

  // definição de variáveis

  float preco_gasolina = 0, gasolina_bomba = 0, preco_abastecimento = 0, aux,
        aux2;
  int tamanho_fila = 0, menu, submenu = 0, j = 0;
  int fila = 0, carros_atendidos = 0;
  float gasolina_carro, gasolina_total = 0, preco_total = 0;
  struct Tcarro *filaEspera, *filaAtendidos;
  int sair;
  // Enunciado do programa

  printf(BLUE "Osvaldo Beltrame Neto RA:2485990\n\n");
  printf("Este programa faz o gerenciamento de um posto de combustível, ele "
         "tem as funções de fila, gerenciamento de quantidade restante de "
         "combustível e fazer relatórios.\n" WHITE);

  // Valor do combustível

  valorDoCombustivel(&preco_gasolina);

  // Tamanho da fila

  tamanhoFila(&tamanho_fila);

  // alocação dinâmica

  filaEspera = (struct Tcarro *)malloc(tamanho_fila * sizeof(struct Tcarro));
  filaAtendidos = (struct Tcarro *)malloc(1 * sizeof(struct Tcarro));

  // total de combustivel

  totalDeCombustivel(&gasolina_bomba);

  // infos printadas fornecidas pelo usuário
  system("clear");
  printf("\nO valor do combustível é: %.2f\n", preco_gasolina);
  printf("\nO número máximo de carros na fila é: %d\n", tamanho_fila);
  printf("\nQuantia de combustível na bomba: %.1f\n", gasolina_bomba);
  printf(GREEN "\nInicialização completa\n\n" WHITE);
  // MENU

  while (menu != 6) {

    printf(RED "\n============================================================="
               "========\n" WHITE);
    printf(MAG "\n\n----MENU PRINCIPAL DO PROGRAMA----\n\n" WHITE);
    printf("(1) Adicionar um carro a fila\n" WHITE);
    printf("(2) Abastecimento\n");
    printf("(3) Exibir lista de espera com informações dos carros\n");
    printf("(4) Relatório\n");
    printf("(5) Abastecer o posto de gasolina\n");
    printf("(6) Encerrar\n\n\n");
    printf("\n");
    printf(YELLOW "Digite o número referente a sua escolha: " WHITE);

    scanf("%d", &menu);

    // Opções do menu

    switch (menu) {

      // Adicionar carro a fila

    case 1:
      system("clear");
      if (gasolina_bomba == 0) {
        printf(RED "Não é possível adicionar um carro a fila enquanto a "
                   "bomba de combustível estiver vazia\n");

      } else if (tamanho_fila == fila) {
        printf(RED "\nNúmero limite da fila atingido, favor escolher outra "
                   "ação." WHITE);
      } else if (tamanho_fila != fila) {
        printf("\nNúmero de carros na fila de abastecimento: %d\n",
               fila);
        filaEspera[fila] = addCarro();
        fila = fila + 1;
        printf(GREEN "\nCarro adicionado a fila de abastecimento.\n" WHITE);
        printf("");
      }
      break;

      // Abastecimento

    case 2:
      system("clear");
      printf(YELLOW "\nInforme quantos litros gostaria de abastecer: " WHITE);
      scanf("%f", &gasolina_carro);
      if (fila == 0) {
        printf(RED "\nNenhum carro na fila de abastecimento, favor adicionar "
                   "para prosseguir o processo.\n\n" WHITE);
      } else if ((gasolina_bomba > 0) && (gasolina_carro > 0)) {
        if (gasolina_bomba >= gasolina_carro) {

          // Alocação dinâmica

          filaAtendidos = (struct Tcarro *)realloc(
              filaAtendidos, (carros_atendidos + 1) * sizeof(struct Tcarro));

          // Abastecimento do carro, retirada do combustível na bomba, preço e
          // etc.

          filaAtendidos[carros_atendidos] = filaEspera[0];
          carros_atendidos = carros_atendidos + 1;
          fila -= 1;
          gasolina_bomba -= gasolina_carro;
          gasolina_total = gasolina_carro + gasolina_total;
          preco_abastecimento = gasolina_carro * preco_gasolina;
          preco_total = preco_abastecimento + preco_total;

          for (j = 0; j < fila; j++) {
            filaEspera[j] = filaEspera[j + 1];
          }
          printf(GREEN "\nO carro foi abastecido!\n" WHITE);
          printf("\nPreço do abastecimento: %.1f\n", preco_abastecimento);
          printf(
              "\nQuantia de combustível restante na bomba do posto: %.1f\n\n",
              gasolina_bomba);

          // Caso não tenha combustível suficiênte na bomba

        } else {
          printf(
              RED
              "\nNão há combustível suficiênte para abastecer esta quantia no "
              "momento \na bomba se encontra com: %.1f de gasolina." WHITE,
              gasolina_bomba);
          printf(
              
              "\n\nCaso queira abastecer, repita o processo com este "
              "valor ou abasteça o posto. \nAbastecer o posto se encontra no "
              "Menu principal, opção 5.");
          printf(YELLOW"\n\nGostaria de sair da fila? para sim use '1' e para não, "
                 "use '2'.\n"WHITE);
          scanf("%d", &sair);
          if (sair == 1) {
            printf(RED "O carro foi retirado da fila" WHITE);

            for (j = 0; j < fila; j++) {
              filaEspera[j] = filaEspera[j + 1];
            }
            fila = fila - 1;
            

          } if (sair == 2){
            printf(GREEN"O carro foi mantido na fila"WHITE);
            }
          if ((sair =! 1) && (sair =!2)){
          printf(RED"Valor inválido, tente novamente"WHITE);
          }
        }
      }

      // Caso não haja combustível no posto

      if (gasolina_bomba == 0) {
        if (fila != 0) {
          printf(RED "Estamos sem gasolina no momento, TODOS os carros na fila "
                     "serão "
                     "DISPENSADOS." WHITE);
          fila = 0;
        }
      }

      break;

      // Lista de espera com info dos carros

    case 3:
      system("clear");
      printf("\nCarros suportados na fila de abastecimento: %d\n",
             tamanho_fila);
      printf("\nSituação atual da fila: %d\n", fila);
      

      printf(CYAN"\nNÚMERO DE CARROS NA FILA DE ABASTECIMENTO: %d\n" WHITE, fila);
          imprimir(filaEspera, fila, stdout);
      break;  

      // Submenu

    case 4:
      system("clear");
      while (submenu != 6) {
        printf(RED "\n========================================================="
                   "============\n" WHITE);
        printf(BLUE "\n----MENU DO RELATÓRIO----\n\n" WHITE);
        printf("(1) Quantidade em litros vendidas\n");
        printf("(2) Montante total arrecadado com as vendas\n");
        printf("(3) Quantidade de carros atendidos e na fila de espera\n");
        printf("(4) Quantidade de combustível restante\n");
        printf("(5) Gerar um arquivo impresso com todas as informações "
               "(1,2,3,4)\n");
        printf("(6) Voltar para o Menu anterior\n\n");

        printf(YELLOW "Digite o número referente a sua escolha: " WHITE);
        scanf("%d" WHITE, &submenu);

        switch (submenu) {

          // Litros vendidos

        case 1:
          system("clear");
          gasolinaAbastecida(gasolina_total);
          break;

          // Dinheiro resultante

        case 2:
          system("clear");
          montanteArrecadado(preco_total);
          break;

          // Quantidade de carros atendidos

        case 3:
          system("clear");

          printf(RED "Numero de carros na fila de espera: %d\n" WHITE, fila);
          imprimir(filaEspera, fila, stdout);

          printf(GREEN "\nNumero de carros atendidos: %d\n" WHITE,
                 carros_atendidos);
          imprimir(filaAtendidos, carros_atendidos, stdout);

          break;

          // Combustível restante no posto

        case 4:
          system("clear");
          quantidadeDeCombustivel(gasolina_bomba);
          break;

          // Arquivo impresso

        case 5:
          system("clear");
          printf(MAG"\nGERANDO UM ARQUIVO IMPRESSO COM AS INFORMAÇÕES!: \n" WHITE);
          gasolinaAbastecida(gasolina_total);
          montanteArrecadado(preco_total);
          printf("\nQUANTIDADE DE CARROS ATENDIDOS: %d\n",
                 carros_atendidos);
          quantidadeDeCombustivel(gasolina_bomba);

          printf(RED "\nCARROS ATUALMENTE NA FILA DE ESPERA\n" WHITE);

          imprimir(filaEspera, fila, stdout);

          printf(GREEN"\nCarros atendidos\n" WHITE);

          imprimir(filaAtendidos, carros_atendidos, stdout);

          arquivotxt(gasolina_total, preco_total, carros_atendidos,
                     gasolina_bomba, tamanho_fila, fila, filaAtendidos,
                     filaEspera);

          // Voltar para o Menu

          break;
        case 6:
          system("clear");
          printf(
              YELLOW
              "\nVoltar para menu anterior (aperte qualquer número)\n" WHITE);
          break;

          // Opções inválidas

        default:
          system("clear");
          printf(RED
                 "\nOpção invalida, favor digitar um valor válido.\n" WHITE);
        }
      }
      submenu = 0;
      getchar();
      system("clear");
      break;

      // Abastecer o posto (letras passam, arrumar isso)

    case 5:
      aux = gasolina_bomba;

      printf("quantidade de combustível na bomba do posto antes do "
                    "abastecimento: %.1f\n",
             gasolina_bomba);
      printf(YELLOW
             "Informe o total de litros de combustível a ser "
             "adicionado ao posto\n(usar PONTO FINAL no lugar de VÍRGULA): "WHITE);
      scanf("%f", &aux2);

      if (aux2 > 0) {

        system("clear");
        gasolina_bomba = gasolina_bomba + aux2;
        printf(GREEN "Posto abastecido!" WHITE);
        printf( "\nquantidade de combustivel na bomba do posto após o "
                     "abastecimento: %.1f\n",
               gasolina_bomba);

      } else {
        system("clear");
        printf(RED "\nValor inválido, favor digitar valor válido.\n" WHITE);

        getchar();
      }

      break;

      // Encerrar o programa

    case 6:
      system("clear");
      printf("O programa vai ser encerrado.\n");

      break;
    default:
      system("clear");
      printf(RED "\nOpção invalida, favor digitar um valor válido." WHITE);
      break;
    }
  }

  return 0;
}
