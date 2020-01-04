/*Name: Owen Douglas
 *Student ID: 1056143
 *Email: douglaso@uoguelph.ca
 */

#include "title.h"
#include "common.h"
#include "binary.h"

struct titleInfo *get_title(char *directory) {
	int i = 0;
	int size = 0;
	int count = 0;
	FILE *fp = NULL;
	char *column = NULL;
	char *tconst = NULL;
	char *pTitle  = NULL;
	char *fullPath = NULL;
	char buffer[1024] = "\0";
	char end[] = "/title.basics.tsv";
	struct titleInfo *titles = malloc(sizeof(struct titleInfo));

	titles->root = NULL;
	titles->root2 = NULL;

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
				fprintf(stderr, "Error reading %s/title.basics.tsv\n", directory);
				exit(-1);
			}
			get_column(buffer, &column, 1);
			if (strstr(column, "movie") != 0) {
				free(column);
				get_column(buffer, &column, 4);
				if (strstr(column, "0") != 0) {
					free(column);
					/*Increments count iff column contains 'movie' and isAdult is 0.*/
					count++;
				}
				else {
					free(column);
				}	
			}
			else {
				free(column);
			}	
		}
		titles->arraySize = count;
		/* Allocates memory for count number of title_basics structs.*/
		titles->titleArray = malloc(count * sizeof(struct title_basics));
		fseek(fp, 0, SEEK_SET);

		/*Loops until each (non-adult) movie title entry has been stored in titleArray.*/
		while (i < count) {
			if ((fgets(buffer, 1024, fp)) == NULL) {
				break;
			}
			if (buffer != buffer) {
				fprintf(stderr, "Error reading %s/title.basics.tsv\n", directory);
				exit(-1);
			}

			get_column(buffer, &column, 1);
			if (strstr(column, "movie") != 0) {
				free(column);
				get_column(buffer, &column, 4);
				if (strstr(column, "0") != 0) {
					free(column);
					/*Copies tconst to the current titles->titleArray index.*/
					get_column(buffer, &column, 0);
					reverse(&column);
					tconst = strdup(column);
					titles->titleArray[i].tconst = tconst;
					free(column);

					/*Copies pTitle to the current titles->titleArray index.*/
					get_column(buffer, &column, 2);
					pTitle = strdup(column);
					titles->titleArray[i].primaryTitle = pTitle;
					free(column);

					i++;
				}
				else {
					free(column);
				}	
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

	return titles;
}

void build_ptindex(struct titleInfo **titles) {
	int i = 0;
	/*Adds each index of titleArray to the titleInfo primaryTitle tree.*/
	for (i = 0; i < (*titles)->arraySize; i++) {
		addNode(&((*titles)->root), (*titles)->titleArray[i].primaryTitle, &((*titles)->titleArray[i]));
	}
	return;
}

struct title_basics *findTitle(struct titleInfo *titles, char *search) {
	/*Returns the titleArray index corresponding to the search key title.*/
	return ((struct title_basics*)findNode(&(titles->root), search));
}

void build_tindex(struct titleInfo **titles) {
	int i = 0;
	/*Adds each index of titleArray to the titleInfo tconst tree.*/
	for (i = 0; i < (*titles)->arraySize; i++) {
		addNode(&((*titles)->root2), (*titles)->titleArray[i].tconst, &((*titles)->titleArray[i]));
	}
	return;
}

struct title_basics *findTconst(struct titleInfo *titles, char *search) {
	/*Returns the titleArray index corresponding to the search key tconst.*/
	return ((struct title_basics*)findNode(&(titles->root2), search));
}
