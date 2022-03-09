#include <stdio.h>
#include <stdlib.h>

char jogo[3][3];
char jogador1[50], jogador2[50];

void inicializarMatriz() {
    int i,j;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            jogo[i][j] = ' ';
        }
    }
}

int eValido(char letra) {
    if(letra == 'x' || letra == 'o')
        return 1;
    else
        return 0;
}

int coordenadaEhValida(int x, int y) {
    if(x >= 0 && x < 3) {
        if(y >= 0 && y < 3)
            return 1;
    }
    return 0;
}

int posicaVazia(int x, int y) {
    if(jogo[x][y] != 'x' && jogo[x][y] != 'o')
        return 1;
    return 0;
}

int ganhouLinhas() {
    int i, j, igual = 1;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            if(eValido(jogo[i][j]) && jogo[i][j] == jogo[i][j+1])
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
    return 0;
}

int ganhouColunas() {
    int i, j, igual = 1;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            if(eValido(jogo[j][i]) && jogo[j][i] == jogo[j+1][i])
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
    return 0;
}

int ganhoudiagPrincipal() {
    int i, igual = 1;
    for(i = 0; i < 2; i++) {
        if(eValido(jogo[i][i]) && jogo[i][i] == jogo[i+1][i+1])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

int ganhoudiagSecundaria() {
    int i, igual = 1;
    for(i = 0; i < 2; i++) {
        if(eValido(jogo[i][3-i-1]) && jogo[i][3-i-1] == jogo[i+1][3-i-2])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}

void imprimir() {
    int lin, col;

    printf("\n\t   0   1   2 \n");
    for(lin = 0; lin < 3; lin++) {
        printf("\t%d ", lin);
        for(col = 0; col < 3; col++) {
            if(col < 2)
                printf(" %c |", jogo[lin][col]);
            else
                printf(" %c ", jogo[lin][col]);
        }
        if(lin < 2)
            printf("\n\t  ........... \n");
    }
}



void jogar() {
    int x, y, valida, jogadas = 0, ganhou = 0, ordem = 1;

    

    do {
        do {
            imprimir();
           
            printf(" \n\n Faça a primeira coordenada que queira jogar. Regras: Introduza 1º Posição Vertical depois faça Enter e de seguida Introduza a 2ª Posição Horizontal:");
            scanf("%d%d", &x, &y);
            valida = coordenadaEhValida(x, y);
            if(valida == 1)
                valida += posicaVazia(x, y);
        } while(valida != 2);
        if(ordem == 1)
            jogo[x][y] = 'x';
        else
            jogo[x][y] = 'o';
        jogadas++;
        ordem++;
        if(ordem == 3)
            ordem = 1;
        ganhou += ganhouLinhas();
        ganhou += ganhouColunas();
        ganhou += ganhoudiagPrincipal();
        ganhou += ganhoudiagSecundaria();
    } while(ganhou == 0 && jogadas < 9);

    if(ganhou != 0) {
        imprimir();
        if(ordem - 1 == 1)
            printf("\n\n Parabéns! Ganhou o Jogo %s\n", jogador1 );
        else
            printf("\n\n Parabéns! Ganhou o Jogo %s\n", jogador2 );
    } else
        printf("\n\n Ups! Ninguém Ganhou!\n\n");
}

int main() {

    int op;

       
    printf("\n\n\tJOGO DO GALO\n\n");

     
    printf("Jogador 1 (X)  -  Jogador 2 (O)\n\n\n");

    printf("Jogador 1 Nome: ");
    fgets(jogador1, 50, stdin);
    printf("Jogador 2 Nome: ");
    fgets(jogador2, 50, stdin);

    do {
        inicializarMatriz();
        jogar();
        printf("Quer jogar novamente?\n1 - Sim\n2 - Nao\n");
        scanf("%d", &op);
    } while(op == 1);

    return 0;
}