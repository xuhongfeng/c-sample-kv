#ifndef __DICT_H
#define __DICT_H

#include "sds.h"

typedef struct dictEntity {
	sds key;
	sds value;
	struct dictEntity* next;
} dictEntity;

typedef struct dict {
	dictEntity** table;
	int size;
} dict;

dict* dictNew();
void dictPut(dict* dict, sds key, sds value);
sds dictGet(dict* dict, sds key);

#endif
