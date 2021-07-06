#ifndef moviesADT_H
#define moviesADT_H

typedef struct moviesCDT * moviesADT;


/*Crea un nuevo TAD vacio*/
moviesADT newMoviesADT();

/*Agrega la pelicula o serie */
void addMovieSeries(moviesADT m, char * genre, unsigned int year, char * data, char * title, unsigned int votes, double rating);

/*Retorna un vector(? con los años (ordenados en forma descendiente) y la cantidad de peliculas y series (por separado) de cada uno, dejando en dim 
la dimension final del vector*/
TYear * solQ1(moviesADT m, int * dim);

/*Retorna un vector(? con los años (ordenados en forma descendiente), sus generos (ordenados alfabeticamente) y la cantidad de peliculas de cada uno, 
dejando en dim la dimension final del vector*/
TGenre * solQ2(moviesADT m, int * dim);

/*Retorna un vector(? con los años (ordenados en forma descendiente), la pelicula mas votada en cada uno, la cantidad de votos y el raiting de cada una, 
y lo mismo para la seria mas votada. Deja en dim la dimension final del vector*/
TQ3 * solQ3();

/*Libera todos los recursos reservados por el TAD*/
void freeMoviesADT(moviesADT m);

#endif
