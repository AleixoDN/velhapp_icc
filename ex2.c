#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Struct de estrutura de informações de un jogador
typedef struct {
    char simbolo;
    char tipo;
} Jogador;

// Inclusão dos headers de funções
#include "desenha_tabuleiro.h"
#include "input_jogadores.h"
#include "jogada_computador.h"
#include "jogada_humano.h"
#include "verificacao_linear.h"
#include "verifica_vitoria.h"
#include "inteligencia_checagem.h"


int main() {

    int n, i, j, m, p, k;
    char aux, vencedor, jogo;

    // Inicio e reforço a pseudo-aleatoriedade da função rand()
    srand((unsigned int)time(NULL));
    rand();
    rand();
    rand();

    jogo = ' ';
    while((jogo != 's') && (jogo != 'n')) {
        system("clear");

        printf("\n                ####################################\n                ##                                ##\n                ##        Jogo da Velha ++        ##\n                ##                                ##\n                ####################################\n\n");

        printf("\n    Jogar agora [s/n]? ");
        scanf("%c", &jogo);
        scanf("%c", &aux);
    }

    if(jogo == 's') {
        vencedor = ' ';
        k = 0; // Zerando o contador de jogadas

        // Input de tamanho do tabuleiro
        printf("\n    Número de linhas e colunas do tabuleiro: ");
        scanf("%d", &n);

        // Declaração do tabuleiro no tamanho indicado
        char **tabuleiro;
        tabuleiro = (char**)malloc(sizeof(char*)*n);
        for(int i=0; i<n; i++){
            tabuleiro[i] = (char*)malloc(sizeof(char)*n);
        }

        // Input do tamanho da sequencia para vitoria
        printf("    Tamanho da sequencia para vitória: ");
        scanf("%d", &p);

        // Input de quantos e quais jogadores serão
        printf("    Número de jogadores: ");
        scanf("%d", &m);
        scanf("%c", &aux);

        Jogador *jogadores;
        jogadores=(Jogador*) malloc(sizeof(Jogador)*m);

        input_jogadores(m, jogadores);

        // Zerando a matriz que conterá as jogadas feitas
        //printf("Zerando o tabuleiro...\n");
        for(j = 0; j < n; j++) {
            for(i = 0; i < n; i++) {
                //printf("Zerendo casa(%d, %d)\n", i, j);
                tabuleiro[i][j] = ' ';
            }
        }

        printf("Iniciando...\n");

        // Loop que inicia jogada por jogada
        desenha_tabuleiro(n, tabuleiro);
        while((vencedor == ' ') && (k != n*n)) {

            // Roda jogadores, cada um em uma jogada
            for(i = 0; i < m; i++) {

                // Verificar se o jogador atual é um humano ou um computador
                if (jogadores[i].tipo == 'h') {
                    //printf("Jogada humana\n");
                    jogada_humano(n, tabuleiro, jogadores[i]);
                } else if(jogadores[i].tipo == 'c') {
                    //printf("Jogada computador\n");
                    char jogada=inteligencia_checagem(n,tabuleiro,p,jogadores[i].simbolo);
                    if(jogada==' '){
                        jogada_computador(n, tabuleiro, jogadores[i]);
                    }
                }
                k++;

                // Verifica se o jogador ganhou com a ultima jogada
                vencedor = verifica_vitoria(n, tabuleiro, p);

                // Desenha o tabuleiro contendo a ultima jogada
                desenha_tabuleiro(n, tabuleiro);

                // Break para sair do for, uma vez que ele sairá automaticamente do while
                if(vencedor != ' ') {
                    printf("O vencedor é o jogador de símbolo: %c\n", vencedor);
                    break;
                }

                //Break para sair do for caso dê velha, uma vez que ele sairá automaticamente do while
                if(k == n*n){
                    printf("Velha\n");
                    break;
                }
            }
        }

        printf("Jogar de novo? ");
        scanf("%c", &jogo);
        scanf("%c", &aux);

        free(tabuleiro);

    }

    return 0;
}
