#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sds.h"

typedef struct sdshead {
	int len;
	int capacity;
	char buf[];
} sdshead;

sds sdsnew(const char *init) {

	sds s;

	int len = strlen(init);
	sdshead* sh = malloc(sizeof(sdshead) + len + 1);

	sh->len = len;
	sh->capacity = len;

	s = (sds) (sh->buf);
	memcpy(s, init, len);
	s[len] = '\0';

	return s;
}

int main(int argc, char** argv) {
	sds s = sdsnew("hello world");
	sdshead* sh = (sdshead*)(s - sizeof(sdshead));
	printf("%s %d %d", s, sh->len, sh->capacity);
}
