#include <stdio.h>
#include <stdlib.h>
#include "File.h"
#include "Globals.h"
#include "FirstPhase.h"

int main(int argc, char **argv) {
    int i;
    initProgramGlobals();

    for(i = 1; i < argc; i++) {
        initFileGlobals();
        FileStruct *file = openFile(argv[i]);
        firstScan(file);

        if (!FIRST_SCAN_ERRORS_FOUND) {
            /*secondScan(file);*/
        } else {
            printf("Cannot continue to the second scan, errors found in the first scan.");
        }

        fclose(file->fp);
        free(file);
    }




    return 0;
}