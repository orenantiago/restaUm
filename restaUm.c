#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int * v;
    int topo;
} pilha;

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

int tamanhoPilha(pilha p) {
    return p.topo;
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

int ** criaMatriz(int m, int n) {
    
    int i;
    int ** tab;
    tab = malloc(m * sizeof(int *));
    for (i = 0; i < m; i++)
        tab[i] = calloc(n, sizeof(int));

    return tab;
}
void destroiMatriz(int ** tab, int m) {
    int i;
    for (i = 0; i < m; i++)
        free(tab[i]);

    free(tab);
}


void imprimeMatriz(int ** tab, int m, int n) {
    int i, j;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
            if(tab[i][j] == -1)
                printf("x ");
            else
                printf("%d ", tab[i][j]);
        printf("\n");
    }
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

/*a partir da lin e da col, encontra o primeiro espaço não vazio do tabuleiro*/
int checaPecas(int ** tab, int m, int n, int * lin, int * col) {
    int i, j;

    i = *lin;
    j = *col;
    
    while (i < m) {
        while (j < n) {
            if (tab[i][j] == 1) {
                *lin = i;
                *col = j;
                return 1;
            }
            j++;
        }
        j = 0;
        i++;
    }

    *lin = 0;
    *col = 0;
    return 0;
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
ela se movimenta sse tiver duas peças ao lado do mov
apos o mov, se torna peça e as peças viram espaço
*/
int verificamov(int ** tab, int m, int n, int mov, int lin, int col) {
    int pode = 0;

    switch (mov) {
        case 1:
            if (col + 2 < n && tab[lin][col+1] == 1 && tab[lin][col+2] == -1) 
                    pode = 1;
            break;
        
        case 2:
            if (lin - 2 >= 0 && tab[lin-1][col] == 1 && tab[lin-2][col] == -1)
                    pode = 1;
            break;

        case 3:
            if (col - 2 >= 0 && tab[lin][col-1] == 1 && tab[lin][col-2] == -1)
                    pode = 1;
            break;

        case 4:
            if (lin + 2 < m && tab[lin+1][col] == 1 && tab[lin+2][col] == -1)
                    pode = 1;
            break;
    }
    return pode;
}


/*a lin e col será empilhada nas respectivas pilhas, e o mov também
feito*/
void movimenta(int ** tab, int mov, int lin, int col) {
    
    tab[lin][col] = -1;
    
    switch (mov) {
        case 1:
            tab[lin][col + 1] = -1;
            tab[lin][col + 2] = 1;
            break;
            
        case 2:
            tab[lin - 1][col] = -1;
            tab[lin - 2][col] = 1;
            break;

        case 3:
            tab[lin][col - 1] = -1;
            tab[lin][col - 2] = 1;
            break;

        case 4:
            tab[lin + 1][col] = -1;
            tab[lin + 2][col] = 1;
            break;
    }
}

void desfazmov(int ** tab, int mov, int lin, int col) {
    
    tab[lin][col] = 1;
    
    switch (mov) {
        case 1:
            tab[lin][col + 1] = 1;
            tab[lin][col + 2] = -1;
            break;
            
        case 2:
            tab[lin - 1][col] = 1;
            tab[lin - 2][col] = -1;
            break;

        case 3:
            tab[lin][col - 1] = 1;
            tab[lin][col - 2] = -1;
            break;

        case 4:
            tab[lin + 1][col] = 1;
            tab[lin + 2][col] = -1;
            break;

    }
}

void jogo(int ** tab, int m, int n) {
    int ** tab_inverso, i, j, movAtual, linAtual, colAtual;
    pilha * movs, * lins, * cols;

    movs = criaPilha(m * n);
    lins = criaPilha(m * n);
    cols = criaPilha(m * n);

    linAtual = 0;
    colAtual = 0;
    movAtual = 1;
    
    /*cria matriz inversa e adiciona os espaços já existentes à lista*/
    tab_inverso = criaMatriz(m, n);

    for (i = 0; i < m; i++) 
        for (j = 0; j < n; j++) {
            if(tab[i][j] == 1) {
                tab_inverso[i][j] = -1;
            }
            else if(tab[i][j] == -1) {
                tab_inverso[i][j] = 1;
            }
            else
                tab_inverso[i][j] = 0;
        }

    while (!tabuleiroIgual(tab, tab_inverso, m, n)) {
        if (checaPecas(tab, m, n, &linAtual, &colAtual)) {
            if (verificamov(tab, m, n, movAtual, linAtual, colAtual)) {
                movimenta(tab, movAtual, linAtual, colAtual);
                
                empilha(lins, linAtual);
                empilha(cols, colAtual);
                empilha(movs, movAtual);
                
                linAtual = 0;
                colAtual = 0;
                movAtual = 1;                
            } 
            else if (movAtual < 4) {
                movAtual++;
            }
            else if(colAtual < n && linAtual < m) {
                colAtual = (colAtual + 1) % n;
                movAtual = 1;
                if(colAtual == 0)
                    linAtual++;
            }
        }
        else { /*backtrack*/
            if (pilhaVazia(*movs)) {
                printf("Impossivel\n");
                return;
            } else {
                movAtual = desempilha(movs);
                linAtual = desempilha(lins);
                colAtual = desempilha(cols);
                desfazmov(tab, movAtual, linAtual, colAtual);
                movAtual++;
            }
        }
    }

    destroiMatriz(tab, m);
    destroiMatriz(tab_inverso, m);
    
    for(i = 0; i < tamanhoPilha(*lins); i++) {
        movAtual = movs -> v[i];
        linAtual = lins -> v[i];
        colAtual = cols -> v[i];

        if (movAtual == 1)
            printf("%d:%d-%d:%d\n", linAtual, colAtual, linAtual, colAtual + 2);
        else if (movAtual == 2)
            printf("%d:%d-%d:%d\n", linAtual, colAtual, linAtual - 2, colAtual);
        else if (movAtual == 3)
            printf("%d:%d-%d:%d\n", linAtual, colAtual, linAtual, colAtual - 2);
        else
            printf("%d:%d-%d:%d\n", linAtual, colAtual, linAtual + 2, colAtual);

    }

    destroiPilha(movs);
    destroiPilha(lins);
    destroiPilha(cols);
    return;
}
int main(int argc, char const *argv[])
{
    int ** tab, m, n, i, j;
    
    scanf("%d %d", &m, &n);

    tab = criaMatriz(m, n);
    
    for(i = 0; i < m; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &tab[i][j]);

    jogo(tab, m, n);
    
    return 0;
}