#include <stdbool.h>
#include "../Wahlaan/Rii.h"

#ifndef LUCEROANDRUSKIEWITSCH_TESTS_H
#define LUCEROANDRUSKIEWITSCH_TESTS_H

// MACROS
#ifndef qfor
#define qfor(i,n) for(u32 i=0; i<n; ++i)
#endif

// COLORS
#ifndef COLORS
#define COLORS
#define NO_COLOR (u32) 0b11111111111111111111111111111111
#define MAX_VALUE (u32) 0b11111111111111111111111111111111
#define MIN_COLOR 0
#define WHITE 0
#define BLACK 1
#endif

    // PERFORMANCE CONTROL
#define roundz(x,d) ((floor(((x)*pow(10,d))+.5))/pow(10,d))
#define SECONDS(X) roundz((((double) clock() - (X)) / CLOCKS_PER_SEC), 2)
#define MINUTES(X) roundz(SECONDS(X) / (double) 60.0, 2)
#define TICK(X) clock_t X = clock()
#define TOCK(X) printf("FIN: Tiempo de ejecución de %s: %g %s.\n\n", (#X), \
                            MINUTES(X) < 1 ? SECONDS(X): MINUTES(X), \
                        MINUTES(X) < 1 ? "sec" : "min")
#define PARTIAL_TOCK(X, SECTION) printf("PARTIAL: Tiempo de ejecución de %s: %g %s.\n\n", SECTION, \
                        MINUTES(X) < 1 ? SECONDS(X): MINUTES(X), \
                        MINUTES(X) < 1 ? "sec" : "min")

// MARK: -- SUITES

enum Suite {
    SANITY,
    PERFORMANCE,
    COLOR,
    BIPARTITO,
    CUSTOM,
    NONE
};

enum Suite SuiteFromString(char * str);

void SanitySuite();

void ColorSuite();

void PerformanceSuite();

void BipartitoSuite();

void CustomSuite();

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

// MARK: -- COLOREO

void TestGreedy(Grafo G);

int TestBipartito(Grafo G);

// MARK: -- MULTIPLES

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

// MARK: -- ORDEN

void TestOrdenNatural(Grafo G);

void TestOrdenWelshPowell(Grafo G);

void TestSwitchVertices(Grafo G);

void TestSwitchColores(Grafo G);

void TestMultipleSwitchVertices(Grafo G, u32 cantidad);

void TestOrdenRMBCNormal(Grafo G);

void TestOrdenRMBCInverso(Grafo G);

void TestOrdenRMBchicogrande(Grafo G);

void TestCopiaDeGrafo(Grafo G);

// MARK: -- Funciones de testeo

void ValidarColoreo(Grafo G);

#endif //LUCEROANDRUSKIEWITSCH_TESTS_H
