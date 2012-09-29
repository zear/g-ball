#ifndef _MAP_H_
#define _MAP_H_

typedef struct MapStruct
{
	char *title;
	int w;
	int h;
	int **array;
} Map;

extern Map CurMap;

#endif /* _MAP_H_ */
