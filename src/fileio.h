#ifndef _FILEIO_H_
#define _FILEIO_H_

#include <stdio.h>

int fgetLine(FILE *fp, char line[], int max);
int getWords(char *line, char *words[], int maxwords);

#endif /* _FILEIO_H_ */
