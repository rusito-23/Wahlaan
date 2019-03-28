#include <stdbool.h>
#include "../Wahlaan/Rii.h"

#ifndef LUCEROANDRUSKIEWITSCH_TESTS_H
#define LUCEROANDRUSKIEWITSCH_TESTS_H

// PERFORMANCE CONTROL
#define roundz(x,d) ((floor(((x)*pow(10,d))+.5))/pow(10,d))
#define TICK(X) clock_t X = clock()
#define TOCK(X) printf("FIN: Tiempo de ejecución de %s: %g min.\n\n", (#X), \
                      roundz((((double) clock() - (X)) / CLOCKS_PER_SEC) / (double) 60.0, 2))
#define PARTIAL_TOCK(X, SECTION) printf("PARTIAL: Tiempo de ejecución de %s: %g min.\n\n", SECTION, \
                                roundz((((double) clock() - (X)) / CLOCKS_PER_SEC) / (double) 60.0, 2))

// MARK: -- SUITES

enum Suite {
    SANITY,
    PERFORMANCE,
    COLOR,
    BIPARTITO,
    NONE
};

enum Suite SuiteFromString(char * str);

void SanitySuite();

void ColorSuite();

void PerformanceSuite();

void BipartitoSuite();

// MARK: -- HELPERS

u32 randint(u32 N);
// devuelve un número random entre 0 y N

void printTitle(char *title);
// función de print para un título

void printSection(char *section);
// función de print para una sección

void printGrafo(Grafo grafo);
// mostrar datos de un grafo

// MARK: -- TEST DE UNIDAD

// COLOREO

void TestGreedy(Grafo G);

void TestBipartito(Grafo G);

// MULTIPLES

void TestMultipleSwitchVertices(Grafo G, u32 cantidad);
// Switchea vertices la cantidad de veces indicada, sin repetición de vértices
// sirve para probar coloreos porque tiene un orden alto

void TestMultipleSwitchVerticesRepeticion(Grafo G, u32 cantidad);
// Switchea vertices la cantidad de veces indicada, con repetición de vértices
// esta función es para testear performance, porque no va a dar buenos resultados
// a la hora de probar coloreos

void TestMultipleRMBC(Grafo G, u32 cantidad);
// Testea distintos RMBCs la cantidad de veces indicada
// no sirve para probar performance ya que el randint es costoso

void TestMultipleRMBChicoGrande(Grafo G, u32 cantidad);
// Testea la cantidad dada de RMBCs chicoGrande
// usamos esta para performance ya que es la más costosa de los RMBC
// y nos ahorramos el cálculo del randint

// ORDEN

void TestOrdenNatural(Grafo G);

void TestOrdenWelshPowell(Grafo G);

void TestSwitchVertices(Grafo G);

void TestSwitchColores(Grafo G);

void TestMultipleSwitchVertices(Grafo G, u32 cantidad);

void TestOrdenRMBCNormal(Grafo G);

void TestOrdenRMBCInverso(Grafo G);

void TestOrdenRMBchicogrande(Grafo G);



#endif //LUCEROANDRUSKIEWITSCH_TESTS_H
