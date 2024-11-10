#ifndef LIST_OPERATIONS_
#define LIST_OPERATIONS_

#include "list.h"

RETURN_VALUES listAddElement (LIST *list, int value, int line, const char* function, const char* file);
RETURN_VALUES listAddElementBeforeAnchor (LIST *list, int anchor, int value, int line, const char* function, const char* file);
RETURN_VALUES listPrint (LIST *list, int line, const char* function, const char* file);
RETURN_VALUES listDeleteElement (LIST *list, int anchor, int line, const char* function, const char* file);
int listSearchElement (LIST *list, int value, int line, const char* function, const char* file);

#endif