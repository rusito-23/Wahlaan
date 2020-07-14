// SPECIFICATION FILE
//
//      Rodrigo Lucero              ( lucero.rodrigoar@gmail.com )
//      Igor Andruskiewitsch        ( i.andruskiewitsch23@gmail.com )
//

/* TODO:
  - preguntar como debería ser la implementación de los test a la hora de probar la performance
  - agregar manejo de error para todos los alloc que haya!
*/

#ifndef RII_H
#define RII_H

// INCLUDES
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

// MACROS
#define qfor(i,n) for(u32 i=0; i<n; ++i)

// COLORS
#ifndef COLORS
#define COLORS
#define NO_COLOR (u32) 0b11111111111111111111111111111111
#define MAX_VALUE (u32) 0b11111111111111111111111111111111
#define MIN_COLOR 0
#define WHITE 0
#define BLACK 1
#endif

// DATA TYPES:
typedef uint32_t u32;

// GRAPH STRUCT

typedef struct {
    // Datos del grafo
    u32 N;              // cantidad de vértices
    u32 M;              // cantidad de aristas
    u32 D;              // Delta : grado máximo
    u32 C;              // cantidad de colores

    // Datos de vértices
    u32 *order;         // posicion          ---> label
    u32 *names;         // label             ---> nombre
    u32 *grade;         // label             ---> grado
    u32 *colors;        // label             ---> color
    u32 **neighbours;   // (label, posicion) ---> label de vecino

    // Arreglo auxiliar para la corrida de greedy
    bool *used;         // color             ---> está siendo usado por un vecino?

    // Arreglos auxiliares para RMBCs
    u32 *compartidos;   // color             ---> cantidad de vértices compartidos

}GrafoSt, *Grafo ;


// FUNCTIONS:

/*
 * GRAFO
 * */

Grafo ConstruccionDelGrafo(); // ManejoDeGrafo.c
/* Esta función aloca memoria, inicializa lo que haya que inicializar de una estructura GrafoSt,
 * lee un grafo desde standard input en el formato indicado en la seccíon 9,
 * lo carga en la estructura, incluyendo algún orden de los vertices, corre Greedy con ese orden
 * para dejar todos los vertices coloreados y devuelve un puntero a la estructura. */

void DestruccionDelGrafo(Grafo G); // ManejoDeGrafo.c
/* Destruye G y libera la memoria alocada. */

Grafo CopiarGrafo(Grafo G); // ManejoDeGrafo.c
/*  La funcíon aloca memoria suficiente para copiar todos los datos guardados en G,
 *  hace una copia de G en esa memoria y devuelve un puntero a esa memoria. */

/*
 * COLOREO
 * */

u32 Greedy(Grafo G); // Greedy.c
/* Corre greedy en G con el orden interno que debe estar guardado de alguna forma dentro de G.
 * Devuelve el numero de colores que se obtiene. */

int Bipartito(Grafo G); // Bipartito.c
/* Devuelve 1 si G es bipartito, 0 si no.
 * Si es bipartito, deja a G coloreado en forma propia con los colores 0 y 1.
 * Si devuelve 0, antes debe colorear a G con Greedy, en algún orden. */


/*
 *  INFO DEL GRAFO Y LOS VÉRTICES
 * */

u32 NumeroDeVertices(Grafo G); // DatosDeGrafo.c
/* O(1) */

u32 NumeroDeLados(Grafo G); // DatosDeGrafo.c
/* O(1) */

u32 NumeroDeColores(Grafo G); // DatosDeGrafo.c
/* O(1) */

u32 NombreDelVertice(Grafo G, u32 i); // DatosDeVertices.c
/* Devuelve el nombre real del v́ertice número i
 * en el orden guardado en ese momento en G.*/

u32 ColorDelVertice(Grafo G, u32 i); // DatosDeVertices.c
/* Devuelve el color con el que est́a coloreado el v́ertice número i en el orden guardado en ese momento en G.
 * Si i es mayor o igual que el número de v́ertices, devuelve 232 −1. */

u32 GradoDelVertice(Grafo G, u32 i); // DatosDeVertices.c
/* Devuelve el el grado del v́ertice número i en el orden guardado en ese momento en G.
 * Si i es mayor o igual que el número de v́ertices, devuelve 232 −1. */

u32 LabelDelVertice(Grafo G, u32 name); // DatosDeVertices.c
/* Devuelve el label de un vértice dado su nombre real (el dado en el archivo) */

u32 ColorJotaesimoVecino(Grafo G, u32 i,u32 j); // DatosDeVertices.c
/* Devuelve el color del v́ecino numero j (en el orden en que lo tengan guardado uds. en G,
 * con el  ́ındice 0 indicando el primer v́ecino, el  ́ındice 1 el segundo, etc)) del v́ertice número i
 * en el orden guardado en ese momento en G. */

u32 NombreJotaesimoVecino(Grafo G, u32 i,u32 j); // DatosDeVertices.c
/* Devuelve el nombre del v́ecino numero j */

/*
 * ORDENAMIENTO
 * */

char OrdenNatural(Grafo G); // Orden.c
/* Ordena los vertices en orden creciente de sus “nombres” reales. */

char OrdenWelshPowell(Grafo G); // Orden.c
/* Ordena los vertices de W de acuerdo con el orden Welsh-Powell, es decir,
 * con los grados en orden no creciente */

char SwitchVertices(Grafo G, u32 i, u32 j); // Orden.c
/* Verifica que i,j < número de v́ertices. Si no es cierto, retorna 1.
 * Si ambos estan en el intervalo permitido, entonces intercambia las posiciones
 * de los vertices en los lugares i y j del orden interno de G que G tenga en el
 * momento que se llama esta funcíon. (numerados desde 0), y retorna 0. */

char RMBCnormal(Grafo G); // OrdenRMBC.c
/* ver PDF */

char RMBCrevierte(Grafo G); // OrdenRMBC.c
/* ver PDF */

char RMBCchicogrande(Grafo G); // OrdenRMBC.c
/* ver PDF */

char SwitchColores(Grafo G, u32 i, u32 j); // Orden.c
/* intercambia los colores i, j: todos los vertices que esten coloreados en el coloreo actual con i
 * pasan a tener el color j en el nuevo coloreo y los que estan coloreados con j en el coloreo actual
 * pasan a tener el color i en el nuevo coloreo */

/*
 * PARSEO
 * */

int GoToEOL(); // Parseo.c
/* Esta función escanea chars hasta encontrar el caracter EOL */

char NoCommentFound(); // Parseo.c
/* Esta funcion escanea lineas de comentario y devuelve el primer
   carácter de la primer línea que encuentre sin comentario */

/*
 * MANEJO DE MEMORIA
 * */




#endif //RII_H
