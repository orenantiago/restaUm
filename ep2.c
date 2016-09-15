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
    
    int i, j;
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
            printf("%d ", tab[i][j]);
        printf("\n");
    }
}

/*essa função será apagada antes de entregar o ep,
é apenas para testes. Recebe a matriz, m, n e a distancia entre os 1 e o vertice*/
//feita
void setJogo(int ** tab, int m, int dist) {
    int i, j;
    for(i = 0; i < m; i++)
        for (j = dist; j < m - dist; j++) {
            tab[i][j] = 1;
            tab[j][i] = 1;
        }
    tab[(m-1)/2][(m-1)/2] = -1;
}

//feita
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

/*recebe ponteiros da posicao atual e a partir dela procura o espaço vazio(podendo retornar ela mesma.
no inicio do programa, a posicao atual será (0,0)
*/
//feita
int checaVazios(int ** tab, int m, int n, int * linha, int * coluna) {
    int i, j;

    i = *linha;
    j = *coluna;
    
    while (i < m) {
        while (j < n) {
            if (tab[i][j] == -1) {
                *linha = i;
                *coluna = j;
                return 1;
            }
            j++;
        }
        j = 0;
        i++;
    }

    //*linha = 0;
    //*coluna = 0;
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
//feita!
int verificaMovimento(int ** tab, int m, int n, int movimento, int linha, int coluna) {
    int pode = 0;

    if (tab[linha][coluna] != -1)
        return pode;
    switch (movimento) {
        case 1:
            if (coluna + 1 < n && coluna + 2 < n)
                if (tab[linha][coluna + 1] == 1 && tab[linha][coluna + 2] == 1)
                    pode = 1;
        break;
        
        case 2:
            if (linha - 1 >= 0 && linha - 2 > 0)
                if (tab[linha - 1][coluna] == 1 && tab[linha - 2][coluna] == 1)
                    pode = 1;
        break;

        case 3:
            if (coluna - 1 < n && coluna - 2 < n)
                if (tab[linha][coluna - 1] == 1 && tab[linha][coluna - 2] == 1)
                    pode = 1;
        break;

        case 4:
            if (linha + 1 < m && linha + 2 < m)
                if (tab[linha + 1][coluna] == 1 && tab[linha + 2][coluna] == 1)
                    pode = 1;
        break;
    }
    return pode;
}


/*a linha e coluna será empilhada nas respectivas pilhas, e o movimento também
feito*/
void movimenta(int ** tab, int movimento, int linha, int coluna) {
    tab[linha][coluna] = 1;
    
    switch (movimento) {
        case 1:
            tab[linha][coluna + 1] = -1;
            tab[linha][coluna + 2] = -1;
            break;
            
        case 2:
            tab[linha - 1][coluna] = -1;
            tab[linha - 2][coluna] = -1;
            break;

        case 3:
            tab[linha][coluna - 1] = -1;
            tab[linha][coluna - 2] = -1;
            break;

        case 4:
            tab[linha + 1][coluna] = -1;
            tab[linha + 2][coluna] = -1;
            break;
    }
}

// a posicao p é o desempilha da posicao
//feito
void desfazMovimento(int ** tab, int movimento, int linha, int coluna) {
    tab[linha][coluna] = -1;
    switch (movimento) {
        case 1:
            tab[linha][coluna + 1] = 1;
            tab[linha][coluna + 2] = 1;
            break;
            
        case 2:
            tab[linha - 1][coluna] = 1;
            tab[linha - 2][coluna] = 1;
            break;

        case 3:
            tab[linha][coluna - 1] = 1;
            tab[linha][coluna - 2] = 1;
            break;

        case 4:
            tab[linha + 1][coluna] = 1;
            tab[linha + 2][coluna] = 1;
            break;

    }
}

void jogo(int ** tab, int m, int n) {
    int ** tab_inverso, i, j, aux, movimentoAtual = 1, linhaAtual, colunaAtual, x, cont;
    pilha * movimentos, * linhas, * colunas;

    movimentos = criaPilha(m * n);
    linhas = criaPilha(m * n);
    colunas = criaPilha(m * n);
    linhaAtual = 0;
    colunaAtual = 0;
    
    scanf("%d", &x);
    /*cria matriz inversa e adiciona os espaços já existentes à lista*/
    tab_inverso = malloc(m * sizeof(int *));
    for (i = 0; i < n; i++)
        tab_inverso[i] = malloc(n * sizeof(int));

    for (i = 0; i < m; i++) 
        for (j = 0; j < n; j++) {
            if(tab[i][j] == 1) {
                tab_inverso[i][j] = -1;
            }
            else if(tab[i][j] == -1) {
                linhaAtual = i;
                colunaAtual = j;
                tab_inverso[i][j] = 1;
            }
            else
                tab_inverso[i][j] = 0;
        }


    /*VOLTAR AQUI*/
    
    while (!tabuleiroIgual(tab, tab_inverso, m, n) && cont < x) {
        //printf("linha atual = %d coluna atual = %d\n", linhaAtual, colunaAtual);
        if (checaVazios(tab, m, n, &linhaAtual, &colunaAtual))
        {
        if (verificaMovimento(tab, m, n, movimentoAtual, linhaAtual, colunaAtual)) {
            movimenta(tab, movimentoAtual, linhaAtual, colunaAtual);
            empilha(linhas, linhaAtual);
            empilha(colunas, colunaAtual);
            empilha(movimentos, movimentoAtual);
            linhaAtual = 0;
            colunaAtual = 0;
            movimentoAtual = 0;
            //imprimeMatriz(tab, m, n);
            //printf("\n");
        } 
        else if (movimentoAtual < 4) {
            movimentoAtual++;
        }
        else if(colunaAtual < n - 1) {
            //printf("if 2\n");
            //printf("coluna atual = %d linha atual = %d\n", colunaAtual, linhaAtual);
            colunaAtual++;
            movimentoAtual = 0;
        }
        else if(linhaAtual < m - 1) {
            //printf("if 3\n");
            linhaAtual++;
            colunaAtual = 0;
            movimentoAtual = 0;
        }
        }
        else { /*backtrack*/
            //printf("backtrack\n");
            if (pilhaVazia(*movimentos)) {
                printf("o problema não tem solução\n");
                return;
            } else {
                movimentoAtual = desempilha(movimentos);
                linhaAtual = desempilha(linhas);
                colunaAtual = desempilha(colunas);
                desfazMovimento(tab, movimentoAtual, linhaAtual, colunaAtual);
                movimentoAtual++;
            }
            //imprimeMatriz(tab, m, n);
            //printf("\n");
        }
            //printf("tentativa %d\n", cont);
        //imprimeMatriz(tab, m, n);
        //printf("\n");
        x++;
    }

    if (tabuleiroIgual(tab, tab_inverso, m, n)) {
        printf("tabuleiro igual\n");
        imprimeMatriz(tab, m, n);
    }
    else {
        printf("tabuleiro diferente\n");
        imprimeMatriz(tab, m, n);
    }

    destroiMatriz(tab, m);
    destroiMatriz(tab_inverso, m);
    destroiPilha(movimentos);
    destroiPilha(linhas);
    destroiPilha(colunas);
    return;
}
int main(int argc, char const *argv[])
{
    int ** tab, linha, coluna, movimento, l, c;
    
    tab = criaMatriz(7, 7);
    setJogo(tab, 7, 2);
    jogo(tab, 7, 7);
    
    return 0;
}