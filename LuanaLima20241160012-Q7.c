#include <stdio.h>
#include <stdlib.h>


void mostrarTabuleiro(char tabuleiro[3][3]) {
  printf("     1   2   3\n\n");
  printf("A\t %c | %c | %c\n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
  printf("\t---+---+---\n");
  printf("B\t %c | %c | %c\n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
  printf("\t---+---+---\n");
  printf("C\t %c | %c | %c\n\n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
}

int checagemTabuleiro(char tabuleiro[3][3]) {
  for (int i = 0; i < 3; i++) {
    if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != ' ') {
      return tabuleiro[i][0];  
    }
    
    if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' ') {
      return tabuleiro[0][i];  
    }
  }

  
  if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != ' ') {
    return tabuleiro[0][0];
  }
  
  if (tabuleiro[2][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[0][2] && tabuleiro[2][0] != ' ') {
    return tabuleiro[2][0];
  }

  
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (tabuleiro[i][j] == ' ') {
        return -1; 
      }
    }
  }
  return 0; 
}


int main() {
  char tabuleiro[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
  int vencedor = -1;
  int jogador = 0;  
  char escolha[3];  

  printf("Jogo da Velha\n");


  while (vencedor == -1) {
    system("clear");
    mostrarTabuleiro(tabuleiro);

    if (jogador == 0) {
      printf("\nJogador X, informe sua jogada (ex: A1): ");
    } 
    
    else {
      printf("\nJogador O, informe sua jogada (ex: A1): ");
    }

    fgets(escolha, 3, stdin);  
    getchar();  


    int posicao1 = escolha[0] - 'A';  
    int posicao2 = escolha[1] - '1';  


    if (posicao1 >= 0 && posicao1 < 3 && posicao2 >= 0 && posicao2 < 3) {
      if (tabuleiro[posicao1][posicao2] == ' ') {
        tabuleiro[posicao1][posicao2] = (jogador == 0) ? 'X' : 'O';
        jogador = 1 - jogador;  
      } 
      
      else {
        printf("\nJogada inválida! A célula já está ocupada.\n");
        continue;
      }
    } 
    else {
      printf("\nJogada inválida! Informe um valor entre A1 e C3.\n");
      continue;
    }


    vencedor = checagemTabuleiro(tabuleiro);
  }

  
  if (vencedor == 0) {
    printf("\n\nO jogo empatou!\n");
  } 
  else {
    printf("\n\nJogador %c venceu!\n", vencedor);
  }

  return 0;
}
