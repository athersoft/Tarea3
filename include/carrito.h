#ifndef CARRITO_H
#define CARRITO_H
#include <string.h>
#include "list.h"
#include "map.h"
#include "item.h"

// Item en el carrito
typedef struct {
    Item *item;
    int stock;
} CartItem;



typedef struct Cart {   //Carrito
    char name[60];
    List *list;         //Lista de productos del carrito
    int size;           //Cantidad de items en el carrito
    int total;          //Total en pesos del carrito
    CartItem lastCartItem;//Ultimo item ingresado al carrito
} Cart;

int deleteItem(Cart *cart);

void addToCart(Map *mapCarts, Map *mapName); //Agrega un item al carrito

Cart *cartCreate(char *cartName); //Inicializa un carrito

void showCarts(Map *mapCarts);  //Muestra los carritos y su informacion

void showCart(Cart *cart);      //Muestra la informacion de un solo carrito

CartItem *cartItemCreate(Item* item, int stock);    //Crea un item para el carrito

CartItem *searchCartItem(List *list, char *itemName);   //Busca un item en el carrito

void popLastCart(Map* mapCarts, Map* mapNames);         //Elimina el ultimo item del carrito

void cartCheckout(Map *mapCarts, Map *mapNames);        //Se lleva a cabo la compra del carrito

void deleteStock(Map *mapNames, Cart *cart);            //Elmina el stock al realizar la compra

int stockCheck(Cart *cart, Map *mapNames);              //Revisa si hay stock para concretar la compra

void updateCart(Cart *cart);                            //Actualiza el carrito en caso de no tener stock para realizar la compra

void showCartMain(Map *mapCarts);                      //Muestra el carrito dentro del main

#endif
