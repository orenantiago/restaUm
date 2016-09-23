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

/*a partir da linha e da coluna, encontra o primeiro espaço não vazio do tabuleiro*/
int checaPecas(int ** tab, int m, int n, int * linha, int * coluna) {
    int i, j;

    i = *linha;
    j = *coluna;
    
    while (i < m) {
        while (j < n) {
            if (tab[i][j] == 1) {
                *linha = i;
                *coluna = j;
                return 1;
            }
            j++;
        }
        j = 0;
        i++;
    }

    *linha = 0;
    *coluna = 0;
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
ela se movimenta sse tiver duas peças ao lado do movimento
apos o movimento, se torna peça e as peças viram espaço
*/
int verificaMovimento(int ** tab, int m, int n, int movimento, int linha, int coluna) {
    int pode = 0;

    switch (movimento) {
        case 1:
            if (coluna + 2 < n && tab[linha][coluna + 1] == 1 && tab[linha][coluna + 2] == -1) 
                    pode = 1;
            break;
        
        case 2:
            if (linha - 2 >= 0 && tab[linha - 1][coluna] == 1 && tab[linha - 2][coluna] == -1)
                    pode = 1;
            break;

        case 3:
            if (coluna - 2 >= 0 && tab[linha][coluna - 1] == 1 && tab[linha][coluna - 2] == -1)
                    pode = 1;
            break;

        case 4:
            if (linha + 2 < m && tab[linha + 1][coluna] == 1 && tab[linha + 2][coluna] == -1)
                    pode = 1;
            break;
    }
    return pode;
}


/*a linha e coluna será empilhada nas respectivas pilhas, e o movimento também
feito*/
void movimenta(int ** tab, int movimento, int linha, int coluna) {
    
    tab[linha][coluna] = -1;
    
    switch (movimento) {
        case 1:
            tab[linha][coluna + 1] = -1;
            tab[linha][coluna + 2] = 1;
            break;
            
        case 2:
            tab[linha - 1][coluna] = -1;
            tab[linha - 2][coluna] = 1;
            break;

        case 3:
            tab[linha][coluna - 1] = -1;
            tab[linha][coluna - 2] = 1;
            break;

        case 4:
            tab[linha + 1][coluna] = -1;
            tab[linha + 2][coluna] = 1;
            break;
    }
}

void desfazMovimento(int ** tab, int movimento, int linha, int coluna) {
    
    tab[linha][coluna] = 1;
    
    switch (movimento) {
        case 1:
            tab[linha][coluna + 1] = 1;
            tab[linha][coluna + 2] = -1;
            break;
            
        case 2:
            tab[linha - 1][coluna] = 1;
            tab[linha - 2][coluna] = -1;
            break;

        case 3:
            tab[linha][coluna - 1] = 1;
            tab[linha][coluna - 2] = -1;
            break;

        case 4:
            tab[linha + 1][coluna] = 1;
            tab[linha + 2][coluna] = -1;
            break;

    }
}

void jogo(int ** tab, int m, int n) {
    int ** tab_inverso, i, j, movimentoAtual, linhaAtual, colunaAtual;
    pilha * movimentos, * linhas, * colunas;

    movimentos = criaPilha(m * n);
    linhas = criaPilha(m * n);
    colunas = criaPilha(m * n);

    linhaAtual = 0;
    colunaAtual = 0;
    movimentoAtual = 1;
    
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
        if (checaPecas(tab, m, n, &linhaAtual, &colunaAtual)) {
            if (verificaMovimento(tab, m, n, movimentoAtual, linhaAtual, colunaAtual)) {
                movimenta(tab, movimentoAtual, linhaAtual, colunaAtual);
                
                empilha(linhas, linhaAtual);
                empilha(colunas, colunaAtual);
                empilha(movimentos, movimentoAtual);
                
                linhaAtual = 0;
                colunaAtual = 0;
                movimentoAtual = 1;                
            } 
            else if (movimentoAtual < 4) {
                movimentoAtual++;
            }
            else if(colunaAtual < n && linhaAtual < m) {
                colunaAtual = (colunaAtual + 1) % n;
                movimentoAtual = 1;
                if(colunaAtual == 0)
                    linhaAtual++;
            }
        }
        else { /*backtrack*/
            if (pilhaVazia(*movimentos)) {
                printf("Impossivel\n");
                return;
            } else {
                movimentoAtual = desempilha(movimentos);
                linhaAtual = desempilha(linhas);
                colunaAtual = desempilha(colunas);
                desfazMovimento(tab, movimentoAtual, linhaAtual, colunaAtual);
                movimentoAtual++;
            }
        }
    }

    destroiMatriz(tab, m);
    destroiMatriz(tab_inverso, m);
    
    for(i = 0; i < tamanhoPilha(*linhas); i++) {
        movimentoAtual = movimentos -> v[i];
        linhaAtual = linhas -> v[i];
        colunaAtual = colunas -> v[i];

        if (movimentoAtual == 1)
            printf("%d:%d-%d:%d\n", linhaAtual, colunaAtual, linhaAtual, colunaAtual + 2);
        else if (movimentoAtual == 2)
            printf("%d:%d-%d:%d\n", linhaAtual, colunaAtual, linhaAtual - 2, colunaAtual);
        else if (movimentoAtual == 3)
            printf("%d:%d-%d:%d\n", linhaAtual, colunaAtual, linhaAtual, colunaAtual - 2);
        else
            printf("%d:%d-%d:%d\n", linhaAtual, colunaAtual, linhaAtual + 2, colunaAtual);

    }

    destroiPilha(movimentos);
    destroiPilha(linhas);
    destroiPilha(colunas);
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