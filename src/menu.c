#include "menu.h"
#include "util.h"
#include "string.h"
#include "map.h"

void mostrarMenu(){
    clrscr();
    printf("%s", buf);
    strcpy(buf, "");

    printf("\033[36m\nLibreria\n"COLOR_RESET);

    printf("'c' : Cargar documento\n");
    printf("'m' : Mostrar documentos ordenados\n");
    printf("'b' : Buscar libro\n");
    printf("'B' : Mostrar palabras mas frecuentes\n");
    printf("'A' : Mostrar palabras mas relevantes\n");
    printf("'X' : Buscar palabra\n");

    printf("'q' : Salir\n");
}

void mostrarMenuBuscar(){
    clrscr();
    printf("%s", buf);
    strcpy(buf, "");


    printf(COLOR_CYAN"Menu de busqueda\n"COLOR_RESET);
    printf("'n': Por Titulo\n");
    printf("'t': Por Palabra\n");
    printf("'e': Salir\n");
    
                
}



