//
// Created by Mor Haham on 29.8.2018.
//

#ifndef LASTCHANCE_FIRSTPHASE_H
#define LASTCHANCE_FIRSTPHASE_H

#include "File.h"

void firstScan(FileStruct *file);
unsigned int isInstruction(char *word);
void handleInstruction(char *inst, unsigned int symbolFound, char *symbolName);
int isOperation(char *word);
void handleOperation(char *op, unsigned int symbolFound, char *symbolName);

#endif //LASTCHANCE_FIRSTPHASE_H
