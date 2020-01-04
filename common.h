/*Name: Owen Douglas
 *Student ID: 1056143
 *Email: douglaso@uoguelph.ca
 */

#ifndef __COMMON__
#define __COMMON__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct tree {
	char *key;
	void *data;
	struct tree *child[2];
};

struct nameInfo {
	int arraySize;
	struct name_basics *nameArray;
	struct tree *root;
	struct tree *root2;
};

struct titleInfo {
	int arraySize;
	struct title_basics *titleArray;
	struct tree *root;
	struct tree *root2;
};

struct principalInfo {
	int arraySize;
	struct title_principals *principalsArray;
	struct tree *nameRoot;
	struct tree *titleRoot;
};

void get_column (char *line, char **column, int colNum);
void reverse(char **str);
char *cleanWS(char *str);
char *strdup(const char *src);

#endif