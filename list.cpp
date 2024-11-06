#include "list.h"

RETURN_VALUES listCtor (LIST *list, int size)
{
    assert (list);

    if (list->free != 1)
    {
        printf ("This list is not empty\n");
        return ERROR;
    }

    list->data = (int*)calloc (size, sizeof(int));
    if (list->data == NULL)
    {
        return ERROR;
    }

    for (int i = 0; i < LIST_SIZE; i++)
    {
        list->data[i] = POISON;
    }

    list->next = (int*)calloc (size, sizeof(int));
    if (list->next == NULL)
    {
        return ERROR;
    }

    for (int i = 0; i < LIST_SIZE; i++)
    {
        if (i == 0 || i == LIST_SIZE - 1)
        {
            list->next[i] = 0;
        } else {
            list->next[i] = i + 1;
        }
    }

    list->prev = (int*)calloc (size, sizeof(int));
    if (list->prev == NULL)
    {
        return ERROR;
    }

    for (int i = 0; i < LIST_SIZE; i++)
    {
        if (i == 0)
        {
            list->prev[i] = 1;
        } else {
            list->prev[i] = EMPTY_ELEMENT;
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

void listDump (LIST *list)
{
    printf ("\n\n\n");

    printf ("Number:");
    for (int i = 0; i < LIST_SIZE; i++)
    {
        printf ("%4d ", i);
    }
    printf ("\n");

    print (list->data, "Data: ");
    print (list->next, "Next: ");
    print (list->prev, "Prev: ");

    printf ("Size: %d\n", LIST_SIZE);
    printf ("Free: %d\n", list->free);

    printf ("\n\n\n");
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

void print (int *array, const char *name)
{
    printf ("%s ", name);

    for (int i = 0; i < LIST_SIZE; i++)
    {
        printf ("%4d ", array[i]);
    }

    printf ("\n");
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