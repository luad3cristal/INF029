// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do
//  trabalho

//  ----- Dados do Aluno -----
//  Nome: Luana dos Santos Lima
//  email: luanalima.2006@hotmail.com ou 20241160012@ifba.edu.br
//  Matrícula: 20241160012
//  Semestre: 2024.2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include "LuanaLima20241160012.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
  Somar dois valores x e y e retonar o resultado da soma
@entrada
  dois inteiros x e y
@saida
  resultado da soma (x + y)
 */
int somar(int x, int y) {
  int soma;
  soma = x + y;
  return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
  calcular o fatorial de um número
@entrada
  um inteiro x
@saida
  fatorial de x -> x!
 */
int fatorial(int x) { // função utilizada para testes
  int i, fat = 1;

  for (i = x; i > 1; i--)
    fat = fat * i;

  return fat;
}

int teste(int a) {
  int val;
  if (a == 2)
    val = 3;
  else
    val = 4;

  return val;
}

/*
 Q1 = validar data
@objetivo
  Validar uma data
@entrada
  uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm
= mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem
ter apenas dois digitos.
@saida
  0 -> se data inválida
  1 -> se data válida
 @restrições
  Não utilizar funções próprias de string (ex: strtok)
  pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[]) {
  DataQuebrada dataAtual = quebraData(data);
  int fevereiro = 28;

  int datavalida = 1;

  // quebrar a string data em strings sDia, sMes, sAno
  int dia = dataAtual.iDia;
  int mes = dataAtual.iMes;
  int ano = dataAtual.iAno;

  // checa bissexto
  if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) {
    fevereiro = 29;
  }

  // checa ano aa ou aaaa
  if (ano < 10 || ano > 2024) {
    datavalida = 0;
  }

  // checa mes
  else if (mes < 1 || mes > 12) {
    datavalida = 0;
  }

  // checa dias de fevereiro
  else if (mes == 2) {
    if (dia > fevereiro)
      datavalida = 0;
  }

  // checa os meses com 30 dias
  else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
    if (dia > 30) {
      datavalida = 0;
    }
  }

  // checa se tem mais de 31 dias
  else if (dia > 31) {
    datavalida = 0;
  }

  if (datavalida)
    return 1;
  else
    return 0;
}

/*
 Q2 = diferença entre duas datas
 @objetivo
  Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
  uma string datainicial, uma string datafinal.
 @saida
  Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis
 valores abaixo 1 -> cálculo de diferença realizado com sucesso 2 -> datainicial
 inválida 3 -> datafinal inválida 4 -> datainicial > datafinal Caso o cálculo
 esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos
 com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[]) {
  // calcule os dados e armazene nas três variáveis a seguir
  DiasMesesAnos dma;

  DataQuebrada dataInicial = quebraData(datainicial);
  DataQuebrada dataFinal = quebraData(datafinal);

  // checa a validade das datas a partir da questão 1
  if (q1(datainicial) == 0) {
    dma.retorno = 2;
    return dma;
  } 
  else if (q1(datafinal) == 0) {
    dma.retorno = 3;
    return dma;
  }

  else {
    // verifique se a data final não é menor que a data inicial
    if (dataInicial.iAno > dataFinal.iAno) {
      dma.retorno = 4;
      return dma;
    } 

    else if (dataFinal.iAno == dataInicial.iAno 
      && dataInicial.iMes > dataFinal.iMes) {
      dma.retorno = 4;
      return dma;
    } 

    else if (dataFinal.iAno == dataInicial.iAno 
    && dataFinal.iMes == dataInicial.iMes && 
    dataInicial.iDia > dataFinal.iDia) {
      dma.retorno = 4;
      return dma;
    }


    int fevAtual = 28;
    if (dataFinal.iAno % 4 == 0 && (dataFinal.iAno % 100 != 0 || dataFinal.iAno % 400 == 0)) {
      fevAtual = 29;
    }

    dma.qtdAnos = dataFinal.iAno - dataInicial.iAno;
    dma.qtdMeses = dataFinal.iMes - dataInicial.iMes;
    dma.qtdDias = dataFinal.iDia - dataInicial.iDia;


    if (dma.qtdDias < 0) {
      int mesAnterior;

      if (dataFinal.iMes == 1) {
        mesAnterior = 31;
      }
      else if (dataFinal.iMes == 3) {
        mesAnterior = fevAtual;
      }
      else if (dataFinal.iMes == 5 || dataFinal.iMes == 7 ||
               dataFinal.iMes == 10 || dataFinal.iMes == 12) {
        mesAnterior = 30;
      }
      else {
        mesAnterior = 31;
      }

      dma.qtdDias += mesAnterior;
      dma.qtdMeses--;
    }

    if (dma.qtdMeses < 0) {
      dma.qtdMeses += 12;
      dma.qtdAnos--;
    } 

    // se tudo der certo
    dma.retorno = 1;
    return dma;
  }
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
  Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
  uma string texto, um caracter c e um inteiro que informa se é uma pesquisa
 Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar
 diferenças entre maiúsculos e minúsculos. Se isCaseSensitive != 1, a pesquisa
 não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
  Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive) {
  setlocale(LC_ALL, ""); 
  
  wchar_t maiusculas[6][5] = {
      {"Á", "À", "Â", "Ã", "Ä"}, {"É", "È", "Ê", "Ë"}, {"Í", "Ì", "Î", "Ï"},
      {"Ó", "Ò", "Ô", "Õ", "Ö"}, {"Ú", "Ù", "Û", "Ü"}, {"Ç", "\0", "\0", "\0", "\0"},
  };

  wchar_t minusculas[6][5] = {
      {"á", "à", "â", "ã", "ä"}, {"é", "è", "ê", "ë"}, {"í", "ì", "î", "ï"},
      {"ó", "ò", "ô", "õ", "ö"}, {"ú", "ù", "û", "ü"}, {"ç", "\0", "\0", "\0", "\0"},
  };

  int qtdOcorrencias = -1;
  qtdOcorrencias++;

  for (int i = 0; texto[i] != '\0'; i++) {
    if (isCaseSensitive) {
      if (c == texto[i])
        qtdOcorrencias++;


      else {
        for (int j = 0; j < 5; j++) {
          if (c == 'a' && texto[i] == minusculas[0][j]) 
            qtdOcorrencias++;

          else if (c == 'e' && texto[i] == minusculas[1][j]) 
            qtdOcorrencias++;

          else if (c == 'i' && texto[i] == minusculas[2][j]) 
            qtdOcorrencias++;

          else if (c == 'o' && texto[i] == minusculas[3][j]) 
            qtdOcorrencias++;

          else if (c == 'u' && texto[i] == minusculas[4][j]) 
            qtdOcorrencias++;

          else if (c == 'c' && texto[i] == minusculas[5][j]) 
            qtdOcorrencias++;

          else if (c == 'A' && texto[i] == maiusculas[0][j]) 
            qtdOcorrencias++;

          else if (c == 'E' && texto[i] == maiusculas[1][j]) 
            qtdOcorrencias++;

          else if (c == 'I' && texto[i] == maiusculas[2][j]) 
            qtdOcorrencias++;

          else if (c == 'O' && texto[i] == maiusculas[3][j]) 
            qtdOcorrencias++;

          else if (c == 'U' && texto[i] == maiusculas[4][j]) 
            qtdOcorrencias++;

          else if (c == 'C' && texto[i] == maiusculas[5][j]) 
            qtdOcorrencias++;
        }
      }
    }

    else {
      if ((c == texto[i]) || (c == texto[i] + 32) || (c == texto[i] - 32))
        qtdOcorrencias++;

      else {
        for (int j = 0; j < 5; j++) {
          if ((c == 'a' || c == 'A') && (texto[i] == minusculas[0][j] || texto[i] == maiusculas[0][j])) 
            qtdOcorrencias++;

          else if ((c == 'e' || c == 'E') && (texto[i] == minusculas[1][j] || texto[i] == maiusculas[1][j])) 
            qtdOcorrencias++;

          else if ((c == 'i' || c == 'I') && (texto[i] == minusculas[2][j] || texto[i] == maiusculas[2][j])) 
            qtdOcorrencias++;

          else if ((c == 'o' || c == 'O') && (texto[i] == minusculas[3][j] || texto[i] == maiusculas[3][j])) 
            qtdOcorrencias++;

          else if ((c == 'u' || c == 'U') && (texto[i] == minusculas[4][j] || texto[i] == maiusculas[4][j])) 
            qtdOcorrencias++;

          else if ((c == 'c' || c == 'C') && (texto[i] == minusculas[5][j] || texto[i] == maiusculas[5][j])) 
            qtdOcorrencias++;

        }
      }
    }
  }

  return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
  Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
  uma string texto base (strTexto), uma string strBusca e um vetor de inteiros
 (posicoes) que irá guardar as posições de início e fim de cada ocorrência da
 palavra (strBusca) no texto base (texto).
 @saida
  Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
  O vetor posicoes deve ser preenchido com cada entrada e saída correspondente.
 Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser
 preenchido com o índice de início do texto, e na posição 1, deve ser preenchido
 com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda
 ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha
 a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma
 ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da
 seguinte forma: posicoes[0] = 13; posicoes[1] = 16; Observe que o índice da
 posição no texto deve começar ser contado a partir de 1. O retorno da função,
 n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30]) {

  setlocale(LC_ALL, "");

  char maiusculas[6][5] = {
      {"Á", "À", "Â", "Ã", "Ä"}, {"É", "È", "Ê", "Ë"}, {"Í", "Ì", "Î", "Ï"},
      {"Ó", "Ò", "Ô", "Õ", "Ö"}, {"Ú", "Ù", "Û", "Ü"}, {"Ç"},
  };
  char minusculas[6][5] = {{"á", "à", "â", "ã", "ä"}, {"é", "è", "ê", "ë"},
                           {"í", "ì", "î", "ï"},      {"ó", "ò", "ô", "õ", "ö"},
                           {"ú", "ù", "û", "ü"},      {"ç"}};

  for (int i = 0; strlen(strTexto) > i; i++) {
    for (int k = 0; k < 5; k++) {
      if (strTexto[i] == maiusculas[0][k] || strTexto[i] == minusculas[0][k]) {
        strTexto[i] = 'a';

        for (int j = i + 1; j < strlen(strTexto); j++) {
          strTexto[j] = strTexto[j + 1];
        }
      }

      else if (strTexto[i] == maiusculas[1][k] ||
               strTexto[i] == minusculas[1][k]) {
        strTexto[i] = 'e';

        for (int j = i + 1; j < strlen(strTexto); j++) {
          strTexto[j] = strTexto[j + 1];
        }
      }

      else if (strTexto[i] == maiusculas[2][k] ||
               strTexto[i] == minusculas[2][k]) {
        strTexto[i] = 'i';

        for (int j = i + 1; j < strlen(strTexto); j++) {
          strTexto[j] = strTexto[j + 1];
        }
      }

      else if (strTexto[i] == maiusculas[3][k] ||
               strTexto[i] == minusculas[3][k]) {
        strTexto[i] = 'o';

        for (int j = i + 1; j < strlen(strTexto); j++) {
          strTexto[j] = strTexto[j + 1];
        }
      }

      else if (strTexto[i] == maiusculas[4][k] ||
               strTexto[i] == minusculas[4][k]) {
        strTexto[i] = 'u';

        for (int j = i + 1; j < strlen(strTexto); j++) {
          strTexto[j] = strTexto[j + 1];
        }
      }

      else if (strTexto[i] == maiusculas[5][k] ||
               strTexto[i] == minusculas[5][k]) {
        strTexto[i] = 'c';

        for (int j = i + 1; j < strlen(strTexto); j++) {
          strTexto[j] = strTexto[j + 1];
        }
      }
    }
  }

  int qtdOcorrencias = -1;
  qtdOcorrencias++;

  int armazenamento = 0;

  for (int i = 0; strlen(strTexto) > i; i++) {
    if (strBusca[0] == strTexto[i]) {
      posicoes[armazenamento] = i + 1;

      for (int j = 1; strlen(strBusca) > j; j++) {
        for (int k = i + 1; strlen(strBusca) + i > k; k++) {

          if (strBusca[j] == strTexto[k]) {
            if (j + 1 == strlen(strBusca)) {
              posicoes[armazenamento + 1] = k + 1;
              qtdOcorrencias++;
              armazenamento = armazenamento + 2;

              i = k;
              break;
            }

            else {
              j++;
            }
          }

          else {
            posicoes[armazenamento] = -1;
            j = strlen(strBusca);

            i = k;
            break;
          }
        }
      }
    }
  }

  return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
  Inverter número inteiro
 @entrada
  uma int num.
 @saida
  Número invertido
 */

int q5(int num) {
  int contador = 0;
  for (int i = num; i > 0; i = i / 10) {
    contador++;
  }

  int inversao = 0;
  while (contador != 0) {
    int valor = num % 10;
    inversao = (inversao * 10) + valor;
    num /= 10;

    contador--;
  }

  num = inversao;

  return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
  Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
  Um número base (numerobase) e um número de busca (numerobusca).
 @saida
  Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca) {
  int tam1 = 0;
  int tam2 = 0;
  for (int i = numerobase; i > 0; i = i / 10) {
    tam1++;
  }
  for (int i = numerobusca; i > 0; i = i / 10) {
    tam2++;
  }

  char numerobase_str[tam1];
  sprintf(numerobase_str, "%d", numerobase);
  char numerobusca_str[tam2];
  sprintf(numerobusca_str, "%d", numerobusca);

  int qtdOcorrencias;
  qtdOcorrencias = 0;

  for (int i = 0; tam1 > i; i++) {
    if (numerobusca_str[0] == numerobase_str[i]) {

      if (tam2 > 1) {
        for (int j = 1; tam2 > j; j++) {
          for (int k = i + 1; tam2 + i > k; k++) {

            if (numerobusca_str[j] == numerobase_str[k]) {
              if (j + 1 == tam2) {
                qtdOcorrencias++;

                i = k;
                break;
              }
              else {
                j++;
              }
            }          
          }
        }    
      }

      else {
        qtdOcorrencias++;
      }

    }
  }


  return qtdOcorrencias;
}

DataQuebrada quebraData(char data[]) {
  DataQuebrada dq;
  char sDia[3];
  char sMes[3];
  char sAno[5];
  int i;

  for (i = 0; data[i] != '/'; i++) {
    sDia[i] = data[i];
  }

  if (i == 1 || i == 2) { // testa se tem 1 ou dois digitos
    sDia[i] = '\0';       // coloca o barra zero no final
  } else {
    dq.valido = 0;
    return dq;
  }

  int j = i + 1; // anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '/'; j++) {
    sMes[i] = data[j];
    i++;
  }

  if (i == 1 || i == 2) { // testa se tem 1 ou dois digitos
    sMes[i] = '\0';       // coloca o barra zero no final
  } else {
    dq.valido = 0;
    return dq;
  }

  j = j + 1; // anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '\0'; j++) {
    sAno[i] = data[j];
    i++;
  }

  if (i == 2 || i == 4) { // testa se tem 2 ou 4 digitos
    sAno[i] = '\0';       // coloca o barra zero no final
  } else {
    dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno);

  dq.valido = 1;

  return dq;
}