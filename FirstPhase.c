//
// Created by Mor Haham on 29.8.2018.
//
#include <string.h>
#include "FirstPhase.h"
#include "File.h"
#include "Globals.h"

void firstScan(FileStruct *file) {
    char *word, *symbolName;
    unsigned int charIndex, symbolFound;

    while (readLine(file)) {
        word = strtok(file->lineStr, WHITE_SPACE);
        charIndex = 0;
        /* Set symbolName to point to the first index of the first word in case a symbol will be found */
        symbolName = word;
        /* Scan the first word in the line char by char */
        while (word[charIndex] != '\0') {
            /* If the next char is the end of the first word, check for symbol's colon  */
            if (word[charIndex + 1] == '\0') {
                if (word[charIndex] == ':') {
                    symbolFound = 1;
                    /* In case a symbol was not found, set symbolName to NULL */
                } else {
                    symbolFound = 0;
                    symbolName = NULL;
                }
            }
            ++charIndex;
        } /* END OF FIRST WORD IN LINE SCAN */

        /* Scan the second word in the current line */
        if ((word = strtok(NULL, WHITE_SPACE)) == NULL) {
            ASSEMBLY_SYNTAX_ERROR("Operation or instruction %s not found at line %d", word, file->lineNum);
            FIRST_SCAN_ERRORS_FOUND = 1;
            /* If a second word not found in the current line, skip to the next line */
            continue;
        }

        /* If the first char in the second word is a dot, check for an instruction. */
        if (word[0] == '.') {
            /* If an instruction is found, handleInstruction will handle the rest of the line
            * by continuing to extract the tokens of the word using strtok */
            if (isInstruction(word)) {
                handleInstruction(word, symbolFound, symbolName);
            } else {
                ASSEMBLY_SYNTAX_ERROR("Instruction name %s is invalid at line %d", word, file->lineNum);
                FIRST_SCAN_ERRORS_FOUND = 1;
            }
            /* If an operation is found, handleOperation will handle the rest of the line
            * by continuing to extract the tokens of the word using strtok */
        } else if (isOperation(word)) {
            handleOperation(word, symbolFound, symbolName);
        } else {
            ASSEMBLY_SYNTAX_ERROR("Operation name %s is invalid at line %d", word, file->lineNum);
            FIRST_SCAN_ERRORS_FOUND = 1;
        }

    } /* END OF READING LINES LOOP */

} /* END OF firstScan FUNCTION */

unsigned int isInstruction(char *word) {
    /* An approx of 0(1) search time */
    if (getValue(instructionsHT, word)) {
        return TRUE;
    }
    return FALSE;
}

/* This function already knows that we have a valid instruction name in the second word of the line
 * and it just scans the parameters(if exist) with strtok and handle the whole instruction line */
void handleInstruction(char *inst, unsigned int symbolFound, char *symbolName) {





    /* After we know that the instruction line is valid, we can add the symbol if exists */
    if (symbolFound) {
        addSymbol(symbolName);
    }
}
