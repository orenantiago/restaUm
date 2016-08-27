#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int * v;
    int topo;
} pilha;

typedef struct {
    int linha, coluna;
} posicao;

pilha * criaPilha(int n) {
    pilha * p;
    p = malloc(sizeof(pilha));
    p -> v = calloc(n, sizeof(int));
    p -> topo = 0;
    return p;
}

void empilha(pilha * p, int x) {
    p -> v[p -> topo++] = x;
}

int desempilha(pilha * p) {
    p -> topo --;
    return p -> v[p -> topo];
}

int pilhaVazia(pilha p) {
    if (p.topo == 0)
        return 1;
    else
        return 0;
}

void destroiPilha(pilha * p) {
    free(p -> v);
    free(p);
}

int tamanhoPilha(pilha p) {
    return p.topo;
}

int ** criaMatriz(int m, int n) {
    
    int i, j;
    int ** tab;
    tab = malloc(m * sizeof(int *));
    for (i = 0; i < m; i++)
        tab[i] = calloc(n, sizeof(int));

    return tab;
}
void destroiMatriz(int ** tab, int m, int n) {
    int i;
    for (i = 0; i < m; i++)
        free(tab[i]);

    free(tab);
}


void imprimeMatriz(int ** tab, int m, int n) {
    int i, j;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
            printf("%d ", tab[i][j]);
        printf("\n");
    }
}

/*essa função será apagada antes de entregar o ep,
é apenas para testes. Recebe a matriz, m, n e a distancia entre os 1 e o vertice*/
void setJogo(int ** tab, int m, int dist) {
    int i, j;
    for(i = 0; i < m; i++)
        for (j = dist; j < m - dist; j++) {
            tab[i][j] = 1;
            tab[j][i] = 1;
        }
    tab[(m-1)/2][(m-1)/2] = -1;
}

int ** inverteTabuleiro(int ** tab, int m, int n) {
    int ** T, i, j;

    T = malloc(m * sizeof(int *));
    for (i = 0; i < n; i++)
        T[i] = malloc(n * sizeof(int));

    for (i = 0; i < m; i++) 
        for (j = 0; j < n; j++) {
            if(tab[i][j] == 1)
                T[i][j] = -1;
            else if(tab[i][j] == -1)
                T[i][j] = 1;
            else
                T[i][j] = 0;
        }
    return T;
}

int tabuleiroIgual(int ** tab1, int ** tab2, int m, int n) {
    int i, j, igual;

    igual = 1;

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (tab1[i][j] != tab2[i][j]) {
                igual = 0;
                break;
            }

    return igual;
}
/*
    2
    ^
    |
3<--v-->1 
    |
    v
    4
v = peça vazia
ela se movimenta sse tiver duas peças ao lado do movimento
apos o movimento, se torna peça e as peças viram espaço
*/

int verificaMovimento(int ** tab, int m, int n, posicao p, int movimento) {
    int pode;

    switch movimento {
        case 1:
            if (p.coluna + 1 < n && p.coluna + 2 < n)
                if (tab[p.linha][p.coluna + 1] == 1 && tab[p.linha][p.coluna + 2] == 1)
                    pode = 1;
        break;
        
        case 2:
            if (p.linha - 1 >= 0 && p.linha - 2 > 0)
                if (tab[p.linha - 1][p.coluna] == 1 && tab[p.linha + 2][p.coluna] == 1)
                    pode = 1;
        break;

        case 3:
            if (p.coluna - 1 < n && p.coluna - 2 < n)
                if (tab[p.linha][p.coluna - 1] == 1 && tab[p.linha][p.coluna - 2] == 1)
                    pode = 1;
        break;

        case 4:
            if (p.linha + 1 < m && p.linha + 2 < m)
                if (tab[p.linha + 1][p.coluna] == 1 && tab[p.linha + 2][p.coluna] == 1)
                    pode = 1;
        break;
    }
}
//void movimenta(int ** tab, posicao)

void jogo(int n) {
    pilha  * movimentos, pilha *vazios

}
int main(int argc, char const *argv[])
{
    int ** tab, ** tab2;
    tab = criaMatriz(7, 7);
    setJogo(tab, 7, 2);

    tab2 = criaMatriz(7, 7);
    tab2 = inverteTabuleiro(tab, 7, 7);
    
    imprimeMatriz(tab2, 7, 7);
    printf("\n");
    imprimeMatriz(tab, 7, 7);
    printf("%d", tabuleiroIgual(tab, tab2, 7, 7));
    
    destroiMatriz(tab, 7, 7);
    destroiMatriz(tab2, 7, 7);
    return 0;
}