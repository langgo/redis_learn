#include "sds.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void sdsOomAbort(void) {
	fprintf(stderr, "SDS: Out Of Memory (SDS_ABORT_ON_OOM defined)\n");
	abort();
}

sds sdsnewlen(const void *init, size_t initlen) {
	struct sdshdr *sh;

	sh = malloc(sizeof(struct sdshdr) + initlen + 1);
	if (!sh) sdsOomAbort();

	sh->len = initlen;
	sh->free = 0;
	if (initlen) {
		if (init) memcpy(sh->buf, init, initlen);
		else memset(sh->buf, 0, initlen);
	}
	sh->buf[initlen] = '\0';
	return sh->buf;
}

sds sdsnew(const char *init) {
	size_t initlen = (init == NULL) ? 0 : strlen(init);
	return sdsnewlen(init, initlen);
}

sds sdsempty() {
	return sdsnewlen(NULL, 0);
}

void sdsfree(sds s) {
	if (s) free(s - sizeof(struct sdshdr));
}

size_t sdslen( sds s) {
	struct sdshdr *sh = (void*) (s - sizeof(struct sdshdr));
	return sh->len;
}

sds sdsdup( sds s) {
	return sdsnewlen(s, sdslen(s));
}

size_t sdsavail( sds s) {
	struct sdshdr *sh = (void*) (s - sizeof(struct sdshdr));
	return sh->free;
}

static sds sdsMakeRoomFor(sds s, size_t addlen) {
	struct sdshdr *sh = (void*) (s - sizeof(struct sdshdr));
	size_t free = sdsavail(s);
	if (free >= addlen) return s;

	size_t len = sdslen(s);
	size_t newlen = (len + addlen) * 2;
	struct sdshdr *newsh = realloc(sh, sizeof(struct sdshdr) + newlen + 1);
	if (!newsh) sdsOomAbort();

	newsh->free = newlen - len;
	return newsh->buf;
}

sds sdscatlen(sds s, const void *t, size_t len) {
	s = sdsMakeRoomFor(s, len);

	struct sdshdr *sh = (void*) (s - sizeof(struct sdshdr));
	size_t curlen = sdslen(s);

	memcpy(s + curlen, t, len);
	sh->len = curlen + len;
	sh->free = sdsavail(s) - len;
	s[curlen + len] = '\0';
	return s;
}

sds sdscat(sds s, const char *t) {
	return sdscatlen(s, t, strlen(t));
}

sds sdscpylen(sds s, const void *t, size_t len) {
	struct sdshdr *sh = (void*) (s - sizeof(struct sdshdr));
	size_t totlen = sdsavail(s) + sdslen(s);
	if (totlen < len) {
		s = sdsMakeRoomFor(s, len - totlen);
		sh = (void*) (s - sizeof(struct sdshdr));
		totlen = sdsavail(s) + sdslen(s);
	}

	memcpy(s, t, len);
	s[len] = '\0';
	sh->len = len;
	sh->free = totlen - len;
	return s;
}

sds sdscpy(sds s, const char *t) {
	return sdscpylen(s, t, strlen(t));
}

int sdscmp(sds s1, sds s2) {
	size_t l1 = sdslen(s1);
	size_t l2 = sdslen(s2);

	size_t minlen  = l1 < l2 ? l1 : l2;
	size_t cmp = memcmp(s1, s2, minlen);
	if (cmp == 0) return l1 - l2;
	return cmp;
}

sds sdsrange(sds s, long start, long end) {
	size_t len = sdslen(s);
	if (len == 0) return s; /* 防止memmove出错 */

	start = start % len;
	start = start < 0 ? start + len : start;
	end = end % len;
	end = end < 0 ? end + len : end;

	long newlen = end - start;
	if (newlen <= 0) return s;

	printf("%d %d\n", start, end);
	memmove(s, s + start, newlen);
	struct sdshdr *sh = (void*) (s - sizeof(struct sdshdr));
	s[newlen] = '\0';
	sh->len = newlen;
	sh->free = len + sh->free - newlen;
	return s;
}