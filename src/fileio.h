#ifndef _FILEIO_H_
#define _FILEIO_H_

#include <stdio.h>

#define MAX_LINE	1000
#define MAX_WORDS	500

int fgetLine(FILE *fp, char line[], int max);
int getWords(char *line, char *words[], int maxwords);
int loadMap(char *fileName);

#endif /* _FILEIO_H_ */
