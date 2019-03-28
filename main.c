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
           "             options: SANITY, PERFORMANCE, COLOR, BIPARTITO\n\n");
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
        case NONE:
            printHelp();
            break;
    }

}

int
main(int argv, char** argc)
{

    if (argv < 3 || strcmp(argc[1], "--suite") != 0) {
        // incorrect arguments
        printHelp();
    }

    enum Suite suite = SuiteFromString(argc[2]);

    testGrafo(suite);
    return 0;
}
