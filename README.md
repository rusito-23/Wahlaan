# Wahlaan 🤓

Discrete Math II 2019 - Famaf, Argentina.
Uses the Greedy algorithm for Graph Coloring with C.

## Test Suites

- **SANITY**
	
        Runs several UnitTests over the required functions.
	
- **PERFORMANCE**

        Runs several actions, saving the partial time for each of one:
	- Graph reading
	- Greedy with natural order
	- WelshPowell Re-Ordering and Greedy
	- 100 SwitchVertices
	- 1000 RMBCs + Greedy

- **COLOR**

        Shows the results of Greedy with the following orders:
	
	- Natural
	- Welsh Powell
	- 100 SwitchVértices
	- 100 RMBCs

- **BIPARTITO**

        Shows the results of running Greedy and Bipartite over the graph.
	
	
## Makefile 🔛

The makefile provides the following targets:

- `make <suite> GRAPH=Path/to/Graph` Suite over a Graph

	Example: `make sanity GRAPH=Graphs/K4.txt`
	
- `make <suite>-all FOLDER=Path/To/Folder` Suite over a folder of Graphs

	Ejemplo: `make performance-all FOLDER=Graphs/Performance`
	
- `make <suite>-valgrind GRAPH=Path/To/Graph` Suite over a Graph with Valgrind results:
	
	`make bipartito-valgrind GRAPH=Graphs/Bipartito.txt VALGRIND='valgrind --leak-check=full --show-leak-kinds=all'`
	

### Structure

```
.
├── Graphs
│   ├── Bipartito
│   │   └── Grafos Bipartitos
│   ├── Color
│   │   └── Grafos chicos para probar suite COLOR
│   ├── Completes
│   │   └── Grafo Completos
│   └── Performance
│       └── Grafos para probar performance
├── Makefile
├── README.md
├── Test
│   ├── PrintTests.c
│   ├── TestSuites.c
│   ├── Tests.h
│   ├── TestsMultiples.c
│   └── UnitTests.c
├── Wahlaan
│   ├── Project .c files
│   └── Rii.h
└── main.c
```


