#include <stdio.h>
#include "sds.h"

void test_sdsnewlen() {
	printf("test_sdsnewlen:\n");

	printf("%s\n", sdsnewlen("123456", 5));

	char buf[] = "123456";
	printf("%s\n", sdsnewlen(buf, 5));

	int data[] = {0x414243, 0x45, 67, 68, 69, 70};
	printf("%s\n", sdsnewlen(data, 8));

	printf("\n");
}

void test_sdsnew() {
	printf("test_sdsnew:\n");
	printf("%s\n", sdsnew("123456"));
	printf("\n");
}

void test_sdsempty() {
	printf("test_sdsempty:\n");
	sds s = sdsempty();
	printf("%s\n", s);
	printf("\n");
}

void test_sdsfree() {
	printf("test_sdsfree:\n");
	sds s = sdsnew("123456");
	sdsfree(s);
	/* s = NULL; */
	printf("\n");
	/* 这里还可以使用释放掉的内存，没有立刻出现错误。 */
	/*s[1] = '0';
	printf("%s\n", s);*/
}

void test_sdslen() {
	printf("test_sdslen:\n");

	sds s = sdsnewlen("1234567890", 10);
	printf("%d\n", sdslen(s));

	printf("\n");
}

void test_sdsdup() {
	printf("test_sdsdup:\n");

	sds s1 = sdsnewlen("123456", 5);
	sds s2 = sdsdup(s1);
	s1[1] = '0';
	printf("s1 : %s\n", s1);
	printf("s2 : %s\n", s2);

	sdsfree(s1);
	s1 = NULL;
	sdsfree(s2);
	s2 = NULL;

	printf("\n");
}

void test_sdsavail() {
	printf("test_sdsavail:\n");

	printf("%d\n", sdsavail(sdsempty()));

	printf("\n");
}

void test_sdscatlen() {
	printf("test_sdscatlen:\n");

	sds s = sdsnew("123");
	s = sdscatlen(s, "4567", 3);
	printf("%s\n", s);

	sdsfree(s);
	s = NULL;

	printf("\n");
}

void test_sdscat() {
	printf("test_sdscat:\n");

	sds s = sdsnew("123");
	s = sdscat(s, "4567890");
	printf("%s\n", s);

	printf("\n");
}

void test_sdscpylen() {
	printf("test_sdscpylen:\n");

	sds s = sdsnew("123");
	s = sdscpylen(s, "4567890", 6);
	printf("%s\n", s);

	printf("\n");
}

void test_sdscpy() {
	printf("test_sdscpy:\n");

	sds s = sdsnew("123");
	s = sdscpy(s, "4567890");
	printf("%s\n", s);

	printf("\n");
}

void test_sdscmp() {
	printf("test_sdscmp:\n");

	sds s1, s2;
	s1 = sdsnew("123456");
	s2 = sdsnew("123457");
	printf("%d\n", sdscmp(s1, s2));

	s1 = sdsnew("123");
	s2 = sdsnew("1234");
	printf("%d\n", sdscmp(s1, s2));

	s1 = sdsnew("123456");
	s2 = sdsnew("123456");
	printf("%d\n", sdscmp(s1, s2));

	s1 = sdsnew("123457");
	s2 = sdsnew("123456");
	printf("%d\n", sdscmp(s1, s2));

	s1 = sdsnew("1234");
	s2 = sdsnew("123");
	printf("%d\n", sdscmp(s1, s2));

	printf("\n");
}

void test_sdsrange() {
	printf("test_sdsrange:\n");

	sds s;
	s = sdsnew("abc123456def");
	s = sdsrange(s, 3, 8);
	printf("%s\n", s);

	s = sdsnew("abc123456def");
	s = sdsrange(s, -3, -1);
	printf("%s\n", s);

	s = sdsnew("abc123456def");
	s = sdsrange(s, 0, 2);
	printf("%s\n", s);

	printf("\n");
}


int main() {
	/*
	test_sdsnewlen();
	test_sdsnew();
	test_sdsempty();
	test_sdsfree();
	*/

	/*test_sdslen();*/

	/*test_sdsdup();*/

	/*test_sdsavail();*/

	/*test_sdscatlen();
	test_sdscat();*/

	/*
	test_sdscpylen();
	test_sdscpy();*/

	/*test_sdscmp();*/

	test_sdsrange();

	return 0;
}