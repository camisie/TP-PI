COMPILER=gcc
OUTPUT_FILE=imdb
FILES=main.c moviesADT.o
FLAGS=-pedantic -std=c99 -Wall -fsanitize=address

all: back
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES) $(FLAGS)

back:
	$(COMPILER) -c moviesADT.c

clean:
	rm -r $(OUTPUT_FILE) *.o