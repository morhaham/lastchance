//
// Created by Mor Haham on 29.8.2018.
//

#include "Globals.h"

void initProgramGlobals() {
    symbolsHT = createHashTable(20500);
    initOperationsHT();
    initInstructionsHT();
    initRegistersHT();
}

void initFileGlobals() {
    FIRST_SCAN_ERRORS_FOUND = 0;
    IC = 0;
    DC = 0;
    dataHead = NULL;
}

/* The value of each operation is the decimal value -
 * later in the second phase converts to binary */
void initOperationsHT() {
    operationsHT = createHashTable(17);
    setValue(operationsHT, "mov", 0, NULL);
    setValue(operationsHT, "cmp", 1, NULL);
    setValue(operationsHT, "add", 2, NULL);
    setValue(operationsHT, "sub", 3, NULL);
    setValue(operationsHT, "not", 4, NULL);
    setValue(operationsHT, "clr", 5, NULL);
    setValue(operationsHT, "lea", 6, NULL);
    setValue(operationsHT, "inc", 7, NULL);
    setValue(operationsHT, "dec", 8, NULL);
    setValue(operationsHT, "jmp", 9, NULL);
    setValue(operationsHT, "bne", 10, NULL);
    setValue(operationsHT, "red", 11, NULL);
    setValue(operationsHT, "prn", 12, NULL);
    setValue(operationsHT, "jsr", 13, NULL);
    setValue(operationsHT, "rts", 14, NULL);
    setValue(operationsHT, "stop", 15, NULL);
}

/* This hash table is just for an approx 0(1) search time through instructions names
 * (for example with isInstruction func) */
void initInstructionsHT() {
    instructionsHT = createHashTable(4);
    setValue(instructionsHT, ".data", TRUE, NULL);
    setValue(instructionsHT, ".string", TRUE, NULL);
    setValue(instructionsHT, ".entry", TRUE, NULL);
    setValue(instructionsHT, ".extern", TRUE, NULL);
}

void initRegistersHT() {
    registersHT = createHashTable(11);
    setValue(registersHT, "r0", 0, NULL);
    setValue(registersHT, "r1", 1, NULL);
    setValue(registersHT, "r2", 2, NULL);
    setValue(registersHT, "r3", 3, NULL);
    setValue(registersHT, "r4", 4, NULL);
    setValue(registersHT, "r5", 5, NULL);
    setValue(registersHT, "r6", 6, NULL);
    setValue(registersHT, "r7", 7, NULL);
}

void addNode(Data **head, int new_data) {
    /* The new node is added to the head of the list - not to the tail-
     * so the addition of the new node is more efficient(O(1)) */
    /* allocate node */
    Data *new_node = (Data *) malloc(sizeof(Data));
    /* insert the data  */
    new_node->data = new_data;
    /* make the next new node as head */
    new_node->next = (*head);
    /* move the head to point to the new node */
    (*head) = new_node;
}

void removeChar(char *str, char garbage) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}