//
// Created by Mor Haham on 1.9.2018.
//

#include "SecondPhase.h"

void secondScan() {
    char *word, *symbolName;
    unsigned int charIndex, symbolFound;

    while (readLine(file)) {
        word = strtok(file->lineStr, WHITE_SPACE);
        charIndex = 0;
        /* Set symbolName to point to the first index of the first word in case a symbol will be found */
        symbolName = word;

        /* Scan the first word in the line char by char til a colon or null
         * char to check later if the first word is a symbol  */
        while (word[charIndex + 1] != '\0') {
            ++charIndex;
        } /* END OF FIRST WORD IN LINE SCAN */

        /* Check if the first word is a symbol */
        if (word[charIndex] == ':') {
            symbolFound = 1;
            if ((word = strtok(NULL, WHITE_SPACE)) == NULL) {
                /* If a second word not found in the current line, print an error and skip to the next line */
                ASSEMBLY_SYNTAX_ERROR("Operation or instruction %s not found at line %d", word, file->lineNum);
                continue;
            }
        } else {
            symbolFound = 0;
            symbolName = NULL;
        }
        /* Check if the first word is an .entry instruction */
        if (word[0] == '.') {
            /* If an instruction is found, handleInstruction will handle the rest of the line
            * by continuing to extract the tokens of the word using strtok */
            if (isInstruction(word)) {
                handleInstruction(word, symbolFound, symbolName);
            } else {
                ASSEMBLY_SYNTAX_ERROR("Instruction name %s is invalid at line %d", word, file->lineNum);
                FIRST_SCAN_ERRORS_FOUND = 1;
                continue;
            }
        }
    }
}

