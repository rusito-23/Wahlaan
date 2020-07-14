#include <stdlib.h>
#include <stdio.h>
#include "Rii.h"

// MARK: -- OrdenNatural

char
OrdenNatural(Grafo G)
{
    qfor(i, G->N) {
        G->order[i] = i;
    }
    return 0;
}

// MARK: -- OrdenWelshPowell

static int
OrdenWelshPowellComparator(const void *a, const void *b)
{
    // recuperamos el grafo
    static Grafo G;
    if (a == NULL) {
        G = *(const Grafo*) b;
        return 0;
    }

    // inicializamos grados
    u32 grado_a = G->grade[*(const u32*) a];
    u32 grado_b = G->grade[*(const u32*) b];

    // comparamos
    return grado_a > grado_b ? -1 : 1;
}

char
OrdenWelshPowell(Grafo G)
{
    OrdenWelshPowellComparator(NULL, &G);
    qsort(G->order, G->N, sizeof(u32), OrdenWelshPowellComparator);
    return 0;
}

// MARK: -- Funciones de switch

char
SwitchVertices(Grafo G, u32 i,u32 j)
{
    if (i >= G->N || j >= G->N) return 1;

    u32 temp = G->order[i];
    G->order[i] = G->order[j];
    G->order[j] = temp;

    return 0;
}

char
SwitchColores(Grafo G, u32 i, u32 j)
{
    if ( i >= ( G->C + 1 ) || j >= ( G->C + 1 ) ) { return 1; }
    qfor(k, G->N) {
        if (G->colors[k] == i) { G->colors[k] = j; }
        else if (G->colors[k] == j) { G->colors[k] = i; }
    }

    // switcheamos cantidad de compartidos
    u32 temp = G->compartidos[i];
    G->compartidos[i] = G->compartidos[j];
    G->compartidos[j] = temp;

    return 0;
}
