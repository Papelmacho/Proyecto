#ifndef GRAPH_HEADER
#define GRAPH_HEADER

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <stdio.h>
//#include <omp.h> ->>>de momento no es necesario


 typedef struct 
{
    double precio; //llave del lugar
    bool bebida;
    bool bolillo_tortilla;
    bool sopa;
    bool guisado;
    bool postre;

} Menu;
/**
 * @brief Es la información de la cafeteria.
 */
typedef struct 
{
   int id;   ///< campo de indexado (key) para los vértices
   double quality_score; ///< calidad del establecimiento
   char* nearly[65]; ///< punto cercano
   char* name[65]; ///< nombre de la cafeteria
} Cafeteria;

typedef enum
{
   BLACK, ///< vértice no descubierto
   GRAY,  ///< vértice descubierto
   WHITE, ///< vértice visitado
} eGraphColors;


/**
 * @brief Declara lo que es un nodo (lo usa la clase Vertex).
 */
typedef struct Node_
{
   size_t index;       ///< índice del elemento en la Slla de vértices
   struct Node_ *next; ///< índice al nodo siguiente en la Slla simplemente enlazada
} Node;

typedef struct
{
   Cafeteria cafe;      ///< campo de indexado. En este ejemplo Data.val
   size_t index; ///< índice del elemento en la tabla de datos
} Pair;

typedef struct
{
   Pair  kv;        ///< Par <key, index>: <Data.val, index (a la tabla de datos)>
   Node* neighbors; ///< apunta al primer vecino, ¡no debe perderse!
   Node* cursor;    ///< Nodo de movimiento libre (freewheel pointer)


   // para el algoritmo BFS:

   eGraphColors color;
   int distance;
   int predecessor;

   // para el algoritmo DFS:
   size_t discovery_time;
   size_t finish_time;

} Vertex;

typedef enum 
{ 
   eGraphType_UNDIRECTED, ///< grafo no dirigido
   eGraphType_DIRECTED    ///< grafo dirigido (digraph)
} eGraphType; 

typedef struct
{
   Vertex* vertices; ///< Slla de vértices
   size_t size;      ///< Tamaño de la Slla de vértices

   /**
    * Número de vértices actualmente en el grafo. 
    * Como esta versión no borra vértices, lo podemos usar como índice en la
    * función de inserción
    */
   size_t len;  

   eGraphType type; ///< tipo del grafo, UNDIRECTED o DIRECTED
} Graph;

typedef struct
{
   int*   array;
   size_t front;
   size_t back;
   size_t size;
   size_t len;
} Queue;



void bfs( Graph* g, Vertex* start );
static int find( Vertex* vertices, size_t size, int key );
static bool find_index_in_vertex( Vertex* vertex, int index );
bool Graph_AddEdge( Graph* g, int start, int finish );
void Graph_AddVertex( Graph* g, int key, size_t index );
void Graph_Delete( Graph** g );
size_t Graph_GetIndexFromVertex( Graph* g, Vertex* v );
size_t Graph_GetLen( Graph* g );
Node* Graph_GetNeighborsByKey( Graph* g, int key );
size_t Graph_GetSize( Graph* g );
Vertex* Graph_GetVertexByIndex( Graph* g, size_t index );
Vertex* Graph_GetVertexByKey( Graph* g, int key );
Graph* Graph_New( size_t size, eGraphType type );
void Graph_Print( Graph* g, int depth );
void Graph_Print_bfs( Graph* g, int depth );
static void insert( Vertex* vertex, int index );
static Node* newNode(int item);
void Queue_Delete( Queue** q );
int Queue_Dequeue( Queue* q );
void Queue_Enqueue( Queue* q, int item );
bool Queue_IsEmtpy( Queue* q );
bool Queue_IsFull( Queue* q );
Queue* Queue_New( size_t size);
bool Vertex_End( const Vertex* v );
size_t Vertex_Get( const Vertex* v );
eGraphColors Vertex_GetColor( Vertex* v );
size_t Vertex_GetDataIndex( Vertex* v );
int Vertex_GetDistance( Vertex* v );
int Vertex_GetKey( Vertex* v );
int Vertex_GetPredecessor( Vertex* v );
void Vertex_Next( Vertex* v );
void Vertex_SetColor( Vertex* v, eGraphColors color );
void Vertex_SetDiscovery_time( Vertex* v, size_t time );
void Vertex_SetDistance( Vertex* v, int distance );
void Vertex_SetFinished_time( Vertex* v, size_t time ;
void Vertex_SetPredecessor( Vertex* v, int predecessor_idx );
void Vertex_Start( Vertex* v );


#endif  /* ----- #ifndef GRAPH_HEADER ----- */
