#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sds.h"

typedef struct SdsHead {
    int len;
    int capacity;
    char buf[];
} SdsHead;

Sds sdsNew(const char *init) {

    Sds s;

    int len = strlen(init);
    SdsHead* sh = malloc(sizeof(SdsHead) + len + 1);

    sh->len = len;
    sh->capacity = len;

    s = (Sds) (sh->buf);
    memcpy(s, init, len);
    s[len] = '\0';

    return s;
}

/*
 int main(int argc, char** argv) {
 Sds s = SdsNew("hello world");
 Sdshead* sh = (Sdshead*)(s - sizeof(Sdshead));
 printf("%s %d %d", s, sh->len, sh->capacity);
 }

 */
