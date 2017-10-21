
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

/** Build an exclude structure given an exclude pattern. */
static void make_exclude(struct exclude_list_struct *listp, const char *pat,
			 unsigned int pat_len, unsigned int mflags)
{
	struct exclude_struct *ret;
	const char *cp;
	unsigned int ex_len;

	ret = new(struct exclude_struct);
	if (!ret)
		out_of_memory("make_exclude");

	memset(ret, 0, sizeof ret[0]);

	if (exclude_path_prefix)
		mflags |= MATCHFLG_ABS_PATH;
	if (exclude_path_prefix && *pat == '/')
		ex_len = strlen(exclude_path_prefix);
	else
		ex_len = 0;
	ret->pattern = new_array(char, ex_len + pat_len + 1);
	if (!ret->pattern)
		out_of_memory("make_exclude");
	if (ex_len)
		memcpy(ret->pattern, exclude_path_prefix, ex_len);
	strlcpy(ret->pattern + ex_len, pat, pat_len + 1);
	pat_len += ex_len;

	if (strpbrk(ret->pattern, "*[?")) {
		mflags |= MATCHFLG_WILD;
		if ((cp = strstr(ret->pattern, "**")) != NULL) {
