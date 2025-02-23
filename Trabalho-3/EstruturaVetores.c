#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10
#define ARQUIVO "dados.txt"

#include "EstruturaVetores.h"

typedef struct {
  int *vetor;
  int posicao;
  int tamanho;
} estrutura;

estrutura vetorPrincipal[TAM];

void insertionSort(int vetor[], int vetorAux[], int size) {
  for (int i = 0; i < size; i++) {
    vetorAux[i] = vetor[i];
  }

  for (int i = 1; i < size; i++) {
    int key = vetorAux[i];
    int j = i - 1;
    while (j >= 0 && vetorAux[j] > key) {
      vetorAux[j + 1] = vetorAux[j];
      j--;
    }

    vetorAux[++j] = key;
  }
}

int organizarCabecote(int valor, No **cabecote) {
  No *novoCabecote = (No *)malloc(sizeof(No));

  if (novoCabecote == NULL) {
    return 0;
  }

  novoCabecote->conteudo = valor;
  novoCabecote->prox = NULL;

  (*cabecote)->prox = novoCabecote;
  *cabecote = novoCabecote;
  return 1;
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
  SUCESSO - criado com sucesso
  JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
  POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
  SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
  TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho) {
  posicao -= 1;

  if (posicao >= TAM || posicao < 0) {
    // se posição é um valor válido {entre 1 e 10}
    return POSICAO_INVALIDA;
  }

  if (tamanho < 1) {
    // o tamanho nao pode ser menor que 1
    return TAMANHO_INVALIDO;
  }

  if (vetorPrincipal[posicao].vetor != NULL) {
    // a posicao pode já existir estrutura auxiliar
    return JA_TEM_ESTRUTURA_AUXILIAR;
  }

  vetorPrincipal[posicao].vetor = malloc(sizeof(int) * tamanho);
  if (vetorPrincipal[posicao].vetor == NULL) {
    // o tamanho ser muito grande
    return SEM_ESPACO_DE_MEMORIA;
  }

  vetorPrincipal[posicao].posicao = 0;
  vetorPrincipal[posicao].tamanho = tamanho;

  // deu tudo certo, crie
  return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
  SUCESSO - inserido com sucesso
  SEM_ESPACO - não tem espaço
  SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
  POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor) {
  posicao -= 1;

  if (posicao >= TAM || posicao < 0)
    return POSICAO_INVALIDA;

  else {
    // testar se existe a estrutura auxiliar
    if (vetorPrincipal[posicao].vetor != NULL) {

      if (vetorPrincipal[posicao].posicao < vetorPrincipal[posicao].tamanho) {
        vetorPrincipal[posicao].vetor[vetorPrincipal[posicao].posicao++] =
            valor;

        return SUCESSO;
      }

      else {
        return SEM_ESPACO;
      }
    } else {
      return SEM_ESTRUTURA_AUXILIAR;
    }
  }
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar
da seguinte forma [3, 8, 7,  ,  ,  ]. Obs. Esta é uma exclusão lógica

Rertono (int)
  SUCESSO - excluido com sucesso
  ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
  SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
  POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao) {
  posicao -= 1;

  if (posicao >= TAM || posicao < 0) {
    return POSICAO_INVALIDA;
  }

  if (vetorPrincipal[posicao].vetor == NULL) {
    return SEM_ESTRUTURA_AUXILIAR;
  }

  if (vetorPrincipal[posicao].posicao == 0) {
    return ESTRUTURA_AUXILIAR_VAZIA;
  }

  vetorPrincipal[posicao].posicao--;
  return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições
anteriores ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o
valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ] Obs. Esta é
uma exclusão lógica Rertono (int) SUCESSO - excluido com sucesso 'valor' da
estrutura na posição 'posicao' ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
  SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
  NUMERO_INEXISTENTE - Número não existe
  POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
  posicao -= 1;

  if (posicao >= TAM || posicao < 0) {
    return POSICAO_INVALIDA;
  }

  if (vetorPrincipal[posicao].vetor == NULL) {
    return SEM_ESTRUTURA_AUXILIAR;
  }

  else {
    if (vetorPrincipal[posicao].posicao == 0) {
      return ESTRUTURA_AUXILIAR_VAZIA;
    }

    else {
      for (int i = 0; i < vetorPrincipal[posicao].posicao; i++) {
        if (valor == vetorPrincipal[posicao].vetor[i]) {
          for (int j = i + 1; j < vetorPrincipal[posicao].posicao; j++) {
            vetorPrincipal[posicao].vetor[i] = vetorPrincipal[posicao].vetor[j];
          }
          vetorPrincipal[posicao].posicao--;
          return SUCESSO;
        }

        else {
          return NUMERO_INEXISTENTE;
        }
      }
    }
  }
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao) {
  int retorno = 0;
  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
  } else
    retorno = SUCESSO;

  return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
  SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
  SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
  POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
  posicao -= 1;

  if (posicao >= TAM || posicao < 0) {
    return POSICAO_INVALIDA;
  }

  if (vetorPrincipal[posicao].vetor == NULL) {
    return SEM_ESTRUTURA_AUXILIAR;
  } else {
    for (int i = 0; i < vetorPrincipal[posicao].posicao; i++) {
      vetorAux[i] = vetorPrincipal[posicao].vetor[i];
    }
    return SUCESSO;
  }
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao
(1..10)'. os números devem ser armazenados em vetorAux

Rertono (int)
  SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao
(1..10)' SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar POSICAO_INVALIDA -
Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
  posicao -= 1;

  if (posicao >= TAM || posicao < 0) {
    return POSICAO_INVALIDA;
  }

  if (vetorPrincipal[posicao].vetor == NULL) {
    return SEM_ESTRUTURA_AUXILIAR;
  }

  else {
    insertionSort(vetorPrincipal[posicao].vetor, vetorAux,
                  vetorPrincipal[posicao].posicao);
    return SUCESSO;
  }
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
  SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
  TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão
vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
  int vazio = 1;
  int contador = 0;

  for (int i = 0; i < TAM; i++) {
    if (vetorPrincipal[i].vetor != NULL) {
      for (int j = 0; j < vetorPrincipal[i].posicao; j++) {
        vetorAux[contador] = vetorPrincipal[i].vetor[j];
        contador++;
        vazio = 0;
      }
    }
  }
  if (vazio == 1) {
    return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  }

  return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
  SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
  TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão
vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
  int vazio = 1;
  int contador = 0;

  for (int i = 0; i < TAM; i++) {
    if (vetorPrincipal[i].vetor != NULL) {
      for (int j = 0; j < vetorPrincipal[i].posicao; j++) {
        vetorAux[contador] = vetorPrincipal[i].vetor[j];
        contador++;
        vazio = 0;
      }
    }
  }

  if (vazio == 1) {
    return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  } else {
    insertionSort(vetorAux, vetorAux, contador);
    return SUCESSO;
  }
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o
novo tamanho 'novoTamanho' + tamanho atual Suponha o tamanho inicial = x, e novo
tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser
sempre >= 1

Rertono (int)
  SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
  SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
  POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
  NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
  SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
  posicao -= 1;

  if (posicao >= TAM || posicao < 0) {
    return POSICAO_INVALIDA;
  }

  if (vetorPrincipal[posicao].vetor == NULL) {
    return SEM_ESTRUTURA_AUXILIAR;
  }

  int tamanhoTotal = novoTamanho + vetorPrincipal[posicao].tamanho;
  if (tamanhoTotal < 1) {
    return NOVO_TAMANHO_INVALIDO;
  }

  int *vetorAtualizado =
      realloc(vetorPrincipal[posicao].vetor, sizeof(int) * tamanhoTotal);
  if (vetorAtualizado == NULL) {
    return SEM_ESPACO_DE_MEMORIA;
  }

  vetorPrincipal[posicao].tamanho = tamanhoTotal;
  vetorPrincipal[posicao].vetor = vetorAtualizado;

  while (vetorPrincipal[posicao].posicao > vetorPrincipal[posicao].tamanho) {
    vetorPrincipal[posicao].posicao--;
  }

  return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da
posição 'posicao'.

Retorno (int)
  POSICAO_INVALIDA - posição inválida
  SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
  ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
  Um número int > 0 correpondente a quantidade de elementos preenchidos da
estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
  posicao -= 1;

  if (posicao >= TAM || posicao < 0) {
    return POSICAO_INVALIDA;
  }

  if (vetorPrincipal[posicao].vetor == NULL) {
    return SEM_ESTRUTURA_AUXILIAR;
  } else {
    if (vetorPrincipal[posicao].posicao == 0) {
      return ESTRUTURA_AUXILIAR_VAZIA;
    } else {
      return vetorPrincipal[posicao].posicao;
    }
  }
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes
em todas as estruturas.

Retorno (No*)
  NULL, caso não tenha nenhum número nas listas
  No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote() {
  No *cabecote = malloc(sizeof(No));
  if (cabecote == NULL)
    return NULL;

  cabecote->prox = NULL;

  No *aux = cabecote;

  for (int i = 0; i < TAM; i++) {
    if (vetorPrincipal[i].vetor != NULL) {
      for (int j = 0; j < vetorPrincipal[i].posicao; j++) {
        if (!organizarCabecote(vetorPrincipal[i].vetor[j], &aux)) {
          return NULL;
        }
      }
    }
  }

  return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em
vetorAux. Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
  No *cabecote = inicio->prox;

  for (int i = 0; cabecote != NULL; cabecote = cabecote->prox, i++) {
    vetorAux[i] = cabecote->conteudo;
  }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno
  void.
*/
void destruirListaEncadeadaComCabecote(No **inicio) {
  No *cabecote = *inicio;
  No *aux;

  while (cabecote != NULL) {
    aux = cabecote;
    cabecote = cabecote->prox;
    free(aux);
  }

  *inicio = NULL;
}

/* Trabalho 3 */

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa

*/

char *lerArquivo(char *caminho) {
  FILE *arquivo = fopen(caminho, "r");
  if (!arquivo) {
    return NULL;
  }
  
  fseek(arquivo, 0, SEEK_END);
  long fileSize = ftell(arquivo);
  rewind(arquivo);

  char *buffer = (char *)malloc((fileSize + 1) * sizeof(char));
  if (!buffer) {
    fclose(arquivo);
    return NULL;
  }
  fread(buffer, 1, fileSize, arquivo);
  buffer[fileSize] = '\0';

  fclose(arquivo);
  return buffer;
}

void escreverArquivo(char *caminho, char *data) {
  FILE *arquivo = fopen(caminho, "w");
  if (!arquivo) {
    return;
  }
  fprintf(arquivo, "%s", data);
  fclose(arquivo);
}

void salvarArquivos() {
  char buffer[10000] = "";
  char linha[1000];

  for (int i = 0; i < TAM; i++) {
    if (vetorPrincipal[i].vetor == NULL) {
      strcat(buffer, "0 0");
    } else {
      sprintf(linha, "%d %d ", vetorPrincipal[i].tamanho,
              vetorPrincipal[i].posicao);
      strcat(buffer, linha);
      for (int j = 0; j < vetorPrincipal[i].tamanho; j++) {
        if (j < vetorPrincipal[i].posicao) {
          sprintf(linha, "%d ", vetorPrincipal[i].vetor[j]);
          strcat(buffer, linha);
        } 
        else
          break;
      }
    }
    if (i + 1 != TAM) {
      strcat(buffer, "\n");
    }
  }
  escreverArquivo(ARQUIVO, buffer);
}

void carregarArquivos() {
  char *conteudo = lerArquivo(ARQUIVO);
  if (!conteudo)
    return;

  char *linha = strtok(conteudo, "\n");
  for (int i = 0; i < TAM && linha != NULL; i++) {
    int tamanho, posicao;
    if (sscanf(linha, "%d %d", &tamanho, &posicao) != 2) {
      vetorPrincipal[i].tamanho = 0;
      vetorPrincipal[i].posicao = 0;
      vetorPrincipal[i].vetor = NULL;
    } else {
      vetorPrincipal[i].tamanho = tamanho;
      vetorPrincipal[i].posicao = posicao;
      vetorPrincipal[i].vetor = malloc(sizeof(int) * tamanho);
      char *num = strtok(linha, " ");
      num = strtok(NULL, " ");
      for (int j = 0; j < tamanho; j++) {
        num = strtok(NULL, " ");
        vetorPrincipal[i].vetor[j] = num ? atoi(num) : 0;
      }
    }
    linha = strtok(NULL, "\n");
  }
  free(conteudo);
}

void inicializar() {
  for (int i = 0; i < TAM; i++) {
    vetorPrincipal[i].vetor = NULL;
    vetorPrincipal[i].posicao = 0;
    vetorPrincipal[i].tamanho = 0;
  }
  carregarArquivos();
}

void finalizar() {
  salvarArquivos();
  for (int i = 0; i < TAM; i++) {
    free(vetorPrincipal[i].vetor);
    vetorPrincipal[i].vetor = NULL;
    vetorPrincipal[i].posicao = 0;
    vetorPrincipal[i].tamanho = 0;
  }
}