#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "Rii.h"

u32
Greedy(Grafo G)
{
    // inicializamos variables auxiliares
    u32 max_color = MIN_COLOR;
    u32 delta = G->D + 1;

    // despintamos el grafo
    memset(G->colors, NO_COLOR, G->N*sizeof(u32));
    memset(G->compartidos, 0, (delta)*sizeof(u32));

    // recorremos los vértices del grafo en el orden dado
    qfor(i, G->N) {
        // obtenemos la información del vértice
        u32 label = G->order[i];
        u32 grade = GradoDelVertice(G, i);

        // volvemos a setear todos los colores como no usados
        memset(G->used, false, delta*sizeof(bool));

        // recorremos los vecinos y guardamos los colores que usan
        qfor(j, grade) {
            u32 n_color = ColorJotaesimoVecino(G, i, j);
            if (n_color != NO_COLOR) {
                G->used[n_color] = true;
            }
        }

        // buscamos el menor color con el que podríamos pintarlo
        // siempre que no haya sido usado por un vecino
        u32 color;
        for(color = MIN_COLOR; color < delta; color++) {
            if (!G->used[color]) { break; }
        }

        // escribimos el color
        G->colors[label] = color;
        G->compartidos[color]++;

        // calculamos el color máximo
        if (color > max_color) max_color=color;

    }

    // guardamos el color máximo
    max_color++;
    G->C = max_color;
    return max_color;
}
