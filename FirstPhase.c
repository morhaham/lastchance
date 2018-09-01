//
// Created by Mor Haham on 29.8.2018.
//
#include <string.h>
#include <ctype.h>
#include "FirstPhase.h"
#include "File.h"
#include "Globals.h"

void firstScan() {
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
            word[charIndex] = '\0';
            /* Skip to the second word in the current line */
            if ((word = strtok(NULL, WHITE_SPACE)) == NULL) {
                /* If a second word not found in the current line, print an error and skip to the next line */
                ASSEMBLY_SYNTAX_ERROR("Operation or instruction %s not found at line %d", word, file->lineNum);
                continue;
            }

        } else {
            symbolFound = 0;
            symbolName = NULL;
        }
        /* word points now to the first or the second word in the current line depends on
         * if we found a symbol previously. */

        /* If the first char is a dot, check for an instruction. */
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
            /* If an operation is found, handleOperation will handle the rest of the line
            * by continuing to extract the tokens of the word using strtok */
        } else if (isOperation(word)) {
            handleOperation(word, symbolFound, symbolName);
        } else {
            ASSEMBLY_SYNTAX_ERROR("Operation name %s is invalid at line %d", word, file->lineNum);
            continue;
        } /* END OF - IF '.' FOUND IN THE FIRST CHAR AT THE CURRENT WORD */

    } /* END OF READING LINES LOOP */
    /*TODO: Step 14 in the first scan is not represented in this function.
     * maybe L is file->LineNum? */
} /* END OF firstScan FUNCTION */

unsigned int isInstruction(char *word) {
    /* An approx of 0(1) search time */
    if (getValue(instructionsHT, word)) {
        return TRUE;
    }
    return FALSE;
}

/* This function already knows that we have a valid instruction name
 * and it just enters the relevant func that will handle instruction params */
void handleInstruction(char *inst, unsigned int symbolFound, char *symbolName) {
    if (strcmp(inst, ".extern") == 0) {
        handleExternInst(inst);
    } else if (strcmp(inst, ".data") == 0) {
        handleDataInst(inst, symbolFound, symbolName);
    } else if (strcmp(inst, ".string") == 0) {
        handleStringInst(inst, symbolFound, symbolName);
    }
}

int isOperation(char *word) {
    /* An approx of 0(1) search time */
    if (getValue(operationsHT, word)) {
        return TRUE;
    }
    return FALSE;
}

/*TODO: decide if we do strcmp and op. check for each op. or check the parameters of common ops (like mov, add and sub - check page 27 at the notebook) */

void handleOperation(char *op, unsigned int symbolFound, char *symbolName) {
    char *paramsSection = op, *param;
    paramsSection = strtok(NULL, WHITE_SPACE);

    /**/
    if (getValue(operationsHT, op) == STOP || getValue(operationsHT, op) == RTS) {
        if (!paramsSection) {
            ASSEMBLY_SYNTAX_ERROR("Invalid parameter for operation %s at line %d", op, file->lineNum);
            return;
        }
    }
    if (getValue(operationsHT, op) == JMP || getValue(operationsHT, op) == BNE || getValue(operationsHT, op) == JSR) {
        if (paramsSection) {
            if (isJmpWithParamsAddrMethod(paramsSection)) {
                /* TODO: skip spaces between the label and the brackets*/
                /*TODO: handle the params split with a dedicated function (like Costa's ProcessCommandParam)*/
                /*TODO: handle the lable check with a dedicated function*/
                if (symbolFound) {
                    setValue(symbolsHT, symbolName, IC, "code");
                }
            }

        } else {
            ASSEMBLY_SYNTAX_ERROR("Operation %s at line %d should receive parameters", op, file->lineNum);
        }
    }


    if (symbolFound) {
        /*addSymbol(symbolName);*/
    }
}


void handleExternInst(char *inst) {
    char *param, *paramsSection;
    /* Get to the params section in the line */
    paramsSection = strtok(NULL, WHITE_SPACE);
    /* split the line's params section by commas */
    param = strtok(paramsSection, COMMA);
    do {
        if (getValue(symbolsHT, param)) {
            continue;
        }
        if (isSyntaxValidSymbol(param)) {
            setValue(symbolsHT, param, 0, "entry");
        } else {
            ASSEMBLY_SYNTAX_ERROR("Invalid symbol name %s at line %d", param, file->lineNum)
        }
    } while ((param = strtok(NULL, COMMA)) != NULL);
}

int isSyntaxValidSymbol(char *symbol) {
    int i = 1;
    if (!isalpha(symbol[0])) {
        return FALSE;
    }
    while (symbol[i] != '\0') {
        if (!isalpha(symbol[i]) && !isdigit(symbol[i])) {
            return FALSE;
        }
        ++i;
    }
    return TRUE;
}

void handleDataInst(char *inst, unsigned int symbolFound, char *symbolName) {
    /* param should point to a specific parameter, and paramsSection points to whole part
     * after the instruction word */
    char *param, *paramsSection = inst;
    int num;
    if (symbolFound) {
        if (getType(symbolsHT, symbolName) == NULL) {
            setValue(symbolsHT, symbolName, DC, "data");
        }
    }
    /* Get to the params section in the line */
    paramsSection = strtok(NULL, WHITE_SPACE);
    if (isCommasValid(paramsSection)) {
        /* split the line's params section by commas */
        /* TODO: Deal with the commas issue (if comma is before\after the paramsSection)
         * therefore, isCommasValid should deal with that. */
        param = strtok(paramsSection, COMMA);
        do {
            if (getValue(symbolsHT, param)) {
                continue;
            }
            if ((num = strtol(param, NULL, 10))) {
                /* TODO: add data to data linked list */
                addDataParamToDataList(num);
                ++DC;
            } else {
                ASSEMBLY_SYNTAX_ERROR("Invalid .data parameter %s at line %d", param, file->lineNum)
            }
        } while ((param = strtok(NULL, COMMA)) != NULL);
    } else {
        ASSEMBLY_SYNTAX_ERROR("Invalid comma in %s at line %d", paramsSection, file->lineNum);
    }
}

void addDataParamToDataList(int newDataNum) {
    if (isdigit(newDataNum) == 0) {
        addNode(&dataHead, newDataNum);
    }
}

void handleStringInst(char *inst, unsigned int symbolFound, char *symbolName) {
    char *param, *paramsSection = inst;
    if (symbolFound) {
        if (getType(symbolsHT, symbolName) == NULL) {
            setValue(symbolsHT, symbolName, DC, "string");
        }
    }

    /* Get to the params section in the line */
    paramsSection = strtok(NULL, WHITE_SPACE);
    if (isQuotationsValid(paramsSection)) {
        /* split the line's params section by quotation marks */
        param = strtok(paramsSection, QUOTATIONS);
        do {
            if (getValue(symbolsHT, param)) {
                continue;
            }
            while (*param != '\0') {
                if (isalpha(*param) != 0) {
                    /* TODO: add data to data linked list */
                    addDataParamToDataList(*param);
                    ++DC;
                } else {
                    removeChar(param, '\n');
                    ASSEMBLY_SYNTAX_ERROR("Invalid .string parameter %s at line %d", param, file->lineNum)
                }
                ++param;
            }
        } while ((param = strtok(NULL, COMMA)) != NULL);
    }
}

int isCommasValid(char *paramsSection) {
    return 1;
}

int isQuotationsValid(char *paramsSection) {
    return 1;
}

unsigned short isJmpWithParamsAddrMethod(char *paramsSection) {
    int charIndexForLabelsCut = 0, charIndexForParamsCut = 0, isNotJmpWithParamsAddrMethod = 0;
    char *tempLabel = malloc(sizeof(paramsSection));
    char *paramsAfterOpenBracket = malloc(sizeof(paramsSection));
    char *param;
    if (paramsSection == NULL) {
        return FALSE;
    }
    paramsSection = strtok(paramsSection, "\n");
    if (getType(symbolsHT, paramsSection) != NULL) {
        return TRUE;
    }
    /* check if it's a jump with parameters addr method */
    while (paramsSection[charIndexForLabelsCut] != NULL_CHAR) {
        /* check if there is a symbol before an open bracket */
        while (paramsSection[charIndexForLabelsCut] != OPEN_BRACKET) {
            if (paramsSection[charIndexForLabelsCut] == NULL_CHAR) {
                /* if we get to a null char before an open bracket, and the label doesn't exist (because we
                 * checked it before) then the parameter is wrong. */
                ASSEMBLY_SYNTAX_ERROR("Invalid parameter %s at line %d", paramsSection, file->lineNum)
            }
            ++charIndexForLabelsCut;
        }
        /* Cuts the label from paramsSections and checks if the label is valid */
        strncpy(tempLabel, paramsSection, charIndexForLabelsCut);
        if (getType(symbolsHT, tempLabel) == NULL) {
            ASSEMBLY_SYNTAX_ERROR("Symbol %s does not exist at line %d", tempLabel, file->lineNum);
            return FALSE;
        }
        ++charIndexForLabelsCut;
        /* Cuts the params part (after OPEN_BRACKET) and checks if the params are valid*/
        strncpy(paramsAfterOpenBracket, paramsSection + charIndexForLabelsCut, strlen(paramsSection) - 1);
        /*param = strtok(paramsAfterOpenBracket, COMMA);*/
        while (paramsAfterOpenBracket[charIndexForParamsCut] != CLOSE_BRACKET_CHAR) {
            if (paramsAfterOpenBracket[charIndexForParamsCut] == NULL_CHAR) {
                /* if we get to a null char before an open bracket, and the label doesn't exist (because we
                 * checked it before) then the parameter is wrong. */
                ASSEMBLY_SYNTAX_ERROR("Invalid parameter %s at line %d", paramsSection, file->lineNum)
                return FALSE;
            }
            ++charIndexForParamsCut;
        }
        /* paramsAfterOpenBracket will point to the first parameter after the open bracket */
        paramsAfterOpenBracket = strtok(paramsAfterOpenBracket, DANI_CALFON);
        do {
            if (getParamAddrMethod(paramsAfterOpenBracket) != IMMEDIATE &&
                getParamAddrMethod(paramsAfterOpenBracket) != DIRECT &&
                getParamAddrMethod(paramsAfterOpenBracket) != REGISTER) {
                ASSEMBLY_SYNTAX_ERROR("Invalid param for %s operation at line %d", paramsAfterOpenBracket,
                                      file->lineNum);
            }
        } while ((paramsAfterOpenBracket = strtok(NULL, strcat(CLOSE_BRACKET_STR, COMMA))) != NULL);
    }
    return TRUE;
}

unsigned short getParamAddrMethod(char *param) {
    int charIndex = 0, numAfterHashTag = -1;
    char *paramWithoutHashTag = malloc(sizeof(param)), *charAfterStrtol = NULL;
    while (param != NULL_CHAR) {
        if (getType(registersHT, param) != NULL) {
            return REGISTER;
        } else if (param[charIndex] == HASH_TAG) {
            strncpy(paramWithoutHashTag, param + 1, strlen(param) - 1);
            numAfterHashTag = strtol(paramWithoutHashTag, charAfterStrtol, 10);
            if (charAfterStrtol == NULL) {
                return IMMEDIATE;
            }
        } else if (getType(symbolsHT, param) != NULL) {
            /*TODO: what do we do if the label wasn't declared yet? according to p. 17, we should take care of that*/
            return DIRECT;

        } else if (DANI_CALFON) {}

    }

    return TRUE;
    /* check if it's a direct addr method */
}