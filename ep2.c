#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int * v;
    int topo;
} pilha;

pilha * criaPilha(int n) {
    pilha * p;
    p = malloc(sizeof(pilha));
    (*p).v = calloc(n, sizeof(int));
    (*p).topo = 0;
    return p;
}

/*void empilha(pilha * p, int x) {
    (*p).v[(*p).topo++]
}*/

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

void jogo(int n) {

}
int main(int argc, char const *argv[])
{
    int ** tab;
    tab = criaMatriz(7, 7);
    setJogo(tab, 7, 2);
    imprimeMatriz(tab, 7, 7);
    destroiMatriz(tab, 7, 7);
    return 0;
}