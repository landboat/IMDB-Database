/*Name: Owen Douglas
 *Student ID: 1056143
 *Email: douglaso@uoguelph.ca
 */

#include "binary.h"
#include "common.h"
#include "name.h"
#include "title.h"
#include "principals.h"

int main (int argc, char **argv) {
	int i = 0;
	int j = 0;
	char command[257]= "\0";
	char userInput[257] = "\0";
	struct nameInfo *names = NULL;
	struct name_basics *name = NULL;
	struct titleInfo *titles = NULL;
	struct title_basics *title = NULL;
	struct principalInfo *principals = NULL;
	struct tree *principal = NULL;

	if (argc != 2) {
		fprintf(stderr, "Usage:  %s directory\n", argv[1]);
	}

	/*Builds trees.*/
	titles = get_title(argv[1]);
	build_ptindex(&titles);
	build_tindex(&titles);
	names = get_name(argv[1]);
	build_pnindex(&names);
	build_nindex(&names);
	principals = get_principals(argv[1]);
	build_tindex_tp(&principals);
	build_nindex_tp(&principals);

	/*Would have used an exit command of 'exit' to break, but was not part of project instructions.*/
	while (1) {
		j = 0;
		name = NULL;
		title = NULL;
		principal = NULL;
		strcpy(command, "\0");
		strcpy(userInput, "\0");
		
		printf("> ");
		fgets(command, 257, stdin);
		strcpy(command, cleanWS(command));
		if (command[0] == 'n') {
			for (i = 4; i < strlen(command); i++) {
				userInput[j] = command[i];
				j++;
				userInput[j] = '\0';
			}
			strcpy(userInput, cleanWS(userInput));
			command[4] = '\0';
		}
		else if (command[0] == 't') {
			for (i = 5; i < strlen(command); i++) {
				userInput[j] = command[i];
				j++;
				userInput[j] = '\0';
			}
			strcpy(userInput, cleanWS(userInput));
			command[5] = '\0';
		}
		else {};

		while (strcmp(command, "name") != 0 && strcmp(command, "title") != 0) {
			j = 0;
			strcpy(command, "\0");
			strcpy(userInput, "\0");
			fprintf(stdout, "Invalid command. Try again:\n");
			
			printf("> ");
			fgets(command, 257, stdin);
			strcpy(command, cleanWS(command));
			if (command[0] == 'n') {
				for (i = 4; i < strlen(command); i++) {
					userInput[j] = command[i];
					j++;
					userInput[j] = '\0';
				}
				strcpy(userInput, cleanWS(userInput));
				command[4] = '\0';
			}
			else if (command[0] == 't') {
				for (i = 5; i < strlen(command); i++) {
					userInput[j] = command[i];
					j++;
					userInput[j] = '\0';
				}
				strcpy(userInput, cleanWS(userInput));
				command[5] = '\0';
			}
			else {};
		}


		if (strcmp(command, "name") == 0) {
			name = findName(names, userInput);
			if (name == NULL) {
				printf("Not found.\n");
			}
			else {
	  			principal = find_nconst_tp(principals, name->nconst);
	  			if (principal == NULL) {
		  			printf("Not found.\n");
		  		}
		  		else {
		  		/*Loops through each occurence of the name in principals.*/
		  			/*Only searches right branch due to the nature of the traversal algorithm.*/
		  			principal = find_nconst_tp(principals, name->nconst);
		  			while (principal) {
		  				title = findTconst( titles, ((struct title_principals*)principal->data)->tconst);
		  				if (title) {
		  					printf("%s : %s", title->primaryTitle, ((struct title_principals*)principal->data)->characters);
		  				}
		  				principal = find_tp_alt(principal->child[1], name->nconst);
		  			}
					printf("\n");
		  		}
	  		}	  		
		}
		else if (strcmp(command, "title") == 0) {
			title = findTitle(titles, userInput);
			if (title == NULL) {
				printf("Not found.\n");
			}
			else {
	  			principal = find_tconst_tp(principals, title->tconst);
	  			if (principal == NULL) {
		  			printf("Not found.\n");
		  		}
		  		else {
		  		/*Loops through each occurence of the title in principals.*/
		  			/*Only searches right branch due to the nature of the traversal algorithm.*/
		  			principal = find_tconst_tp(principals, title->tconst);
		  			while (principal) {
		  				name = findNconst(names, ((struct title_principals*)principal->data)->nconst);
		  				if (name) {
		  					printf("%s : %s", name->primaryName, ((struct title_principals*)principal->data)->characters);
		  				}
		  				principal = find_tp_alt(principal->child[1], title->tconst);
		  			}
					printf("\n");
		  		}
	  		}	  
		}	
	}
	free(titles);
	free(names);
	free(principals);
	return 0;
}
