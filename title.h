/*Name: Owen Douglas
 *Student ID: 1056143
 *Email: douglaso@uoguelph.ca
 */

#ifndef __TITLE__
#define __TITLE__


struct title_basics {
	char *tconst;
	char *primaryTitle;
};

struct titleInfo *get_title(char *directory);
void build_ptindex(struct titleInfo **titles);
struct title_basics *findTitle(struct titleInfo *titles, char *search);
void build_tindex(struct titleInfo **titles);
struct title_basics *findTconst(struct titleInfo *titles, char *search);

#endif