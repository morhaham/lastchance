//
// Created by Mor Haham on 29.8.2018.
//

#ifndef LASTCHANCE_GLOBALS_H
#define LASTCHANCE_GLOBALS_H

#define END_PROCESS_ERROR(msg) \
perror(#msg ); \
exit(-1);

#define ASSEMBLY_SYNTAX_ERROR(msg, word, lineNum) \
printf(#msg, word, lineNum); \



#define READ_MODE "r"
#define WHITE_SPACE " \t\v\f\r"

unsigned int FIRST_SCAN_ERRORS_FOUND;
unsigned int IC;
unsigned int DC;

/* Funcs decs */
void initGlobals();


#endif //LASTCHANCE_GLOBALS_H
