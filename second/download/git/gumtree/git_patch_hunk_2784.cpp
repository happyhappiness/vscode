 	strbuf_release(&fancy);
 	if (added_decoration)
 		strbuf_addch(stat, ' ');
 	free(ref);
 }
 
-static void add_verbose_info(struct strbuf *out, struct ref_item *item,
-			     int verbose, int abbrev)
+static void add_verbose_info(struct strbuf *out, struct ref_array_item *item,
+			     struct ref_filter *filter, const char *refname)
 {
 	struct strbuf subject = STRBUF_INIT, stat = STRBUF_INIT;
 	const char *sub = _(" **** invalid ref ****");
 	struct commit *commit = item->commit;
 
 	if (!parse_commit(commit)) {
 		pp_commit_easy(CMIT_FMT_ONELINE, commit, &subject);
 		sub = subject.buf;
 	}
 
-	if (item->kind == REF_LOCAL_BRANCH)
-		fill_tracking_info(&stat, item->name, verbose > 1);
+	if (item->kind == FILTER_REFS_BRANCHES)
+		fill_tracking_info(&stat, refname, filter->verbose > 1);
 
 	strbuf_addf(out, " %s %s%s",
-		find_unique_abbrev(item->commit->object.sha1, abbrev),
+		find_unique_abbrev(item->commit->object.oid.hash, filter->abbrev),
 		stat.buf, sub);
 	strbuf_release(&stat);
 	strbuf_release(&subject);
 }
 
-static void print_ref_item(struct ref_item *item, int maxwidth, int verbose,
-			   int abbrev, int current, char *prefix)
+static char *get_head_description(void)
+{
+	struct strbuf desc = STRBUF_INIT;
+	struct wt_status_state state;
+	memset(&state, 0, sizeof(state));
+	wt_status_get_state(&state, 1);
+	if (state.rebase_in_progress ||
+	    state.rebase_interactive_in_progress)
+		strbuf_addf(&desc, _("(no branch, rebasing %s)"),
+			    state.branch);
+	else if (state.bisect_in_progress)
+		strbuf_addf(&desc, _("(no branch, bisect started on %s)"),
+			    state.branch);
+	else if (state.detached_from) {
+		/* TRANSLATORS: make sure these match _("HEAD detached at ")
+		   and _("HEAD detached from ") in wt-status.c */
+		if (state.detached_at)
+			strbuf_addf(&desc, _("(HEAD detached at %s)"),
+				state.detached_from);
+		else
+			strbuf_addf(&desc, _("(HEAD detached from %s)"),
+				state.detached_from);
+	}
+	else
+		strbuf_addstr(&desc, _("(no branch)"));
+	free(state.branch);
+	free(state.onto);
+	free(state.detached_from);
+	return strbuf_detach(&desc, NULL);
+}
+
+static void format_and_print_ref_item(struct ref_array_item *item, int maxwidth,
+				      struct ref_filter *filter, const char *remote_prefix)
 {
 	char c;
+	int current = 0;
 	int color;
 	struct strbuf out = STRBUF_INIT, name = STRBUF_INIT;
-
-	if (item->ignore)
-		return;
+	const char *prefix = "";
+	const char *desc = item->refname;
+	char *to_free = NULL;
 
 	switch (item->kind) {
-	case REF_LOCAL_BRANCH:
-		color = BRANCH_COLOR_LOCAL;
+	case FILTER_REFS_BRANCHES:
+		skip_prefix(desc, "refs/heads/", &desc);
+		if (!filter->detached && !strcmp(desc, head))
+			current = 1;
+		else
+			color = BRANCH_COLOR_LOCAL;
 		break;
-	case REF_REMOTE_BRANCH:
+	case FILTER_REFS_REMOTES:
+		skip_prefix(desc, "refs/remotes/", &desc);
 		color = BRANCH_COLOR_REMOTE;
+		prefix = remote_prefix;
+		break;
+	case FILTER_REFS_DETACHED_HEAD:
+		desc = to_free = get_head_description();
+		current = 1;
 		break;
 	default:
 		color = BRANCH_COLOR_PLAIN;
 		break;
 	}
 
 	c = ' ';
 	if (current) {
 		c = '*';
 		color = BRANCH_COLOR_CURRENT;
 	}
 
-	strbuf_addf(&name, "%s%s", prefix, item->name);
-	if (verbose) {
+	strbuf_addf(&name, "%s%s", prefix, desc);
+	if (filter->verbose) {
 		int utf8_compensation = strlen(name.buf) - utf8_strwidth(name.buf);
 		strbuf_addf(&out, "%c %s%-*s%s", c, branch_get_color(color),
 			    maxwidth + utf8_compensation, name.buf,
 			    branch_get_color(BRANCH_COLOR_RESET));
 	} else
 		strbuf_addf(&out, "%c %s%s%s", c, branch_get_color(color),
 			    name.buf, branch_get_color(BRANCH_COLOR_RESET));
 
-	if (item->dest)
-		strbuf_addf(&out, " -> %s", item->dest);
-	else if (verbose)
+	if (item->symref) {
+		skip_prefix(item->symref, "refs/remotes/", &desc);
+		strbuf_addf(&out, " -> %s", desc);
+	}
+	else if (filter->verbose)
 		/* " f7c0c00 [ahead 58, behind 197] vcs-svn: drop obj_pool.h" */
-		add_verbose_info(&out, item, verbose, abbrev);
+		add_verbose_info(&out, item, filter, desc);
 	if (column_active(colopts)) {
-		assert(!verbose && "--column and --verbose are incompatible");
+		assert(!filter->verbose && "--column and --verbose are incompatible");
 		string_list_append(&output, out.buf);
 	} else {
 		printf("%s\n", out.buf);
 	}
 	strbuf_release(&name);
 	strbuf_release(&out);
+	free(to_free);
 }
 
-static int calc_maxwidth(struct ref_list *refs)
-{
-	int i, w = 0;
-	for (i = 0; i < refs->index; i++) {
-		if (refs->list[i].ignore)
-			continue;
-		if (refs->list[i].width > w)
-			w = refs->list[i].width;
-	}
-	return w;
-}
-
-static char *get_head_description(void)
+static int calc_maxwidth(struct ref_array *refs, int remote_bonus)
 {
-	struct strbuf desc = STRBUF_INIT;
-	struct wt_status_state state;
-	memset(&state, 0, sizeof(state));
-	wt_status_get_state(&state, 1);
-	if (state.rebase_in_progress ||
-	    state.rebase_interactive_in_progress)
-		strbuf_addf(&desc, _("(no branch, rebasing %s)"),
-			    state.branch);
-	else if (state.bisect_in_progress)
-		strbuf_addf(&desc, _("(no branch, bisect started on %s)"),
-			    state.branch);
-	else if (state.detached_from) {
-		/* TRANSLATORS: make sure these match _("HEAD detached at ")
-		   and _("HEAD detached from ") in wt-status.c */
-		if (state.detached_at)
-			strbuf_addf(&desc, _("(HEAD detached at %s)"),
-				state.detached_from);
-		else
-			strbuf_addf(&desc, _("(HEAD detached from %s)"),
-				state.detached_from);
-	}
-	else
-		strbuf_addstr(&desc, _("(no branch)"));
-	free(state.branch);
-	free(state.onto);
-	free(state.detached_from);
-	return strbuf_detach(&desc, NULL);
-}
+	int i, max = 0;
+	for (i = 0; i < refs->nr; i++) {
+		struct ref_array_item *it = refs->items[i];
+		const char *desc = it->refname;
+		int w;
 
-static void show_detached(struct ref_list *ref_list)
-{
-	struct commit *head_commit = lookup_commit_reference_gently(head_sha1, 1);
+		skip_prefix(it->refname, "refs/heads/", &desc);
+		skip_prefix(it->refname, "refs/remotes/", &desc);
+		w = utf8_strwidth(desc);
 
-	if (head_commit && is_descendant_of(head_commit, ref_list->with_commit)) {
-		struct ref_item item;
-		item.name = get_head_description();
-		item.width = utf8_strwidth(item.name);
-		item.kind = REF_LOCAL_BRANCH;
-		item.dest = NULL;
-		item.commit = head_commit;
-		item.ignore = 0;
-		if (item.width > ref_list->maxwidth)
-			ref_list->maxwidth = item.width;
-		print_ref_item(&item, ref_list->maxwidth, ref_list->verbose, ref_list->abbrev, 1, "");
-		free(item.name);
+		if (it->kind == FILTER_REFS_REMOTES)
+			w += remote_bonus;
+		if (w > max)
+			max = w;
 	}
+	return max;
 }
 
-static int print_ref_list(int kinds, int detached, int verbose, int abbrev, struct commit_list *with_commit, const char **pattern)
+static void print_ref_list(struct ref_filter *filter, struct ref_sorting *sorting)
 {
 	int i;
-	struct append_ref_cb cb;
-	struct ref_list ref_list;
+	struct ref_array array;
+	int maxwidth = 0;
+	const char *remote_prefix = "";
 
-	memset(&ref_list, 0, sizeof(ref_list));
-	ref_list.kinds = kinds;
-	ref_list.verbose = verbose;
-	ref_list.abbrev = abbrev;
-	ref_list.with_commit = with_commit;
-	if (merge_filter != NO_FILTER)
-		init_revisions(&ref_list.revs, NULL);
-	cb.ref_list = &ref_list;
-	cb.pattern = pattern;
-	cb.ret = 0;
-	for_each_rawref(append_ref, &cb);
-	if (merge_filter != NO_FILTER) {
-		struct commit *filter;
-		filter = lookup_commit_reference_gently(merge_filter_ref, 0);
-		if (!filter)
-			die(_("object '%s' does not point to a commit"),
-			    sha1_to_hex(merge_filter_ref));
-
-		filter->object.flags |= UNINTERESTING;
-		add_pending_object(&ref_list.revs,
-				   (struct object *) filter, "");
-		ref_list.revs.limited = 1;
-
-		if (prepare_revision_walk(&ref_list.revs))
-			die(_("revision walk setup failed"));
-
-		for (i = 0; i < ref_list.index; i++) {
-			struct ref_item *item = &ref_list.list[i];
-			struct commit *commit = item->commit;
-			int is_merged = !!(commit->object.flags & UNINTERESTING);
-			item->ignore = is_merged != (merge_filter == SHOW_MERGED);
-		}
-
-		for (i = 0; i < ref_list.index; i++) {
-			struct ref_item *item = &ref_list.list[i];
-			clear_commit_marks(item->commit, ALL_REV_FLAGS);
-		}
-		clear_commit_marks(filter, ALL_REV_FLAGS);
-
-		if (verbose)
-			ref_list.maxwidth = calc_maxwidth(&ref_list);
-	}
+	/*
+	 * If we are listing more than just remote branches,
+	 * then remote branches will have a "remotes/" prefix.
+	 * We need to account for this in the width.
+	 */
+	if (filter->kind != FILTER_REFS_REMOTES)
+		remote_prefix = "remotes/";
 
-	qsort(ref_list.list, ref_list.index, sizeof(struct ref_item), ref_cmp);
+	memset(&array, 0, sizeof(array));
 
-	detached = (detached && (kinds & REF_LOCAL_BRANCH));
-	if (detached && match_patterns(pattern, "HEAD"))
-		show_detached(&ref_list);
+	verify_ref_format("%(refname)%(symref)");
+	filter_refs(&array, filter, filter->kind | FILTER_REFS_INCLUDE_BROKEN);
 
-	for (i = 0; i < ref_list.index; i++) {
-		int current = !detached &&
-			(ref_list.list[i].kind == REF_LOCAL_BRANCH) &&
-			!strcmp(ref_list.list[i].name, head);
-		char *prefix = (kinds != REF_REMOTE_BRANCH &&
-				ref_list.list[i].kind == REF_REMOTE_BRANCH)
-				? "remotes/" : "";
-		print_ref_item(&ref_list.list[i], ref_list.maxwidth, verbose,
-			       abbrev, current, prefix);
-	}
+	if (filter->verbose)
+		maxwidth = calc_maxwidth(&array, strlen(remote_prefix));
 
-	free_ref_list(&ref_list);
+	/*
+	 * If no sorting parameter is given then we default to sorting
+	 * by 'refname'. This would give us an alphabetically sorted
+	 * array with the 'HEAD' ref at the beginning followed by
+	 * local branches 'refs/heads/...' and finally remote-tacking
+	 * branches 'refs/remotes/...'.
+	 */
+	if (!sorting)
+		sorting = ref_default_sorting();
+	ref_array_sort(sorting, &array);
 
-	if (cb.ret)
-		error(_("some refs could not be read"));
+	for (i = 0; i < array.nr; i++)
+		format_and_print_ref_item(array.items[i], maxwidth, filter, remote_prefix);
 
-	return cb.ret;
+	ref_array_clear(&array);
 }
 
 static void rename_branch(const char *oldname, const char *newname, int force)
 {
 	struct strbuf oldref = STRBUF_INIT, newref = STRBUF_INIT, logmsg = STRBUF_INIT;
 	struct strbuf oldsection = STRBUF_INIT, newsection = STRBUF_INIT;
