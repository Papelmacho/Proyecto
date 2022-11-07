/*Copyright (C) 
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 * 2021 - francisco dot rodriguez at ingenieria dot unam dot mx
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>


// 20/06/21:
// Esta versión no borra elementos
// Esta versión no modifica los datos originales

#ifndef PRINT_LEVEL
#define PRINT_LEVEL 2
#endif  

#ifndef DBG_HELP 
#define DBG_HELP 0
#endif  

#if DBG_HELP > 0
#define DBG_PRINT( ... ) do{ fprintf( stderr, "DBG:" __VA_ARGS__ ); } while( 0 )
#else
#define DBG_PRINT( ... ) ;
#endif  

/**
 * @brief Es la informacion del menu
 */
typedef struct 
{
    double precio; //llave del lugar
    bool bebida;
    bool bolillo_tortilla;
    bool sopa;
    bool guisado;
    bool postre

}Menu;
/**
 * @brief Es la información de la cafeteria.
 */
typedef struct 
{

    char faultad_cercana[65];
    char name[65];
    Menu* menus;

}Cafeteria;



//----------------------------------------------------------------------
// Vertex stuff: 
//----------------------------------------------------------------------

/**
 * @brief Declara lo que es un nodo (lo usa la clase Vertex).
 */
typedef struct Node_
{
   size_t index;       ///< índice del elemento en la lista de vértices
   struct Node_ *next; ///< índice al nodo siguiente en la lista simplemente enlazada
   double weight;
} Node;

/**
 * @brief Mantiene juntas la llave (que se usa a lo largo de todas las funciones
 * de los grafos) y el índice de la misma en la tabla de datos.
 */
typedef struct
{
   int    key;      ///< campo de indexado. En este ejemplo cafeteria.nombre
   size_t caferetia_idx; ///< índice del elemento en la tabla de datos
} Map;

/**
 * @brief Declara lo que es un vértice.
 */
typedef struct
{
   Map   map;       ///< Par <key, idue>: cafeteria.name, index (a la tabla de datos)>
   Node* neighbors; ///< apunta al primer vecino, ¡no debe perderse!
   Node* cursor;    ///< nodo libre
} Vertex;

/**
 * @brief Devuelve el índice del vecino (correspondiente a la lista de vértices) al 
 * que apunta el |cursor| en la lista de vecinos.
 *
 * @param v El vértice base (del cual queremos conocer el índice de su vecino).
 *
 * @return El índice del vecino en la lista de vértices.
 *
 * @pre El cursor debe apuntar a un nodo válido en la lista de vecinos.
 *
 * Ejemplo
 * @code
   Vertex* v = Graph_GetVertexByKey( grafo, 100 );
   for( Vertex_Start( v ); !Vertex_End( v ); Vertex_Next( v ) )
   {
      size_t index = Vertex_Get( v );
      printf( "[Index=%ld, [id=%d, iata_code=%c] ], ", 
         index, 
         aereopuertos[ index ].id,
         aereopuertos[ index ].iata_code );
   }
   @endcode
   @note Esta función debe utilizarse únicamente cuando se recorra el grafo con las funciones Vertex_Start(), Vertex_End() y Vertex_Next().
 */
size_t Vertex_Get( const Vertex* v )
{
   assert( v->cursor );

   return v->cursor->index;
}

/**
 * @brief Hace que cursor libre apunte al inicio de la lista de vecinos. Se debe
 * de llamar siempre que se vaya a iniciar un recorrido de dicha lista.
 *
 * @param v El vértice de trabajo (es decir, el vértice del cual queremos obtener 
 * la lista de vecinos).
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
 * @post El cursor se movió un elemento a la derecha en la lista de vecinos.
 */
void Vertex_Next( Vertex* v )
{
   assert( v->cursor );

   v->cursor = v->cursor->next;
}

/**
 * @brief Indica si se alcanzó el final de la lista de vecinos.
 *
 * @param v El vértice de trabajo.
 *
 * @return true si se alcanazó el final de la lista; false en cualquier otro
 * caso.
 */
bool Vertex_End( const Vertex* v )
{
   return v->cursor == NULL;
}

/**
 * @brief Devuelve la llave asociada al vértice indicado.
 *
 * @param v El vértice de trabajo.
 *
 * @return La llave asociada al vértice indicado.
 */
int Vertex_GetKey( Vertex* v )
{
   // para terminar
}

/**
 * @brief Devuelve el índice en la tabla de datos asociado al vértice indicado.
 *
 * @param v El vértice de trabajo.
 *
 * @return El índice en la tabla de datos asociado al vértice indicado.
 */
size_t Vertex_GetaereopuertosIndex( Vertex* v )
{
   return v->map.aereopuertos_idx;
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
typedef struct
{
   Vertex* vertices; ///< Lista de vértices
   size_t size;      ///< Tamaño de la lista de vértices

   /**
    * Número de vértices actualmente en el grafo. 
    * Como esta versión no borra vértices, lo podemos usar como índice en la
    * función de inserción
    */
   size_t len;  

   eGraphType type; ///< tipo del grafo, UNDIRECTED o DIRECTED
} Graph;

/**
 * @brief Crea un nuevo grafo.
 *
 * @param size Número de vértices que tendrá el grafo. Este idor no se puede
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
      // un idor diferente de cero:
      if( g->vertices ){
         
         Vertex* vertices = g->vertices;
         // para simplificar la notación. 
         // La variable |vertices| sólo existe dentro de este if.

         for( size_t i = 0; i < g->size; ++i ){
            vertices[ i ].map.key = 0;
            vertices[ i ].map.aereopuertos_idx = 0;
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
      printf( "<map.key:%d, map.aereopuertos_idx:%ld: %d>, \n", vertex->map.key, vertex->map.aereopuertos_idx );

      // LEVEL 0:
      printf( vertex->neighbors ? "Has neighbors\n" : "Has no neighbors\n" );

      // LEVEL 1:
      if( depth > 0 )
      {
         for( Node* node = vertex->neighbors; node != NULL; node = node->next )
         {
            DBG_PRINT( "Print():(Node:%p, (*Node.index:%ld, *Node.next:%p), Weight: %.2f)\n", node, node->index, node->next, node-> weight );
            
            //printf( " id:%d, w:%0.2f ", g->vertices[ node->index ].map.key, node->weight );
            printf( " %d(W:%f) ", g->vertices[ node->index ].map.key, node->weight );

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

   vertex->map.key      = key;
   vertex->map.aereopuertos_idx = index;
   vertex->neighbors    = NULL;

   ++g->len;
}

size_t Graph_GetSize( Graph* g )
{
   return g->size;
}


// vertices: lista de vértices
// size: número de elementos en la lista de vértices
// key: idor a buscar
// ret: el índice donde está la primer coincidencia; -1 si no se encontró
static int find( Vertex* vertices, size_t size, int key )
{
   for( size_t i = 0; i < size; ++i ){

      if( vertices[ i ].map.key == key ) return i;
   }

   return -1;
}

// busca si el índice (a la tabla de vértices) ya está en un vértice
bool find_index_in_vertex( Vertex* vertex, int index )
{
   for( Node* node = vertex->neighbors; node != NULL; node = node->next ){
      if( node->index == index ) return true;
   }
   return false;
}

// vertex: vértice de trabajo
// index: índice en la lista de vértices del vértice vecino que está por insertarse
static Node* insert( Vertex* vertex, int index )
{
   if( find_index_in_vertex( vertex, index ) == false )
   {
      // Crea al nodo:
      Node* n = (Node*) calloc( 1, sizeof( Node ) );
      assert( n );

      // Inserta al nodo al frente de la lista
      n->index = index;
      n->next = vertex->neighbors;
      vertex->neighbors = n;
      DBG_PRINT( "insert():Inserting the neighbor with (idx:%d, Node:%p)\n", index, n );
      return n;
   } 
   else DBG_PRINT( "insert: duplicated index\n" );
   return NULL;
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

   //   DBG_PRINT( "AddEdge(): start_idx=%d, finish_idx=%d\n", start_idx, finish_idx );
   DBG_PRINT( "AddEdge(): from:%d (with index:%d), to:%d (with index:%d)\n", start, start_idx, finish, finish_idx );

   if( start_idx == -1 || finish_idx == -1 ) return false;
   // uno o ambos vértices no existen

   insert( &g->vertices[ start_idx ], finish_idx );
   // insertamos la arista start-finish

   if( g->type == eGraphType_UNDIRECTED ) insert( &g->vertices[ finish_idx ], start_idx );
   // si el grafo no es dirigido, entonces insertamos la arista finish-start

   return true;
}

bool Graph_AddWeightedEdge( Graph* g, int start, int finish, double weight )
{
   assert( g->len > 0 );

   // obtenemos los índices correspondientes:
   int start_idx = find( g->vertices, g->size, start );
   int finish_idx = find( g->vertices, g->size, finish );

   //   DBG_PRINT( "AddEdge(): start_idx=%d, finish_idx=%d\n", start_idx, finish_idx );
   DBG_PRINT( "AddEdge(): from:%d (with index:%d), to:%d (with index:%d)\n", start, start_idx, finish, finish_idx );

   if( start_idx == -1 || finish_idx == -1 ) return false;
   // uno o ambos vértices no existen

   Node* n = insert( &g->vertices[ start_idx ], finish_idx);
   // insertamos la arista start-finish
   assert( n );
   //insert() no creó el nodo: PROBLEMAS
   n->weight = weight;

   // si el grafo no es dirigido, entonces insertamos la arista finish-start
   if( g->type == eGraphType_UNDIRECTED )
   {
      n = insert( &g->vertices[ finish_idx ], start_idx );
      n->weight = weight;
   } 
   // si el grafo no es dirigido, entonces insertamos la arista finish-start

   return true;
}

/**
 * @brief Devuelve el nodo que apunta al inicio de la lista de vecinos.
 *
 * @param g     El grafo.
 * @param key   El criterio de búsqueda
 *
 * @return      El nodo que apunta a la lista de vecinos. Si no los tuviera,
 *              devuelve NULL
 */
Node* Graph_GetNeighborsByKey( Graph* g, int key )
{
   for( size_t i = 0; i < g->len; ++i ){

      if( g->vertices[ i ].map.key == key ) return g->vertices[ i ].neighbors;
   }

   return NULL;
}

/**
 * @brief Devuelve el vértice correspondiente a la llave especificada.
 *
 * @param g     El grafo.
 * @param index El índice a la tabla de vértices.
 *
 * @return El vértice correspondiente a la llave especificada.
 */
Vertex* Graph_GetVertexByKey( Graph* g, int key )
{
   assert( g );

   for( size_t i = 0; i < g->len; ++i ){

      if( g->vertices[ i ].map.key == key ) return &g->vertices[ i ];
   }

   return NULL;
}

/**
 * @brief Devuelve el vértice correspondiente al índice especificado.
 *
 * @param g     El grafo.
 * @param index El índice a la tabla de vértices.
 *
 * @return El vértice correspondiente al índice especificado.
 */
Vertex* Graph_GetVertexByIndex( Graph* g, size_t index )
{
   assert( g );
   assert( index < g->len );

   return &g->vertices[ index ];
}


/**
 * @brief Devuelve el índice en la lista de vértices del vértice indicado.
 *
 * @param g El grafo.
 * @param v El vértice del cual queremos obtener el índice.
 *
 * @return El índice en la lista de vértices del vértice v.
 *
 * @pre Ambos, el grafo y el vértice deben existir.
 */
size_t Graph_GetIndex( Graph* g, Vertex* v )
{
   assert( g );
   assert( v );

   size_t index;
   for( index = 0; index < g->len; ++index ){
      if( g->vertices[ index ].map.key == v->map.key ) break;
   }

   assert( index < g->len );

   return index;
}

size_t Graph_GetLen( Graph* g )
{
   return g->len;
}

double Graph_GetWeight( Graph* g, int start, int finish)
{
    
}

//----------------------------------------------------------------------
// Driver program 
//----------------------------------------------------------------------
#define MAX_aereopuertos 7

/*
100 - 200 - 600
 |  \     \
300 - 400 - 500
*/
int main()
{
   // Inicializa la tabla de datos. <100,A>, <200,B>, ...
   Airport aereopuertos[ MAX_aereopuertos ];
   aereopuertos[0].id = 120;
   aereopuertos[0].iata_code[4] = "LHR";
   aereopuertos[0].country[65] = "LONDON";
   aereopuertos[0].city[65] = "HEATHROW";
   aereopuertos[0].name[65] = "LONDON HEATHROW";
   aereopuertos[0].utc_time = 3;
   
   aereopuertos[1].id = 130;
   aereopuertos[1].iata_code[4] = "MAD";
   aereopuertos[1].country[65] = "ESPA�A";
   aereopuertos[1].city[65] = "MADRID";
   aereopuertos[1].name[65] = "MADRID-BARAJAS";
   aereopuertos[1].utc_time = 3;

   aereopuertos[2].id = 140;
   aereopuertos[2].iata_code[4] = "FRA";
   aereopuertos[2].country[65] = "ALEMANIA";
   aereopuertos[2].city[65] = "FRANCFORT DEL MENO";
   aereopuertos[2].name[65] = "FLUGHAFEN FRANKFURT AM MAIN";
   aereopuertos[2].utc_time = 3;

   aereopuertos[3].id = 150;
   aereopuertos[3].iata_code[4] = "CDG";
   aereopuertos[3].country[65] = "FRANCIA";
   aereopuertos[3].city[65] = "PARIS";
   aereopuertos[3].name[65] = "CHARLES DE GAULLE";
   aereopuertos[3].utc_time = 3;

   aereopuertos[4].id = 160;
   aereopuertos[4].iata_code[4] = "BER";
   aereopuertos[4].country[65] = "ALEMANIA";
   aereopuertos[4].city[65] = "BERLIN";
   aereopuertos[4].name[65] = "FLUGHAFEN BERLIN BRANDENBURG";
   aereopuertos[4].utc_time = 3;

   aereopuertos[5].id = 170;
   aereopuertos[5].iata_code[4] = "HKG";
   aereopuertos[5].country[65] = "CHINA";
   aereopuertos[5].city[65] = "HONG KONG";
   aereopuertos[5].name[65] = "HONG KONG INTERNATIONAL AIRPORT";
   aereopuertos[5].utc_time = 3;

   aereopuertos[5].id = 100;
   aereopuertos[5].iata_code[4] = "MEX";
   aereopuertos[5].country[65] = "MEXICO";
   aereopuertos[5].city[65] = "MEXICO CITY";
   aereopuertos[5].name[65] = "AEROPUERTO INTERNACIONAL BENITO JU�REZ";
   aereopuertos[5].utc_time = -6;
   Graph* grafo = Graph_New( 
         MAX_aereopuertos,                // cantidad máxima de nodos
         eGraphType_UNDIRECTED ); // será un grafo no dirigido

   // crea los vértices:
    Graph_AddVertex(grafo, 120, 0);//lhr
	Graph_AddVertex(grafo, 130, 1 );//mad
	Graph_AddVertex(grafo, 140, 2);//fra
	Graph_AddVertex(grafo, 150, 3);//cdg
	Graph_AddVertex(grafo, 160, 4);//ber
	Graph_AddVertex(grafo, 170, 5 );//hkg
	Graph_AddVertex(grafo, 100, 6);//mex
   
   // crea las conexiones entre vértices:
   Graph_AddWeightedEdge( grafo, 140, 160, 1.5 );//fra a ber
   Graph_AddWeightedEdge( grafo, 140, 120, 3 );//fra a lhr
   Graph_AddWeightedEdge( grafo, 100, 140, 10 );//mex a fra
   Graph_AddWeightedEdge( grafo, 100, 150, 9 );//mex a cdg
   Graph_AddWeightedEdge( grafo, 100, 130, 9.5 );//mex a mad
   Graph_AddWeightedEdge( grafo, 150, 100, 9 );//cdg a mex
   Graph_AddWeightedEdge( grafo, 150, 170, 14 );//cdg a hkg
   Graph_AddWeightedEdge( grafo, 170, 150, 14 );//hkg a cdg
   Graph_AddWeightedEdge( grafo, 150, 120, 2.5 );//cdg a lhr
   Graph_AddWeightedEdge( grafo, 120, 160, 2 );//lhr a ber
   Graph_AddWeightedEdge( grafo, 130, 150, 1.5 );//mad a cdg
   Graph_AddWeightedEdge( grafo, 130, 120, 2 );//mad a lhr
   Graph_AddWeightedEdge( grafo, 160, 100, 14 );//ber a mex
   

   Graph_Print( grafo, PRINT_LEVEL );
   // imprime el grafo completo



   Graph_Delete( &grafo );
   assert( grafo == NULL );
}

