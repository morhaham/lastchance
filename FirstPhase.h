//
// Created by Mor Haham on 29.8.2018.
//

#ifndef LASTCHANCE_FIRSTPHASE_H
#define LASTCHANCE_FIRSTPHASE_H

#include "File.h"

void firstScan();
unsigned int isInstruction(char *word);
void handleInstruction(char *inst, unsigned int symbolFound, char *symbolName);
void handleExternInst(char *inst);
void handleDataInst(char *inst, unsigned int symbolFound, char *symbolName);
void handleStringInst(char *inst, unsigned int symbolFound, char *symbolName);
void handleOperation(char *op, unsigned int symbolFound, char *symbolName);
void addDataParamToDataList(int newDataNum);
int isSyntaxValidSymbol(char *symbol);
int isOperation(char *word);
int isCommasValid(char *paramsSection);
int isQuotationsValid(char *paramsSection);
unsigned short isJmpWithParamsAddrMethod(char *paramsSection);
unsigned short getParamAddrMethod(char *paramsSection);

#endif //LASTCHANCE_FIRSTPHASE_H
