//
// Created by Mor Haham on 29.8.2018.
//

#ifndef LASTCHANCE_FILE_H
#define LASTCHANCE_FILE_H
#define  LINE_SIZE 80
#include <stdio.h>
#include "Globals.h"




typedef struct FileStruct {
    char *fileName;
    FILE *fp;
    char lineStr[LINE_SIZE];
    int lineNum;
} FileStruct;

FileStruct *file;
/* Funcs decs */
FileStruct* openFile(char *fileName);
unsigned int readLine(FileStruct *file);

#endif //LASTCHANCE_FILE_H