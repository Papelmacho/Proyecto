#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

#include "graph.h"
#include "sll.c"
#ifndef PRINT_LEVEL
#define PRINT_LEVEL 0
#endif  

#ifndef DBG_HELP
#define DBG_HELP 0
#endif  

#if DBG_HELP > 0
#define DBG_PRINT( ... ) do{ fprintf( stderr, "DBG:" _VA_ARGS_ ); } while( 0 )
#else
#define DBG_PRINT( ... ) ;
#endif  




/**************************************************************
me parece que en este caso no es necesario  la estructura data
pues donde se guardaran los datos va a ser en "Cafeteria"
typedef struct 
{
   int val;   ///< campo de indexado (key) para los vértices
   char name; ///< una letra (por el momento)
} Data;
*/ //***************************************

//----------------------------------------------------------------------
// Vertex stuff: 
//----------------------------------------------------------------------




/**
 * @brief Declara lo que es un nodo (lo usa la clase Vertex).
 */

/**
 * @brief Mantiene juntas la llave (que se usa a lo largo de todas las funciones
 * de los grafos) y el índice de la misma en la tabla de datos.
 */


/**
 * @brief Declara lo que es un vértice.
 */

/**
 * @brief Devuelve el índice del vecino (correspondiente a la Slla de vértices) al 
 * que apunta el |cursor| en la Slla de vecinos.
 *
 * @param v El vértice base (del cual queremos conocer el índice de su vecino).
 *
 * @return El índice del vecino en la Slla de vértices.
 *
 * @pre El cursor debe apuntar a un nodo válido en la Slla de vecinos.
 *
 * Ejemplo
 * @code
   Vertex* v = Graph_GetVertexByKey( grafo, 100 );
   for( Vertex_Start( v ); !Vertex_End( v ); Vertex_Next( v ) )
   {
      size_t index = Vertex_Get( v );
      printf( "[Index=%ld, [Val=%d, Name=%c] ], ", 
         index, 
         data[ index ].val,
         data[ index ].name );
   }
   @endcode
   @note Esta función debe utilizarse únicamente cuando se recorra el grafo con las funciones Vertex_Start(), Vertex_End() y Vertex_Next().
 */
size_t Vertex_Get( const Vertex* v){
   assert( v->cursor );
   return v->cursor->index;
}

/**
 * @brief Hace que cursor libre apunte al inicio de la Slla de vecinos. Se debe
 * de llamar siempre que se vaya a iniciar un recorrido de dicha Slla.
 *
 * @param v El vértice de trabajo (es decir, el vértice del cual queremos obtener 
 * la Slla de vecinos).
 */
void Vertex_Start( Vertex* v )
{
   assert( v );

   v->cursor = v->neighbors;
}

/**
 * @brief Mueve al cursor libre un nodo adelante.
 *
 * @param v El vértice de trabajo.
 *
 * @pre El cursor apunta a un nodo válido.
 * @post El cursor se movió un elemento a la derecha en la Slla de vecinos.
 */
void Vertex_Next( Vertex* v )
{
   assert( v->cursor );

   v->cursor = v->cursor->next;
}

/**
 * @brief Indica si se alcanzó el final de la Slla de vecinos.
 *
 * @param v El vértice de trabajo.
 *
 * @return true si se alcanazó el final de la Slla; false en cualquier otro
 * caso.
 */
bool Vertex_End( const Vertex* v )
{
   return v->cursor == NULL;
}

void Vertex_SetColor( Vertex* v, eGraphColors color )
{
    assert(color ==BLACK || color==GRAY || color==WHITE);
    v->color=color;
}

eGraphColors Vertex_GetColor( Vertex* v )
{
    return v->color;
}

void Vertex_SetDistance( Vertex* v, int distance )
{
    v->distance=distance;
}

int Vertex_GetDistance( Vertex* v )
{
    return v->distance;
}

/**
 * @brief Establece el vértice predecesor.
 *
 * @param v El vértice de trabajo.
 * @param predecessor_idx El índice vértices del vértice
 * predecesor en la Slla de vértices.
 */
void Vertex_SetPredecessor( Vertex* v, int predecessor_idx )
{
    v->predecessor=predecessor_idx;
}

int Vertex_GetPredecessor( Vertex* v )
{
    return v->predecessor;
}

void Vertex_SetDiscovery_time( Vertex* v, size_t time )
{
    v->discovery_time=time;
}

void Vertex_SetFinished_time( Vertex* v, size_t time )
{
    v->finish_time=time;
}

/**
 * @brief Devuelve la llave asociada al vértice indicado.
 *
 * @param v El vértice de trabajo.
 *
 * @return La llave asociada al vértice indicado.
 */
int Vertex_GetKey( Vertex* v )
{//en esta funcion  se va a cambiar
   return v->kv.cafe.key;
}

/**
 * @brief Devuelve el índice en la tabla de datos asociado al vértice indicado.
 *
 * @param v El vértice de trabajo.
 *
 * @return El índice en la tabla de datos asociado al vértice indicado.
 */
size_t Vertex_GetDataIndex( Vertex* v )
{
   return v->kv.index;
}



//----------------------------------------------------------------------
// Graph stuff: 
//----------------------------------------------------------------------

/** Tipo del grafo.
 */
typedef enum 
{ 
   eGraphType_UNDIRECTED, ///< grafo no dirigido
   eGraphType_DIRECTED    ///< grafo dirigido (digraph)
} eGraphType; 

/**
 * @brief Declara lo que es un grafo.
 */

/**
 * @brief Crea un nuevo grafo.
 *
 * @param size Número de vértices que tendrá el grafo. Este valor no se puede
 * cambiar luego de haberlo creado.
 *
 * @return Un nuevo grafo.
 *
 * @pre El número de elementos es mayor que 0.
 */
Graph* Graph_New( size_t size, eGraphType type )
{
   assert( size > 0 );

   Graph* g = (Graph*) malloc( sizeof( Graph ) );
   if( g ){
      g->size = size;
      g->len = 0;
      g->type = type;

      g->vertices = (Vertex*) calloc( size, sizeof( Vertex ) );
      // crea un arreglo para guardar los vértices


      // La siguiente inicialización NO ES NECESARIA, dado que calloc() ya se
      // encargó de eso; lo hice por si alguno de los campos debe ser puesto a
      // un valor diferente de cero:
      if( g->vertices ){
         
         Vertex* vertices = g->vertices;
         // para simplificar la notación. 
         // La variable |vertices| sólo existe dentro de este if.

         for( size_t i = 0; i < g->size; ++i ){
            vertices[ i ].kv.cafe.key = 0;
            vertices[ i ].kv.index = 0;
            vertices[ i ].neighbors = NULL;
         }
      } 

      // error de memoria para g->vertices:
      else{ 
         free( g );
         g = NULL;
      }
   }

   return g;
   // el cliente es responsable de verificar que el grafo se creó correctamente
}

void Graph_Delete( Graph** g )
{
   assert( *g );

   Graph* graph = *g;
   // para simplificar la notación 

   // 1. Borramos la verticesa enlazada de cada vértice:
   for( size_t i = 0; i < graph->size; ++i ){

      Vertex* vertex = &graph->vertices[ i ];
      // para simplificar la notación. 
      // La variable |vertex| sólo existe dentro de este for.

      Node* node = vertex->neighbors;
      while( node ){
         Node* tmp = node->next;
         free( node );
         node = tmp;
      }
   }

   // 2. Borramos el arreglo dinámico de vértices:
   free( graph->vertices );

   // 3. Borramos al objeto grafo:
   free( graph );

   // 4. Hacemos que el grafo apunte a nada (para control de daños):
   *g = NULL;
}

/**
 * @brief Imprime un reporte del grafo
 *
 * @param g     El grafo.
 * @param depth Cuán detallado deberá ser el reporte (0: lo mínimo)
 */
void Graph_Print( Graph* g, int depth )
{
   for( size_t i = 0; i < g->len; ++i )
   {
      Vertex* vertex = &g->vertices[ i ];
      // para simplificar la notación. 

      printf( "\n=== Vertex[ %ld ] ===\n", i );
      printf( "<%d, %ld>\n", vertex->kv.cafe.key, vertex->kv.index );

      // LEVEL 0:
      printf( vertex->neighbors ? "Has neighbors\n" : "Has no neighbors\n" );

      // LEVEL 1:
      if( depth > 0 )
      {
         for( Node* node = vertex->neighbors; node != NULL; node = node->next )
         {
            DBG_PRINT( "Print():(Node:%p, (*Node.index:%ld, *Node.next:%p))\n", node, node->index, node->next );
            
            printf( " %d ", g->vertices[ node->index ].kv.cafe.key );

            // LEVEL 2:
            if( depth > 1 )
            {
               printf( "(Node:%p) ", node );
            }

            printf( "->" );
         } if( vertex->neighbors ) printf( " Nil\n" );
      }
   } printf( "\n" );
}

/**
 * @brief Imprime un reporte del grafo despues de usar la funcion bfs
 *
 * @param g     El grafo.
 * @param depth Cuán detallado deberá ser el reporte (0: lo mínimo)
 */
void Graph_Print_bfs( Graph* g, int depth )
{
   for( size_t i = 0; i < g->len; ++i )
   {
      Vertex* vertex = &g->vertices[ i ];
      // para simplificar la notación. 

      printf( "\n=== Vertex[ %ld ] ===\n", i );
      printf( "<%d, %ld>\n", vertex->kv.cafe.key, vertex->kv.index );
      printf( "Distance:%d",Vertex_GetDistance(vertex) );
      printf( "Predecessor vertex[%d]",Vertex_GetPredecessor(vertex));

      // LEVEL 0:
      printf( vertex->neighbors ? "Has neighbors\n" : "Has no neighbors\n" );

      // LEVEL 1:
      if( depth > 0 )
      {
         for( Node* node = vertex->neighbors; node != NULL; node = node->next )
         {
            DBG_PRINT( "Print():(Node:%p, (*Node.index:%ld, *Node.next:%p))\n", node, node->index, node->next );
            
            printf( " %d ", g->vertices[ node->index ].kv.cafe.key );

            // LEVEL 2:
            if( depth > 1 )
            {
               printf( "(Node:%p) ", node );
            }

            printf( "->" );
         } if( vertex->neighbors ) printf( " Nil\n" );
      }
   } printf( "\n" );
}

/**
 * @brief Crea un vértice a partir de los datos reales.
 *
 * @param g     El grafo.
 * @param key   Es el campo de indexado en los datos.
 * @param index Es el índice de los datos en la tabla de datos.
 */
void Graph_AddVertex( Graph* g, int key, size_t index )
{
   assert( g->len < g->size );

   Vertex* vertex = &g->vertices[ g->len ];
   // para simplificar la notación 

   vertex->kv.cafe.key     = key;
   vertex->kv.index   = index;
   vertex->neighbors = NULL;

   ++g->len;
}

size_t Graph_GetSize( Graph* g )
{
   return g->size;
}


// vertices: Slla de vértices
// size: número de elementos en la Slla de vértices
// key: valor a buscar
// ret: el índice donde está la primer coincidencia; -1 si no se encontró
static int find( Vertex* vertices, size_t size, int key )
{
   for( size_t i = 0; i < size; ++i ){

      if( vertices[ i ].kv.cafe.key == key ) return i;
   }

   return -1;
}

// INDICA SI INDEX ESTÁ DUPLICADO
// busca si el índice (a la tabla de vértices) ya está en un vértice
static bool find_index_in_vertex( Vertex* vertex, int index )
{
   for( Node* node = vertex->neighbors; node != NULL; node = node->next ){
      if( node->index == index ) return true;
   }
   return false;
}

// vertex: vértice de trabajo
// index: índice en la Slla de vértices del vértice vecino que está por insertarse
static void insert( Vertex* vertex, int index )
{
   if( find_index_in_vertex( vertex, index ) == false ){

   // Crea al nodo:
   Node* n = (Node*) calloc( 1, sizeof( Node ) );
   assert( n );
   DBG_PRINT( "Insert(): idx=%d, Node = %p\n", index, n );

   // Inserta al nodo al frente de la Slla
   n->index = index;
   n->next = vertex->neighbors;
   vertex->neighbors = n;

   } 
   else DBG_PRINT( "insert: duplicated index\n" );

}

/**
 * @brief Inserta una relación de adyacencia del vértice |start| hacia el vértice |finish|.
 *
 * @param g     El grafo.
 * @param start Vértice de salida.
 * @param finish Vertice de llegada.
 *
 * @return false si uno o ambos vértices no existen; true si la relación se creó con éxito.
 *
 * @pre El grafo no puede estar vacío.
 */
bool Graph_AddEdge( Graph* g, int start, int finish )
{
   assert( g->len > 0 );

   // obtenemos los índices correspondientes:
   int start_idx = find( g->vertices, g->size, start );
   int finish_idx = find( g->vertices, g->size, finish );

   DBG_PRINT( "AddEdge(): start_idx=%d, finish_idx=%d\n", start_idx, finish_idx );

   if( start_idx == -1 || finish_idx == -1 ) return false;
   // uno o ambos vértices no existen

   insert( &g->vertices[ start_idx ], finish_idx );
   // insertamos la arista start-finish

   if( g->type == eGraphType_UNDIRECTED ) insert( &g->vertices[ finish_idx ], start_idx );
   // si el grafo no es dirigido, entonces insertamos la arista finish-start

   return true;
}

/**
 * @brief Devuelve el nodo que apunta al inicio de la Slla de vecinos.
 *
 * @param g     El grafo.
 * @param key   El criterio de búsqueda
 *
 * @return      El nodo que apunta a la Slla de vecinos. Si no los tuviera,
 *              devuelve NULL
 */
Node* Graph_GetNeighborsByKey( Graph* g, int key )
{
   for( size_t i = 0; i < g->len; ++i ){

      if( g->vertices[ i ].kv.cafe.key == key ) return g->vertices[ i ].neighbors;
   }

   return NULL;
}

/**
 * @brief Devuelve el vértice correspondiente a la llave indicada
 *
 * @param g     El grafo.
 * @param key   La llave del vértice que estamos buscando.
 *
 * @return El vértice asociado a la llave.
 */
Vertex* Graph_GetVertexByKey( Graph* g, int key )
{
   assert( g );

   for( size_t i = 0; i < g->len; ++i ){

      if( g->vertices[ i ].kv.cafe.key == key ) return &g->vertices[ i ];
   }

   return NULL;
}

/**
 * @brief Devuelve el vértice correspondiente al índice en la Slla de vértices.
 *
 * @param g     El grafo.
 * @param index El índice en la Slla de vértices del vértice v.
 *
 * @return El vértice asociado al índice en la Slla de vértices.
 */
Vertex* Graph_GetVertexByIndex( Graph* g, size_t index )
{
   assert( g );
   assert( index < g->len );

   return &g->vertices[ index ];
}


/**
 * @brief Devuelve el índice en la Slla de vértices del vértice indicado.
 *
 * @param g El grafo.
 * @param v El vértice del cual queremos obtener el índice.
 *
 * @return El índice en la Slla de vértices del vértice v.
 *
 * @pre Ambos, el grafo y el vértice deben existir.
 */
size_t Graph_GetIndexFromVertex( Graph* g, Vertex* v )
{
   assert( g );
   assert( v );

   size_t index;
   for( index = 0; index < g->len; ++index ){
      if( g->vertices[ index ].kv.key == v->kv.cafe.key ) break;
   }

   assert( index < g->len );

   return index;
}

size_t Graph_GetLen( Graph* g )
{
   return g->len;
}

//----------------------------------------------------------------------
// Queue stuff: 
//----------------------------------------------------------------------
typedef struct
{
   int*   array;
   size_t front;
   size_t back;
   size_t size;
   size_t len;
} Queue;

Queue* Queue_New( size_t size )
{
   assert( size > 0 );

   Queue* q = (Queue*) calloc( 1, sizeof( Queue ) );
   if( q ){

      q->size = size;
      q->array = (int*) calloc( size, sizeof( int ) );

      if( q->array == NULL ){
         free( q );
         q = NULL;
      }
   }

   return q;
}

void Queue_Delete( Queue** q )
{
   assert( *q );

   free( (*q)->array );
   free( *q );
   *q = NULL;
}

void Queue_Enqueue( Queue* q, int item )
{
   assert( q->len < q->size );
   q->array[q->back++]=item;
   ++q->len;
}

int Queue_Dequeue( Queue* q )
{
   assert( q->len > 0 );
   int tmp=q->array[q->front++];
   --q->len;
   q->front %= q->size;
   return tmp;

}

bool Queue_IsEmtpy( Queue* q )
{
    return q->len == 0;
}

bool Queue_IsFull( Queue* q )
{
    return q->len == q->size;
}



//----------------------------------------------------------------------
// BFS algorithm 
//----------------------------------------------------------------------
void bfs( Graph* g, Vertex* start )
{
   // inicializa los atributos correspondientes al recorrido BFS:
   for( size_t i = 0; i < g->len; ++i )
   {
      Vertex* vertex = Graph_GetVertexByIndex( g, i );

      Vertex_SetColor( vertex, BLACK );
      Vertex_SetDistance( vertex, 0 );
      Vertex_SetPredecessor( vertex, -1 );
   }

   Vertex_SetColor( start, GRAY );

   Queue* q = Queue_New( Graph_GetLen( g ) );
   assert( q );

   Queue_Enqueue( q, Graph_GetIndexFromVertex( g, start ) );

   while( !Queue_IsEmtpy( q ) )
   {
      size_t v_idx = Queue_Dequeue( q );
      // v_idx es el índice del vecino que estamos visitando

      Vertex* v = Graph_GetVertexByIndex( g, v_idx );
      // v es el vértice de trabajo; lo obtuvimos a partir de su índice
      // en la Slla de adyacencia


      printf( "PROCESSING VERTEX WITH INDEX %ld AND KEY: %d\n", v_idx, Vertex_GetKey( v ) );


      // para todos los vecinos w de v:
      for( Vertex_Start( v ); !Vertex_End( v ); Vertex_Next( v ) )
      {
         Vertex* w = Graph_GetVertexByIndex( g, Vertex_Get( v ) );

         if( Vertex_GetColor( w ) == BLACK )
         {
            Vertex_SetColor( w, GRAY );
            Vertex_SetDistance( w, Vertex_GetDistance( v ) + 1 );
            Vertex_SetPredecessor( w, Graph_GetIndexFromVertex( g, v ) );

            Queue_Enqueue( q, Graph_GetIndexFromVertex( g, w ) );
         }
      }

      Vertex_SetColor( v, WHITE );
   }
}


//----------------------------------------------------------------------
// BSF stuff: 
//----------------------------------------------------------------------

void Graph_Print_bfs( Graph* g, int depth )
{
   for( size_t i = 0; i < g->len; ++i )
   {
      Vertex* vertex = &g->vertices[ i ];
      // para simplificar la notación. 

      printf( "\n=== Vertex[ %ld ] ===\n", i );
      printf( "<%d, %ld, %d, %d>\n", vertex->kv.key, vertex->kv.index, vertex->distance, vertex->predecessor );

      // LEVEL 0:
      printf( vertex->neighbors ? "Has neighbors\n" : "Has no neighbors\n" );

      // LEVEL 1:
      if( depth > 0 )
      {
         for( Node* node = vertex->neighbors; node != NULL; node = node->next )
         {
            //DBG_PRINT( "Print():(Node:%p, (*Node.index:%ld, *Node.next:%p))\n", node, node->index, node->next );
            
            printf( " %d ", g->vertices[ node->index ].kv.key );

            // LEVEL 2:
            if( depth > 1 )
            {
               printf( "(Node:%p) ", node );
            }

            printf( "->" );
         } if( vertex->neighbors ) printf( " Nil\n" );
      }
   } printf( "\n" );
}



//----------------------------------------------------------------------
// Driver program 
//----------------------------------------------------------------------
#define MAX_DATA 6

/*
100 - 200 - 600
 |  \     \
300 - 400 - 500
*/