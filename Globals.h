//
// Created by Mor Haham on 29.8.2018.
//

#ifndef LASTCHANCE_GLOBALS_H
#define LASTCHANCE_GLOBALS_H


#include "HashTable.h"

#define END_PROCESS_ERROR(msg) \
perror(#msg ); \
exit(-1);

#define ASSEMBLY_SYNTAX_ERROR(msg, word, lineNum) \
printf(#msg, word, lineNum); \


#define TRUE 1
#define FALSE 0
#define COMMA ","
#define READ_MODE "r"
#define WHITE_SPACE " \t\v\f\r"

unsigned int FIRST_SCAN_ERRORS_FOUND;
unsigned int IC;
unsigned int DC;

HashTable *symbolsHT;
HashTable *instructionsHT;
HashTable *operationsHT;
HashTable *registersHT;



/* Funcs decs */
void initProgramGlobals();
void initFileGlobals();
void initOperationsHT();
void initInstructionsHT();


#endif //LASTCHANCE_GLOBALS_H
