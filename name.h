/*Name: Owen Douglas
 *Student ID: 1056143
 *Email: douglaso@uoguelph.ca
 */

#ifndef __NAME__
#define __NAME__


struct name_basics {
	char *nconst;
	char *primaryName;
};

struct nameInfo *get_name(char *directory);
void build_pnindex(struct nameInfo **names);
struct name_basics *findName(struct nameInfo *names, char *search);
void build_nindex(struct nameInfo **names);
struct name_basics *findNconst(struct nameInfo *names, char *search);


#endif