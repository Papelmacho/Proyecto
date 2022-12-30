#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    double precio; 
    bool bebida;
    bool bolillo_tortilla;
    bool sopa;
    bool guisado;
    bool postre;
} Menu;

typedef struct 
{
	Menu* menus;
    char facultad_cercana[65];
    char name[65];
} Cafeteria;

void create_yaml( Cafeteria* cofeteria, char* file_name );
void read_file( char* file_name );

