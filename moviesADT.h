#ifndef moviesADT_H
#define moviesADT_H

typedef struct moviesCDT * moviesADT;

/*Estructura que contiene los datos de cada pelicula o serie */
typedef struct data{
	char * type;
	char * title;
	char * genre;
	unsigned int year;
	unsigned int rating;
	unsigned int votes;
}dataType;

/*Crea un nuevo TAD vacio*/
moviesADT new();

/*Agrega la pelicula o serie */
int addData(moviesADT m, dataType * data);

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
