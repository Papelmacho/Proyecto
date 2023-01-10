int main()
{
   setlocale(LC_ALL,"Spanish");
   // Inicializa la tabla de datos. <100,A>, <200,B>, ...
   Cafeteria cafeteria[ MAX_COFFESHOP ];
   cafeteria[0].id = 120;
   cafeteria[0].quality_score = 4.5;
   strcpy(cafeteria[0].nearly, "Facultad de Ingeniería y anexo");
   strcpy(cafeteria[0].name, "Cibarium");
   
   
   cafeteria[1].id = 130;
   cafeteria[1].quality_score = 3.3;
   strcpy(cafeteria[1].nearly, "Diseño Industrial");
   strcpy(cafeteria[1].name, "Cafeteria Diseño");
   

   cafeteria[2].id = 140;
   cafeteria[2].quality_score = 4.1;
   strcpy(cafeteria[2].nearly, "Ciencias, Contaduria y Anexo de Ingenieria");
   strcpy(cafeteria[2].name, "Cafesin");
   

   cafeteria[5].id = 170;
   cafeteria[5].quality_score = 3.5;
   strcpy(cafeteria[5].nearly, "Islas");
   strcpy(cafeteria[5].name, "Cafeteria Islas");
   

   cafeteria[4].id = 160;
   cafeteria[4].quality_score = 4.1;
   strcpy(cafeteria[4].nearly, "Facultad de Arquitectura");
   strcpy(cafeteria[4].name, "Cafeteria diseño");
   

   cafeteria[3].id = 150;
   cafeteria[3].quality_score = 3.5;
   strcpy(cafeteria[3].nearly, "Facultad de Contaduria y Administración");
   strcpy(cafeteria[3].name, "Cafeterias FCA");
   

   cafeteria[6].id = 100;
   cafeteria[6].quality_score = 4.3;
   strcpy(cafeteria[6].nearly, "Facultad de Ciencias");
   strcpy(cafeteria[6].name, "Comedor estudiantil ciencias");

   cafeteria[7].id = 180;
   cafeteria[7].quality_score = 4.1;
   strcpy(cafeteria[7].nearly, "Faculta de Veterinaria");
   strcpy(cafeteria[7].name, "Cafeteria Veterinaria");

   cafeteria[8].id = 190;
   cafeteria[8].quality_score = 2.9;
   strcpy(cafeteria[8].nearly, "Facultad de Derecho y Filosofia");
   strcpy(cafeteria[8].name, "Cafeteria Filosofia y Letras");

   cafeteria[9].id = 200;
   cafeteria[9].quality_score = 4.0;
   strcpy(cafeteria[9].nearly, "Facutad de Sociales y Politicas");
   strcpy(cafeteria[9].name, "Cafeteria FCPyS");


   Map adyacency_table[ MAX_COFFESHOP ];
   adyacency_table[0].key= cafeteria[0].id;
   adyacency_table[0].data_idx = 0;
   adyacency_table[1].key= cafeteria[1].id;
   adyacency_table[1].data_idx = 1;
   adyacency_table[2].key= cafeteria[2].id;
   adyacency_table[2].data_idx = 2;
   adyacency_table[3].key= cafeteria[3].id;
   adyacency_table[3].data_idx = 3;
   adyacency_table[4].key= cafeteria[4].id;
   adyacency_table[4].data_idx = 4;
   adyacency_table[5].key= cafeteria[5].id;
   adyacency_table[5].data_idx = 5;
   adyacency_table[6].key= cafeteria[6].id;
   adyacency_table[6].data_idx = 6;
   adyacency_table[7].key= cafeteria[7].id;
   adyacency_table[7].data_idx = 7;
   adyacency_table[8].key= cafeteria[8].id;
   adyacency_table[8].data_idx = 8;
   adyacency_table[9].key= cafeteria[9].id;
   adyacency_table[9].data_idx = 9;
   
   //lo que se tiene que agarrar para agregar vertices son las tablad de adyacencia
   //no la tabla maestra identificada como aereopuertos

   Graph* grafo = Graph_New( 
         MAX_COFFESHOP,                // cantidad máxima de nodos
         eGraphType_DIRECTED ); // será un grafo no dirigido

   // crea los vértices:
   Graph_AddVertex(grafo, 120, 0);//cibarium
   Graph_AddVertex(grafo, 130, 1 );//diseño ind.
   Graph_AddVertex(grafo, 140, 2);//cafesin
	Graph_AddVertex(grafo, 150, 3);//cafeterias FCA
	Graph_AddVertex(grafo, 160, 4);//cafeteria arqui
	Graph_AddVertex(grafo, 170, 5 );//cafeteria islas
	Graph_AddVertex(grafo, 100, 6);//ciencias
   Graph_AddVertex(grafo, 180, 7);//Veterinaria
   Graph_AddVertex(grafo, 190, 8);//filosofia
   Graph_AddVertex(grafo, 200, 9);//Cafeteria FCPyS

   // crea las conexiones entre vértices:
   Graph_AddWeightedEdge( grafo, 120, 130, 550 );//cibarium a diseño ind.
   Graph_AddWeightedEdge( grafo, 120, 140, 700 );//cibarium a cafesin
   Graph_AddWeightedEdge( grafo, 140, 150, 300 );//cafesin a cafeterias FCA
   Graph_AddWeightedEdge( grafo, 130, 160, 700 );//diseño ind. a cafeteria arqui
   Graph_AddWeightedEdge( grafo, 130, 170, 700 );//diseño ind. a cafeteria islas
   Graph_AddWeightedEdge( grafo, 140, 100, 550 );//cafesin a comedor de ciencias
   Graph_AddWeightedEdge( grafo, 120, 180, 1000 );//cibarium a veterianaria
   Graph_AddWeightedEdge( grafo, 170, 190, 500 );//cafeteria islas a cafeteria filos
   Graph_AddWeightedEdge( grafo, 100, 150, 850 );//comedor ciencias a veterinaria
   Graph_AddWeightedEdge( grafo, 170, 160, 600 );//cafeteria arqui a cafeteria islas
   Graph_AddWeightedEdge( grafo, 100, 200, 1000 );//comedor ciencias a cafeteria FCPyS

   Graph_Print( grafo, PRINT_LEVEL, cafeteria );
   // imprime el grafo completo

   Graph_Delete( &grafo );
   assert( grafo == NULL );
}




