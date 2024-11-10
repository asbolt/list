#include "list.h"

RETURN_VALUES listCtor (LIST *list, int size)
{
    assert (list);

    if (list->free != EMPTY_LIST)
    {
        printf ("This list is not empty\n");
        return ERROR;
    }

    list->data = (int*)calloc ((size_t)size, sizeof(int));
    if (list->data == NULL)
    {
        return ERROR;
    }

    for (int numberElement = 0; numberElement < LIST_SIZE; numberElement++ )
    {
        list->data[numberElement]  = POISON;
    }

    list->next = (int*)calloc ((size_t)size, sizeof(int));
    if (list->next == NULL)
    {
        return ERROR;
    }

    for (int numberElement = 0; numberElement < LIST_SIZE; numberElement++ )
    {
        if (numberElement == 0 || numberElement == LIST_SIZE - 1)
        {
            list->next[numberElement]  = 0;
        } else {
            list->next[numberElement]  = numberElement + 1;
        }
    }

    list->prev = (int*)calloc ((size_t)size, sizeof(int));
    if (list->prev == NULL)
    {
        return ERROR;
    }

    for (int numberElement = 0; numberElement < LIST_SIZE; numberElement++ )
    {
        if (numberElement == 0)
        {
            list->prev[numberElement]  = 1;
        } else {
            list->prev[numberElement]  = EMPTY_ELEMENT;
        }
    }

    return CORRECT;
}

RETURN_VALUES listDtor (LIST *list, int line, const char* function, const char* file)
{
    assert (list);

    LIST_CHECK(list, line, function, file);

    free (list->data);
    list->data = NULL;

    free (list->next);
    list->next = NULL;

    free (list->prev);
    list->prev = NULL;

    return CORRECT; 
}

void listDump (FILE *logFile, LIST *list)
{
    fprintf (logFile, "\n\n\n");

    fprintf (logFile, "Number:");
    for (int numberElement = 0; numberElement < LIST_SIZE; numberElement++ )
    {
        fprintf (logFile, "%4d ", numberElement);
    }
    fprintf (logFile, "\n");

    print (logFile, list->data, "Data: ");
    print (logFile, list->next, "Next: ");
    print (logFile, list->prev, "Prev: ");

    fprintf (logFile, "Size: %d\n", LIST_SIZE);
    fprintf (logFile, "Free: %d\n", list->free);

    fprintf (logFile, "\n\n\n");
}

LIST_ERRORS listCheckForError (LIST *list)
{
    assert (list);

    if (list->data == NULL)
    {
        return LIST_DATA_NULL;
    }

    if (list->next == NULL)
    {
        return LIST_NEXT_NULL;
    }

    if (list->prev == NULL)
    {
        return LIST_PREV_NULL;
    }

    if (list->size != LIST_SIZE)
    {
        return LIST_BAD_SIZE;
    }

    if (list->free < 0)
    {
        return LIST_BAD_FREE;
    }

    return LIST_CORRECT;
}

void print (FILE *logFile, int *array, const char *name)
{
    fprintf (logFile, "%s ", name);

    for (int numberElement = 0; numberElement < LIST_SIZE; numberElement++ )
    {
        fprintf (logFile, "%4d ", array[numberElement]);
    }

    fprintf (logFile, "\n");
}

LIST_ERRORS listPrintError (LIST *list, int line, const char* function, const char* file)
{
    switch (list->listState)
    {
    case LIST_DATA_NULL:
        printf ("Data NULL\n");
        break;

    case LIST_NEXT_NULL:
        printf ("Next NULL\n");
        break;

    case LIST_PREV_NULL:
        printf ("Prev NULL\n");
        break;

    case LIST_BAD_SIZE:
        printf ("Size is not correct\n");
        break;

    case LIST_BAD_FREE:
        printf ("Free is not correct\n");
        break;

    case LIST_CORRECT:
    default:
        break;
    }

    printf ("Error in file %s:%d (function %s)\n", file, line, function);

    return list->listState;
}

RETURN_VALUES makeDotFile (LIST *list)
{
    FILE * dotFile = fopen ("dot.dot", "w");
        if (dotFile == NULL)
        {
            return ERROR;
        }

    fprintf (dotFile, "digraph G{\nsplines=ortho;\nrankdir=LR;\nlist[shape=record,label=\" number | value | next | prev\"];\n");

    for (int numberElement = 0; numberElement < LIST_SIZE; numberElement++ )
    {
        if (list->data[numberElement]  != POISON || numberElement == 0)
        {
            if (numberElement == 0)
            {
                fprintf (dotFile, "%d [shape=record,label=\" NULL | %d | %d | %d\", fontcolor = red];\n", numberElement, list->data[numberElement], list->next[numberElement], list->prev[numberElement]);
            } else {
                fprintf (dotFile, "%d [shape=record,label=\" %d | %d | %d | %d\" ];\n", numberElement, numberElement, list->data[numberElement], list->next[numberElement], list->prev[numberElement]);
            }
        }
    }

    fprintf (dotFile, "list -> 0[color=white];\n");

    fprintf (dotFile, "0 -> ");
    int ind = 0;
    for (int numberElement = list->prev[0]; numberElement != 0 && list->data[list->next[numberElement]] != POISON; numberElement = list->next[numberElement])
    {
        fprintf (dotFile, "%d -> ", numberElement);
        ind = numberElement;
    }
    fprintf (dotFile, "%d[weight = 1000];\n", list->next[ind]);

    fprintf (dotFile, "tail -> %d;\n", list->next[0]);
    fprintf (dotFile, "head -> %d;\n", list->prev[0]);

    fprintf (dotFile, "}");

    fclose (dotFile);

    return CORRECT;
}