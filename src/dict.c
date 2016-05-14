#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dict.h"
#include "sds.h"

static const int __DICT_SIZE = 1024;


/////  private

static dictEntity* _dictEntityNew(sds key, sds value, dictEntity* next) {
	dictEntity* entity = (dictEntity*) malloc(sizeof(dictEntity));
	entity->key = key;
	entity->value = value;
	entity->next = next;
	return entity;
}

static int _sdsHash(sds s) {
	int len = strlen(s);
	int h = 1;

	for (int i = 0; i<len; i++) {
		h = h * 31 + s[i];
	}

	return h;
}

static int _dictIdx(dict* dict, sds key) {
	int idx = _sdsHash(key);
	if (idx < 0) {
		idx = 0 - idx;
	}
	return idx % dict->size;
}

///// API

dict* dictNew() {
	dict* d = (dict*) malloc(sizeof(dict));

	d->size = __DICT_SIZE;
    d->table = (dictEntity**) malloc(d->size * sizeof(dictEntity*));

	return d;
}

void dictPut(dict* dict, sds key, sds value) {
	int idx = _dictIdx(dict, key);

	dictEntity* entity = dict->table[idx];
	while (entity != NULL) {
		if (strcmp(entity->key, key) == 0) {
			entity->value = value;
			return;
		}
		entity = entity->next;
	}

	dict->table[idx] = _dictEntityNew(key, value, dict->table[idx]);
}

sds dictGet(dict* dict, sds key) {
	int idx = _dictIdx(dict, key);

	dictEntity* entity = dict->table[idx];
	while (entity != NULL) {
		if (strcmp(entity->key, key) == 0) {
			return entity->value;
		}
		entity = entity->next;
	}

	return NULL;
}

/*
int main(int argc, char** argv) {
	dict* d = dictNew();

	sds k = sdsNew("hello");
	sds v = sdsNew("world");

	dictPut(d, k, v);
	sds r =dictGet(d, k);

	printf("%s", r);
}

*/
