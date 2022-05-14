#include "word.h"
#include "list.h"
#include <string.h>

Word *createWord(){
    Word *word = (Word*) malloc(sizeof(Word));
    strcpy(word->name, "");
    word -> num = 0;
    //word -> ocurrencias = listCreate();
    return word;
}