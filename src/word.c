#include "import.h"
#include "util.h"
#include "menu.h"
#include "map.h"
#include "word.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

//Comparar Strings
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

int lower_than_int(void * key1, void * key2) {
    if(*(int*)key1 < *(int*)key2) return 1;
    return 0;
}

Word *createWord(){
    Word *word = (Word*) malloc(sizeof(Word));
    strcpy(word -> name, "");
    word -> num = 1;
    word -> ocurrencias = listCreate();

    return word;
}

Pos *createPos(){
    Pos *pos = (Pos*) malloc(sizeof(Pos));
    pos -> pos = 0;
    strcpy(pos -> bookName, "");

    return pos;
}

//Agregue los valores iniciales para el book
Book *createBook(){
    Book * book = (Book*) malloc(sizeof(Book));
    book->words = createMap(is_equal_string,lower_than_string);
    strcpy(book -> bookName, "");
    strcpy(book -> fileName, "");
    book->totalPalabras = 0;
    book -> totalChar = 0;
    book -> totalWords = 0;
    book -> mostRelevant = createTreeMap(lower_than_int);
    book -> mostFrecuent = createTreeMap(lower_than_int);
    return book;
}



void initBook(Book * book,char *id){
    //El archivo se abre y queda referenciado en book
    char open[20];
    strcpy(open, id);
    strcat(open, ".txt");
    strcpy(book -> fileName,id);    //Le pone el filename al libro
    book -> arch = fopen(open, "r");//Abre el archivo
    if(book->arch == NULL){
        printf("Error al abrir archivo\n");
        return;
    }
    char x[1024];
    //Se salta las primeras palabras hasta llegar al inicio del titulo
    for(int i = 0; i < 5; i++){
        fscanf(book -> arch," %1023s", x);
    }
    //Lee hasta llegar al by que significa que se acabo el titulo del libro
    while (fscanf(book->arch, " %1023s", x) == 1){
        if(strcmp(x,"by") == 0){
            break;
        }else{
            //Agrega el las palabras(del titulo) al book
            if(quitar_caracteres(x, ",")){
                strcat(book -> bookName,x);
            }else{
                strcat(book -> bookName,x);
                strcat(book -> bookName," ");
            }
        }
    }

}

void readBook(Book * book){
    rewind(book->arch);//Vuelve a abrir al inicio del archivo
    char * x = malloc(1024 * sizeof (char) );
    while((fscanf(book->arch, " %1023s", x) == 1)){ //recorre cada palabra del archivo
        //printf("%s largo = %lo\n",x,strlen(x));
        book -> totalChar += strlen(x);//Suma los caracteres de la palabra
        quitar_caracteres(x,".,;:-_()/?¡![]{}+*=%%$&‘’“");//elimina esos caracteres de la palabra
        lower(x);//Lo hace minuscula
        Word *aux = searchMap(book -> words,x);//ve si la palabra existe dentro del mapa libro (que almacena todas las palabras del libro)
        if(aux == NULL){//Si no existe la crea y agrega al mapa
            Word * new = createWord();
            strcpy(new -> name, x);
            insertMap(book -> words,new ->name,new);
        }else{//Si existe le suma 1 a la cantidad de veces que se repite
            (aux -> num)++;
        }          
    }

    /*for(Word *aux = firstMap(book -> words);
            aux != NULL; 
            aux = nextMap(book -> words)) 
    {
        printf("la cuenta va en %lo\n",book -> totalWords);
        (book -> totalWords)+= aux -> num;
        printf("%s: ",aux ->name);
        printf("%lo\n",aux ->num);
    }
    printf("%lo",book ->totalChar);*/
    return;
}

void bookToMap(Map *mapBook, Book *book){
//Agrega un libro al mapa
    Book *aux = searchMap(mapBook,book ->fileName);
    if(aux == NULL){
        insertMap(mapBook,book ->fileName,book);
    }else{
        printf("Libro ya existe");
    }
    /*for(Book *aux = firstMap(mapBook);
            aux != NULL; 
            aux = nextMap(mapBook)) 
    {
        printf("%s\n",aux -> fileName);
    }*/
    return;
}



void searchWord(Map* mapWords){
    Word* aux = createWord();
    char *palabra = (char *) malloc(sizeof(char)*50);
    printf("Ingresa la palabra que quiere buscar: ");
    fflush(stdin);
    scanf("%[^\n]*s", palabra);
    getchar();

    //char last_book[50] = NULL;

    if (searchMap(mapWords, palabra) != NULL){
        aux = searchMap(mapWords, palabra);
        listFirst(aux->ocurrencias);
        strcat(buf, "Libros en los que aparece: ");
        strcat(buf, "\n");
        for (Pos* i = listFirst(aux->ocurrencias); i != NULL; i = listNext(aux->ocurrencias) ){
            //if(strcmp(last_book, i -> bookName) != 0){
                strcat(buf, "Titulo: ");
                strcat(buf, i->bookName);
                strcat(buf, "\n");
                //strcpy(last_book[50], i->bookName);
            //}
        }
    }else{
        strcat(buf, "No se encontro la palabra\n");
    }


}

double relevanciaPalabras(char* palabra, char* titulo, Map* mapWords, Map* mapBooks){

    Word* word = createWord();
    Book* book = createBook();

    word = searchMap(mapWords, palabra);
    book = searchMap(mapBooks, titulo);

    int totalOcurrencias = 0;//Total de veces que aparece la palabra en el libro
    int totalLibros = 0;
    int librosDiferentes = 0;
    double finalPart = 0;
    
    char lastBook[100];
    strcpy ( lastBook, titulo);

    if (word != NULL && book != NULL){
        for (Pos* i = listFirst(word->ocurrencias); i != NULL; i = listNext(word->ocurrencias)){
            if (strcmp(i->bookName, titulo) == 0){
                totalOcurrencias++;
            }else{
                
                if (strcmp(lastBook, i->bookName) != 0){
                    strcpy(lastBook, i->bookName);
                    librosDiferentes++;
                }
            }
        }

        double firstPart = totalOcurrencias / book->totalPalabras;

        for (Book* i = firstMap(mapBooks); i != NULL; i = nextMap(mapBooks)){
            totalLibros++;
        }

        double secondPart = log(totalLibros /  librosDiferentes);  

        finalPart = firstPart * secondPart;
    }

    return finalPart;
}
/*
void showPos(Word *word){
    for (Pos* i = listFirst(word->ocurrencias); i != NULL; i = listNext(word->ocurrencias) ){
        strcat(buf, i->bookName);
    }
}
*/

/*
void showWords(Map * mapWords){
    for(Word *word = firstMap(mapWords);
            word != NULL; 
            word = nextMap(mapWords)) 
    {
        strcat(buf, word ->name);
        showPos(word);
        strcat(buf, "\n");
    }
}
*/

void showInContext(char *_word, char *_title, Map *mapWords, Map *mapBooks){
    Word *word = searchMap(mapWords, _word);
    if(word == NULL){
        strcat(buf, "Palabra no encontrada");
        return;
    }
    Book *book = searchMap(mapBooks, _title);
    if(book == NULL){
        strcat(buf, "Libro no encontrado");
        return;
    }
    FILE *file = fopen(book ->fileName , "r");

    char *mensaje = (char*) malloc(sizeof(char)*100);

    clrscr();
    strcat(buf, "Ocurrencias en ");
    strcat(buf, _title);
    strcat(buf, ": \n");

    for (Pos* i = listFirst(word->ocurrencias); i != NULL; i = listNext(word->ocurrencias) ){
        if(strcmp(i -> bookName, book ->bookName) == 0){
            fseek(file, i->pos, SEEK_SET);
            fgets(mensaje,100,file);
            strcat(buf, "-");
            strcat(buf, mensaje);
        }
    }
    fclose(file);
}

void searchContext(Map *mapWords, Map *mapBooks){
    char *palabra = (char *) malloc(sizeof(char)*50);
    printf("Ingresa la palabra que quiere buscar: ");
    fflush(stdin);
    scanf("%[^\n]*s", palabra);
    getchar();

    char *titulo = (char *) malloc(sizeof(char)*50);
    printf("Ingresa el titulo del libro: ");
    fflush(stdin);
    scanf("%[^\n]*s", titulo);
    getchar();

    showInContext(palabra, titulo, mapWords, mapBooks);
}

TreeMap *makeRelevantTree(Map *mapWords, Map *mapBooks, char *title){
    TreeMap *map = createTreeMap(lower_than_int);
    int found = 0;
    double relev = 0;
    for(Word *i = firstMap(mapWords); i!= NULL; i = nextMap(mapWords)){
        for(Pos* j = listFirst(i->ocurrencias); j != NULL; j = listNext(i->ocurrencias) ){
            if(found == 0){
                if(strcmp(j->bookName, title) == 0){
                    found = 1;
                    break;
                }
            }
        }
        if(found == 1){
            relev = relevanciaPalabras(i -> name, title, mapWords, mapBooks);
        }
        found = 0;
    }
    return map;
}
/*Problemas


totalChar cuenta caracteres demas(hay palabras que cuenta caracteres de mas, por ejemplo en hola.txt a Gutenberg le cuenta 11 caracteres)
totalWords cuenta palabras de mas(Es raro porque num en cada palabra si corresponde con la cantidad de veces que sale la palabra)
Falta quitar algunos caracteres en la funcion (no se cuales son pero quedan palabras con cosas  raras)
*/
