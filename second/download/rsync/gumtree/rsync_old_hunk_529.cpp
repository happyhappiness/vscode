#include "rsync.h"

extern int verbose;

static struct exclude_struct **exclude_list;

/* build an exclude structure given a exclude pattern */
static struct exclude_struct *make_exclude(char *pattern, int include)
{
	struct exclude_struct *ret;

	ret = (struct exclude_struct *)malloc(sizeof(*ret));
	if (!ret) out_of_memory("make_exclude");

	memset(ret, 0, sizeof(*ret));

	ret->orig = strdup(pattern);

	if (strncmp(pattern,"- ",2) == 0) {
		pattern += 2;
	} else if (strncmp(pattern,"+ ",2) == 0) {
		ret->include = 1;
		pattern += 2;
	} else {
		ret->include = include;
	}

	ret->pattern = strdup(pattern);

	if (!ret->orig || !ret->pattern) out_of_memory("make_exclude");

	if (strpbrk(pattern, "*[?")) ret->regular_exp = 1;

	if (strlen(pattern) > 1 && pattern[strlen(pattern)-1] == '/') {
		ret->pattern[strlen(pattern)-1] = 0;
		ret->directory = 1;
	}

