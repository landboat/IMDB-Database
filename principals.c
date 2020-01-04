/*Name: Owen Douglas
 *Student ID: 1056143
 *Email: douglaso@uoguelph.ca
 */

#include "principals.h"
#include "common.h"
#include "binary.h"

struct principalInfo *get_principals(char *directory) {
	int i = 0;
	int size = 0;
	int count = 0;
	FILE *fp = NULL;
	char *column = NULL;
	char *tconst = NULL;
	char *nconst = NULL;
	char *fullPath = NULL;
	char *characters = NULL;
	char buffer[1024] = "\0";
	char end[] = "/title.principals.tsv";
	struct principalInfo *principals = malloc(sizeof(struct principalInfo));

	principals->nameRoot = NULL;
	principals->titleRoot = NULL;

	size = strlen(directory) + strlen(end) + 1;

	fullPath = malloc(size);
	strcpy (fullPath, directory);
	strcat (fullPath, end);
	fp = fopen(fullPath, "r");

	if (fp != NULL) {
		/*Loops until EOF.*/
		while (!feof(fp)) {
			if ((fgets(buffer, 1024, fp)) == NULL) {
				break;
			}
			if (buffer != buffer) {
				fprintf(stderr, "Error reading %s/title.principals.tsv\n", directory);
				exit(-1);
			}
			get_column(buffer, &column, 3);
			if ((strstr(column, "actor") != 0) || (strstr(column, "actress") != 0)) {
				/*Increments count if column contains 'actor' or 'actress'.*/
				count++;
			}
			free(column);
		}
		principals->arraySize = count;
		/* Allocates memory for count number of title_principals structs.*/
		principals->principalsArray = malloc(count * sizeof(struct title_principals));
		fseek(fp, 0, SEEK_SET);

		/*Loops until each actor/actress entry has been stored in principalsArray.*/
		while (i < count) {
			if ((fgets(buffer, 1024, fp)) == NULL) {
				break;
			}
			if (buffer != buffer) {
				fprintf(stderr, "Error reading %s/title.principals.tsv\n", directory);
				exit(-1);
			}

			get_column(buffer, &column, 3);
			if ((strstr(column, "actor") != 0) || (strstr(column, "actress") != 0)) {
				free(column);
				/* Copies tconst to the current principals->principalsArray index.*/
				get_column(buffer, &column, 0);
				reverse(&column);
				tconst = strdup(column);
				principals->principalsArray[i].tconst = tconst;
				free(column);

				/* Copies nconst to the current principals->principalsArray index.*/
				get_column(buffer, &column, 2);
				reverse(&column);
				nconst = strdup(column);
				principals->principalsArray[i].nconst = nconst;
				free(column);

				/* Copies characters to the current principals->principalsArray index.*/
				get_column(buffer, &column, 5);
				characters = strdup(column);
				principals->principalsArray[i].characters = characters;
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
	return principals;
}

void build_nindex_tp(struct principalInfo **principals) {
	int i = 0;
	/*Adds each index of principalArray to the principalInfo nconst tree.*/
	for (i = 0; i < (*principals)->arraySize; i++) {
		addNode(&((*principals)->nameRoot), (*principals)->principalsArray[i].nconst, &((*principals)->principalsArray[i]));
	}
	return;
}

void build_tindex_tp(struct principalInfo **principals) {
	int i = 0;
	/*Adds each index of principalArray to the principalInfo tconst tree.*/
	for (i = 0; i < (*principals)->arraySize; i++) {
		addNode(&((*principals)->titleRoot), (*principals)->principalsArray[i].tconst, &((*principals)->principalsArray[i]));
	}
	return;
}

struct tree *find_nconst_tp(struct principalInfo *principals, char *search) {
	/*Returns the tree leaf corresponding to the search key nconst.*/
	return ((struct tree*)findPrincipals(&(principals->nameRoot), search));
}

struct tree *find_tconst_tp(struct principalInfo *principals, char *search) {
	/*Returns the tree leaf corresponding to the search key tconst.*/
	return ((struct tree*)findPrincipals(&(principals->titleRoot), search));
}

/*Alternate function that takes in a tree leaf as parameter instead of an Info struct.*/
struct tree *find_tp_alt(struct tree *principal, char *search) {
	/*Returns the tree leaf corresponding to the search key.*/
	return ((struct tree*)findPrincipals(&principal, search));
}