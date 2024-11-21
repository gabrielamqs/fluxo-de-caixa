typedef struct Item{
  char nome[50];
  int tipo;
  float valor;
  float valorTotal;
}Item;


typedef struct Totais{
  float saldoAnterior;
  float saldoPeriodo;
  float saldoFinal;

  float totalACPC;
  float totalANC;
  float totalPNCPL;

  float finalACPC;
  float finalANC;
  float finalPNCPL;

  int quantidadeACPC;
  int quantidadeANC;
  int quantidadePNCPL;
}Totais;

void menuPeriodos();
void menuOpcoes(int *periodo, int *i);
void menuItens(int *quantidadeItens, int *i, int *periodo, Item item[], Totais *totais);
void mostraCaixa(int *quantidadeItens, float *saldoInicial, Item item[], Totais *totais);
void switchCase(int *quantidadeItens, int *periodo, int *quantidadePeriodos, Item item[], Totais *totais);
void declararNomesTiposItens(Item item[], Totais *totais);
void declararValoresTipoItens(Item item[], Totais *totais, int *quantidadeItens);
void limparBufferEntrada();
void zerarTotais(Totais *totais);
void zerarItens(Item item[]);
void mostraPeriodo(int *periodo, int *i);
void finalizarPeriodo(Totais *totais);

void inserirEntrada(int *quantidadeItens, Item *item, Totais *totais);
void inserirSaida(int *quantidadeItens, Item *item, Totais *totais);