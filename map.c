
#include <stdlib.h>
#include <string.h>

#include "map.h"

void expand (StringMap *map);
int hash (char *string);
void mapItemFree (MapItem *item);
MapItem* makeMapItem (char *string, int value, int hash, MapItem *next);
MapItem* findMapItem (StringMap *map, char *string);

// Create a new map
StringMap* mapCreate () {
    StringMap *map = (StringMap*) malloc(sizeof(StringMap));
    map->arrSize = MAP_ARR_SIZE;
    map->size = 0;
    map->array = (MapItem**) calloc(sizeof(MapItem), MAP_ARR_SIZE);
    return map;
}

// Free the memory used by a map
void mapFree (StringMap *map) {
    int i;
    for (i = 0; i < map->arrSize; i++)
        mapItemFree(map->array[i]);
    free(map->array);
    free(map);
}

// Free the memory used by a string of MapItems
void mapItemFree (MapItem *item) {
    if (item) {
        mapItemFree(item->next);
        free(item);
    }
}

// Sets the value for a string in the map
// Returns 1 if this was an update, 0 if 
// the string is new.
int mapSet (StringMap *map, char *string, int value) {
    int shash, index;
    MapItem *item = findMapItem(map, string);
    // Replace old value, if exists
    if (item) {
        item->value = value;
        return 1;
    } 
    // Check if array needs to be expanded
    if ((float) map->size / map->arrSize > MAX_LOAD_FACTOR) {
        expand(map);
    }
    // Add the item
    shash = hash(string);
    index = shash % map->arrSize;
    map->array[index] = makeMapItem(
        string, value, shash, map->array[index]);
    return 1; 
} 

// Gets an int value from the map
// (Returns 0 if the string does not exist in the map)
int mapGet (StringMap *map, char *string) {
    MapItem *item = findMapItem(map, string);
    if (item)
        return item->value;
    return 0;
}

// Checks if a string is in the array
int mapInt (StringMap *map, char *string) {
    return findMapItem(map, string) != NULL;
}

// Returns the size of the map
int mapSize (StringMap *map) {
    return map->size;
}



// Compute a hash value for the string
int hash (char *s) {
    int out = 0;
    while (*s)
        out = 31*out + *(s++);
    return out;
}

// Expand the array underlying the map
void expand (StringMap *map) {
    // TODO: expand array, rehash
}

// allocate and create a MapItem struct
MapItem* makeMapItem (char *string, int value, int hash, MapItem *next) {
    MapItem *mapitem = malloc(sizeof(MapItem));
    strncpy(mapitem->string, string, MAP_STR_SIZE);
    mapitem->value = value;
    mapitem->hash = hash;
    mapitem->next = next;
    return mapitem;
}

// Finds a map item by string
MapItem* findMapItem (StringMap *map, char *string) {
    int shash = hash(string);
    int index = shash % map->arrSize;
    MapItem *item = map->array[index];
    while (item) {
        if (item->hash == shash && strcmp(item->string, string) == 0)
            return item;
        item = item->next;
    }
    return NULL;
}
