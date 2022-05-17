/* Entrada y salida estándar */
#include <stdio.h>

/* manipulación de Strings */
#include <string.h>

#include "import.h"
#include "menu.h"
#include "util.h"
#include "search.h"
#include "list.h" 
#include "map.h"

int lower_than_string(void* key1, void* key2);
int is_equal_string(void * key1, void * key2);


/* main function */
int main(){
    Map * mapBooks = createMap(is_equal_string);
    Map * mapWords = createMap(is_equal_string);

    char in = '\0';

    while(in != 'q' ){
        mostrarMenu();
        fflush(stdin);
        scanf("%c", &in);
        getchar();

        switch(in) {
            case ('c'): // Importar libro
                import("1.txt", mapBooks, mapWords);
                break;

            case ('e'): // Exportar archivo por nombre
                break;
            case('a'): // Agregar producto
                break;
            case('x'): // Quitar producto
                break;
            case('b'): // Buscar producto
                break;
            case('M'): // Mostrar todos los productos
                break;
            case('A'): // Añadir al carrito
                break;
            case('X'): // Quitar del carrito
                break;
            case('p'): // Concretar compra
                break;
            //case('C'): // Mostrar carritos
            //    break;
            //case('c'): // Mostrar carrito
            //    break;
            default:
                break;
          } 

    } // while (in != q)
    printf("Bye bye\n");
    return 0;
}


int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

int lower_than_string(void* key1, void* key2){
    char* k1=(char*) key1;
    char* k2=(char*) key2;
    if(strcmp(k1,k2)<0) return 1;
    return 0;
}
