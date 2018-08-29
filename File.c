//
// Created by Mor Haham on 29.8.2018.
//

#include "File.h"
#include <stdlib.h>

FileStruct* openFile(char *fileName) {
    FILE *fp;
    FileStruct *file = malloc(sizeof(FileStruct));
    if ((fp = fopen(fileName, READ_MODE)) == NULL) {
        END_PROCESS_ERROR("Error opening file");
    }
    file->fileName = fileName;
    file->fp = fp;
    file->lineNum = 0;
    return file;
}

unsigned int readLine(FileStruct *file) {
    if (fgets(file->lineStr, LINE_SIZE, file->fp) == NULL) {
        return 0;
    }
    file->lineNum++;
    return 1;
}



#include "File.h"
