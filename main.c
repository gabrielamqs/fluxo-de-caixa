#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

int main(void) {
  int periodo;
  float saldoInicial;
  int quantidadePeriodos;
  int quantidadeItens = 10;
  Item item[MAX];
  Totais totais;

  totais.finalACPC = 0;
  totais.finalANC = 0;
  totais.finalPNCPL = 0;
  for(int i = 0; i < quantidadeItens; i++){
  item[i].valorTotal = 0;  
  }

  menuPeriodos();
  printf("\nEscolha uma opção: ");
  scanf("%d", &periodo); 
  printf("\nInforme o número de períodos: ");
  scanf("%d", &quantidadePeriodos);
  puts(" ");
  printf("Informe o valor do saldo anterior: ");
  scanf("%f", &totais.saldoAnterior);
  saldoInicial = totais.saldoAnterior;
  system("clear");
  

  declararNomesTiposItens(item, &totais);
  declararValoresTipoItens(item, &totais, &quantidadeItens);
  switchCase(&quantidadeItens, &periodo, &quantidadePeriodos, item, &totais);
  mostraCaixa(&quantidadeItens, &saldoInicial, item, &totais);
  
  
  return 0;
}