# Wahlaan Tests 🤓
Tests para el proyecto de Matemática Discreta II 2019, en Famaf, Argentina.

## Suites 🙈
El proyecto cuenta con 4 suites de test, cada uno de los cuales toma un único grafo:

- **SANITY**
	
	Prueba TODAS las funciones requeridas por el proyecto, validando la funcionalidad **a grandes rasgos** con ayuda de *asserts*, se puede encontrar el código en UnitTests.c
	
- **PERFORMANCE**

	Corre los siguientes tests, imprimendo los tiempos parciales de cada uno y un tiempo final que debería ser menor a los 15 minutos:
	
	- Toma de grafo
	- Greedy con orden natural
	- Reordena con WelshPowell y corre Greedy
	- 100 SwitchVertices
	- 1000 RMBCs, corriendo Greedy luego de cada uno

- **COLOR**

	Muestra los resultados de correr Greedy con los siguientes ordenes, el usuario queda encargado de validar que los resultados se acerquen lo más posible a los requeridos:
	
	- Orden natural
	- Orden Welsh Powell
	- 100 SwitchVértices
	- 100 RMBCs

- **BIPARTITO**

	Muestra los resultados de correr Greedy y Bipartito sobre el grafo.
	
	
## Makefile 🔛
El makefile permite al usuario llamar a los disintos suites con distintas configuraciones y grafos.
Los target son los siguientes:

- `make <suite> GRAPH=Path/Al/Grafo` toma un único grafo y corre el suite dado (en minúscula). 

	Ejemplo: `make sanity GRAPH=Graphs/K4.txt`
	
- `make <suite>-all FOLDER=Path/Al/Folder` toma una carpeta y corre el suite dado en todos los grafos que encuentre dentro. Observaciones: la carpeta no debe estar vacía y no debe contener otras carpetas dentro, o podría producir errores en la ejecución.

	Ejemplo: `make performance-all FOLDER=Graphs/Performance`
	
- `make <suite>-valgrind GRAPH=Path/Al/Grafo` toma un único grafo y corre la suite dada, ejecutando valgrind con las opciones: **valgrind --tool=memcheck**, si se desea cambiar las opciones con las que se corre valgrind, se debe especificar al llamar make de la siguiente forma:
	
	`make bipartito-valgrind GRAPH=Graphs/Bipartito.txt VALGRIND='valgrind --leak-check=full --show-leak-kinds=all'`
	
## Instalación y seteo de la estructura 🔧
Para setear los test, lo único que se debe hacer es agregar la carpeta Wahlaan con la especificación requerida por el profe en la carpeta donde se encuentra el Makefile.

La estructura que debería quedar es:

```
.
├── Graphs
│   ├── Bipartito
│   │   └── Grafos Bipartitos
│   ├── Color
│   │   └── Grafos chicos para probar suite COLOR
│   ├── Completes
│   │   └── Grafo Completos
│   └── Test
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
│   ├── Todos los archivos .c propios del proyecto
│   └── Rii.h
└── main.c
```





