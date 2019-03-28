#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Wahlaan/Rii.h"


// PRINTS

 void
printTitle(char *title)
{
    printf("***********");
    qfor(j, strlen(title)) { printf("*"); };
    printf("***********\n");

    printf("********** %s **********\n", title);

    printf("***********");
    qfor(j, strlen(title)) { printf("*"); };
    printf("***********\n");
    printf("\n\n");
}

void
printSection(char *section)
{
    printf("\n---------- %s -----------\n\n", section);
}

void
printGrafo(Grafo g)
{
    if (g != NULL) {
        printf("GRAFO -> N: %d, M:%d, D:%d, C: %d \n",
                NumeroDeVertices(g),
                NumeroDeLados(g),
                Delta(g),
                NumeroDeColores(g));

        // no imprimir los vertices si son demasiados
        if (NumeroDeVertices(g) > 10) { return; }

        qfor(i, g->N) {
            printf("nombre: %d, color: %d, grado: %d, vecinos: [",
                    NombreDelVertice(g, i),
                    ColorDelVertice(g, i),
                    GradoDelVertice(g, i));

            qfor(j, GradoDelVertice(g, i)) {
                printf(" %d ", NombreJotaesimoVecino(g, i, j));
            }
            printf("]\n");
        }

    } else {
        printf("PrintGrafo -> Error: el grafo es nulo \n");
    }
    printf("\n");
}
