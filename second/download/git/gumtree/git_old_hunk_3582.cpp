#include "diff.h"
#include "parse-options.h"
#include "xdiff-interface.h"
#include "ll-merge.h"
#include "rerere.h"

/*
 *  --check turns on checking that the working tree matches the
 *    files that are being modified, but doesn't apply the patch
 *  --stat does just a diffstat, and doesn't actually apply
 *  --numstat does numeric diffstat, and doesn't actually apply
 *  --index-info shows the old and new index info for paths if available.
 *  --index updates the cache as well.
 *  --cached updates only the cache without ever touching the working tree.
 */
static const char *prefix;
static int prefix_length = -1;
static int newfd = -1;

static int unidiff_zero;
static int p_value = 1;
static int p_value_known;
static int check_index;
static int update_index;
static int cached;
static int diffstat;
static int numstat;
static int summary;
static int check;
static int apply = 1;
static int apply_in_reverse;
static int apply_with_reject;
static int apply_verbosely;
static int allow_overlap;
static int no_add;
static int threeway;
static int unsafe_paths;
static const char *fake_ancestor;
static int line_termination = '\n';
static unsigned int p_context = UINT_MAX;
static const char * const apply_usage[] = {
	N_("git apply [<options>] [<patch>...]"),
	NULL
};

static enum ws_error_action {
	nowarn_ws_error,
	warn_on_ws_error,
	die_on_ws_error,
	correct_ws_error
} ws_error_action = warn_on_ws_error;
static int whitespace_error;
static int squelch_whitespace_errors = 5;
static int applied_after_fixing_ws;

static enum ws_ignore {
	ignore_ws_none,
	ignore_ws_change
} ws_ignore_action = ignore_ws_none;


static const char *patch_input_file;
static struct strbuf root = STRBUF_INIT;
static int read_stdin = 1;
static int options;

static void parse_whitespace_option(const char *option)
{
	if (!option) {
		ws_error_action = warn_on_ws_error;
		return;
	}
	if (!strcmp(option, "warn")) {
		ws_error_action = warn_on_ws_error;
		return;
	}
	if (!strcmp(option, "nowarn")) {
		ws_error_action = nowarn_ws_error;
		return;
	}
	if (!strcmp(option, "error")) {
		ws_error_action = die_on_ws_error;
		return;
	}
	if (!strcmp(option, "error-all")) {
		ws_error_action = die_on_ws_error;
		squelch_whitespace_errors = 0;
		return;
	}
	if (!strcmp(option, "strip") || !strcmp(option, "fix")) {
		ws_error_action = correct_ws_error;
		return;
	}
	die(_("unrecognized whitespace option '%s'"), option);
}

static void parse_ignorewhitespace_option(const char *option)
{
	if (!option || !strcmp(option, "no") ||
	    !strcmp(option, "false") || !strcmp(option, "never") ||
	    !strcmp(option, "none")) {
		ws_ignore_action = ignore_ws_none;
		return;
	}
	if (!strcmp(option, "change")) {
		ws_ignore_action = ignore_ws_change;
		return;
	}
	die(_("unrecognized whitespace ignore option '%s'"), option);
}

static void set_default_whitespace_mode(const char *whitespace_option)
{
	if (!whitespace_option && !apply_default_whitespace)
		ws_error_action = (apply ? warn_on_ws_error : nowarn_ws_error);
}

/*
 * For "diff-stat" like behaviour, we keep track of the biggest change
 * we've seen, and the longest filename. That allows us to do simple
 * scaling.
 */
static int max_change, max_len;

/*
 * Various "current state", notably line numbers and what
 * file (and how) we're patching right now.. The "is_xxxx"
 * things are flags, where -1 means "don't know yet".
 */
static int linenr = 1;

/*
 * This represents one "hunk" from a patch, starting with
 * "@@ -oldpos,oldlines +newpos,newlines @@" marker.  The
 * patch text is pointed at by patch, and its byte length
 * is stored in size.  leading and trailing are the number
 * of context lines.
 */
