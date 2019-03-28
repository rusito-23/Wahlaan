#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../Wahlaan/Rii.h"

// MARK: -- randint auxiliar

u32
randint(u32 N)
{
    if ((N - 1) == RAND_MAX) {
        return (u32) rand();
    } else {
        assert (N <= RAND_MAX);

        int end = RAND_MAX / N;
        assert (end > 0);
        end *= N;

        int r;
        while ((r = rand()) >= end);

        return r % N;
    }
}

// MARK: -- TEST DE MULTIPLE EJECUCION PARA COLOREO

void
TestMultipleSwitchVertices(Grafo G, u32 cantidad)
{
    u32 N = NumeroDeVertices(G);

    if (N < cantidad) {
        printf("TestMultipleSwitchVertices: El grafo no tiene suficientes vértices \n");
        exit(1);
    }

    // inicializamos matriz auxiliar
    bool **used = calloc(N, sizeof(bool*));
    qfor(i, N) { used[i] = calloc(N, sizeof(bool)); }

    u32 v1 = randint(N);
    u32 v2 = randint(N);

    // repetimos la cantidad veces pedida
    qfor(o, cantidad) {

        // aseguramos que los vertices que switchemos
        // no fueron switcheados
        while (used[v1][v2] || used[v2][v1]) {
            v1 = randint(N);
            v2 = randint(N);
        }

        // switcheamos
        SwitchVertices(G, v1, v2);

        // los marcamos como usados
        used[v1][v2] = true;
        used[v2][v1] = true;

        // buscamos nuevos
        v1 = randint(N);
        v2 = randint(N);
    }

    // liberamos matrix auxiliar
    qfor(i, N) { free(used[i]); }
    free(used);
    used = NULL;
}

void
TestMultipleRMBC(Grafo G, u32 cantidad)
{

    // repetimos la cantidad de veces pedida
    qfor(i, cantidad) {

        // para cada uno, elegimos un RMBC distinto
        u32 rand = randint(3);
        switch (rand) {
            case 0:
                RMBCnormal(G);
                break;
            case 1:
                RMBCrevierte(G);
                break;
            case 2:
                RMBCchicogrande(G);
                break;
            default:
                RMBCnormal(G);
                break;
        }

        // corremos greedy de nuevo para buscar otro coloreo
        Greedy(G);
    }

}

// MARK: -- TESTS DE MULTIPLE EJECUCION PARA PERFORMANCE

void
TestMultipleSwitchVerticesRepeticion(Grafo G, u32 cantidad)
{
    u32 N = NumeroDeVertices(G);
    qfor(i, cantidad) {
        u32 v1 = randint(N);
        u32 v2 = randint(N);
        SwitchVertices(G, v1, v2);
    }
}

void
TestMultipleRMBChicoGrande(Grafo G, u32 cantidad) {
    qfor(i, cantidad) {
        RMBCchicogrande(G);
        Greedy(G);
    }
}
