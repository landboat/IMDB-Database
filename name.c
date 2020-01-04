/*Name: Owen Douglas
 *Student ID: 1056143
 *Email: douglaso@uoguelph.ca
 */

#include "name.h"
#include "common.h"
#include "binary.h"

struct nameInfo *get_name(char *directory) {
	int i = 0;
	int size = 0;
	int count = 0;
	FILE *fp = NULL;
	char *column = NULL;
	char *nconst = NULL;
	char *pName  = NULL;
	char *fullPath = NULL;
	char buffer[257] = "\0";
	char end[] = "/name.basics.tsv";
	struct nameInfo *names = malloc(sizeof(struct nameInfo));

	names->root = NULL;
	names->root2 = NULL;

	size = strlen(directory) + strlen(end) + 1;

	fullPath = malloc(size);
	strcpy (fullPath, directory);
	strcat (fullPath, end);
	fp = fopen(fullPath, "r");

	if (fp != NULL) {
		/*Loops until EOF.*/
		while ((fgets(buffer, 257, fp)) != NULL) {
			if (buffer != buffer) {
				fprintf(stderr, "Error reading %s/name.basics.tsv\n", directory);
				exit(-1);
			}
			get_column(buffer, &column, 4);
			if ((strstr(column, "actor") != 0) || (strstr(column, "actress") != 0)) {
				/*Increments count if column contains 'actor' or 'actress'.*/
				count++;
			}
			free(column);
		}
		names->arraySize = count;
		/*Allocates memory for count number of name_basics structs.*/
		names->nameArray = malloc(count * sizeof(struct name_basics));
		fseek(fp, 0, SEEK_SET);

		/*Loops until each actor/actress entry has been stored in nameArray.*/
		while (i < count) {
			fgets(buffer, 257, fp);
			if (buffer != buffer) {
				fprintf(stderr, "Error reading %s/name.basics.tsv\n", directory);
				exit(-1);
			}
			get_column(buffer, &column, 4);
			if ((strstr(column, "actor") != 0) || (strstr(column, "actress") != 0)) {
				free(column);
				/*Copies nconst to the current names->nameArray index.*/
				get_column(buffer, &column, 0);
				reverse(&column);
				nconst = strdup(column);
				names->nameArray[i].nconst = nconst;
				free(column);

				/*Copies pName to the current names->nameArray index.*/
				get_column(buffer, &column, 1);
				pName = strdup(column);
				names->nameArray[i].primaryName = pName;
				free(column);	

				i++;	
			}
			else {
				free(column);
			}	
		}
		fclose(fp);
		free(fullPath);
	}
	else {
		/*Error message if fp is NULL.*/
		fprintf(stderr, "Error opening the file\n");
		exit(-1);
	}
	return names;
}

void build_pnindex(struct nameInfo **names) {
	int i = 0;
	/*Adds each index of nameArray to the nameInfo primaryName tree.*/
	for (i = 0; i < (*names)->arraySize; i++) {
		addNode(&((*names)->root), (*names)->nameArray[i].primaryName, &((*names)->nameArray[i]));
	}
	return;
}

struct name_basics *findName(struct nameInfo *names, char *search) {
	/*Returns the nameArray index corresponding to the search key name.*/
	return ((struct name_basics*)findNode(&(names->root), search));
}

void build_nindex(struct nameInfo **names) {
	int i = 0;
	/*Adds each index of nameArray to the nameInfo nconst tree.*/
	for (i = 0; i < (*names)->arraySize; i++) {
		addNode(&((*names)->root2), (*names)->nameArray[i].nconst, &((*names)->nameArray[i]));
	}
	return;
}

struct name_basics *findNconst(struct nameInfo *names, char *search) {
	/*Returns the nameArray index corresponding to the search key nconst.*/
	return ((struct name_basics*)findNode(&(names->root2), search));
}

