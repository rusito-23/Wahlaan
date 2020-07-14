#include "Rii.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// MARK: -- Funciones auxiliares estáticas

// libera si no es nulo
static void
safe_free(void* item)
{
    if (item != NULL){
        free(item);
    }
}

// Manejo de la matriz auxiliar
static u32**
MallocAux(u32 M)
{
    u32 **temp = malloc((2*M) * sizeof(u32*));
    qfor(k, 2*M){temp[k] = malloc(2 * sizeof(u32));}
    return temp;
}

static void
FreeAux(u32 **temp, u32 M)
{
    // liberamos la matrix auxiliar
    qfor(k, 2*M){ safe_free(temp[k]); temp[k] = NULL; }
    safe_free(temp);
    temp = NULL;
}

// comparador para ordenar los lados al parsear el archivo
static int
MatrixComparator(const void *_a, const void *_b)
{
    const u32 *a = *(const u32 **)_a;
    const u32 *b = *(const u32 **)_b;
    if (a[0] == b[0]){
        if(a[1] <= b[1]){
            return -1;
        }
        return 1;
    }
    if (a[0] <= b[0]){
        return -1;
    }
    return 1;
}

// MARK: -- ConstruccionDelGrafo

Grafo
ConstruccionDelGrafo()
{
    u32 i, j;
    u32 N, M;

    // Nos salteamos los comentarios y vamos directo a
    // la primer linea sin comentario
    char c;
    while((c = NoCommentFound()) && c == 'c');
    if (c != 'p' || scanf(" edge %u %u", &N, &M) != 2) {
        // si el scanf falla
        printf("Error en primera linea sin comentario \n");
        return NULL;
    }

    // inializamos la matriz auxiliar
    u32 **temp = MallocAux(M);

    // CARGAMOS LA MATRIX AUXILIAR
    i = j = 0;
    u32 x, y;
    while(i < 2*M){
        GoToEOL(); j++;
        if(scanf("e %u %u", &x, &y) != 2) {
            printf("Error de lectura en el lado %d \n", j);
            FreeAux(temp, M);
            return NULL;
        }
        temp[i][0] = x;
        temp[i][1] = y;
        temp[++i][0] = y;
        temp[i++][1] = x;
    }

    // Inicializamos el grafo y allocamos
    Grafo grafo = malloc(sizeof(GrafoSt));
    grafo->N = N;
    grafo->M = M;
    grafo->C = grafo->N;
    grafo->D = 1;
    grafo->names = malloc((grafo->N) * sizeof(u32));
    grafo->grade = malloc((grafo->N) * sizeof(u32));
    grafo->order = malloc((grafo->N) * sizeof(u32));
    grafo->colors = malloc((grafo->N) * sizeof(u32));
    grafo->neighbours = malloc((grafo->N) * sizeof(u32*));

    qfor(i,N){ grafo->neighbours[i] = NULL;}
    grafo->used = NULL;
    grafo->compartidos = NULL;

    // ordenamos los lados de la matriz auxiliar, primero en base al vértice y luego
    // según los vecinos que figuran, ésto es para poder recorrerla sabiendo que
    // vamos a recorrer los lados según cada vértice
    qsort(temp, 2*grafo->M, sizeof(temp[0]), MatrixComparator);

    //PRIMERA VUELTA A LA MATRIX
    // en esta vuelta contamos el grado de cada vértice
    // allocamos la memoria que vamos a necesitar
    u32 label = 0;
    u32 grade = 1;
    for(i = 0; (i < (2*grafo->M)) && (label < grafo->N); ++i){

        // mientras el vértice no cambie
        if(i == (2*grafo->M)-1 || temp[i][0] != temp[i+1][0]){
            // crear el vertice con el grado encontrado
            grafo->names[label] = temp[i][0];
            grafo->colors[label] = label;
            grafo->order[label] = label;
            grafo->grade[label] = grade;
            grafo->neighbours[label] = malloc((grade)*sizeof(u32));

            // reecribimos el Delta del Grafo si es necesario
            if (grade > grafo->D) { grafo->D = grade;}

            // y continuamos con el próximo vértice
            label++;
            grade = 1;
        } else {
            // mientras sigamos viendo los vecinos del mismo vértice
            // vamos incrementando el grado
            grade++;
        }
    }

    // si la cantidad de labels que vamos encontrando
    // supera la cantidad de vértices declarada:
    if (i != (2*grafo->M)) {
        printf("Cantidad de vertices leidos no es la declarada \n");
        FreeAux(temp, grafo->M);
        DestruccionDelGrafo(grafo);
        return NULL;
    }

    // en este punto, ya tenemos el delta del grafo
    // podemos allocar memoria para el arreglo auxiliar
    grafo->used = malloc((grafo->D + 1) * sizeof(bool));
    grafo->compartidos = malloc((grafo->D + 1) * sizeof(u32));

    //SEGUNDA VUELTA A LA MATRIX
    // en esta vuelta guardamos todos los vecinos,
    // asumimos que la cantidad de vecinos a encontrar, es la
    // declarada en el grado que encontramos en la primer vuelta
    label = 0;
    grade = 0;
    grafo->neighbours[label][grade] = LabelDelVertice(grafo, temp[0][1]);
    for(i = 1; i < 2*grafo->M; ++i){
        if(temp[i][0] != temp[i-1][0]){
            label++;
            grade = 0;
        } else {
            grade++;
        }
        grafo->neighbours[label][grade] = LabelDelVertice(grafo, temp[i][1]);
    }

    // corremos greedy con orden natural
    Greedy(grafo);
    FreeAux(temp, grafo->M);
    return grafo;
}

// MARK: -- DestruccionDelGrafo

void
DestruccionDelGrafo(Grafo G)
{
    if(G != NULL) {
        safe_free(G->names);
        safe_free(G->grade);
        safe_free(G->order);
        safe_free(G->colors);
        safe_free(G->used);
        safe_free(G->compartidos);

        // liberamos vecinos
        if (G->neighbours != NULL) {
            qfor(i, G->N) {
                safe_free(G->neighbours[i]);
            }
            safe_free(G->neighbours);
        }

        safe_free(G);
    }
}

// MARK: -- CopiarGrafo

Grafo CopiarGrafo(Grafo G) {

    if(G == NULL){
        return G;
    }

    Grafo grafo = malloc(sizeof(GrafoSt));
    grafo->N = G->N;
    grafo->M = G->M;
    grafo->C = G->C;
    grafo->D = G->D;

    grafo->order = malloc((grafo->N) * sizeof(u32));
    grafo->names = malloc((grafo->N) * sizeof(u32));
    grafo->grade = malloc((grafo->N) * sizeof(u32));
    grafo->colors = malloc((grafo->N) * sizeof(u32));
    grafo->neighbours = malloc((grafo->N) * sizeof(u32*));
    grafo->used = malloc((grafo->D + 1) * sizeof(bool));
    grafo->compartidos = malloc((grafo->D + 1) * sizeof(u32*));

    // copiamos los vertices
    qfor(i, G->N) {
        // crear el vertice
        grafo->names[i] = G->names[i];
        grafo->order[i] = G->order[i];
        grafo->colors[i] = G->colors[i];
        grafo->grade[i] = G->grade[i];

        grafo->neighbours[i] = malloc((grafo->grade[i])*sizeof(u32));
        qfor(j, grafo->grade[i]) {
            grafo->neighbours[i][j] = G->neighbours[i][j];
        }
    }

    // copiamos el arreglo de compartidos de los colores
    qfor(i, G->C) {
        grafo->compartidos[i] = G->compartidos[i];
    }

    return grafo;
}
