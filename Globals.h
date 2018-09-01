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
printf(msg, word, lineNum); \
printf("\n"); \
FIRST_SCAN_ERRORS_FOUND = 1;


#define TRUE 1
#define FALSE 0
#define NULL_CHAR '\0'
#define COMMA ","
#define QUOTATIONS "\""
#define OPEN_BRACKET '('
#define CLOSE_BRACKET_STR ")"
#define CLOSE_BRACKET_CHAR ')'
#define DANI_CALFON "),"
#define BRACKETS "()"
#define READ_MODE "r"
#define WHITE_SPACE " \t\v\f\r"

unsigned int FIRST_SCAN_ERRORS_FOUND;
unsigned int IC;
unsigned int DC;

HashTable *symbolsHT;
HashTable *instructionsHT;
HashTable *operationsHT;
HashTable *registersHT;

typedef struct Data {
    int data;
    struct Data *next;
} Data;

Data *dataHead;

enum operations {MOV, CMP, ADD, SUB, NOT, CLR, LEA, INC, DEC, JMP, BNE, RED, PRN, JSR, RTS, STOP};
enum addressingMethods{IMMEDIATE,DIRECT,JMP_WITH_PARAMS,REGISTER};
/* Funcs decs */
void initProgramGlobals();
void initFileGlobals();
void initOperationsHT();
void initInstructionsHT();
void initRegistersHT();
void addNode(Data **head, int new_data);
void removeChar(char *str, char garbage);


#endif //LASTCHANCE_GLOBALS_H
