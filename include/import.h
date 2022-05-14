#ifndef IMPORT_H
#define IMPORT_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "util.h"
#include "map.h"


typedef struct {
    FILE *fd;
    List *list;
}CSV;


void import(char *fileName, Map* mapBooks, Map* mapWords);

// Menú interactivo
void listaImportarArchivo(Map* mapNames, Map* mapTypes, Map* mapBrands);

void listaExportarArchivo(Map* mapNames);

CSV *CSVnew();
#endif
