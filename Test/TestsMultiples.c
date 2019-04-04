#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <zconf.h>
#include <time.h>
#include "../Wahlaan/Rii.h"
#include "Tests.h"

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
    bool print = cantidad > 300; // solo vamos a hacer print si son muchas vueltas
    char (*rmbcs[3])(Grafo) = {RMBCnormal, RMBCrevierte, RMBCchicogrande};
    char *str = malloc(15*sizeof(char));

    TICK(VUELTA);
    if (print) printf("INIT: TestMultipleRMBC : %d vueltas : \n\n", cantidad);

    // seteamos el greedy como valor máximo
    u32 last_greedy = 0b11111111111111111111111111111111;

    // repetimos la cantidad de veces pedida
    qfor(i, cantidad) {

        // para cada uno, elegimos un RMBC distinto
        rmbcs[i%3](G);

        // resultados parciales por 100 vueltas
        if (!(i%100) && (i != 0) && print) {
            sprintf(str, "vuelta %d", i);
            PARTIAL_TOCK(VUELTA, str);
        }

        // corremos greedy de nuevo para buscar otro coloreo
        u32 new_greedy = Greedy(G);

        // RMBC nunca debe bajar el coloreo!
        if (last_greedy < new_greedy) {
            printf("ERROR: RMBC: coloreo anterior: %d -- coloreo actual %d \n", last_greedy, new_greedy);
        }
        last_greedy = new_greedy;
    }

    free(str);
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
