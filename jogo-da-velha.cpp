#include <stdio.h>  // Biblioteca padrão pra entrada e saída

// Tabuleiro do jogo
char t[3][3] = {};  

// Variáveis pra armazenar os jogadores e o símbolo atual
char simbolo = 'X';
char jogador1[50], jogador2[50];

// Placar dos jogadores
int placar1 = 0, placar2 = 0;

// Só mostra o tabuleiro de forma bonitinha no terminal
void mostrar() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", t[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

// Verifica se alguém ganhou, olhando linhas, colunas e diagonais
int ganhou() {
    for (int i = 0; i < 3; i++) {
        if (t[i][0] == simbolo && t[i][1] == simbolo && t[i][2] == simbolo) return 1;
        if (t[0][i] == simbolo && t[1][i] == simbolo && t[2][i] == simbolo) return 1;
    }
    if (t[0][0] == simbolo && t[1][1] == simbolo && t[2][2] == simbolo) return 1;
    if (t[0][2] == simbolo && t[1][1] == simbolo && t[2][0] == simbolo) return 1;

    return 0;
}

// Reinicia o tabuleiro antes de cada nova partida
void zerarTabuleiro() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            t[i][j] = ' ';
}

// Mostra o placar atual dos jogadores
void mostrarPlacar() {
    printf("\nPlacar:\n");
    printf("%s (X): %d\n", jogador1, placar1);
    printf("%s (O): %d\n\n", jogador2, placar2);
}

int main() {
    // Pede o nome dos dois jogadores logo no início
    printf("Digite o nome do jogador 1 (X): ");
    scanf(" %49[^\n]", jogador1);

    printf("Digite o nome do jogador 2 (O): ");
    scanf(" %49[^\n]", jogador2);

    // Começa com o jogador 1 e o símbolo X
    char* jogadorAtual = jogador1;
    simbolo = 'X';

    char jogarNovamente = 's';

    // Enquanto os jogadores quiserem jogar...
    while (jogarNovamente == 's' || jogarNovamente == 'S') {
        zerarTabuleiro();
        int jogada, cont = 0;

        while (1) {
            mostrar();

            // Entrada da jogada
            printf("%s (%c), escolha (1-9): ", jogadorAtual, simbolo);
            scanf("%d", &jogada);

            jogada--;  // Adapta pra índice de 0 a 8
            int l = jogada / 3;
            int c = jogada % 3;

            // Se a jogada for inválida, avisa e continua
            if (jogada < 0 || jogada > 8 || t[l][c] == 'X' || t[l][c] == 'O') {
                printf("Jogada inválida! Tente novamente.\n");
                continue;
            }

            // Marca a jogada
            t[l][c] = simbolo;
            cont++;

            // Se venceu, mostra o tabuleiro e parabeniza
            if (ganhou()) {
                mostrar();
                printf("Parabéns, %s! Você venceu!\n", jogadorAtual);
                if (simbolo == 'X') placar1++;
                else placar2++;
                break;
            }

            // Se ninguém venceu e o tabuleiro encheu: empate
            if (cont == 9) {
                mostrar();
                printf("Empate!\n");
                break;
            }

            // Troca de jogador
            if (simbolo == 'X') {
                simbolo = 'O';
                jogadorAtual = jogador2;
            } else {
                simbolo = 'X';
                jogadorAtual = jogador1;
            }
        }

        mostrarPlacar();

        // Pergunta se querem mais uma
        printf("Quer jogar novamente? (s/n): ");
        scanf(" %c", &jogarNovamente);

        // Reinicia pro próximo jogo começar certinho
        jogadorAtual = jogador1;
        simbolo = 'X';
    }

    printf("Obrigado por jogar!\n");
    return 0;
}
