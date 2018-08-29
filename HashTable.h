//
// Created by Mor Haham on 29.8.2018.
//

#ifndef LASTCHANCE_HASHTABLE_H
#define LASTCHANCE_HASHTABLE_H

#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux.  See feature_test_macros(7) */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define TYPE_SIZE 20

typedef struct Entry {
    char *key;
    unsigned char value;
    char entryType[TYPE_SIZE];
    struct entry *next;
} Entry;

typedef struct HashTable {
    int size;
    Entry** table;
} HashTable;


HashTable *createHashTable( int size );
/*map the key to the value*/
void setValue (HashTable* labelHashTable, char* key, unsigned char value,  char* entryType);
int hash(HashTable *hashTable, char *key);
Entry *createNewPair( char *key, unsigned char value, char* entryType );
unsigned char getValue( HashTable *hashTable, char *key );
char* getType( HashTable *hashTable, char *key );
void deleteHashTable(HashTable **hashTable);



#endif //LASTCHANCE_HASHTABLE_H
