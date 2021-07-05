#include"moviesADT.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Este es el nodo para la lista de generos
typedef struct genreNode{
    char * name;
    size_t sizeM; //cantidad de peliculas de ese genero
    struct genreNode *tail;
}TGenre;

//estructura del nodo para la lista de años
typedef struct yearNode{
    TGenre * firstGenre;     
    unsigned int year;
    size_t totalM;      //cantidad total de peliculas en ese año
    size_t totalS;      //cantidad total de series en ese año
    dataType * bestMovie;
    size_t votesM;
    dataType * bestSerie;
    size_t votesS;
    struct yearNode *tail;
}TYear;

typedef struct moviesCDT{
    TYear * firstYear;
}moviesCDT;



static TYear * addYear(TYear * first, unsigned int year){
    if(first == NULL || first->year < year){ //o usar compare?
        TYear * aux = calloc(1, sizeof(TYear));
        aux->year = year;
        aux->tail = first;
        return aux;
    }
    if(first->year > year)
        first->tail = addYear(first->tail, year);

    return first;
}

static TGenre * addGenre(TGenre * first, char * name){
    int c;
    if(first == NULL || (c = strcmp(first->name, name)) > 0){
        TGenre * aux = malloc(sizeof(TGenre));
        aux->name = name;
        aux->sizeF = 0;
        aux->tail = first;
        return aux;
    }
    if(c < 0)
        first->tail = addGenre(first->tail, name);

    return first;
}

void addData(moviesADT m, char * genre, unsigned int year, char * data, char * title, unsigned int votes, double rating){
    TYear * currentY = addYear(m->firstYear, year); //busco el año, si no estaba lo agrega la funcion add y devuelve el nodo. si estaba solo devuelve el nodo
    if(strcmp("TvSeries", data) == 0){ //si es una serie lo que me pasan
        currentY->totalS ++;
        if(currentY->votesS < votes){ //actualizo el mas popular
            m->bestSerie.type = data;
            m->bestSerie.title = title;
            m->bestSerie->genre = genre;
            m->bestSerie->rating = rating;
            m->bestSerie->votes = votes;
        } //sino no hago nada
    }
    if(strcmp("movie", data) == 0){ //si me pasan una pelicula
        currentY->totalM++;
        if(currentY->votesM < votes){ //actualizo el mas popular
            m->bestMovie.type = data;
            m->bestMovie.title = title;
            m->bestMovie->genre = genre;
            m->bestMovie->rating = rating;
            m->bbestMovie->votes = votes;
        }
        
        TGenre * currentG = addGenre(currentY->firstGenre, genre); //busca el genero y retorna el nodo si esta; sino lo agrega y lo retorna
        currentG->sizeM++;
    }
    return;
}




