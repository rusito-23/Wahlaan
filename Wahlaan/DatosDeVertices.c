#include "Rii.h"
#include <stdio.h>

u32
NombreDelVertice(Grafo G, u32 i)
{
    return G->names[G->order[i]];
}

u32
GradoDelVertice(Grafo G, u32 i)
{
    if(i >= G->N){
        return MAX_VALUE;
    }
    else {
        return G->grade[G->order[i]];
    }
}

u32
ColorDelVertice(Grafo G, u32 i)
{
    if(i >= G->N){
        return MAX_VALUE;
    }
    else {
        return G->colors[G->order[i]];
    }
}

u32
LabelDelVertice(Grafo grafo, u32 name)
{
    // realizamos busqueda binaria para que
    // la búsqueda de la label sea más rápida

    u32 inf = 0;
    u32 sup = grafo->N-1;

    while(inf <= sup) {
        u32 mit = (inf + sup)/2;
        u32 cname = grafo->names[mit];
        u32 clabel = mit;
        if (cname == name) {
            return clabel;
        } else if (cname > name) {
            sup = mit-1;
        } else if (cname < name) {
            inf = mit+1;
        }
    }
    return 0;
}


u32
ColorJotaesimoVecino(Grafo G, u32 i, u32 j)
{
    u32 label = G->order[i];
    u32 neighbour = G->neighbours[label][j];
    return G->colors[neighbour];
}

u32
NombreJotaesimoVecino(Grafo G, u32 i, u32 j)
{
    u32 label = G->order[i];
    u32 neighbour = G->neighbours[label][j];
    return G->names[neighbour];
}
