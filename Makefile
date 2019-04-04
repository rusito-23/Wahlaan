# COMPILER OPTS
CC = gcc
CFLAGS = -IWahlaan -Wall -Werror -Wextra -O3 -std=c99
RM = rm -rf
VALGRIND_2 = valgrind --leak-check=full --show-leak-kinds=all
VALGRIND = valgrind --tool=memcheck

# SOURCES AND OBJECTS
SRC = Wahlaan/*.c Test/*.c main.c
MAIN = Ejecutable
COMPILED = *.o Wahlaan/*.o Test/*.o

# SOURCE FILES/FOLDERS
GRAPH = 0
FOLDER = 0
GRAPHS = $(FOLDER)/*

# HELPERS
ECHO_FILE = printf "\n\n RUNNING FOR FILE: "; echo
ECHO_F_ERROR = echo "ERROR: no folder found, please set the folder with option: FOLDER=/Your/Folder/Path"
ECHO_G_ERROR = echo "ERROR: no graph found, please set the graph with option: GRAPH=/Your/Graph/Path"
ECHO_F_SUCCESS = echo "RUNNING FOR FOLDER: " $(FOLDER)
ECHO_G_SUCCESS = echo "RUNNING FOR GRAPH: " $(GRAPH)

# CUSTOM FOR
FOR_F_RUN = for f in $(GRAPHS); do $(ECHO_FILE) $$f; ./$(MAIN) --suite
ENDFOR = < $$f; done

# CUSTOM EXEC
EXEC = $(VALGRIND) ./$(MAIN) --suite
END_EXEC = < $(GRAPH)

# GENERAL

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(MAIN) $(SRC)

clean:
	$(RM) $(MAIN) $(MAIN).dSYM $(COMPILED)

# ERROR HANDLING

--folder:
ifeq ($(FOLDER), 0)
	@$(ECHO_F_ERROR)
	@exit 1
else
	@$(ECHO_F_SUCCESS)
endif

--graph:
ifeq ($(GRAPH), 0)
	@$(ECHO_G_ERROR)
	@exit 1
else
	@$(ECHO_G_SUCCESS)
endif

# SUITES

color-all: --folder all
	@$(FOR_F_RUN) COLOR $(ENDFOR)

bipartito-all: --folder all
	@$(FOR_F_RUN) BIPARTITO $(ENDFOR)

sanity-all: --folder all
	@$(FOR_F_RUN) SANITY $(ENDFOR)

performance-all: --folder all
	@$(FOR_F_RUN) PERFORMANCE $(ENDFOR)

custom-all: --folder all
	@$(FOR_F_RUN) CUSTOM $(ENDFOR)


# INDIVIDUAL SUITES
sanity color performance bipartito custom: VALGRIND =

sanity: --graph all
	$(EXEC) SANITY $(END_EXEC)

color: --graph all
	$(EXEC) COLOR $(END_EXEC)

performance: --graph all
	@date +"START -> +%T"
	$(EXEC) PERFORMANCE $(END_EXEC)
	@date +"END -> +%T"

bipartito: --graph all
	$(EXEC) BIPARTITO $(END_EXEC)

custom: --graph all
	$(EXEC) CUSTOM $(END_EXEC)

# VALGRIND SUITES

sanity-valgrind: --graph all
	$(EXEC) SANITY $(END_EXEC)

color-valgrind: --graph all
	$(EXEC) COLOR $(END_EXEC)

performance-valgrind: --graph all
	@date +"START -> +%T"
	$(EXEC) PERFORMANCE $(END_EXEC)
	@date +"END -> +%T"

bipartito-valgrind: --graph all
	$(EXEC) BIPARTITO $(END_EXEC)

custom-valgrind: --graph all
	$(EXEC) CUSTOM $(END_EXEC)

