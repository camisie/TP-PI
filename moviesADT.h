#ifndef moviesADT_H
#define moviesADT_H

typedef struct moviesCDT * moviesADT;

/*Crea un nuevo TAD vacio*/
moviesADT new();

/*Agrega un nuevo año en forma descendente (insertando los mayores al principio). Si lo agrego retorna 1, si ya estaba o no pudo agregarlo retorna 0 */
int addYear(moviesADT m, int year);

/*Agrega un nuevo genero en orden alfabetico, segun el año indicado en el parametro year. Si lo agrego retorna 1, si ya estaba o no pudo agregarlo retorna 0 */
int addGenre(moviesADT m, int year, const char * genre);

/*Agrega la pelicula film a el o los generos especificados por el parametro genre en el año indicado por year */
int addMovie(moviesADT m, int year, const char * genre, const char * film);

/*Agrega la serie 'serie' a el o los generos especificados por el parametro genre en el año indicado por year */
int addSerie(moviesADT m, int year, const char * genre, const char * serie);

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
