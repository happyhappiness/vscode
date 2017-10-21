#include "rsync.h"

extern int verbose;

static struct exclude_struct **exclude_list;

/*
 * Optimization for special case when all included files are explicitly
 *   listed without wildcards in the "exclude" list followed by a "- *"
 *   to exclude the rest.
 * Contributed by Dave Dykstra <dwd@bell-labs.com>
 */
static int only_included_files = 1;
static struct exclude_struct *exclude_the_rest;

int send_included_file_names(int f,struct file_list *flist)
{
	struct exclude_struct *ex, **ex_list;
	int n;
	char *p;

	if (!only_included_files || (exclude_the_rest == NULL))
		return 0;

	if (verbose > 1) {
		rprintf(FINFO,"(using include-only optimization) ");
	}

	/* set exclude_list to NULL temporarily so check_exclude */
	/*   will always return true */
	ex_list = exclude_list;
	exclude_list = NULL;
	for (n=0; (ex = ex_list[n]) != NULL; n++) {
		if (ex == exclude_the_rest)
			break;
		p = ex->pattern;
		while (*p == '/') {
			/* skip the allowed beginning slashes */
			p++;
		}
		send_file_name(f,flist,p,0,0);
	}
	exclude_list = ex_list;
	
	return 1;
}

/* build an exclude structure given a exclude pattern */
static struct exclude_struct *make_exclude(char *pattern, int include)
{
	struct exclude_struct *ret;

	ret = (struct exclude_struct *)malloc(sizeof(*ret));
	if (!ret) out_of_memory("make_exclude");

	memset(ret, 0, sizeof(*ret));

	if (strncmp(pattern,"- ",2) == 0) {
		pattern += 2;
	} else if (strncmp(pattern,"+ ",2) == 0) {
		ret->include = 1;
		pattern += 2;
	} else {
		ret->include = include;
	}

	ret->pattern = strdup(pattern);

	if (!ret->pattern) out_of_memory("make_exclude");

	if (strpbrk(pattern, "*[?")) {
	    if (!ret->include && (*pattern == '*') && (*(pattern+1) == '\0')) {
		    exclude_the_rest = ret;
	    } else {
		    only_included_files = 0;
	    }
	    ret->regular_exp = 1;
	} else if (!ret->include) {
		only_included_files = 0;
	}

	if (strlen(pattern) > 1 && pattern[strlen(pattern)-1] == '/') {
		ret->pattern[strlen(pattern)-1] = 0;
		ret->directory = 1;
	}

