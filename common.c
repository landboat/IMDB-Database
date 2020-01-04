/*Name: Owen Douglas
 *Student ID: 1056143
 *Email: douglaso@uoguelph.ca
 */

#include "common.h"

void get_column (char *line, char **column, int colNum) {
	int index1 = 0;
	int index2 = 0;
	int tabs = 0;
	int i = 0;

	/*Adjusts colNum to access the intended columnn.*/
	colNum = colNum + 1;
	while (tabs < colNum) {
		if (line[i] == '\t') {
			/*Counts number of tabs in line.*/
			tabs++;
			if (tabs == (colNum - 1)) {
				/*Sets beginning index of column string.*/
				index1 = i + 1;
			}
			if (tabs == colNum) {
				/*Sets end index of column string.*/
				index2 = i;
			}
		}
		i++;
	}
	/*Allocates memory for and copies column contents into column.*/
	i = index2 - index1;
	*column = calloc(1, i + 1);
	strncpy(*column, (line + index1), i);
	return;
}

void reverse(char **str) {
	char temp = '\0';
	int start = 0;
	int end = (strlen(*str) - 1);

	/*Reverses input string.*/
	while (start < end) {
		temp = (*str)[start];
		(*str)[start] = (*str)[end];
		(*str)[end] = temp;
		temp = '\0';
		start++;
		end--;
	}
	return;
}

char *cleanWS(char *str) {
	char *end = NULL;

	/*Removes whitespace before the first non-WS character.*/
	while (isspace((unsigned char)*str)) {
		str++;
	}
	end = str + strlen(str) - 1;
	/*Removes whitespace after the last non-WS character.*/
	while (end > str && isspace((unsigned char)*end)) {
		end--;
	}
	end[1] = '\0';
	return str;
}

char *strdup(const char *src) {
	/*Allocates and copies input string.*/
    char *dst = malloc(strlen (src) + 1);
    if (dst == NULL) {
    	return NULL;
    }
    strcpy(dst, src);
    return dst;         
}