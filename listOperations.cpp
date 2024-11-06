#include "listOperations.h"

RETURN_VALUES listPrint (LIST *list, int line, const char* function, const char* file)
{
    assert (list);

    LIST_CHECK(list, line, function, file);

    printf ("\nLIST\n");

    for (int i = 1, numberElement = list->prev[0]; numberElement != 0; i++, numberElement = list->next[numberElement])
    {
        printf ("%d %d\n", i, list->data[numberElement]);
    }
    printf ("\n");

    return CORRECT;
}

RETURN_VALUES listAddElement (LIST *list, int value, int line, const char* function, const char* file)
{
    assert (list);

    LIST_CHECK(list, line, function, file);

    if (list->free == 0)
    {
        printf ("Data overflow\n");
        return ERROR;
    }

    list->data[list->free] = value;

    int currentElement = list->free;
    int nextEmptyElement = list->next[list->free];
    int previousElement = list->next[0];

    list->free = nextEmptyElement;  
    list->next[0] = currentElement;

    list->next[previousElement] = currentElement;
    list->next[currentElement] = 0;

    list->prev[currentElement] = previousElement;

    //makeDotFile (list, previousElement, currentElement, "green");
    //system ("dot dot.dot -Tpng -o gr.png");

    return CORRECT;
}

RETURN_VALUES listAddElementBeforeAnchor (LIST *list, int anchor, int value, int line, const char* function, const char* file)
{
    assert (list);

    LIST_CHECK(list, line, function, file);

    if (list->free == 0)
    {
        printf ("Data overflow\n");
        return ERROR;
    }

    int nextEmptyElement = list->next[list->free];

    list->data[list->free] = value;

    list->next[list->free] = anchor;
    if (list->prev[anchor] != 0)
    {
        list->next[list->prev[anchor]] = list->free;
    }

    list->prev[list->free] = list->prev[anchor];

    if (list->prev[anchor] == 0)
    {
        list->prev[0] = list->free;
    }
    list->prev[anchor] = list->free;

    list->free = nextEmptyElement;

    return CORRECT;
}

RETURN_VALUES listDeleteElement (LIST *list, int anchor, int line, const char* function, const char* file)
{
    assert (list);

    LIST_CHECK(list, line, function, file);

    list->data[anchor] = - list->data[anchor];

    list->next[list->prev[anchor]] = list->next[anchor];

    if (list->next[anchor] != 0)
    {
        list->prev[list->next[anchor]] = list->prev[anchor];
    }

    list->next[anchor] = list->free;
    list->prev[anchor] = EMPTY_ELEMENT;

    list->free = anchor;

    return CORRECT;
}

int listSearchElement (LIST *list, int value, int line, const char* function, const char* file)
{
    assert (list);

    LIST_CHECK(list, line, function, file);

    for (int numberElement = list->prev[0]; numberElement != 0; numberElement = list->next[numberElement])
    {
        if (list->data[numberElement] == value)
        {
            return numberElement;
        }
    }

    printf ("This element doesn't exist");
    return EMPTY_ELEMENT;
}

RETURN_VALUES makeDotFile (LIST *list, int anchor, int prev, const char *color)
{
    FILE * dotFile = fopen ("dot.dot", "w");
        if (dotFile == NULL)
        {
            return ERROR;
        }

    fprintf (dotFile, "digraph G{\nrankdir=LR;\nlist[shape=record,label=\" number | value | next | prev\"];\n");

    for (int i = 0; i < LIST_SIZE; i++)
    {
        fprintf (dotFile, "%d [shape=record,label=\" %d | %d | %d | %d\" ];\n", i, i, list->data[i], list->next[i], list->prev[i]);
    }

    fprintf (dotFile, "list -> 0[color=white];\n");

    for (int i = 0; i < LIST_SIZE - 1; i++)
    {
        fprintf (dotFile, "%d -> ", i);
    }
    fprintf (dotFile, "%d;\n", LIST_SIZE - 1);

    fprintf (dotFile, "%d -> %d [color=\"%s\"];\n", prev, anchor, color);

    fprintf (dotFile, "tail -> %d;\n", list->prev[0]);
    fprintf (dotFile, "head -> %d;\n", list->next[0]);

    fprintf (dotFile, "}");

    fclose (dotFile);

    return CORRECT;
}