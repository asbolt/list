#include "listOperations.h"

int main ()
{
    FILE * logFile = fopen ("logfile.txt", "w");
    if (logFile == NULL)
        {
            return ERROR;
        }

    LIST list = {};
    listCtor (&list, LIST_SIZE);

    listDump (logFile, &list);
    listAddElement (&list, 20, VALUES_FOR_ERROR);
    listDump (logFile, &list);
    listAddElement (&list, 30, VALUES_FOR_ERROR);
    listDump (logFile, &list);
    listAddElement (&list, 40, VALUES_FOR_ERROR);
    listDump (logFile, &list);

    listAddElementBeforeAnchor (&list, 1, 10, VALUES_FOR_ERROR);
    listDump (logFile, &list);

    listAddElement (&list, 50, VALUES_FOR_ERROR);
    listDump (logFile, &list);
    listAddElement (&list, 60, VALUES_FOR_ERROR);
    listDump (logFile, &list);
    listAddElement (&list, 70, VALUES_FOR_ERROR);
    listDump (logFile, &list);

    listDeleteElement (&list, 7, VALUES_FOR_ERROR);
    listDump (logFile, &list);

    listDeleteElement (&list, listSearchElement(&list, 30, VALUES_FOR_ERROR), VALUES_FOR_ERROR);

    listPrint (&list, VALUES_FOR_ERROR);

    listDtor (&list, VALUES_FOR_ERROR);

    fclose (logFile);

    return 0;
}