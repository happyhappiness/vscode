
/* include/exclude cluestick added by Martin Pool <mbp@samba.org> */

#include "rsync.h"

extern int verbose;

struct exclude_struct **exclude_list;
struct exclude_struct **local_exclude_list;
struct exclude_struct **server_exclude_list;
char *exclude_path_prefix = NULL;

/** Build an exclude structure given a exclude pattern */
static struct exclude_struct *make_exclude(const char *pattern, int include)
{
	struct exclude_struct *ret;
	char *cp;
	int pat_len;

	ret = new(struct exclude_struct);
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

	if (exclude_path_prefix)
		ret->match_flags |= MATCHFLG_ABS_PATH;
	if (exclude_path_prefix && *pattern == '/') {
		ret->pattern = new_array(char,
			strlen(exclude_path_prefix) + strlen(pattern) + 1);
		if (!ret->pattern) out_of_memory("make_exclude");
		sprintf(ret->pattern, "%s%s", exclude_path_prefix, pattern);
	}
	else {
		ret->pattern = strdup(pattern);
		if (!ret->pattern) out_of_memory("make_exclude");
	}

	if (strpbrk(pattern, "*[?")) {
		ret->match_flags |= MATCHFLG_WILD;
		if (strstr(pattern, "**")) {
			ret->match_flags |= MATCHFLG_WILD2;
			/* If the pattern starts with **, note that. */
			if (*pattern == '*' && pattern[1] == '*')
				ret->match_flags |= MATCHFLG_WILD2_PREFIX;
		}
	}

	pat_len = strlen(ret->pattern);
	if (pat_len > 1 && ret->pattern[pat_len-1] == '/') {
		ret->pattern[pat_len-1] = 0;
		ret->directory = 1;
	}

	for (cp = ret->pattern; (cp = strchr(cp, '/')) != NULL; cp++)
		ret->slash_cnt++;

	return ret;
}

static void free_exclude(struct exclude_struct *ex)
{
	free(ex->pattern);
	memset(ex,0,sizeof(*ex));
	free(ex);
}


void free_exclude_list(struct exclude_struct ***listp)
{
	struct exclude_struct **list = *listp;

	if (verbose > 2)
		rprintf(FINFO,"clearing exclude list\n");

	if (!list)
		return;

	while (*list)
		free_exclude(*list++);

	free(*listp);
	*listp = NULL;
}

static int check_one_exclude(char *name, struct exclude_struct *ex,
                             int name_is_dir)
{
	char *p;
