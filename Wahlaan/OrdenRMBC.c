#include "Rii.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// MARK: -- RMBC

static char
RMBC(Grafo G, bool normal)
{
    // inicializamos matriz auxiliar
    u32 **aux = malloc(G->C * sizeof(u32*));
    if (aux == NULL) { return 1; }
    qfor(color, G->C) {
        aux[color] = malloc(G->compartidos[color] * sizeof(u32));
        if (aux[color] == NULL) { return 1; }
    }

    // populamos la matriz
    // al usar el color como índice, aseguramos el
    // orden al recorrerla //Mas diez y a favoritos maquinola : )
    memset(G->compartidos, 0, (G->D+1) * sizeof(u32));
    qfor(vert, G->N) {
        u32 color = G->colors[vert];
        aux[color][G->compartidos[color]++] = vert;
    }

    // copiamos el orden de la matriz al grafo
    u32 order = normal ? 0 : G->N - 1;
    qfor(color, G->C) {
        qfor(label, G->compartidos[color]) {
            G->order[order] = aux[color][label];
            normal ? order++ : order--;
        }
    }

    // liberamos la memoria
    qfor(i, G->C) {
        free(aux[i]);
    }; free(aux);

    return 0;
}

// MARK: -- RMBCNormal

char
RMBCnormal(Grafo G)
{
    return RMBC(G, true);
}

// MARK: -- RMBCrevierte

char
RMBCrevierte(Grafo G)
{
    return RMBC(G, false);
}

// MARK: -- RMBCchicogrande

static int
RMBCchicograndeComparator(const void *a, const void *b)
{

    // recuperamos los colores
    static u32 *colors;
    if (a == NULL) {
        colors = (u32*) b;
        return 0;
    }

    // recuperamos los bloques
    static u32 *compartidos;
    if (b == NULL) {
        compartidos = (u32 *) a;
        return 0;
    }

    // inicializamos colores
    u32 color_a = colors[*(u32 *) a];
    u32 color_b = colors[*(u32 *) b];

    if (color_a == color_b) {
        // si los colores coinciden, no nos importa
        return 0;
    }
    else if(compartidos[color_a] == compartidos[color_b]) {
        // si la cantidad de colores que poseen compartidos son iguales
        return color_a < color_b ? -1 : 1;

    }
    else {
        // si no comparten el color
        // comparamos según los compartidos de cada uno
        return compartidos[color_a] < compartidos[color_b] ? -1 : 1;
    }
}

char
RMBCchicogrande(Grafo G)
{
    // inicializamos variables auxiliares
    if(G->compartidos == NULL){return 0;};

    RMBCchicograndeComparator(G->compartidos, NULL); // seteamos los bloques en el comparador
    RMBCchicograndeComparator(NULL, G->colors); // seteamos los colores en el comparador

    // ordenamos
    qsort(G->order, G->N, sizeof(u32), RMBCchicograndeComparator);

    return 0;
}
