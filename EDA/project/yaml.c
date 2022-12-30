#include "yaml.h"

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

void create_yaml( Cafeteria* cafeteria, char* file_name ){
   
    strcat(file_name, ".yaml");
    FILE* yaml_output = fopen(file_name, "w");
    if (yaml_output == NULL){
        printf( "El archivo %s no pudo ser abierto para escritura.\n", file_name);
        exit( -1 );
    }
    fprintf(yaml_output, "Nombre: %s\n", cafeteria->name);
	fprintf(yaml_output, "Facultad cercana: %s\n", cafeteria->facultad_cercana);
        
    fprintf(yaml_output, "Menú:\n");
    fprintf(yaml_output, "Precio: %0.2f\n", cafeteria->menus->precio);
    fprintf(yaml_output, "Bebida: %s\n", cafeteria->menus->bebida ? "true" : "false");
    fprintf(yaml_output, "Bolillo o tortilla: %s\n", cafeteria->menus->bolillo_tortilla ? "true" : "false");
    fprintf(yaml_output, "Sopa: %s\n", cafeteria->menus->sopa ? "true" : "false");
    fprintf(yaml_output, "Guisado: %s\n", cafeteria->menus->guisado ? "true" : "false");
    fprintf(yaml_output, "Postre: %s\n", cafeteria->menus->postre ? "true" : "false");
    fclose(yaml_output);
}

int main(){
    char nombreArchivoYaml[80] = "Info";
    Cafeteria Info = {
        .name = "Ciberium",
        .facultad_cercana = "Facultad de Ingeniería"
	};
    
    printf("\nInformacion en YAML\n");
    create_yaml(&Info, nombreArchivoYaml);
    read_file(nombreArchivoYaml);
}

