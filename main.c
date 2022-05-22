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
    Book * test = createBook();
    //Book * test2 = createBook();

    char in = '\0';

    while(in != 'q' ){
        mostrarMenu();
        fflush(stdin);
        scanf("%c", &in);
        getchar();

        switch(in) {
            case ('c'): // Importar libro
                importBook(mapBooks, mapWords);
                test = firstMap(mapBooks);
                break;
            case ('m'): // Mostrar documentos 
                showWords(mapWords);
                break;
            case('b'): // Buscar libro
                initBook(test,"67937");
                readBook(test);
                bookToMap(mapBooks,test);
                context(test,"Tiadatha");
                scanf("%c",&in);
                break;
            case('B'): // Mostrar palabras mas frecuentes
                showBook(test);
                scanf("%c",&in);
                break;
            case('A'): // Mostrar palabras mas relevantes
                printf("“Stout old heart,” cheered Tiadatha,");
                scanf("%c",&in);
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


