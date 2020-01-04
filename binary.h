/*Name: Owen Douglas
 *Student ID: 1056143
 *Email: douglaso@uoguelph.ca
 */

#ifndef __BINARY__
#define __BINARY__

#include "common.h"
#include "title.h"

void addNode(struct tree **root, char *key, void *data);
void *findNode(struct tree **root, char *search);
void *findPrincipals(struct tree **root, char *search);

#endif