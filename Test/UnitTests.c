#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include "Tests.h"
#include "../Wahlaan/Rii.h"

// COLOREO

void
TestGreedy(Grafo G)
{
    u32 N = NumeroDeVertices(G);

    printTitle("TestGreedy");
    u32 colors = Greedy(G);
    printf("Resultado Greedy -> %d \n", colors);

    // validamos que el coloreo sea propio
    qfor(i, N) {
        qfor(j, OrdenDelVertice(G, i)) {
            assert(ColorDelVertice(G, i) != ColorJotaesimoVecino(G, i, j));
        }
    }
}

void
TestBipartito(Grafo G)
{
    printTitle("TestBipartito");

    u32 N = NumeroDeVertices(G);
    int bipartito = Bipartito(G);
    printf("Resultado bipartito -> %d \n", bipartito);

    // validamos que el coloreo sea propio
    qfor(i, N) {
        qfor(j, GradoDelVertice(G, i)) {
            assert(ColorDelVertice(G, i) != ColorJotaesimoVecino(G, i, j));
        }
    }
}

// ORDEN

void
TestOrdenNatural(Grafo G)
{
    u32 N = NumeroDeVertices(G);
    printTitle("OrdenNatural");
    OrdenNatural(G);

    // validamos el orden
    qfor(i, N - 1) {
        assert(NombreDelVertice(G, i) < NombreDelVertice(G, i+1));
    }
}


void
TestOrdenWelshPowell(Grafo G)
{
    u32 N = NumeroDeVertices(G);
    printTitle("TestOrdenWelshPowell");
    OrdenWelshPowell(G);

    // validamos el orden
    qfor(i, N - 1) {
        assert(GradoDelVertice(G, i) >= GradoDelVertice(G, i+1));
    }
}

void
TestSwitchVertices(Grafo G)
{
    u32 N = NumeroDeVertices(G);
    printTitle("TestSwitchVertices");

    // generar dos vertices random
    u32 v1 = randint(N);
    u32 v2 = randint(N);

    // guardamos los nombres para luego validar
    u32 name_1 = NombreDelVertice(G, v1);
    u32 name_2 = NombreDelVertice(G, v2);

    char res = SwitchVertices(G, v1, v2);
    if (res == 1) { printf("--- SwitchVertices returned 1! ---\n"); }
    else {
        // validamos que se hayan cambiado los vertices
        assert(NombreDelVertice(G, v1) == name_2);
        assert(NombreDelVertice(G, v2) == name_1);
    }

}


void
TestSwitchColores(Grafo G)
{
    printTitle("TestSwitchColores");

    u32 C = NumeroDeColores(G);
    // generar dos colores random
    printSection("Test Case Exitoso");
    u32 c1 = randint(C) + 1;
    u32 c2 = randint(C) + 1;
    char res = SwitchColores(G, c1, c2);
    assert (res == 0);

    // asignar un número que debe generar error
    printSection("Test Case Error");
    c1 = C + 1;
    res = SwitchColores(G, c1, c2);
    assert(res == 1);
}

void
TestOrdenRMBCNormal(Grafo G)
{
    printTitle("TestOrdenRMBCNormal");
    RMBCnormal(G);

    u32 N = NumeroDeVertices(G);
    // chequeamos que los vertices estén ordenados
    // de manera ascendiente por color
    qfor(i, (N - 1)) {
        u32 color = ColorDelVertice(G, i);
        u32 next_color = ColorDelVertice(G, i+1);

        assert(color <= next_color);
    }

}

void
TestOrdenRMBCInverso(Grafo G)
{
    printTitle("TestOrdenRMBCInverso");
    RMBCrevierte(G);

    u32 N = NumeroDeVertices(G);
    // chequeamos que los vertices estén ordenados
    // de manera descendiente por color
    qfor(i, (N - 1)) {
        u32 color = ColorDelVertice(G, i);
        u32 next_color = ColorDelVertice(G, i+1);

        assert(color >= next_color);
    }

}

void
TestOrdenRMBchicogrande(Grafo G)
{
    printTitle("TestOrdenRMBchicogrande");
    RMBCchicogrande(G);

    u32 C = NumeroDeColores(G);
    u32 N = NumeroDeVertices(G);

    u32 *compartidos = calloc(C, sizeof(u32)); // color -> cantidad de vertices con ese color
    if(compartidos == NULL){ // error al hacer el malloc
        printf("TestOrdenRMBchicogrande: Error al hacer el malloc! \n");
        exit(1);
    };

    // contamos cantidad de vertices que comparte cada color
    qfor(i, N) {
        u32 color = ColorDelVertice(G, i);
        compartidos[--color]++;
    }

    // chequeamos que los vertices tengan el orden que deberían tener
    qfor(i, (N - 1)) {
        u32 color = ColorDelVertice(G, i);
        u32 next_color = ColorDelVertice(G, i+1);

        assert(compartidos[color - 1] <= compartidos[next_color - 1]);
    }

    free(compartidos);
    compartidos = NULL;
}
