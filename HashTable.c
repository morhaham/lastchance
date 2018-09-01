//
// Created by Mor Haham on 29.8.2018.
//



#include "HashTable.h"
#include "string.h"


/* Create a new hashtable. */
HashTable *createHashTable( int size ) {

    HashTable *hashtable = NULL;
    int i;

    if( size < 1 ) return NULL;

    /* Allocate the table itself. */
    if( ( hashtable = malloc( sizeof( HashTable ) ) ) == NULL ) {
        return NULL;
    }

    /* Allocate pointers to the head nodes. */
    if( ( hashtable->table = malloc( sizeof( Entry * ) * size ) ) == NULL ) {
        return NULL;
    }
    for( i = 0; i < size; i++ ) {
        hashtable->table[i] = NULL;
    }

    hashtable->size = size;

    return hashtable;
}

/* Hash a string for a particular hash table. */
int hash(HashTable *hashtable, char *key) {

    unsigned long int hashval = 0;
    int i = 0;

    /* Convert our string to an integer */
    while( hashval < ULONG_MAX && i < strlen( key ) ) {
        hashval = hashval << 8;
        hashval += key[ i ];
        i++;
    }

    return hashval % hashtable->size;
}

/* Create a key-value pair. */
Entry *createNewPair(char *key, unsigned char value, char* entryType ) {
    Entry *newpair;

    if( ( newpair = malloc( sizeof( Entry ) ) ) == NULL ) {
        return NULL;
    }

    if( ( newpair->key = strdup( key ) ) == NULL ) {
        return NULL;
    }

    newpair->value =value;

    if (entryType != NULL) {
        strcpy(newpair->entryType, entryType);
    }

    newpair->next = NULL;

    return newpair;
}

/* Insert a key-value pair into a hash table. */
void setValue( HashTable *hashtable, char *key, unsigned int value,  char* entryType ) {
    int bin = 0;
    Entry *newpair = NULL;
    Entry *next = NULL;
    Entry *last = NULL;

    bin = hash(hashtable, key);

    next = hashtable->table[ bin ];

    while( next != NULL && next->key != NULL && strcmp( key, next->key ) > 0 ) {
        last = next;
        next = next->next;
    }

    /* If there's already a pair,  Let's replace that string. */
    if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 ) {

        next->value = value;
        strcpy(next->entryType, entryType);
        /* Nope, could't find it.  Time to grow a pair. */
    } else {
        newpair = createNewPair( key, value, entryType);

        /* We're at the start of the linked list in this bin. */
        if( next == hashtable->table[ bin ] ) {
            newpair->next = next;
            hashtable->table[ bin ] = newpair;

            /* We're at the end of the linked list in this bin. */
        } else if ( next == NULL ) {
            last->next = newpair;

            /* We're in the middle of the list. */
        } else  {
            newpair->next = next;
            last->next = newpair;
        }
    }
}

/* Retrieve a key-value pair from a hash table. */
unsigned char getValue(HashTable *hashtable, char *key ) {
    int bin = 0;
    Entry *pair;

    bin = hash(hashtable, key);

    /* Step through the bin, looking for our value. */
    pair = hashtable->table[ bin ];
    while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 ) {
        pair = pair->next;
    }

    /* Did we actually find anything? */
    if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ) {
        return '\0';

    } else {
        return pair->value;
    }

}

char* getType(HashTable *hashtable, char *key ) {
    int bin = 0;
    Entry *pair;

    bin = hash(hashtable, key);

    /* Step through the bin, looking for our value. */
    pair = hashtable->table[ bin ];
    while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 ) {
        pair = pair->next;
    }

    /* Did we actually find anything? */
    if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ) {
        return NULL;

    } else {
        return pair->entryType;
    }
}

void deleteHashTable(HashTable **hashTable) {
    int i;
    for (i = 0; i < (*hashTable)->size; i++) {
        while ((*hashTable)->table[i] != NULL){
            free((*hashTable)->table[i]->key);
            free((*hashTable)->table[i]);
            (*hashTable)->table[i] = (*hashTable)->table[i]->next;
        }
    }
    free(*hashTable);
}