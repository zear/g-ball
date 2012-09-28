#include "fileio.h"
#include <stdio.h>

// Reads one line from fp
int fgetLine(FILE *fp, char line[], int max)
{
	int nch = 0;
	int c;
	max = max - 1;		/* leave room for '\0' */

	int ignoreLine = 0;

	while((c = getc(fp)) != EOF)
	{
		if(c == '\n')
		{
			ignoreLine = 0;
			break;
		}

		/* We're treating anything after '#' as comments and ignoring the rest of the line */
		if(c == '#')
		{
			ignoreLine = 1;
		}

		if(nch < max)
		{
			if(!ignoreLine)
			{
				line[nch] = c;
				nch = nch + 1;
			}
		}
	}

	if(c == EOF && nch == 0)
	{
		return EOF;
	}

	line[nch] = '\0';
	return nch;
}

//breaks a line into words
int getWords(char *line, char *words[], int maxwords)
{
	char *p = line;
	int nwords = 0;

	while(1)
	{
		while(isspace(*p))
		{
			p++;
		}

		if(*p == '\0')
		{
			return nwords;
		}

		words[nwords++] = p;

		while(!isspace(*p) && *p != '\0')
		{
			p++;
		}

		if(*p == '\0')
		{
			return nwords;
		}

		*p++ = '\0';

		if(nwords >= maxwords)
		{
			return nwords;
		}
	}
}
