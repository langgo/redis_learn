#ifndef __SDS_H
#define __SDS_H

#include <sys/types.h>

typedef char *sds;

struct sdshdr {
	long len;
	long free;
	char buf[0];
};

/* 初始化一个值为 init所指向的内容的字符串，长度为initlen */
sds sdsnewlen(const void *init, size_t initlen);
sds sdsnew(const char* init);
sds sdsempty();

/* 释放内存 */
void sdsfree(sds s); /* const sds s */

size_t sdslen(sds s); /* 相当于 char * const s */
size_t sdsavail(sds s);

sds sdsdup(sds s);
sds sdscatlen(sds s, const void *t, size_t len);
sds sdscat(sds s, const char *t);
sds sdscpylen(sds s, const void *t, size_t len);
sds sdscpy(sds s, const char *t);

sds sdsrange(sds s, long start, long end);

int sdscmp(sds s1, sds s2);



#endif
