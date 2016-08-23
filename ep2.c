#include <stdio.h>
#include <stdlib.h>

int ** criaTabuleiro(int m, int n) {
    
    int i, j;
    int ** tab;
    tab = malloc(m * sizeof(int *));
    for (i = 0; i < m; i++)
        tab[i] = calloc(n, sizeof(int));

    return tab;
}
void destroiTabuleiro(int ** tab, int m, int n) {
    int i;
    for (i = 0; i < m; i++)
        free(tab[i]);

    free(tab);
}

void imprimeTabuleiro(int ** tab, int m, int n) {
    int i, j;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
            printf("%d ", tab[i][j]);
        printf("\n");
    }

}
int main(int argc, char const *argv[])
{
    int ** tab;
    tab = criaTabuleiro(10, 10);
    imprimeTabuleiro(tab, 10, 10);
    destroiTabuleiro(tab, 10, 10);
    return 0;
}