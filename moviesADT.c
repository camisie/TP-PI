#include"moviesADT.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct mostVotedNode{
  char titleType;
  char *primaryTitle;
  unsigned int startYear;
  unsigned int endYear;
  char *genres;
  unsigned int averageRating;
  unsigned int numVotes;
  unsigned int runtimeMinutes;
}mostVotedNode;
