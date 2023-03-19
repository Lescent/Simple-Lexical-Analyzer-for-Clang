
#ifndef _INC_STDIO
#define _INC_STDIO
#include<stdio.h>
#endif


void usage(){
    printf("Usage: lexer [OPTION] [FILE_PATH]\n");
    printf("\t-p : print word type encoding\n");
    printf("\t-s : save analyzing result to a new file\n");
}