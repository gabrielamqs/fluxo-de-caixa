#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Limpa o Buffer de Entrada
void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

// Exibe o menu de períodos
void menuPeriodos() {
  puts(" ________________");
  puts("|      MENU      |");
  puts("|----------------|");
  puts("| 1. ANUAL       |");
  puts("| 2. SEMESTRAL   |");
  puts("| 3. TRIMESTRAL  |");
  puts("| 4. BIMESTRAL   |");
  puts("| 5. MENSAL      |");
  puts("| 6. QUINZENAL   |");
  puts("| 7. SEMANAL     |");
  puts("| 8. DIÁRIO      |");
  puts("|________________|");
}

//mostra o período atual
void mostraPeriodo(int *periodo, int *i){
  switch(*periodo){
    case 1:
    printf("ANO %d\n", *i);
    break;

    case 2:
    printf("SEMESTRE %d\n", *i);
    break;

    case 3:
    printf("TRIMESTRE %d\n", *i);
    break;

    case 4:
    printf("BIMESTRE %d\n", *i);
    break;

    case 5:
    printf("MÊS %d\n", *i);
    break;

    case 6:
    printf("QUINZENA %d\n", *i);
    break;

    case 7:
    printf("SEMANA %d\n", *i);
    break;

    case 8:
    printf("DIA %d\n", *i);
    break;
  }
}

// Exibe o menu de opções
void menuOpcoes(int *periodo, int *i) {
  system("clear");
  mostraPeriodo(periodo, i);
  printf("\nQue operação gostaria de fazer no arquivo?\n");
  puts(" ");
  puts(" _____________________");
  puts("|        MENU         |");
  puts("|---------------------|");
  puts("| 1. INSERIR ENTRADA. |");
  puts("| 2. INSERIR SAÍDA.   |");
  puts("| 3. PRÓXIMO PERÍODO. |");
  puts("| 4. FECHAR PROGRAMA. |");
  puts("|_____________________|");
}

//mostra os itens existentes
void menuItens(int *quantidadeItens, int *i, int *periodo, Item item[], Totais *totais) {
  mostraPeriodo(periodo, i);
  
  printf("---------------------------------------------------------------\n");
  printf("Saldo Anterior:                                      | %.2f\n", totais->saldoAnterior);
  printf("---------------------------------------------------------------\n");
  printf("---------------------------------------------------------------\n");
  
  for (int i = 0; i < *quantidadeItens; i++) {
    printf("%-53s| %.2f\n", item[i].nome, item[i].valor);
    
    if(i == totais->quantidadeACPC - 1){
      printf("---------------------------------------------------------------\n");
      printf("(=) Saldo FC Operacional:                            | %.2f\n", totais->totalACPC);
      printf("---------------------------------------------------------------\n");
    }else if(i == (totais->quantidadeACPC + totais->quantidadeANC) - 1){
      printf("---------------------------------------------------------------\n");
      printf("(=) Saldo FC Investimento:                           | %.2f\n", totais->totalANC);
      printf("---------------------------------------------------------------\n");
  }else if(i == *quantidadeItens - 1){
      printf("---------------------------------------------------------------\n");
      printf("(=) Saldo FC Financiamento:                          | %.2f\n", totais->totalPNCPL);
      printf("---------------------------------------------------------------\n");
  }
}
  printf("---------------------------------------------------------------\n");
  printf("Saldo Incial do Período:                             | %.2f\n", totais->saldoAnterior);
  printf("Saldo do Período:                                    | %.2f\n", totais->saldoPeriodo);
  printf("Saldo Final:                                         | %.2f\n", totais->saldoFinal);
  printf("---------------------------------------------------------------\n");  
  puts(" ");
}

// Mostra o fluxo de caixa final
void mostraCaixa(int *quantidadeItens, float *saldoInicial, Item item[], Totais *totais){
  float soma = totais->finalACPC + totais->finalANC +  totais->finalPNCPL;
  printf("---------------------------------------------------------------\n");
  for (int i = 0; i < *quantidadeItens; i++) {
    printf("%-53s| %.2f\n", item[i].nome, item[i].valorTotal);

    if(i == totais->quantidadeACPC - 1){
      printf("---------------------------------------------------------------\n");
      printf("(=) Saldo FC Operacional:                            | %.2f\n", totais->finalACPC);
      printf("---------------------------------------------------------------\n");
    }else if(i == (totais->quantidadeACPC + totais->quantidadeANC) - 1){
      printf("---------------------------------------------------------------\n");
      printf("(=) Saldo FC Investimento:                           | %.2f\n", totais->finalANC);
      printf("---------------------------------------------------------------\n");
  }else if(i == *quantidadeItens - 1){
      printf("---------------------------------------------------------------\n");
      printf("(=) Saldo FC Financiamento:                          | %.2f\n", totais->finalPNCPL);
      printf("---------------------------------------------------------------\n");
  }
}
  totais->saldoPeriodo = totais->totalACPC + totais->totalANC + totais->totalPNCPL;
  totais->saldoFinal = totais->saldoAnterior + totais->saldoPeriodo;
  printf("---------------------------------------------------------------\n");
  printf("Saldo Incial do Período:                             | %.2f\n", *saldoInicial); // PERGUNTAR SOBRE ISSO
  printf("Saldo do Período:                                    | %.2f\n", soma);
  printf("Saldo Final:                                         | %.2f\n", totais->saldoFinal);
  printf("---------------------------------------------------------------\n");  
  puts(" ");
}

// Zera totais
void zerarTotais(Totais *totais) {
  totais->totalACPC = 0;
  totais->totalANC = 0;
  totais->totalPNCPL = 0;
}

// Finaliza o período e prepara para o próximo
void finalizarPeriodo(Totais *totais) {  
  totais->finalACPC += totais->totalACPC;
  totais->finalANC += totais->totalANC;
  totais->finalPNCPL += totais->totalPNCPL;
  totais->saldoPeriodo = 0;

  zerarTotais(totais);
}

// Declara os itens do fluxo de caixa
void declararNomesTiposItens(Item item[], Totais *totais){
  strcpy(item[0].nome, "(+) Recebimento de vendas");
  strcpy(item[1].nome, "(-) Salario");
  strcpy(item[2].nome, "(-) Fornecedores");
  strcpy(item[3].nome, "(-) Impostos");
  strcpy(item[4].nome, "(+) Venda de Imobilizados");
  strcpy(item[5].nome, "(-) Aquisicao de Imobilizados");
  strcpy(item[6].nome, "(+) Aquisicao de Emprestimo");
  strcpy(item[7].nome, "(-) Amortizacao de Emprestimo");
  strcpy(item[8].nome, "(+) Integralizacao de Capital");
  strcpy(item[9].nome, "(-) Pagamento de Dividendos");

  totais->quantidadeACPC = 4;
  totais->quantidadeANC = 2;
  totais->quantidadePNCPL = 4;
}

//Declara os valores e tipos dos itens do fluxo de caixa
void declararValoresTipoItens(Item item[], Totais *totais, int *quantidadeItens){
  for(int i = 0; i < *quantidadeItens; i++){
    item[i].valor = 0.0;
    if(i < totais->quantidadeACPC){
      item[i].tipo = 1;
    }else if(i >= totais->quantidadeACPC && i < (totais->quantidadeANC + totais->quantidadeACPC)) {
      item[i].tipo = 2;
    }else{
      item[i].tipo = 3;
    }
  }
}

// Switch case do menu de opções
void switchCase(int *quantidadeItens, int *periodo, int *quantidadePeriodos, Item item[], Totais *totais) {
  int opcao;
  int i = 1;
  do{
    menuOpcoes(periodo, &i);
    printf("\nEscolha uma opção: ");
    scanf("%d", &opcao);
    puts(" ");

    switch(opcao){
      case 1:
      system("clear");
      menuItens(quantidadeItens, &i, periodo, item, totais);
      inserirEntrada(quantidadeItens, item, totais);
      break;

      case 2:
      system("clear");
      menuItens(quantidadeItens, &i, periodo, item, totais);
      inserirSaida(quantidadeItens, item, totais);
      break;

      case 3:
      system("clear");
      finalizarPeriodo(totais);
      for(int k = 0; k < *quantidadeItens; k++){
        item[k].valor = 0;
      }
      totais->saldoAnterior = totais->saldoFinal;
      i++;
      break;

      case 4:
      break;
      
      default:
      system("clear");
      printf("Opção inválida.\n");
      break;
    }
    if(i - 1 == *quantidadePeriodos){
      opcao = 4;
    }
  }while (opcao != 4);
}

// Função para normalizar nomes de itens
void normalizeItemName(char *str){
  char temp[50];
  int j = 0;
  
  // Ignora caracteres até encontrar uma letra
  for (int i = 0; str[i]; i++) {
    if (isalpha(str[i])) {  // Inicia a cópia quando encontra uma letra
      temp[j++] = tolower(str[i]);  // Copia apenas letras e as converte para minúsculas
    }
  }
  temp[j] = '\0';  // Termina a string temporária
  strcpy(str, temp);  // Copia de volta para a string original
}


//insere entrada no fluxo de caixa
void inserirEntrada(int *quantidadeItens, Item *item, Totais *totais) {
  char nome[50];
  float valor;

  puts(" --------------------------");
  puts("|     INSERIR ENTRADA      |");
  puts(" --------------------------");

  printf("Informe o nome do item (ou digite '0' para voltar): ");
  scanf(" %[^\n]%*c", nome); // Lê a linha inteira até o newline

  // Verifica se o usuário deseja voltar
  if (strcmp(nome, "0") == 0) {
    system("clear");
    return; // Retorna para o menu anterior
  }
  zerarTotais(totais);
  normalizeItemName(nome);
  printf("Informe o valor do item: ");
  scanf("%f", &valor);
  limparBufferEntrada();
  
  for (int i = 0; i < *quantidadeItens; i++) {
    char itemNome[50];
    strcpy(itemNome, item[i].nome); // Copia o nome do item para uma variável temporária
    normalizeItemName(itemNome); // Normaliza o nome do item

    if (strcmp(itemNome, nome) == 0) {
      item[i].valor = valor;
      item[i].valorTotal += item[i].valor;
    }
    if (item[i].tipo == 1) {
      totais->totalACPC += item[i].valor;
    } else if (item[i].tipo == 2) {
      totais->totalANC += item[i].valor;
    } else if (item[i].tipo == 3) {
      totais->totalPNCPL += item[i].valor;
    }
  }
  totais->saldoPeriodo = totais->totalACPC + totais->totalANC + totais->totalPNCPL;
  totais->saldoFinal = totais->saldoAnterior + totais->saldoPeriodo;
  system("clear");
  printf("Entrada inserida com sucesso!\n");
}

//insere saída no fluxo de caixa
void inserirSaida(int *quantidadeItens, Item *item, Totais *totais){
  char nome[50];
  float valor;

  puts(" --------------------------");
  puts("|      INSERIR SAÍDA      |");
  puts(" --------------------------");

  printf("Informe o nome do item (ou digite '0' para voltar): ");
  scanf(" %[^\n]%*c", nome); // Lê a linha inteira até o newline

  // Verifica se o usuário deseja voltar
  if (strcmp(nome, "0") == 0) {
    system("clear");
    return;
  }
  zerarTotais(totais);
  normalizeItemName(nome);
  printf("Informe o valor do item: ");
  scanf("%f", &valor);
  limparBufferEntrada();

  for (int i = 0; i < *quantidadeItens; i++) {
    char itemNome[50];
    strcpy(itemNome, item[i].nome); // Copia o nome do item para uma variável temporária
    normalizeItemName(itemNome); // Normaliza o nome do item

    if (strcmp(itemNome, nome) == 0) {
      item[i].valor = -valor;
      item[i].valorTotal += (item[i].valor * -1);
    }
    if (item[i].tipo == 1) {
      totais->totalACPC += item[i].valor;
    } else if (item[i].tipo == 2) {
      totais->totalANC += item[i].valor;
    } else if (item[i].tipo == 3) {
      totais->totalPNCPL += item[i].valor;
    }
  }
  totais->saldoPeriodo = totais->totalACPC + totais->totalANC + totais->totalPNCPL;
  totais->saldoFinal = totais->saldoAnterior + totais->saldoPeriodo;
  system("clear");
  printf("Entrada inserida com sucesso!\n");
}
