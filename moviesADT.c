#include"moviesADT.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <errno.h>
#define BLOCK 20
#define GDIV ","

//Estructura que contiene los datos de la pelicula o serie mas votada
typedef struct dataNode{
    char * type;
    char * title;
    double rating;
    unsigned int votes; 
}TData;

//Este es el nodo para la lista de generos
typedef struct genreNode{
    char * name;
    unsigned int sizeM;      //Cantidad de peliculas de ese genero
    struct genreNode * tail;
}TGenre;

//Estructura del nodo para la lista de años
typedef struct yearNode{
    TGenre * firstGenre;     
    unsigned int year;
    unsigned int totalM;      //Cantidad total de peliculas en ese año
    unsigned int totalS;      //Cantidad total de series en ese año
    TData * bestMovie;        //Puntero a la estructura con datos de la pelicula mas votada
    TData * bestSerie;        //Puntero a la estructura con datos de la serie mas votada
    struct yearNode * tail;
}TYear;

typedef struct moviesCDT{
    TYear * firstYear;
    TYear * currentYear;    //Para iterar por los años
    TGenre * currentGenre;  //Para iterar por los generos
}moviesCDT;

moviesADT newMoviesADT(){
    moviesADT newM = calloc(1, sizeof(moviesCDT));
    if(newM == NULL || errno == ENOMEM){
        perror("Not enough memory");
        return NULL;
    }    
    return newM;
}

static TYear * searchYear(TYear * first, unsigned int year){
    if(first == NULL || first->year < year)
        return NULL;
    if(first->year > year)
        return searchYear(first->tail, year);
    return first;
}

static TYear * addYearRec(TYear * first, unsigned int year){
    if(first == NULL || first->year < year){ 
        TYear * aux = calloc(1, sizeof(TYear));
        if(aux == NULL || errno == ENOMEM){
            perror("Not enough memory");
            return NULL;
        }
        aux->year = year;
        aux->bestMovie = calloc(1, sizeof(TData));
        if(aux->bestMovie == NULL || errno == ENOMEM){
            free(aux);        
            perror("Not enough memory");
            return NULL;
        }

        aux->bestSerie = calloc(1, sizeof(TData));
        if(aux->bestSerie == NULL || errno == ENOMEM){
            if(aux->bestMovie != NULL)
                free(aux->bestMovie);
            free(aux);
            perror("Not enough memory");
            return NULL;
        }

        aux->tail = first;
        return aux;
    }
    if(first->year > year)
        first->tail = addYearRec(first->tail, year);

    return first;
}

static void addYear(moviesADT m, unsigned int year){
    if(year == 0)
        return;
    m->firstYear = addYearRec(m->firstYear, year);
}

static TGenre * addGenre(TGenre * first, char * name){
    int c;
    if(first == NULL || (c = strcmp(first->name, name)) > 0){
        TGenre * aux = malloc(sizeof(TGenre));

        if(aux == NULL || errno == ENOMEM){
            perror("Not enough memory");
            return NULL;
        }    
        aux->name = malloc(strlen(name) + 1);
        if(aux->name == NULL || errno == ENOMEM){
            return NULL;
        }
        strcpy(aux->name, name);                
        aux->sizeM = 1;         //porque se que estan llamando a la funcion para agregar una pelicula
        aux->tail = first;
        return aux;
    }
    if(c < 0)
        first->tail = addGenre(first->tail, name);
    else
        first->sizeM += 1;

    return first;
}

//Devuelve un vector donde en cada posicion almacena un genero, y deja su dimension en un parametro de salida
char ** genreVec(char * s, unsigned int * dim){
    char * line;
    char ** vec = malloc(sizeof(char *) * BLOCK);
    if(vec == NULL || errno == ENOMEM){
        perror("Not enough memory");
        return NULL;
    }

    unsigned int i = 0;
    line = strtok(s, GDIV);

    while(line != NULL){
        if(i % BLOCK == 0){
            vec= realloc(vec, sizeof(char *) * (BLOCK + i));
        }
        if(vec == NULL || errno == ENOMEM){
            perror("Not enough memory");
            return NULL;
        }
        
        vec[i] = malloc(strlen(line) + 1);
        strcpy(vec[i], line);
        i++;

        line = strtok(NULL, GDIV);
    }
    
    vec = realloc(vec, sizeof(char *) * i);
    if(vec == NULL || errno == ENOMEM){
        perror("Not enough memory");
        return NULL;
    }
    *dim = i;
    return vec;
}

int addMovieSeries(moviesADT m, char * genre, unsigned int year, char * type, char * title, unsigned int votes, double rating){
    addYear(m, year); //Busco el año, si no estaba lo agrega la funcion add y devuelve el nodo. si estaba solo devuelve el nodo
    TYear * currentY = searchYear(m->firstYear, year);
    if(currentY == NULL)
        return 2;   //si en el parametro del año nos pasan "\N" (que nuestra funcion readData lo convierte en 0) 
                    //la funcion no agrega
    
    if(strcmp("tvSeries", type) == 0){ //Si es una serie lo que me pasan
        currentY->totalS++;
        if(currentY->bestSerie->votes < votes){ //Actualizo el mas popular
            currentY->bestSerie->type = type;
            currentY->bestSerie->title = malloc(strlen(title) + 1);

            if(currentY->bestSerie->title == NULL || errno == ENOMEM){
                return 2;
            }
            strcpy(currentY->bestSerie->title, title);              
            currentY->bestSerie->rating = rating;
            currentY->bestSerie->votes = votes;
        } //sino no hago nada
    }
    else if(strcmp("movie", type) == 0){ //Si me pasan una pelicula
        currentY->totalM++;
        if(currentY->bestMovie->votes < votes){ //Actualizo el mas popular
            currentY->bestMovie->type = type;
            currentY->bestMovie->title = malloc(strlen(title) + 1);

            if(currentY->bestMovie->title == NULL || errno == ENOMEM){
                return 2;
            }
            strcpy(currentY->bestMovie->title, title);             
            currentY->bestMovie->rating = rating;
            currentY->bestMovie->votes = votes;
        }
        unsigned int i = 0;
        unsigned int dim = 0;
        
        char ** vec = genreVec(genre, &dim);
        //Recorremos el vector que almacena los distintos generos para una pelicula y agregamos la misma en cada uno
        while(i < dim){
            currentY->firstGenre = addGenre(currentY->firstGenre, vec[i]); //Busca el genero y retorna el nodo si esta; sino lo agrega y lo retorna
            i++;
        }
        for(unsigned int k=0; k < dim; k++){
            free(vec[k]);
        }
        free(vec);
    }
    else
        return 0;   //retorna 0 si NO pudo agregar

    return 1;       //agrego correctamente
}

void toBeginYear(moviesADT m){
    m->currentYear = m->firstYear;
}

unsigned int hasNextYear(moviesADT m){
    return m->currentYear != NULL;
}

unsigned int nextYear(moviesADT m, unsigned int * movies, unsigned int * series){

    *movies = m->currentYear->totalM;
    *series = m->currentYear->totalS;

    unsigned int aux = m->currentYear->year;
    m->currentYear = m->currentYear->tail;
    return aux;
}

void toBeginGenre(moviesADT m, unsigned int year){
    TYear * aux = searchYear(m->firstYear, year);
    if(aux != NULL){
        m->currentGenre = aux->firstGenre;
    }
}

unsigned int hasNextGenre(moviesADT m){
    return m->currentGenre != NULL;
}

char * nextGenre(moviesADT m, unsigned int *movies){
    *movies = m->currentGenre->sizeM;   
    char * aux = m->currentGenre->name;      
    m->currentGenre = m->currentGenre->tail;
    return aux;
}

char * mostVotedMovie(moviesADT m, unsigned int year, unsigned int * movieVotes, double * movieRating){
    TYear * aux = searchYear(m->firstYear, year);   //busco el año que me pasan y lo guardo en TYear
    char * movieTitle = aux->bestMovie->title;
    *movieVotes = aux->bestMovie->votes;
    *movieRating = aux->bestMovie->rating;
    return movieTitle;    
}

char * mostVotedSerie(moviesADT m, unsigned int year, unsigned int * serieVotes, double * serieRating){
    TYear * aux = searchYear(m->firstYear, year);   //busco el año que me pasan y lo guardo en TYear
    char * serieTitle = aux->bestSerie->title;
    *serieVotes = aux->bestSerie->votes;
    *serieRating = aux->bestSerie->rating;
    return serieTitle;    
}

static void freeRecGen(TGenre * first){
    if(first == NULL)
        return;
    freeRecGen(first->tail);
    free(first->name);     
    free(first);
}

static void freeRecYears(TYear * first){
    if(first == NULL)
        return;
    freeRecYears(first->tail);
    freeRecGen(first->firstGenre);
    free(first->bestMovie->title);     
    free(first->bestMovie);
    free(first->bestSerie->title);      
    free(first->bestSerie);
    free(first);
}

void freeMoviesADT(moviesADT m){
    freeRecYears(m->firstYear);
    free(m);
}
