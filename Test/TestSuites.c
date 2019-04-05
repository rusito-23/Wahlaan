#include "../Wahlaan/Rii.h"
#include "Tests.h"
#include <stdio.h>
#include <zconf.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


enum Suite
SuiteFromString(char * str)
{
    if (strcmp(str, "SANITY") == 0) {
        return SANITY;
    } else if (strcmp(str, "PERFORMANCE") == 0) {
        return PERFORMANCE;
    } else if (strcmp(str, "COLOR") == 0) {
        return COLOR;
    } else if (strcmp(str, "BIPARTITO") == 0) {
        return BIPARTITO;
    } else if (strcmp(str, "CUSTOM") == 0) {
        return CUSTOM;
    } else {
        return NONE;
    }
}

void
ColorSuite()
{
    printTitle("COLOR SUITE");

    // toma de grafo
    Grafo G = ConstruccionDelGrafo();
    if (G == NULL) {
        printf("Ocurrió un error al tomar el grafo! \n\n\n\n");
        _exit(1);
    }

    u32 colors;

    // natural
    OrdenNatural(G);
    colors = Greedy(G);
    printf("Greedy con orden natural: %d \n\n", colors);

    // welsh powell
    OrdenWelshPowell(G);
    colors = Greedy(G);
    printf("Greedy con orden WelshPowell: %d \n\n", colors);

    // 100 switch vertices
    TestMultipleSwitchVertices(G, 100);
    colors = Greedy(G);
    printf("Greedy con 100 SwitchVertices: %d \n\n", colors);

    // 100 RMBCs
    TestMultipleRMBC(G, 100);
    colors = Greedy(G);
    printf("Greedy con 100 RMBCs: %d \n\n\n\n", colors);

    // destrucction
    DestruccionDelGrafo(G);
}


void
SanitySuite()
{
    printTitle("SANITY SUITE");

    // toma de grafo
    Grafo G = ConstruccionDelGrafo();
    if (G == NULL) {
        printf("Ocurrió un error al tomar el grafo! \n\n\n");
        _exit(1);
    }

    printGrafo(G);

    TestCopiaDeGrafo(G);

    TestGreedy(G);

    TestBipartito(G);

    TestOrdenNatural(G);

    TestOrdenWelshPowell(G);

    TestSwitchVertices(G);

    TestSwitchColores(G);

    TestOrdenRMBCNormal(G);

    TestOrdenRMBCInverso(G);

    TestOrdenRMBchicogrande(G);

    printGrafo(G);

    // destrucction
    DestruccionDelGrafo(G);
    printf("\n\n\n");
}


void
PerformanceSuite()
{
    printTitle("PERFORMANCE SUITE");

    TICK(TOTAL);

    // Toma del grafo
    TICK(TOMA_DE_GRAFO);
    Grafo G = ConstruccionDelGrafo();
    TOCK(TOMA_DE_GRAFO);

    printGrafo(G);
    printf("\n\n");
    if (G == NULL) { printSection("Error al cargar el grafo!"); return; }

    // Testeo de corridas
    TICK(CORRIDAS);

    // greedy con orden natural
    TICK(GREEDY);
    Greedy(G);
    PARTIAL_TOCK(GREEDY, "Greedy");

    // greedy con welsh powell
    TICK(GREEDY_WP);
    OrdenWelshPowell(G);
    Greedy(G);
    PARTIAL_TOCK(GREEDY_WP, "WelshPowell con Greedy");

    // 100 switch vertices
    TICK(SWV);
    TestMultipleSwitchVerticesRepeticion(G, 100);
    PARTIAL_TOCK(SWV, "100 SwitchVertices");

    // 1000 RMBC
    TICK(RMBC);
    TestMultipleRMBC(G, 1000);
    PARTIAL_TOCK(RMBC, "1000 RMBCs");

    // Fin testeo de corridas
    TOCK(CORRIDAS);

    // Fin de todos los testeos
    TOCK(TOTAL);

    // destrucction
    DestruccionDelGrafo(G);
}


void
BipartitoSuite()
{
    printTitle("BIPARTITO SUITE");

    // toma de grafo
    Grafo G = ConstruccionDelGrafo();
    if (G == NULL) {
        printf("Ocurrió un error al tomar el grafo! \n");
        _exit(1);
    }

    u32 colors;

    // natural
    OrdenNatural(G);
    colors = Greedy(G);
    printf("Greedy con orden natural: %d \n\n", colors);

    // bipartito
    int bipartito = TestBipartito(G);
    bipartito == 1 ? printf("El grafo es bipartito \n\n") : printf("El grafo NO ES BIPARTITO \n\n");

    // destrucction
    DestruccionDelGrafo(G);
}


#define FNUM 3

struct fnc {
    char (*addr)(Grafo);
    char name[32];
};

void
CustomSuite()
{
    printTitle("CUSTOM SUITE");

    static struct fnc fnames[FNUM];

    fnames[0] = (struct fnc){RMBCnormal, "TestOrdenRMBCNormal"};
    fnames[1] = (struct fnc){RMBCrevierte, "TestOrdenRMBCInverso"};
    fnames[2] = (struct fnc){RMBCchicogrande, "TestOrdenRMBchicogrande"};

    // toma de grafo
    Grafo G = ConstruccionDelGrafo();
    if (G == NULL) {
        printf("Ocurrió un error al tomar el grafo! \n");
        _exit(1);
    }

    u32 cantidad = 100;

    // seteamos el greedy como valor máximo
    u32 last_greedy = 0b11111111111111111111111111111111;

    u32 error = 0;
    // repetimos la cantidad de veces pedida
    qfor(i, cantidad) {

        // para cada uno, elegimos un RMBC distinto
        struct fnc rmbc = fnames[i%3];
        rmbc.addr(G);

        // corremos greedy de nuevo para buscar otro coloreo
        u32 new_greedy = Greedy(G);

        // RMBC nunca debe bajar el coloreo!
        if (last_greedy < new_greedy) {
            error++;
            printf("ERROR: RMBC: %s coloreo anterior: %d -- coloreo actual %d \n",
                    rmbc.name,
                    last_greedy,
                    new_greedy);
        }
        last_greedy = new_greedy;
    }

    printf("Errores: %d \n", error);
}
