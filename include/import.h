#ifndef IMPORT_H
#define IMPORT_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "util.h"
#include "map.h"


void import(char *fileName, Map* mapBooks, Map* mapWords);

// Menú interactivo
void importBook(Map* mapBooks, Map* mapWords);

void wordsToMap(char *text, Map * mapWords, long int bookPos, char *title);
#endif
