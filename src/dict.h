#ifndef __DICT_H
#define __DICT_H

#include "sds.h"

typedef struct DictEntity {
    Sds key;
    Sds value;
    struct DictEntity* next;
} DictEntity;

typedef struct Dict {
    DictEntity** table;
    int size;
} Dict;

Dict* dictNew();
void dictPut(Dict* dict, Sds key, Sds value);
Sds dictGet(Dict* dict, Sds key);

#endif
