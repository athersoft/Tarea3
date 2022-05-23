#include "import.h"
#include "util.h"
#include "menu.h"
#include "map.h"
#include "word.h"
#include <stdlib.h>
#include <assert.h>


void wordsToMap(char *text, Map * mapWords, long int bookPos, char *title){

    char *texto = (char *) malloc(sizeof(char)*100);
    strcpy(texto, text);

    Pos *pos = createPos();
    pos -> pos = bookPos;
    strcpy(pos -> bookName, title);
    
    Word *word = searchMap(mapWords, texto); 

    if(!word){
        word = createWord();
        strcpy(word->name, texto);
        listPushBack(word->ocurrencias, pos);
        word -> num = 1; 
        //insertMap(mapWords, text, word);
        _pushFront(mapWords, texto, word);
       // strcat(buf, texto);
       // strcat(buf, " guardada ");
    }else{
        //word = searchMap(mapWords,text);
        //if(strcmp(word -> name,text) == 0){
        listPushBack(word->ocurrencias, pos);
        word -> num++;

        //strcat(buf, text);
        //strcat(buf, " agregada ");
        //}
    }
    
    //strcat(buf, text);//
    //strcat(buf, " guardada ");//
}

void listCreation(Map *mapBooks, Map* mapWords, char *title){
    Book *book = searchMap(mapBooks, title);
    book -> mostRelevant = makeRelevantTree(mapWords, mapBooks, book ->bookName);
    book -> mostFrecuent = makeFrecencyTree(mapWords, book -> bookName);
}

void import(char *name, Map * mapBooks, Map * mapWords){
    clrscr();
    printf("\nCargando libro, espere un momento...");
    FILE *file;
    file = fopen(name, "r");

    char title[100];
    int titleSaved = 0;
    int totalPalabras = 0;

    char text[100];
    //char *text;
    //text = (char*) malloc(sizeof(char)*2);
    long int bookPos = ftell(file);

    int pos = 0;
    long cont = 0;
    //clrscr();

   while(1){
        text[pos] = fgetc(file);
        //cont++;
        //printf("%ld", cont);
        //printf("%s\n", text);
        if(titleSaved == 1){
            if(text[pos] == ' ' || text[pos] == '\n' || text[pos] == ',' || text[pos] == '.' || text[pos] == ':' || text[pos] == '['){
                text[pos] = '\0';
                if(strlen(text) > 1){
                    wordsToMap(text, mapWords, bookPos, title);

                    totalPalabras++;
                }
                bookPos = ftell(file);
                memset(text, 0, 50);
                
                pos = 0;
            }else{
                cont++;
                pos++;
            }
        }else{
            title[pos] = text[pos];
            if(text[pos] == '\n'){
                title[pos] = '\0';
                //strcat(buf, "Titulo: ");//
                //strcat(buf, title); //
                //strcat(buf, "\n");//
                titleSaved = 1;
                pos = 0;
                bookPos = ftell(file);
            }else{
                pos++;
            }
        }

        if(feof(file)){
            text[pos] = '\0';
            if(strlen(text) > 1){
                wordsToMap(text, mapWords, bookPos, title);
            }
           break;
       }
        
    }
    
    strcat(buf, title);
    strcat(buf, " guardado correctamente");

    Book *book = createBook();
    strcpy(book -> bookName, title);
    strcpy(book -> fileName, name);
    book -> totalChar = cont;
    book->totalPalabras = totalPalabras;
    insertMap(mapBooks,book -> bookName,book);
    //_pushFront(mapBooks, book -> bookName, book);

    listCreation(mapBooks, mapWords, book -> bookName);
    //free(text);
    fclose(file);
    
}

void importBook(Map* mapBooks, Map* mapWords) {
    char archivo[30];
    printf("Ingrese la id del libro a importar: ");
    fflush(stdin);
    scanf("%[^\n]*s", archivo);
    getchar();
    FILE* file;
    file = fopen(archivo, "r");
    if(file == NULL){
        
        while(file == NULL){
            printf("Ingrese nuevamente la id del libro (recuerde ingresar '.txt' al final de cada id): ");
            scanf("%[^\n]*s", archivo);
            getchar();
            file = fopen(archivo, "r");
        }
    }else{
        fclose(file);
        import(archivo, mapBooks, mapWords);
    }
    fclose(file);
    import(archivo, mapBooks, mapWords);
}

