	strbuf_release(&fancy);
	if (added_decoration)
		strbuf_addch(stat, ' ');
	free(ref);
}

static void add_verbose_info(struct strbuf *out, struct ref_item *item,
			     int verbose, int abbrev)
{
	struct strbuf subject = STRBUF_INIT, stat = STRBUF_INIT;
	const char *sub = _(" **** invalid ref ****");
	struct commit *commit = item->commit;

	if (!parse_commit(commit)) {
		pp_commit_easy(CMIT_FMT_ONELINE, commit, &subject);
		sub = subject.buf;
	}

	if (item->kind == REF_LOCAL_BRANCH)
		fill_tracking_info(&stat, item->name, verbose > 1);

	strbuf_addf(out, " %s %s%s",
		find_unique_abbrev(item->commit->object.sha1, abbrev),
		stat.buf, sub);
	strbuf_release(&stat);
	strbuf_release(&subject);
}

static void print_ref_item(struct ref_item *item, int maxwidth, int verbose,
			   int abbrev, int current, char *prefix)
{
	char c;
	int color;
	struct strbuf out = STRBUF_INIT, name = STRBUF_INIT;

	if (item->ignore)
		return;

	switch (item->kind) {
	case REF_LOCAL_BRANCH:
		color = BRANCH_COLOR_LOCAL;
		break;
	case REF_REMOTE_BRANCH:
		color = BRANCH_COLOR_REMOTE;
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

	strbuf_addf(&name, "%s%s", prefix, item->name);
	if (verbose) {
		int utf8_compensation = strlen(name.buf) - utf8_strwidth(name.buf);
		strbuf_addf(&out, "%c %s%-*s%s", c, branch_get_color(color),
			    maxwidth + utf8_compensation, name.buf,
			    branch_get_color(BRANCH_COLOR_RESET));
	} else
		strbuf_addf(&out, "%c %s%s%s", c, branch_get_color(color),
			    name.buf, branch_get_color(BRANCH_COLOR_RESET));

	if (item->dest)
		strbuf_addf(&out, " -> %s", item->dest);
	else if (verbose)
		/* " f7c0c00 [ahead 58, behind 197] vcs-svn: drop obj_pool.h" */
		add_verbose_info(&out, item, verbose, abbrev);
	if (column_active(colopts)) {
		assert(!verbose && "--column and --verbose are incompatible");
		string_list_append(&output, out.buf);
	} else {
		printf("%s\n", out.buf);
	}
	strbuf_release(&name);
	strbuf_release(&out);
}

static int calc_maxwidth(struct ref_list *refs)
{
	int i, w = 0;
	for (i = 0; i < refs->index; i++) {
		if (refs->list[i].ignore)
			continue;
		if (refs->list[i].width > w)
			w = refs->list[i].width;
	}
	return w;
}

static char *get_head_description(void)
{
	struct strbuf desc = STRBUF_INIT;
	struct wt_status_state state;
	memset(&state, 0, sizeof(state));
	wt_status_get_state(&state, 1);
	if (state.rebase_in_progress ||
	    state.rebase_interactive_in_progress)
		strbuf_addf(&desc, _("(no branch, rebasing %s)"),
			    state.branch);
	else if (state.bisect_in_progress)
		strbuf_addf(&desc, _("(no branch, bisect started on %s)"),
			    state.branch);
	else if (state.detached_from) {
		/* TRANSLATORS: make sure these match _("HEAD detached at ")
		   and _("HEAD detached from ") in wt-status.c */
		if (state.detached_at)
			strbuf_addf(&desc, _("(HEAD detached at %s)"),
				state.detached_from);
		else
			strbuf_addf(&desc, _("(HEAD detached from %s)"),
				state.detached_from);
	}
	else
		strbuf_addstr(&desc, _("(no branch)"));
	free(state.branch);
	free(state.onto);
	free(state.detached_from);
	return strbuf_detach(&desc, NULL);
}

static void show_detached(struct ref_list *ref_list)
{
	struct commit *head_commit = lookup_commit_reference_gently(head_sha1, 1);

	if (head_commit && is_descendant_of(head_commit, ref_list->with_commit)) {
		struct ref_item item;
		item.name = get_head_description();
		item.width = utf8_strwidth(item.name);
		item.kind = REF_LOCAL_BRANCH;
		item.dest = NULL;
		item.commit = head_commit;
		item.ignore = 0;
		if (item.width > ref_list->maxwidth)
			ref_list->maxwidth = item.width;
		print_ref_item(&item, ref_list->maxwidth, ref_list->verbose, ref_list->abbrev, 1, "");
		free(item.name);
	}
}

static int print_ref_list(int kinds, int detached, int verbose, int abbrev, struct commit_list *with_commit, const char **pattern)
{
	int i;
	struct append_ref_cb cb;
	struct ref_list ref_list;

	memset(&ref_list, 0, sizeof(ref_list));
	ref_list.kinds = kinds;
	ref_list.verbose = verbose;
	ref_list.abbrev = abbrev;
	ref_list.with_commit = with_commit;
	if (merge_filter != NO_FILTER)
		init_revisions(&ref_list.revs, NULL);
	cb.ref_list = &ref_list;
	cb.pattern = pattern;
	cb.ret = 0;
	for_each_rawref(append_ref, &cb);
	if (merge_filter != NO_FILTER) {
		struct commit *filter;
		filter = lookup_commit_reference_gently(merge_filter_ref, 0);
		if (!filter)
			die(_("object '%s' does not point to a commit"),
			    sha1_to_hex(merge_filter_ref));

		filter->object.flags |= UNINTERESTING;
		add_pending_object(&ref_list.revs,
				   (struct object *) filter, "");
		ref_list.revs.limited = 1;

		if (prepare_revision_walk(&ref_list.revs))
			die(_("revision walk setup failed"));

		for (i = 0; i < ref_list.index; i++) {
			struct ref_item *item = &ref_list.list[i];
			struct commit *commit = item->commit;
			int is_merged = !!(commit->object.flags & UNINTERESTING);
			item->ignore = is_merged != (merge_filter == SHOW_MERGED);
		}

		for (i = 0; i < ref_list.index; i++) {
			struct ref_item *item = &ref_list.list[i];
			clear_commit_marks(item->commit, ALL_REV_FLAGS);
		}
		clear_commit_marks(filter, ALL_REV_FLAGS);

		if (verbose)
			ref_list.maxwidth = calc_maxwidth(&ref_list);
	}

	qsort(ref_list.list, ref_list.index, sizeof(struct ref_item), ref_cmp);

	detached = (detached && (kinds & REF_LOCAL_BRANCH));
	if (detached && match_patterns(pattern, "HEAD"))
		show_detached(&ref_list);

	for (i = 0; i < ref_list.index; i++) {
		int current = !detached &&
			(ref_list.list[i].kind == REF_LOCAL_BRANCH) &&
			!strcmp(ref_list.list[i].name, head);
		char *prefix = (kinds != REF_REMOTE_BRANCH &&
				ref_list.list[i].kind == REF_REMOTE_BRANCH)
				? "remotes/" : "";
		print_ref_item(&ref_list.list[i], ref_list.maxwidth, verbose,
			       abbrev, current, prefix);
	}

	free_ref_list(&ref_list);

	if (cb.ret)
		error(_("some refs could not be read"));

	return cb.ret;
}

static void rename_branch(const char *oldname, const char *newname, int force)
{
	struct strbuf oldref = STRBUF_INIT, newref = STRBUF_INIT, logmsg = STRBUF_INIT;
	struct strbuf oldsection = STRBUF_INIT, newsection = STRBUF_INIT;
