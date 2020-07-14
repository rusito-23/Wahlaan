#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Rii.h"

// MARK: -- DFS

static bool
DFS(u32 current, bool* visited, Grafo G)
{
    // inicializo variables
    u32 CURRENT_COLOR = G->colors[current];
    u32 NEXT_COLOR = CURRENT_COLOR == WHITE ? BLACK : WHITE;
    bool res = true;

    qfor(j, G->grade[current]) {

        // buscamos el vecino
        u32 neighbour = G->neighbours[current][j];

        // si no está visitado
        if (!visited[neighbour]) {

            // lo marco como visitado y lo pinto
            visited[neighbour] = true;
            G->colors[neighbour] = NEXT_COLOR;
            G->compartidos[NEXT_COLOR]++;

            // volver a correr BFS sobre el vecino
            res &= DFS(neighbour, visited, G);

        // si está visitado debería tener el mismo color que el padre
        } else if (G->colors[neighbour] == CURRENT_COLOR) {
            res = false;
        }

    }
    return res;
}

int
Bipartito(Grafo G)
{
    // decoloreamos el grafo
    memset(G->colors, NO_COLOR, (G->N)*sizeof(u32));
    memset(G->compartidos, 0, (G->D + 1)*sizeof(u32));

    // inicializamos variables
    bool bipartito = true;
    bool *visited = calloc(G->N, sizeof(bool));

    // recorremos los vertices,
    // corriendo DFS sobre cada componente conexa
    qfor(i, G->N) {

      // buscamos componentes conexas no recorridas
      if(!visited[i]) {
        G->colors[i] = WHITE;
        G->compartidos[WHITE]++;
        visited[i] = true;
        bipartito &= DFS(i, visited, G);

        // cortamos el recorrido si encontramos que no es bipartito
        if (!bipartito) { break; }
      }

    }

    // liberamos arrglo auxiliar
    free(visited);
    visited = NULL;

    // calculamos resultados finales
    if (!bipartito) { Greedy(G); }
    else { G->C = 2; }
    return bipartito ? 1 : 0;
}
