#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tcarro {

  char nome[50];
  int placa;
  char cor[15];
  char modelo[30];
};
struct Tcarro addCarro();

void tamanhoFila(int *tamanho_fila);
void valorDoCombustivel(float *pregaso);
void totalDeCombustivel(float *gasolina_bomba);
void imprimir(struct Tcarro vetor[], int tamanho_fila, FILE *f);
void flush_in();
void gasolinaAbastecida(float gasolina_total);
int arquivotxt(float gasolina_total, float preco_total, int carros_atendidos,
               float gasolina_bomba, int tamanho_fila, int filan,
               struct Tcarro filaAtendidos[], struct Tcarro filaEspera[]);
void montanteArrecadado(float preco_total);
void quantidadeDeCombustivel(float gasolina_bomba);