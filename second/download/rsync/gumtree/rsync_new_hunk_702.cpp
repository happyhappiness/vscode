
/* include/exclude cluestick added by Martin Pool <mbp@samba.org> */

#include "rsync.h"

extern int verbose;
extern int eol_nulls;
extern int list_only;
extern int recurse;

extern char curr_dir[];

struct exclude_list_struct exclude_list = { 0, 0, "" };
struct exclude_list_struct local_exclude_list = { 0, 0, "per-dir .cvsignore " };
struct exclude_list_struct server_exclude_list = { 0, 0, "server " };
char *exclude_path_prefix = NULL;

/** Build an exclude structure given a exclude pattern */
static void make_exclude(struct exclude_list_struct *listp, const char *pattern,
			 int pat_len, int include)
{
	struct exclude_struct *ret;
	const char *cp;
	int ex_len;

	ret = new(struct exclude_struct);
	if (!ret)
		out_of_memory("make_exclude");

	memset(ret, 0, sizeof ret[0]);
	ret->include = include;

	if (exclude_path_prefix)
		ret->match_flags |= MATCHFLG_ABS_PATH;
	if (exclude_path_prefix && *pattern == '/')
		ex_len = strlen(exclude_path_prefix);
	else
		ex_len = 0;
	ret->pattern = new_array(char, ex_len + pat_len + 1);
	if (!ret->pattern)
		out_of_memory("make_exclude");
	if (ex_len)
		memcpy(ret->pattern, exclude_path_prefix, ex_len);
	strlcpy(ret->pattern + ex_len, pattern, pat_len + 1);
	pat_len += ex_len;

	if (strpbrk(ret->pattern, "*[?")) {
		ret->match_flags |= MATCHFLG_WILD;
		if ((cp = strstr(ret->pattern, "**")) != NULL) {
			ret->match_flags |= MATCHFLG_WILD2;
			/* If the pattern starts with **, note that. */
			if (cp == ret->pattern)
				ret->match_flags |= MATCHFLG_WILD2_PREFIX;
		}
	}

	if (pat_len > 1 && ret->pattern[pat_len-1] == '/') {
		ret->pattern[pat_len-1] = 0;
		ret->directory = 1;
	}

	for (cp = ret->pattern; (cp = strchr(cp, '/')) != NULL; cp++)
		ret->slash_cnt++;

	if (!listp->tail)
		listp->head = listp->tail = ret;
	else {
		listp->tail->next = ret;
		listp->tail = ret;
	}
}

static void free_exclude(struct exclude_struct *ex)
{
	free(ex->pattern);
	free(ex);
}

void free_exclude_list(struct exclude_list_struct *listp)
{
	struct exclude_struct *ent, *next;

	if (verbose > 2) {
		rprintf(FINFO, "[%s] clearing %sexclude list\n",
			who_am_i(), listp->debug_type);
	}

	for (ent = listp->head; ent; ent = next) {
		next = ent->next;
		free_exclude(ent);
	}

	listp->head = listp->tail = NULL;
}

static int check_one_exclude(char *name, struct exclude_struct *ex,
                             int name_is_dir)
{
	char *p;
