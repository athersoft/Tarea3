#ifndef ITEM_H
#define ITEM_H
#include "list.h"
#include "util.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct {
    char name[60];
    char brand[30];
    char type[20];
    int stock;
    int price;
}Item;

Item *createItem();

int addItem(Map* mapNames, Map* mapTypes, Map* mapBrands);

void findItem(Map* map, void * key);

void showItem(Item *item);

void showItems(Map *nameMap);

void showItemsByType(Map *typeMap);
void showItemsByBrand(Map *brandMap);

void insertMapList(Map * map,char *key,Item * item);

void showList(List *list);

void searchItem(Map *map);

#endif
