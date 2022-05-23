/* Entrada y salida estándar */
#include <stdio.h>

/* manipulación de Strings */
#include <string.h>
/*Probando*/
#include "import.h"
#include "menu.h"
#include "util.h"
#include "search.h"
#include "list.h" 
#include "map.h"
#include "word.h"




/* main function */
int main(){
    Map * mapBooks = createMap(is_equal_string,lower_than_string);
    Map * mapWords = createMap(is_equal_string,lower_than_string);

    char in = '\0';

    while(in != 'q' ){
        mostrarMenu();
        fflush(stdin);
        scanf("%c", &in);
        getchar();

        switch(in) {
            case ('c'): // Importar libro
                importBook(mapBooks, mapWords);
                break;
            case ('m'): // Mostrar documentos 
                showBook(mapBooks);
                break;
            case('b'): // Buscar libro
                break;
            case('B'): // Mostrar palabras mas frecuentes
                searchMostFrecuent(mapBooks, mapWords);
                break;
            case('A'): // Mostrar palabras mas relevantes
                searchMostRelevant(mapBooks, mapWords);
                break;
            case('X'): // Buscar palabra
                searchWord(mapWords);
                break;
            case('C'):
            
                searchContext(mapWords, mapBooks);
                break;
            
            default:
                break;
          } 

    } // while (in != q)
    printf("Bye bye\n");
    return 0;
}


