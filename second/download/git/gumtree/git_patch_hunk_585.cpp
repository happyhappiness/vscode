 
 		it = &(s->ignored.items[i]);
 		wt_shortstatus_other(it, s, "!!");
 	}
 }
 
-void wt_porcelain_print(struct wt_status *s)
+static void wt_porcelain_print(struct wt_status *s)
 {
 	s->use_color = 0;
 	s->relative_paths = 0;
 	s->prefix = NULL;
 	s->no_gettext = 1;
 	wt_shortstatus_print(s);
 }
+
+/*
+ * Print branch information for porcelain v2 output.  These lines
+ * are printed when the '--branch' parameter is given.
+ *
+ *    # branch.oid <commit><eol>
+ *    # branch.head <head><eol>
+ *   [# branch.upstream <upstream><eol>
+ *   [# branch.ab +<ahead> -<behind><eol>]]
+ *
+ *      <commit> ::= the current commit hash or the the literal
+ *                   "(initial)" to indicate an initialized repo
+ *                   with no commits.
+ *
+ *        <head> ::= <branch_name> the current branch name or
+ *                   "(detached)" literal when detached head or
+ *                   "(unknown)" when something is wrong.
+ *
+ *    <upstream> ::= the upstream branch name, when set.
+ *
+ *       <ahead> ::= integer ahead value, when upstream set
+ *                   and the commit is present (not gone).
+ *
+ *      <behind> ::= integer behind value, when upstream set
+ *                   and commit is present.
+ *
+ *
+ * The end-of-line is defined by the -z flag.
+ *
+ *                 <eol> ::= NUL when -z,
+ *                           LF when NOT -z.
+ *
+ */
+static void wt_porcelain_v2_print_tracking(struct wt_status *s)
+{
+	struct branch *branch;
+	const char *base;
+	const char *branch_name;
+	struct wt_status_state state;
+	int ab_info, nr_ahead, nr_behind;
+	char eol = s->null_termination ? '\0' : '\n';
+
+	memset(&state, 0, sizeof(state));
+	wt_status_get_state(&state, s->branch && !strcmp(s->branch, "HEAD"));
+
+	fprintf(s->fp, "# branch.oid %s%c",
+			(s->is_initial ? "(initial)" : sha1_to_hex(s->sha1_commit)),
+			eol);
+
+	if (!s->branch)
+		fprintf(s->fp, "# branch.head %s%c", "(unknown)", eol);
+	else {
+		if (!strcmp(s->branch, "HEAD")) {
+			fprintf(s->fp, "# branch.head %s%c", "(detached)", eol);
+
+			if (state.rebase_in_progress || state.rebase_interactive_in_progress)
+				branch_name = state.onto;
+			else if (state.detached_from)
+				branch_name = state.detached_from;
+			else
+				branch_name = "";
+		} else {
+			branch_name = NULL;
+			skip_prefix(s->branch, "refs/heads/", &branch_name);
+
+			fprintf(s->fp, "# branch.head %s%c", branch_name, eol);
+		}
+
+		/* Lookup stats on the upstream tracking branch, if set. */
+		branch = branch_get(branch_name);
+		base = NULL;
+		ab_info = (stat_tracking_info(branch, &nr_ahead, &nr_behind, &base) == 0);
+		if (base) {
+			base = shorten_unambiguous_ref(base, 0);
+			fprintf(s->fp, "# branch.upstream %s%c", base, eol);
+			free((char *)base);
+
+			if (ab_info)
+				fprintf(s->fp, "# branch.ab +%d -%d%c", nr_ahead, nr_behind, eol);
+		}
+	}
+
+	free(state.branch);
+	free(state.onto);
+	free(state.detached_from);
+}
+
+/*
+ * Convert various submodule status values into a
+ * fixed-length string of characters in the buffer provided.
+ */
+static void wt_porcelain_v2_submodule_state(
+	struct wt_status_change_data *d,
+	char sub[5])
+{
+	if (S_ISGITLINK(d->mode_head) ||
+		S_ISGITLINK(d->mode_index) ||
+		S_ISGITLINK(d->mode_worktree)) {
+		sub[0] = 'S';
+		sub[1] = d->new_submodule_commits ? 'C' : '.';
+		sub[2] = (d->dirty_submodule & DIRTY_SUBMODULE_MODIFIED) ? 'M' : '.';
+		sub[3] = (d->dirty_submodule & DIRTY_SUBMODULE_UNTRACKED) ? 'U' : '.';
+	} else {
+		sub[0] = 'N';
+		sub[1] = '.';
+		sub[2] = '.';
+		sub[3] = '.';
+	}
+	sub[4] = 0;
+}
+
+/*
+ * Fix-up changed entries before we print them.
+ */
+static void wt_porcelain_v2_fix_up_changed(
+	struct string_list_item *it,
+	struct wt_status *s)
+{
+	struct wt_status_change_data *d = it->util;
+
+	if (!d->index_status) {
+		/*
+		 * This entry is unchanged in the index (relative to the head).
+		 * Therefore, the collect_updated_cb was never called for this
+		 * entry (during the head-vs-index scan) and so the head column
+		 * fields were never set.
+		 *
+		 * We must have data for the index column (from the
+		 * index-vs-worktree scan (otherwise, this entry should not be
+		 * in the list of changes)).
+		 *
+		 * Copy index column fields to the head column, so that our
+		 * output looks complete.
+		 */
+		assert(d->mode_head == 0);
+		d->mode_head = d->mode_index;
+		oidcpy(&d->oid_head, &d->oid_index);
+	}
+
+	if (!d->worktree_status) {
+		/*
+		 * This entry is unchanged in the worktree (relative to the index).
+		 * Therefore, the collect_changed_cb was never called for this entry
+		 * (during the index-vs-worktree scan) and so the worktree column
+		 * fields were never set.
+		 *
+		 * We must have data for the index column (from the head-vs-index
+		 * scan).
+		 *
+		 * Copy the index column fields to the worktree column so that
+		 * our output looks complete.
+		 *
+		 * Note that we only have a mode field in the worktree column
+		 * because the scan code tries really hard to not have to compute it.
+		 */
+		assert(d->mode_worktree == 0);
+		d->mode_worktree = d->mode_index;
+	}
+}
+
+/*
+ * Print porcelain v2 info for tracked entries with changes.
+ */
+static void wt_porcelain_v2_print_changed_entry(
+	struct string_list_item *it,
+	struct wt_status *s)
+{
+	struct wt_status_change_data *d = it->util;
+	struct strbuf buf_index = STRBUF_INIT;
+	struct strbuf buf_head = STRBUF_INIT;
+	const char *path_index = NULL;
+	const char *path_head = NULL;
+	char key[3];
+	char submodule_token[5];
+	char sep_char, eol_char;
+
+	wt_porcelain_v2_fix_up_changed(it, s);
+	wt_porcelain_v2_submodule_state(d, submodule_token);
+
+	key[0] = d->index_status ? d->index_status : '.';
+	key[1] = d->worktree_status ? d->worktree_status : '.';
+	key[2] = 0;
+
+	if (s->null_termination) {
+		/*
+		 * In -z mode, we DO NOT C-quote pathnames.  Current path is ALWAYS first.
+		 * A single NUL character separates them.
+		 */
+		sep_char = '\0';
+		eol_char = '\0';
+		path_index = it->string;
+		path_head = d->head_path;
+	} else {
+		/*
+		 * Path(s) are C-quoted if necessary. Current path is ALWAYS first.
+		 * The source path is only present when necessary.
+		 * A single TAB separates them (because paths can contain spaces
+		 * which are not escaped and C-quoting does escape TAB characters).
+		 */
+		sep_char = '\t';
+		eol_char = '\n';
+		path_index = quote_path(it->string, s->prefix, &buf_index);
+		if (d->head_path)
+			path_head = quote_path(d->head_path, s->prefix, &buf_head);
+	}
+
+	if (path_head)
+		fprintf(s->fp, "2 %s %s %06o %06o %06o %s %s %c%d %s%c%s%c",
+				key, submodule_token,
+				d->mode_head, d->mode_index, d->mode_worktree,
+				oid_to_hex(&d->oid_head), oid_to_hex(&d->oid_index),
+				key[0], d->score,
+				path_index, sep_char, path_head, eol_char);
+	else
+		fprintf(s->fp, "1 %s %s %06o %06o %06o %s %s %s%c",
+				key, submodule_token,
+				d->mode_head, d->mode_index, d->mode_worktree,
+				oid_to_hex(&d->oid_head), oid_to_hex(&d->oid_index),
+				path_index, eol_char);
+
+	strbuf_release(&buf_index);
+	strbuf_release(&buf_head);
+}
+
+/*
+ * Print porcelain v2 status info for unmerged entries.
+ */
+static void wt_porcelain_v2_print_unmerged_entry(
+	struct string_list_item *it,
+	struct wt_status *s)
+{
+	struct wt_status_change_data *d = it->util;
+	const struct cache_entry *ce;
+	struct strbuf buf_index = STRBUF_INIT;
+	const char *path_index = NULL;
+	int pos, stage, sum;
+	struct {
+		int mode;
+		struct object_id oid;
+	} stages[3];
+	char *key;
+	char submodule_token[5];
+	char unmerged_prefix = 'u';
+	char eol_char = s->null_termination ? '\0' : '\n';
+
+	wt_porcelain_v2_submodule_state(d, submodule_token);
+
+	switch (d->stagemask) {
+	case 1: key = "DD"; break; /* both deleted */
+	case 2: key = "AU"; break; /* added by us */
+	case 3: key = "UD"; break; /* deleted by them */
+	case 4: key = "UA"; break; /* added by them */
+	case 5: key = "DU"; break; /* deleted by us */
+	case 6: key = "AA"; break; /* both added */
+	case 7: key = "UU"; break; /* both modified */
+	default:
+		die("BUG: unhandled unmerged status %x", d->stagemask);
+	}
+
+	/*
+	 * Disregard d.aux.porcelain_v2 data that we accumulated
+	 * for the head and index columns during the scans and
+	 * replace with the actual stage data.
+	 *
+	 * Note that this is a last-one-wins for each the individual
+	 * stage [123] columns in the event of multiple cache entries
+	 * for same stage.
+	 */
+	memset(stages, 0, sizeof(stages));
+	sum = 0;
+	pos = cache_name_pos(it->string, strlen(it->string));
+	assert(pos < 0);
+	pos = -pos-1;
+	while (pos < active_nr) {
+		ce = active_cache[pos++];
+		stage = ce_stage(ce);
+		if (strcmp(ce->name, it->string) || !stage)
+			break;
+		stages[stage - 1].mode = ce->ce_mode;
+		hashcpy(stages[stage - 1].oid.hash, ce->oid.hash);
+		sum |= (1 << (stage - 1));
+	}
+	if (sum != d->stagemask)
+		die("BUG: observed stagemask 0x%x != expected stagemask 0x%x", sum, d->stagemask);
+
+	if (s->null_termination)
+		path_index = it->string;
+	else
+		path_index = quote_path(it->string, s->prefix, &buf_index);
+
+	fprintf(s->fp, "%c %s %s %06o %06o %06o %06o %s %s %s %s%c",
+			unmerged_prefix, key, submodule_token,
+			stages[0].mode, /* stage 1 */
+			stages[1].mode, /* stage 2 */
+			stages[2].mode, /* stage 3 */
+			d->mode_worktree,
+			oid_to_hex(&stages[0].oid), /* stage 1 */
+			oid_to_hex(&stages[1].oid), /* stage 2 */
+			oid_to_hex(&stages[2].oid), /* stage 3 */
+			path_index,
+			eol_char);
+
+	strbuf_release(&buf_index);
+}
+
+/*
+ * Print porcelain V2 status info for untracked and ignored entries.
+ */
+static void wt_porcelain_v2_print_other(
+	struct string_list_item *it,
+	struct wt_status *s,
+	char prefix)
+{
+	struct strbuf buf = STRBUF_INIT;
+	const char *path;
+	char eol_char;
+
+	if (s->null_termination) {
+		path = it->string;
+		eol_char = '\0';
+	} else {
+		path = quote_path(it->string, s->prefix, &buf);
+		eol_char = '\n';
+	}
+
+	fprintf(s->fp, "%c %s%c", prefix, path, eol_char);
+
+	strbuf_release(&buf);
+}
+
+/*
+ * Print porcelain V2 status.
+ *
+ * [<v2_branch>]
+ * [<v2_changed_items>]*
+ * [<v2_unmerged_items>]*
+ * [<v2_untracked_items>]*
+ * [<v2_ignored_items>]*
+ *
+ */
+static void wt_porcelain_v2_print(struct wt_status *s)
+{
+	struct wt_status_change_data *d;
+	struct string_list_item *it;
+	int i;
+
+	if (s->show_branch)
+		wt_porcelain_v2_print_tracking(s);
+
+	for (i = 0; i < s->change.nr; i++) {
+		it = &(s->change.items[i]);
+		d = it->util;
+		if (!d->stagemask)
+			wt_porcelain_v2_print_changed_entry(it, s);
+	}
+
+	for (i = 0; i < s->change.nr; i++) {
+		it = &(s->change.items[i]);
+		d = it->util;
+		if (d->stagemask)
+			wt_porcelain_v2_print_unmerged_entry(it, s);
+	}
+
+	for (i = 0; i < s->untracked.nr; i++) {
+		it = &(s->untracked.items[i]);
+		wt_porcelain_v2_print_other(it, s, '?');
+	}
+
+	for (i = 0; i < s->ignored.nr; i++) {
+		it = &(s->ignored.items[i]);
+		wt_porcelain_v2_print_other(it, s, '!');
+	}
+}
+
+void wt_status_print(struct wt_status *s)
+{
+	switch (s->status_format) {
+	case STATUS_FORMAT_SHORT:
+		wt_shortstatus_print(s);
+		break;
+	case STATUS_FORMAT_PORCELAIN:
+		wt_porcelain_print(s);
+		break;
+	case STATUS_FORMAT_PORCELAIN_V2:
+		wt_porcelain_v2_print(s);
+		break;
+	case STATUS_FORMAT_UNSPECIFIED:
+		die("BUG: finalize_deferred_config() should have been called");
+		break;
+	case STATUS_FORMAT_NONE:
+	case STATUS_FORMAT_LONG:
+		wt_longstatus_print(s);
+		break;
+	}
+}
+
+/**
+ * Returns 1 if there are unstaged changes, 0 otherwise.
+ */
+int has_unstaged_changes(int ignore_submodules)
+{
+	struct rev_info rev_info;
+	int result;
+
+	init_revisions(&rev_info, NULL);
+	if (ignore_submodules)
+		DIFF_OPT_SET(&rev_info.diffopt, IGNORE_SUBMODULES);
+	DIFF_OPT_SET(&rev_info.diffopt, QUICK);
+	diff_setup_done(&rev_info.diffopt);
+	result = run_diff_files(&rev_info, 0);
+	return diff_result_code(&rev_info.diffopt, result);
+}
+
+/**
+ * Returns 1 if there are uncommitted changes, 0 otherwise.
+ */
+int has_uncommitted_changes(int ignore_submodules)
+{
+	struct rev_info rev_info;
+	int result;
+
+	if (is_cache_unborn())
+		return 0;
+
+	init_revisions(&rev_info, NULL);
+	if (ignore_submodules)
+		DIFF_OPT_SET(&rev_info.diffopt, IGNORE_SUBMODULES);
+	DIFF_OPT_SET(&rev_info.diffopt, QUICK);
+	add_head_to_pending(&rev_info);
+	diff_setup_done(&rev_info.diffopt);
+	result = run_diff_index(&rev_info, 1);
+	return diff_result_code(&rev_info.diffopt, result);
+}
+
+/**
+ * If the work tree has unstaged or uncommitted changes, dies with the
+ * appropriate message.
+ */
+int require_clean_work_tree(const char *action, const char *hint, int ignore_submodules, int gently)
+{
+	struct lock_file *lock_file = xcalloc(1, sizeof(*lock_file));
+	int err = 0;
+
+	hold_locked_index(lock_file, 0);
+	refresh_cache(REFRESH_QUIET);
+	update_index_if_able(&the_index, lock_file);
+	rollback_lock_file(lock_file);
+
+	if (has_unstaged_changes(ignore_submodules)) {
+		/* TRANSLATORS: the action is e.g. "pull with rebase" */
+		error(_("cannot %s: You have unstaged changes."), _(action));
+		err = 1;
+	}
+
+	if (has_uncommitted_changes(ignore_submodules)) {
+		if (err)
+			error(_("additionally, your index contains uncommitted changes."));
+		else
+			error(_("cannot %s: Your index contains uncommitted changes."),
+			      _(action));
+		err = 1;
+	}
+
+	if (err) {
+		if (hint)
+			error("%s", hint);
+		if (!gently)
+			exit(128);
+	}
+
+	return err;
+}
