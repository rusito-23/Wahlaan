#include "Rii.h"
#include <stdio.h>

int
GoToEOL(){
    char c;
    // escaneamos carácteres hasta encontrar EOL
    while(scanf("%c", &c) != 0 && c != '\n');
    return 1;
}

char
NoCommentFound()
{
    char c;
    if (scanf("%c", &c) != 0 && c == 'c') {
        // si se encontro un comentario, ir a EOL
        while(scanf("%c", &c) != 0 && c != '\n');
        return 'c';
    } else {
        // si no se encontro comentario, devolver primer char
        return c;
    }
}
