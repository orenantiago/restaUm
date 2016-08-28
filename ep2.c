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

typedef struct {
    posicao * v;
    int topo;
} pilhaPosicao;

pilhaPosicao * criaPilhaPosicao(int n) {
    pilhaPosicao * p;
    p = malloc(sizeof(pilha));
    p -> v = malloc(n * sizeof(posicao));
    p -> topo = 0;
    return p;
}

void empilhaPosicao(pilhaPosicao * p, posicao x) {
    p -> v[p -> topo++] = x;
}

posicao desempilhaPosicao(pilhaPosicao * p) {
    p -> topo --;
    return p -> v[p -> topo];
}

int tamanhoPilhaPosicao(pilhaPosicao p) {
    return p.topo;
}

int pilhaPosicaoVazia(pilhaPosicao p) {
    if (p.topo == 0)
        return 1;
    else
        return 0;
}

void destroiPilhaPosicao(pilhaPosicao * p) {
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
void setJogo(int ** tab, int m, int dist) {
    int i, j;
    for(i = 0; i < m; i++)
        for (j = dist; j < m - dist; j++) {
            tab[i][j] = 1;
            tab[j][i] = 1;
        }
    tab[(m-1)/2][(m-1)/2] = -1;
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

    switch (movimento) {
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


/*lembrar de passar a posicao vinda do desempilha da pilha posicoes*/
void movimenta(int ** tab, posicao p, int movimento, pilhaPosicao * posicoesGeradas) {
    posicao aux;

    switch (movimento) {
        case 1:
            tab[p.linha][p.coluna] = 1;
            aux.linha = p.linha;
            aux.coluna = p.coluna + 1;
            
            tab[aux.linha][aux.coluna] = -1;
            empilhaPosicao(posicoesGeradas, aux);
            aux.coluna++;

            tab[aux.linha][aux.coluna] = -1;
            empilhaPosicao(posicoesGeradas, aux);

            break;
            
        case 2:
            tab[p.linha][p.coluna] = 1;
            aux.linha = p.linha - 1;
            aux.coluna = p.coluna;
            
            tab[aux.linha][aux.coluna] = -1;
            empilhaPosicao(posicoesGeradas, aux);
            aux.linha--;

            tab[aux.linha][aux.coluna] = -1;
            empilhaPosicao(posicoesGeradas, aux);

            break;

        case 3:
            tab[p.linha][p.coluna] = 1;
            aux.linha = p.linha;
            aux.coluna = p.coluna - 1;
            
            tab[aux.linha][aux.coluna] = -1;
            empilhaPosicao(posicoesGeradas, aux);
            aux.coluna--;

            tab[aux.linha][aux.coluna] = -1;
            empilhaPosicao(posicoesGeradas, aux);

            break;

        case 4:
            tab[p.linha][p.coluna] = 1;
            aux.linha = p.linha + 1;
            aux.coluna = p.coluna;
            
            tab[aux.linha][aux.coluna] = -1;
            empilhaPosicao(posicoesGeradas, aux);
            aux.linha++;

            tab[aux.linha][aux.coluna] = -1;
            empilhaPosicao(posicoesGeradas, aux);

            break;
    }
}

void jogo(int ** tab, int m, int n) {
    int ** T, i, j, aux, contMovimento = 1;
    pilhaPosicao * posicoes, * posicoesGeradas;
    pilha * movimento;
    posicao paux;

    posicoesGeradas = criaPilhaPosicao(m * n);//melhorar isso


    /*cria matriz inversa e adiciona os espaços já existentes à lista de espaços gerados*/
    T = malloc(m * sizeof(int *));
    for (i = 0; i < n; i++)
        T[i] = malloc(n * sizeof(int));

    
    for (i = 0; i < m; i++) 
        for (j = 0; j < n; j++) {
            if(tab[i][j] == 1)
                T[i][j] = -1;
            else if(tab[i][j] == -1) {
                paux.linha = i;
                paux.coluna = j;
                empilhaPosicao(posicoesGeradas, paux);
                T[i][j] = 1;
            }
            else
                T[i][j] = 0;
        }

    /*VOLTAR AQUI!*/

    if (tabuleiroIgual(tab, T, m, n))
        printf("tabuleiro igual\n");
    else
        printf("tabuleiro diferente\n");

    destroiPilhaPosicao(posicoesGeradas);
    destroiMatriz(tab, m);
    destroiMatriz(T, m);
}
int main(int argc, char const *argv[])
{
    int ** tab;
    tab = criaMatriz(7, 7);
    setJogo(tab, 7, 2);
    jogo(tab, 7, 7);

    
    return 0;
}