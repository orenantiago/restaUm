#include <stdio.h>
#include <stdlib.h>
#define debug(args...) //printf(args)

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
            if(tab[i][j] == -1)
                printf("x ");
            else
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
//feita!
int verificaMovimento(int ** tab, int m, int n, int movimento, int linha, int coluna) {
    int pode = 0;

    if (tab[linha][coluna] != 1)
        return pode;
    switch (movimento) {
        case 1:
            if (coluna + 1 < n && coluna + 2 < n)
                if (tab[linha][coluna + 1] == 1 && tab[linha][coluna + 2] == -1)
                    pode = 1;
        break;
        
        case 2:
            if (linha - 1 > 0 && linha - 2 >= 0)
                if (tab[linha - 1][coluna] == 1 && tab[linha - 2][coluna] == -1)
                    pode = 1;
        break;

        case 3:
            if (coluna - 1 > 0 && coluna - 2 >= 0)
                if (tab[linha][coluna - 1] == 1 && tab[linha][coluna - 2] == -1)
                    pode = 1;
        break;

        case 4:
            if (linha + 1 < m && linha + 2 < m)
                if (tab[linha + 1][coluna] == 1 && tab[linha + 2][coluna] == -1)
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

// a posicao p é o desempilha da posicao
//feito
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
    int ** tab_inverso, i, j, movimentoAtual, linhaAtual, colunaAtual, cont;
    pilha * movimentos, * linhas, * colunas;

    movimentos = criaPilha(m * n);
    linhas = criaPilha(m * n);
    colunas = criaPilha(m * n);

    linhaAtual = 0;
    colunaAtual = 0;
    movimentoAtual = 1;
    
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
                tab_inverso[i][j] = 1;
            }
            else
                tab_inverso[i][j] = 0;
        }

    linhaAtual = 0;
    colunaAtual = 0;
    /*VOLTAR AQUI*/
    while (!tabuleiroIgual(tab, tab_inverso, m, n)) {
        if (checaPecas(tab, m, n, &linhaAtual, &colunaAtual)) {
            if (verificaMovimento(tab, m, n, movimentoAtual, linhaAtual, colunaAtual)) {
                movimenta(tab, movimentoAtual, linhaAtual, colunaAtual);
                
                empilha(linhas, linhaAtual);
                empilha(colunas, colunaAtual);
                empilha(movimentos, movimentoAtual);
                
                //printf("movimenta (%d, %d) %d\n", linhaAtual + 1, colunaAtual + 1, movimentoAtual);
                linhaAtual = 0;
                colunaAtual = 0;
                movimentoAtual = 1;
                
                //imprimeMatriz(tab, m, n);
                //printf("\n");
                cont++;
            } 
            else if (movimentoAtual < 4) {
                //printf("movimento atual Não rola %d\n", movimentoAtual);
                movimentoAtual++;
            }
            else if(colunaAtual < n && linhaAtual < m) {
                colunaAtual = (colunaAtual + 1) % n;
                movimentoAtual = 1;
                if(colunaAtual == 0)
                    linhaAtual++;
                //debug("procura proximo\n");
            }
        }
        else { /*backtrack*/
            //debug("desfaz movimento");
            printf("%d\n", movimentos -> topo);
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
        }
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
    int ** tab, linha, coluna, movimento, l, c;
    
    tab = criaMatriz(5, 5);
    setJogo(tab, 5, 1);
    //imprimeMatriz(tab, 5, 5);
    jogo(tab, 5, 5);
    
    return 0;
}