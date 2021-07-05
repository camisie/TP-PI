#include"moviesADT.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Este es el nodo para la lista de generos
typedef struct genreNode{
    char *name;
    size_t sizeF; //cantidad de peliculas de ese genero
    struct genreNode *tail;
}TGenre;

//estructura del nodo para la lista de años
typedef struct yearNode{
    TGenre *first;
    size_t totalF; //cantidad total de peliculas en ese año
    size_t totalS; //cantidad total de series en ese año
    TData *bestMovie;
    TData *bestSerie;
    struct yearNode *tail;
}TYear;

typedef struct moviesCDT{
    TYear *first;
}moviesCDT;
