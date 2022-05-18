#include "import.h"
#include "util.h"
#include "menu.h"
#include "map.h"
#include "word.h"


void wordsToMap(char *text, Map * mapWords, long int bookPos, char *title){

    Word *word = createWord();

    Pos *pos = createPos();
    pos -> pos = bookPos;
    strcpy(pos -> bookName, title);
    
    if(searchMap(mapWords, text) == NULL){
        strcpy(word->name, text);
        listPushBack(word->ocurrencias, pos);
        word -> num = 1; 
        insertMap(mapWords, text, word);
        //strcat(buf, text);
        //strcat(buf, " guardada ");
    }else{
        word = searchMap(mapWords,text);
        listPushBack(word->ocurrencias, pos);
        word -> num++;
        //strcat(buf, text);
        //strcat(buf, " agregada ");
    }
    
    strcat(buf, text);//
    strcat(buf, " guardada ");//
}

void import(char *name, Map * mapBooks, Map * mapWords){
    clrscr();
    printf("\nCargando libro, espere un momento...");
    FILE *file;
    file = fopen(name, "r");

    char title[50];
    int titleSaved = 0;

    char text[50];
    //char *text;
    //text = (char*) malloc(sizeof(char)*2);
    long int bookPos = ftell(file);

    int pos = 0;

   while(1){
        text[pos] = fgetc(file);

        if(titleSaved == 1){
            if(text[pos] == ' ' || text[pos] == '\n' || text[pos] == ',' || text[pos] == '.'){
                text[pos] = '\0';
                if(strlen(text) > 1){
                    wordsToMap(text, mapWords, bookPos, title);
                }
                bookPos = ftell(file);
                //free(text);
                //text = (char *) realloc(text, sizeof(char)*2);
                memset(text, 0, 50);
                
                pos = 0;
            }else{
                pos++;
                //text =(char *) realloc(text, sizeof(char)*(pos+1));
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
    
    strcat(buf, "Libro Guardado");
    Book *book = createBook();
    strcpy(book -> bookName, title);
    strcpy(book -> fileName, name);

    //free(text);
    fclose(file);
    
}

void importBook(Map* mapBooks, Map* mapWords) {
    char archivo[30];
    printf("Ingresa el nombre del libro a importar: ");
    fflush(stdin);
    scanf("%[^\n]*s", archivo);
    getchar();
    import(archivo, mapBooks, mapWords);
}

