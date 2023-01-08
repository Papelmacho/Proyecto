#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


void create_yaml( Cafeteria* cafeteria, char* file_name ){
   
    strcat(file_name, ".yaml");
    FILE* yaml_output = fopen(file_name, "w");
    if (yaml_output == NULL){
        printf( "El archivo %s no pudo ser abierto para escritura.\n", file_name);
        exit( -1 );
    }
}


    fprintf(yaml_output, "Nombre: %s\n", cafeteria->name);
	fprintf(yaml_output, "Facultad cercana: %s\n", cafeteria->facultad_cercana);
        
    fprintf(yaml_output, "Menu:\n");
    fprintf(yaml_output, "Precio: %0.2f\n", cafeteria->menus);
    fprintf(yaml_output, "Bebida: %s\n", cafeteria->menus ? "true" : "false");
    fprintf(yaml_output, "Bolillo o tortilla: %s\n", cafeteria->menus ? "true" : "false");
    fprintf(yaml_output, "Sopa: %s\n", cafeteria->menus ? "true" : "false");
    fprintf(yaml_output, "Guisado: %s\n", cafeteria->menus ? "true" : "false");
    fprintf(yaml_output, "Postre: %s\n", cafeteria->menus ? "true" : "false");
    fclose(yaml_output);
}

void read_file( char* file_name ){
	FILE* file;
    char c;
    file = fopen(file_name, "r");
    if(file == NULL){
        exit( -1 );
        return;
    }
    while( (c = getc(file)) != EOF){
        printf("%c", c);
    }
    fclose(file);
    printf("\n");
    return;
}