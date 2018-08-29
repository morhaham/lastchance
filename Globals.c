//
// Created by Mor Haham on 29.8.2018.
//

#include "Globals.h"

void initProgramGlobals() {
    labelsHT = createHashTable(20500);
    initOperationsHT();
    initInstructionsHT();
}

void initFileGlobals() {
    FIRST_SCAN_ERRORS_FOUND = 0;
    IC = 0;
    DC = 0;
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
    setValue(operationsHT, "stop",15, NULL);
}

/* This hash table is just for an approx 0(1) search time through instructions names */
void initInstructionsHT() {
    instructionsHT = createHashTable(4);
    setValue(instructionsHT, ".data", TRUE, NULL);
    setValue(instructionsHT, ".string", TRUE, NULL);
    setValue(instructionsHT, ".entry", TRUE, NULL);
    setValue(instructionsHT, ".extern", TRUE, NULL);
}