 #include "diff.h"
 #include "parse-options.h"
 #include "xdiff-interface.h"
 #include "ll-merge.h"
 #include "rerere.h"
 
-/*
- *  --check turns on checking that the working tree matches the
- *    files that are being modified, but doesn't apply the patch
- *  --stat does just a diffstat, and doesn't actually apply
- *  --numstat does numeric diffstat, and doesn't actually apply
- *  --index-info shows the old and new index info for paths if available.
- *  --index updates the cache as well.
- *  --cached updates only the cache without ever touching the working tree.
- */
-static const char *prefix;
-static int prefix_length = -1;
-static int newfd = -1;
-
-static int unidiff_zero;
-static int p_value = 1;
-static int p_value_known;
-static int check_index;
-static int update_index;
-static int cached;
-static int diffstat;
-static int numstat;
-static int summary;
-static int check;
-static int apply = 1;
-static int apply_in_reverse;
-static int apply_with_reject;
-static int apply_verbosely;
-static int allow_overlap;
-static int no_add;
-static int threeway;
-static int unsafe_paths;
-static const char *fake_ancestor;
-static int line_termination = '\n';
-static unsigned int p_context = UINT_MAX;
-static const char * const apply_usage[] = {
-	N_("git apply [<options>] [<patch>...]"),
-	NULL
-};
-
-static enum ws_error_action {
+enum ws_error_action {
 	nowarn_ws_error,
 	warn_on_ws_error,
 	die_on_ws_error,
 	correct_ws_error
-} ws_error_action = warn_on_ws_error;
-static int whitespace_error;
-static int squelch_whitespace_errors = 5;
-static int applied_after_fixing_ws;
+};
+
 
-static enum ws_ignore {
+enum ws_ignore {
 	ignore_ws_none,
 	ignore_ws_change
-} ws_ignore_action = ignore_ws_none;
+};
+
+/*
+ * We need to keep track of how symlinks in the preimage are
+ * manipulated by the patches.  A patch to add a/b/c where a/b
+ * is a symlink should not be allowed to affect the directory
+ * the symlink points at, but if the same patch removes a/b,
+ * it is perfectly fine, as the patch removes a/b to make room
+ * to create a directory a/b so that a/b/c can be created.
+ *
+ * See also "struct string_list symlink_changes" in "struct
+ * apply_state".
+ */
+#define SYMLINK_GOES_AWAY 01
+#define SYMLINK_IN_RESULT 02
 
+struct apply_state {
+	const char *prefix;
+	int prefix_length;
+
+	/* These are lock_file related */
+	struct lock_file *lock_file;
+	int newfd;
+
+	/* These control what gets looked at and modified */
+	int apply; /* this is not a dry-run */
+	int cached; /* apply to the index only */
+	int check; /* preimage must match working tree, don't actually apply */
+	int check_index; /* preimage must match the indexed version */
+	int update_index; /* check_index && apply */
+
+	/* These control cosmetic aspect of the output */
+	int diffstat; /* just show a diffstat, and don't actually apply */
+	int numstat; /* just show a numeric diffstat, and don't actually apply */
+	int summary; /* just report creation, deletion, etc, and don't actually apply */
+
+	/* These boolean parameters control how the apply is done */
+	int allow_overlap;
+	int apply_in_reverse;
+	int apply_with_reject;
+	int apply_verbosely;
+	int no_add;
+	int threeway;
+	int unidiff_zero;
+	int unsafe_paths;
+
+	/* Other non boolean parameters */
+	const char *fake_ancestor;
+	const char *patch_input_file;
+	int line_termination;
+	struct strbuf root;
+	int p_value;
+	int p_value_known;
+	unsigned int p_context;
+
+	/* Exclude and include path parameters */
+	struct string_list limit_by_name;
+	int has_include;
+
+	/* Various "current state" */
+	int linenr; /* current line number */
+	struct string_list symlink_changes; /* we have to track symlinks */
 
-static const char *patch_input_file;
-static struct strbuf root = STRBUF_INIT;
-static int read_stdin = 1;
-static int options;
+	/*
+	 * For "diff-stat" like behaviour, we keep track of the biggest change
+	 * we've seen, and the longest filename. That allows us to do simple
+	 * scaling.
+	 */
+	int max_change;
+	int max_len;
 
-static void parse_whitespace_option(const char *option)
+	/*
+	 * Records filenames that have been touched, in order to handle
+	 * the case where more than one patches touch the same file.
+	 */
+	struct string_list fn_table;
+
+	/* These control whitespace errors */
+	enum ws_error_action ws_error_action;
+	enum ws_ignore ws_ignore_action;
+	const char *whitespace_option;
+	int whitespace_error;
+	int squelch_whitespace_errors;
+	int applied_after_fixing_ws;
+};
+
+static const char * const apply_usage[] = {
+	N_("git apply [<options>] [<patch>...]"),
+	NULL
+};
+
+static void parse_whitespace_option(struct apply_state *state, const char *option)
 {
 	if (!option) {
-		ws_error_action = warn_on_ws_error;
+		state->ws_error_action = warn_on_ws_error;
 		return;
 	}
 	if (!strcmp(option, "warn")) {
-		ws_error_action = warn_on_ws_error;
+		state->ws_error_action = warn_on_ws_error;
 		return;
 	}
 	if (!strcmp(option, "nowarn")) {
-		ws_error_action = nowarn_ws_error;
+		state->ws_error_action = nowarn_ws_error;
 		return;
 	}
 	if (!strcmp(option, "error")) {
-		ws_error_action = die_on_ws_error;
+		state->ws_error_action = die_on_ws_error;
 		return;
 	}
 	if (!strcmp(option, "error-all")) {
-		ws_error_action = die_on_ws_error;
-		squelch_whitespace_errors = 0;
+		state->ws_error_action = die_on_ws_error;
+		state->squelch_whitespace_errors = 0;
 		return;
 	}
 	if (!strcmp(option, "strip") || !strcmp(option, "fix")) {
-		ws_error_action = correct_ws_error;
+		state->ws_error_action = correct_ws_error;
 		return;
 	}
 	die(_("unrecognized whitespace option '%s'"), option);
 }
 
-static void parse_ignorewhitespace_option(const char *option)
+static void parse_ignorewhitespace_option(struct apply_state *state,
+					  const char *option)
 {
 	if (!option || !strcmp(option, "no") ||
 	    !strcmp(option, "false") || !strcmp(option, "never") ||
 	    !strcmp(option, "none")) {
-		ws_ignore_action = ignore_ws_none;
+		state->ws_ignore_action = ignore_ws_none;
 		return;
 	}
 	if (!strcmp(option, "change")) {
-		ws_ignore_action = ignore_ws_change;
+		state->ws_ignore_action = ignore_ws_change;
 		return;
 	}
 	die(_("unrecognized whitespace ignore option '%s'"), option);
 }
 
-static void set_default_whitespace_mode(const char *whitespace_option)
+static void set_default_whitespace_mode(struct apply_state *state)
 {
-	if (!whitespace_option && !apply_default_whitespace)
-		ws_error_action = (apply ? warn_on_ws_error : nowarn_ws_error);
+	if (!state->whitespace_option && !apply_default_whitespace)
+		state->ws_error_action = (state->apply ? warn_on_ws_error : nowarn_ws_error);
 }
 
 /*
- * For "diff-stat" like behaviour, we keep track of the biggest change
- * we've seen, and the longest filename. That allows us to do simple
- * scaling.
- */
-static int max_change, max_len;
-
-/*
- * Various "current state", notably line numbers and what
- * file (and how) we're patching right now.. The "is_xxxx"
- * things are flags, where -1 means "don't know yet".
- */
-static int linenr = 1;
-
-/*
  * This represents one "hunk" from a patch, starting with
  * "@@ -oldpos,oldlines +newpos,newlines @@" marker.  The
  * patch text is pointed at by patch, and its byte length
  * is stored in size.  leading and trailing are the number
  * of context lines.
  */
