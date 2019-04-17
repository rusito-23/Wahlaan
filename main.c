#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Wahlaan/Rii.h"
#include "Test/Tests.h"

static void
printHelp()
{
    printf("Incorrect arguments. \n"
           "Usage:\n"
           "    --suite <<SUITE>> (required)\n"
           "             options: SANITY, PERFORMANCE, COLOR, BIPARTITO, CUSTOM\n\n"
           "    --file <<FILENAME>> (optional)\n");
}

static void
testGrafo(enum Suite suite) {
    // correr tests
    printf("\n\n");

    switch (suite) {
        case SANITY:
            SanitySuite();
            break;
        case PERFORMANCE:
            PerformanceSuite();
            break;
        case COLOR:
            ColorSuite();
            break;
        case BIPARTITO:
            BipartitoSuite();
            break;
        case CUSTOM:
            CustomSuite();
            break;
        case NONE:
            printHelp();
            break;
    }

}

int
main(int argv, char** argc)
{
    // tomamos el argumento suite (requerido)
    if (argv < 3 || strcmp(argc[1], "--suite") != 0) {
        // incorrect arguments
        printHelp();
        return 0;
    }

    // tomamos el argumento file (opcional)
    // y pasamos su contenido como stdin
    //if (argv >= 5 && strcmp(argc[3], "--file") == 0) {
    //    char * file_name = argc[4];
    //    freopen(file_name, "r", stdin);
    //}

    // tomamos la suite y testeamos
    enum Suite suite = SuiteFromString(argc[2]);
    testGrafo(suite);
    return 0;
}
