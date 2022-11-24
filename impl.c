
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


#define BLUE "\e[0;34m"
#define RED "\e[0;31m"
#define WHITE "\e[0;37m"
#define CYAN "\e[0;36m"
#define YELLOW "\e[0;33m"
#define GREEN "\e[0;32m"
#define MAG   "\x1B[35m"


// Adicionar carro


struct Tcarro addCarro() {
  struct Tcarro aux; // definindo uma variável
  getchar();
  printf(YELLOW"\nNome do cliente: \n"WHITE);
  fgets(aux.nome, 50, stdin);
  aux.nome[strcspn(aux.nome, "\n")] = 0;
  printf(YELLOW"\nPlaca do veículo: \n"WHITE);
  scanf("%d", &aux.placa);
  flush_in();
  printf(YELLOW"\nCor do veículo: \n"WHITE);
  fgets(aux.cor, 20, stdin);
  aux.cor[strcspn(aux.cor, "\n")] = 0;
  printf(YELLOW"\nModelo do veículo\n"WHITE);
  fgets(aux.modelo, 30, stdin);
  aux.modelo[strcspn(aux.modelo, "\n")] = 0;

  return aux;
}



// imprimir as infos dos carros

void imprimir(struct Tcarro vetor[], int tamanho_fila, FILE *f) {
  for (int cont = 0; cont < tamanho_fila; cont++) {
    fprintf(f, "\nNome: %s", vetor[cont].nome);
    fprintf(f, "\nPlaca: %d", vetor[cont].placa);
    fprintf(f, "\nCor: %s", vetor[cont].cor);
    fprintf(f, "\nModelo: %s\n", vetor[cont].modelo);
  }
}


void flush_in() { // LIMPA BUFFER 
  int ch;
  while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
  }
}

void valorDoCombustivel(float *pregaso) {
  while (*pregaso <= 0) {

    printf(
           YELLOW"\nInforme o valor do combustível (favor, no lugar de VÍRGULAS, usar o PONTO FINAL): "WHITE);
    scanf("%f", &*pregaso);
    system("clear");
    if (*pregaso <= 0) {
      system("clear");
      printf(RED "\nValor não aceito.\n\n" WHITE);
      getchar();
    }
  }
  fflush(stdin);
}

// Tamanho limite da fila

void tamanhoFila(int *tamanho_fila) {
  while (*tamanho_fila <= 0) {

    printf(YELLOW"Informe o tamanho máximo da fila: "WHITE);
    scanf("%d", *&tamanho_fila);
    system("clear");
    if (*tamanho_fila <= 0) {
      system("clear");
      printf(RED "\nValor não aceito.\n\n" WHITE);
      getchar();
    }
  }
  fflush(stdin);
}

// total de combustivel

void totalDeCombustivel(float *gasolina_bomba) {
  while (*gasolina_bomba <= 0) {
    printf(YELLOW"Informe o total de litros de combustível(usar PONTO FINAL, não VÍRGULA): "WHITE);
    scanf("%f", &*gasolina_bomba);
    system("clear");
    if (*gasolina_bomba <= 0) {
      system("clear");
      printf(RED "\nValor não aceito.\n\n" WHITE);
      getchar();
    }
  }
  fflush(stdin);
}

// Arquivo txt (Submenu case 5)


int arquivotxt(float gasolina_total, float preco_total, int carros_atendidos,
               float gasolina_bomba, int tamanho_fila, int fila,
               struct Tcarro filaAtendidos[], struct Tcarro filaEspera[]) {

  FILE *txt;

  txt = fopen("relatorio.txt", "w");
  if (txt == NULL) {
    printf("não foi possível criar arquivo de relatório");

    return 1;
  }

  fprintf(txt, "\n\n-----ARQUIVO IMPRESSO COM INFORMAÇÕES-----\n\n");


  fprintf(txt, "\nQuantidade de litros vendidos: %.1f\n", gasolina_total);
  fprintf(txt, "Montante total arrecadado com as vendas: %.1f\n", preco_total);
  fprintf(txt, "Quantidade de carros atendidos: %d\n", carros_atendidos);
  fprintf(txt, "Quantidade de carros na fila: %d\n", fila);
  fprintf(txt, "Quantidade de combustível restante: %.1f\n", gasolina_bomba);
  fprintf(txt, "Capacidade máxima de carros que a fila suporta: %d\n",
          tamanho_fila);

  fprintf(txt, "\n===================================================\n");
  
  fprintf(txt, "\nLISTA CARROS ATENDIDOS\n");
  
  imprimir(filaAtendidos, carros_atendidos, txt);

  fprintf(txt, "\n===================================================\n");

  fprintf(txt, "\nLISTA CARROS EM ESPERA\n");

  imprimir(filaEspera, fila, txt);
  
  

  fclose(txt);

return 0;
}


void gasolinaAbastecida(float gasolina_total){
          printf("\nQuantidade em litros vendidas: %.1f\n", gasolina_total);
  }

void montanteArrecadado(float preco_total){
  printf("\nMontante total arrecadado com as vendas: %.1f\n", preco_total);
}

void quantidadeDeCombustivel(float gasolina_bomba){
printf("\nQuantidade de combustível restante: %.1f\n",
                 gasolina_bomba);
  }