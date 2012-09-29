#include "fileio.h"
#include <stdio.h>
#include <stdlib.h>
#include "SDLgfx.h"
#include "game/map.h"

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

int loadMap(char *fileName)
{
	FILE *ifp;
	char line[MAX_LINE];
	char *words[MAX_WORDS];
	int n;
	int i;
	int j;
	int wordsSize;

	ifp = fopen(fileName, "r");
	if(ifp == NULL)
	{
		fprintf(stderr, "ERROR (loadMap): Cannot open map file: %s\n", fileName);
		return 1;
	}

	while(fgetLine(ifp, line, MAX_LINE) != EOF)
	{
		n = getWords(line, words, MAX_WORDS);

		if(!strcmp(words[0], "TITLE:"))
		{
			wordsSize = 0;

			for(i = 1; i < n; i++)
			{
				wordsSize += strlen(words[i]) + 1;
			}

			CurMap.title = malloc(wordsSize);

			strcpy(CurMap.title, "");
			for(i = 1; i < n; i++)
			{
				strcat(CurMap.title, words[i]);
				if(i < n - 1)
				{
					strcat(CurMap.title, " ");
				}
			}
		}
		if(!strcmp(words[0], "BITMAP:"))
		{
			char *bitmapFileName = NULL;

			if(n < 1)
			{
				fprintf(stderr, "ERROR (loadMap): No bitmap filename specified!\n");
				fclose(ifp);
				return 1;
			}

			wordsSize = strlen("./data/gfx/") + strlen(words[1]) + 1;

			bitmapFileName = malloc(wordsSize);
			if(bitmapFileName == NULL)
			{
				fprintf(stderr, "ERROR (loadMap): Insufficient memory!\n");
				fclose(ifp);
				return 1;
			}

			strcpy(bitmapFileName, "./data/gfx/");
			strcat(bitmapFileName, words[1]);

			CurMap.bitmap = loadImage(bitmapFileName);

			if(CurMap.bitmap == NULL)
			{
				fprintf(stderr, "ERROR (loadBitmap): Failed to load bitmap file: %s\n", bitmapFileName);
				fclose(ifp);
				return 1;
			}
			free(bitmapFileName);

			clipImage(CurMap.clip, TILE_SIZE, TILE_SIZE, 16, 256);

		}
		if(!strcmp(words[0], "MAP:"))
		{
			CurMap.w = atoi(words[1]);
			CurMap.h = atoi(words[2]);

			CurMap.array = malloc(CurMap.w * sizeof(int));
			if(CurMap.array == NULL)
			{
				fprintf(stderr, "ERROR (loadMap): Insufficient memory!\n");
				fclose(ifp);
				return 1;
			}
			for(i = 0; i < CurMap.w; i++)
			{
				CurMap.array[i] = malloc(CurMap.h * sizeof(int));
				if(CurMap.array[i] == NULL)
				{
					fprintf(stderr, "ERROR (loadMap): Insufficient memory!\n");
					fclose(ifp);
					return 1;
				}
			}
			for(j = 0; j < CurMap.h; j++)
			{
				fgetLine(ifp, line, MAX_LINE);
				getWords(line, words, MAX_WORDS);

				for(i = 0; i < CurMap.w; i++)
				{
					CurMap.array[i][j] = atoi(words[i]);
				}
			}
		}
	}

	fclose(ifp);

	return 0;
}
