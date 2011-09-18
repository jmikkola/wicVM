#ifndef MAP_H
#define MAP_H

#define MAP_STR_SIZE 32
#define MAP_ARR_SIZE 20
#define MAX_LOAD_FACTOR 0.7f

typedef struct MapItem {
    char string[MAP_STR_SIZE];
    int value;
    int hash;
    struct MapItem *next;
} MapItem;

typedef struct {
    int arrSize;
    int size;
    MapItem **array;
} StringMap;

StringMap* mapCreate (void);
void mapFree (StringMap *map);
int mapSet (StringMap *map, char *string, int value);
int mapGet (StringMap *map, char *string);
int mapIn (StringMap *map, char *string);
int mapSize (StringMap *map);

#endif
