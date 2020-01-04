/*Name: Owen Douglas
 *Student ID: 1056143
 *Email: douglaso@uoguelph.ca
 */

#ifndef __PRINCIPALS__
#define __PRINCIPALS__

struct title_principals {
	char *tconst;
	char *nconst;
	char *characters;
};

struct principalInfo *get_principals(char *directory);
void build_nindex_tp(struct principalInfo **principals);
void build_tindex_tp(struct principalInfo **principals);
struct tree *find_nconst_tp(struct principalInfo *principals, char *search);
struct tree *find_tconst_tp(struct principalInfo *principals, char *search);
struct tree *find_tp_alt(struct tree *principal, char *search);

#endif