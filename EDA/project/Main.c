int main()
{
   // Inicializa la tabla de datos. <100,A>, <200,B>, ...
   Cafeteria cafes[ MAX_DATA ];//cafes hace referencia a los arreglos de tipo cafereria
   char name = 'A';
   for( size_t i = 1; i <= MAX_DATA; ++i, ++name) {
      data[i-1].val = i * 100;
      data[i-1].name = name;
   }

   Graph* grafo = Graph_New( 
         MAX_DATA,                // cantidad máxima de nodos
         eGraphType_UNDIRECTED ); // será un grafo no dirigido

   // crea los vértices:
   for( size_t i = 0; i < MAX_DATA; ++i )
   {

      Graph_AddVertex( 
            grafo,         // el grafo de trabajo
            data[ i ].val, // el campo de indexado en los datos
            i );           // índice de los datos en la tabla de datos
   }

   // crea las conexiones entre vértices:
   Graph_AddEdge( grafo, 100, 200 );
   Graph_AddEdge( grafo, 100, 300 );
   Graph_AddEdge( grafo, 100, 400 );
   Graph_AddEdge( grafo, 200, 500 );
   Graph_AddEdge( grafo, 200, 600 );
   Graph_AddEdge( grafo, 300, 400 );

   assert( Graph_AddEdge( grafo, 300, 100) == true );
   assert( Graph_AddEdge( grafo, 300, 400) == true );
   assert( Graph_AddEdge( grafo, 400, 100) == true );
   assert( Graph_AddEdge( grafo, 400, 300) == true );
   assert( Graph_AddEdge( grafo, 400, 500) == true );
   assert( Graph_AddEdge( grafo, 500, 200) == true );
   assert( Graph_AddEdge( grafo, 500, 400) == true );
   assert( Graph_AddEdge( grafo, 600, 200) == true );

   Graph_Print( grafo, PRINT_LEVEL );
   // imprime el grafo completo

   printf( "100's neighbors: " );
   Vertex* v = Graph_GetVertexByKey( grafo, 100 );

   for( Vertex_Start( v ); !Vertex_End( v ); Vertex_Next( v ) ){

      size_t index = Vertex_Get( v );

      printf( "[Index=%ld, [Val=%d, Name=%c] ], ", 
         index, 
         data[ index ].val,
         data[ index ].name );
   }
   printf( "\n" );

   
#if 0 
   printf( "BFS: \n" );
   bfs( grafo, Graph_GetVertexByKey( grafo, 100 ) );
#endif  

   
   Graph_Delete( &grafo );
   assert( grafo == NULL );
}