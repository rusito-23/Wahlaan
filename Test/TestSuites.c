#include "../Wahlaan/Rii.h"
#include "Tests.h"
#include <stdio.h>
#include <zconf.h>
#include <time.h>
#include <string.h>


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
    Greedy(G);
    PARTIAL_TOCK(CORRIDAS, "Greedy");

    // greedy con welsh powell
    OrdenWelshPowell(G);
    Greedy(G);
    PARTIAL_TOCK(CORRIDAS, "WelshPowell con Greedy");

    // 100 switch vertices
    TestMultipleSwitchVerticesRepeticion(G, 100);
    PARTIAL_TOCK(CORRIDAS, "100 SwitchVertices");

    // 1000 RMBC
    TestMultipleRMBC(G, 1000);
    PARTIAL_TOCK(CORRIDAS, "1000 RMBCs");

    // Fin testeo de corridas
    TOCK(CORRIDAS);

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
    int bipartito = Bipartito(G);
    bipartito == 1 ? printf("El grafo es bipartito \n\n") : printf("El grafo NO ES BIPARTITO \n\n");

    // destrucction
    DestruccionDelGrafo(G);
}
