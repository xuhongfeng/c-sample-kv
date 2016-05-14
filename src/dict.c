#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dict.h"
#include "sds.h"

static const int __DICT_SIZE = 1024;

/////  private

static DictEntity* _dictEntityNew(Sds key, Sds value, DictEntity* next) {
    DictEntity* entity = (DictEntity*) malloc(sizeof(DictEntity));
    entity->key = key;
    entity->value = value;
    entity->next = next;
    return entity;
}

static int _sdsHash(Sds s) {
    int len = strlen(s);
    int h = 1;

    for (int i = 0; i < len; i++) {
        h = h * 31 + s[i];
    }

    return h;
}

static int _dictIdx(Dict* dict, Sds key) {
    int idx = _sdsHash(key);
    if (idx < 0) {
        idx = 0 - idx;
    }
    return idx % dict->size;
}

///// API

Dict* dictNew() {
    Dict* d = (Dict*) malloc(sizeof(Dict));

    d->size = __DICT_SIZE;
    d->table = (DictEntity**) malloc(d->size * sizeof(DictEntity*));

    return d;
}

void dictPut(Dict* dict, Sds key, Sds value) {
    int idx = _dictIdx(dict, key);

    DictEntity* entity = dict->table[idx];
    while (entity != NULL) {
        if (strcmp(entity->key, key) == 0) {
            entity->value = value;
            return;
        }
        entity = entity->next;
    }

    dict->table[idx] = _dictEntityNew(key, value, dict->table[idx]);
}

Sds dictGet(Dict* dict, Sds key) {
    int idx = _dictIdx(dict, key);

    DictEntity* entity = dict->table[idx];
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

 Sds k = SdsNew("hello");
 Sds v = SdsNew("world");

 dictPut(d, k, v);
 Sds r =dictGet(d, k);

 printf("%s", r);
 }

 */
