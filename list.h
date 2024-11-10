#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

#define LIST_CHECK(list, line, function, file) do { \
    if (listCheckForError (list) != LIST_CORRECT)\
        {\
            listPrintError (list, line, function, file);\
            return ERROR;\
        }\
  } while(false)

#define VALUES_FOR_ERROR __LINE__, __FUNCTION__, __FILE__

const int EMPTY_ELEMENT = -1;
const int POISON        = -30;
const int LIST_SIZE     = 10;
const int EMPTY_LIST    = 1;

enum RETURN_VALUES
{
    CORRECT = 0,
    ERROR   = 1
};

enum LIST_ERRORS
{
    LIST_CORRECT,
    LIST_DATA_NULL,
    LIST_NEXT_NULL,
    LIST_PREV_NULL,
    LIST_BAD_SIZE,
    LIST_BAD_FREE
};

struct LIST
{
    int *data             = NULL;
    int *next             = NULL;
    int *prev             = NULL;
    int size              = LIST_SIZE;
    int free              = 1;
    LIST_ERRORS listState = LIST_CORRECT;
};

RETURN_VALUES listCtor (LIST *list, int size);
RETURN_VALUES listDtor (LIST *list, int line, const char* function, const char* file);
void listDump (FILE *logFile, LIST *list);
void print (FILE *logFile, int *array, const char *name);
LIST_ERRORS listCheckForError (LIST *list);
LIST_ERRORS listPrintError (LIST *list, int line, const char* function, const char* file);
RETURN_VALUES makeDotFile (LIST *list);

#endif

