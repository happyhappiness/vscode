
/* include/exclude cluestick added by Martin Pool <mbp@samba.org> */

#include "rsync.h"

extern int verbose;
extern int am_server;
extern int am_sender;
extern int eol_nulls;
extern int list_only;
extern int recurse;
extern int io_error;
extern int local_server;
extern int delete_mode;
extern int delete_excluded;
extern int cvs_exclude;
extern int sanitize_paths;
extern int protocol_version;
extern int module_id;

extern char curr_dir[];
extern unsigned int curr_dir_len;
extern unsigned int module_dirlen;

struct filter_list_struct filter_list = { 0, 0, "" };
struct filter_list_struct cvs_filter_list = { 0, 0, " [cvsignore]" };
struct filter_list_struct server_filter_list = { 0, 0, " [server]" };

/* Need room enough for ":MODS " prefix plus some room to grow. */
#define MAX_RULE_PREFIX (16)

#define MODIFIERS_MERGE_FILE "-+Cenw"
#define MODIFIERS_INCL_EXCL "/!Crs"
#define MODIFIERS_HIDE_PROTECT "/!"

/* The dirbuf is set by push_local_filters() to the current subdirectory
 * relative to curr_dir that is being processed.  The path always has a
 * trailing slash appended, and the variable dirbuf_len contains the length
 * of this path prefix.  The path is always absolute. */
static char dirbuf[MAXPATHLEN+1];
static unsigned int dirbuf_len = 0;
static int dirbuf_depth;

/* This is True when we're scanning parent dirs for per-dir merge-files. */
static BOOL parent_dirscan = False;

/* This array contains a list of all the currently active per-dir merge
 * files.  This makes it easier to save the appropriate values when we
 * "push" down into each subdirectory. */
static struct filter_struct **mergelist_parents;
static int mergelist_cnt = 0;
static int mergelist_size = 0;

/* Each filter_list_struct describes a singly-linked list by keeping track
 * of both the head and tail pointers.  The list is slightly unusual in that
 * a parent-dir's content can be appended to the end of the local list in a
 * special way:  the last item in the local list has its "next" pointer set
 * to point to the inherited list, but the local list's tail pointer points
 * at the end of the local list.  Thus, if the local list is empty, the head
 * will be pointing at the inherited content but the tail will be NULL.  To
 * help you visualize this, here are the possible list arrangements:
 *
 * Completely Empty                     Local Content Only
 * ==================================   ====================================
 * head -> NULL                         head -> Local1 -> Local2 -> NULL
 * tail -> NULL                         tail -------------^
 *
 * Inherited Content Only               Both Local and Inherited Content
 * ==================================   ====================================
 * head -> Parent1 -> Parent2 -> NULL   head -> L1 -> L2 -> P1 -> P2 -> NULL
 * tail -> NULL                         tail ---------^
 *
 * This means that anyone wanting to traverse the whole list to use it just
 * needs to start at the head and use the "next" pointers until it goes
 * NULL.  To add new local content, we insert the item after the tail item
 * and update the tail (obviously, if "tail" was NULL, we insert it at the
 * head).  To clear the local list, WE MUST NOT FREE THE INHERITED CONTENT
 * because it is shared between the current list and our parent list(s).
 * The easiest way to handle this is to simply truncate the list after the
 * tail item and then free the local list from the head.  When inheriting
 * the list for a new local dir, we just save off the filter_list_struct
 * values (so we can pop back to them later) and set the tail to NULL.
 */

static void free_filter(struct filter_struct *ex)
{
	if (ex->match_flags & MATCHFLG_PERDIR_MERGE) {
		free(ex->u.mergelist->debug_type);
		free(ex->u.mergelist);
		mergelist_cnt--;
	}
	free(ex->pattern);
	free(ex);
}

/* Build a filter structure given a filter pattern.  The value in "pat"
 * is not null-terminated. */
static void add_rule(struct filter_list_struct *listp, const char *pat,
		     unsigned int pat_len, uint32 mflags, int xflags)
{
	struct filter_struct *ret;
	const char *cp;
	unsigned int ex_len;

	if (verbose > 2) {
		rprintf(FINFO, "[%s] add_rule(%s%.*s%s)%s\n",
			who_am_i(), get_rule_prefix(mflags, pat, 0, NULL),
			(int)pat_len, pat,
			(mflags & MATCHFLG_DIRECTORY) ? "/" : "",
			listp->debug_type);
	}

	/* This flag also indicates that we're reading a list that
	 * needs to be filtered now, not post-filtered later. */
	if (xflags & XFLG_ANCHORED2ABS) {
		uint32 mf = mflags & (MATCHFLG_RECEIVER_SIDE|MATCHFLG_SENDER_SIDE);
		if (am_sender) {
			if (mf == MATCHFLG_RECEIVER_SIDE)
				return;
		} else {
			if (mf == MATCHFLG_SENDER_SIDE)
				return;
		}
	}

	if (!(ret = new(struct filter_struct)))
		out_of_memory("add_rule");
	memset(ret, 0, sizeof ret[0]);

	if (xflags & XFLG_ANCHORED2ABS && *pat == '/'
	    && !(mflags & (MATCHFLG_ABS_PATH | MATCHFLG_MERGE_FILE))) {
		mflags |= MATCHFLG_ABS_PATH;
		ex_len = dirbuf_len - module_dirlen - 1;
	} else
		ex_len = 0;
	if (!(ret->pattern = new_array(char, ex_len + pat_len + 1)))
		out_of_memory("add_rule");
	if (ex_len)
		memcpy(ret->pattern, dirbuf + module_dirlen, ex_len);
	strlcpy(ret->pattern + ex_len, pat, pat_len + 1);
	pat_len += ex_len;

	if (strpbrk(ret->pattern, "*[?")) {
		mflags |= MATCHFLG_WILD;
		if ((cp = strstr(ret->pattern, "**")) != NULL) {
