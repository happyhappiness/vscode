	strbuf_release(&fancy);
	if (added_decoration)
		strbuf_addch(stat, ' ');
	free(ref);
}

static void add_verbose_info(struct strbuf *out, struct ref_array_item *item,
			     struct ref_filter *filter, const char *refname)
{
	struct strbuf subject = STRBUF_INIT, stat = STRBUF_INIT;
	const char *sub = _(" **** invalid ref ****");
	struct commit *commit = item->commit;

	if (!parse_commit(commit)) {
		pp_commit_easy(CMIT_FMT_ONELINE, commit, &subject);
		sub = subject.buf;
	}

	if (item->kind == FILTER_REFS_BRANCHES)
		fill_tracking_info(&stat, refname, filter->verbose > 1);

	strbuf_addf(out, " %s %s%s",
		find_unique_abbrev(item->commit->object.oid.hash, filter->abbrev),
		stat.buf, sub);
	strbuf_release(&stat);
	strbuf_release(&subject);
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

static void format_and_print_ref_item(struct ref_array_item *item, int maxwidth,
				      struct ref_filter *filter, const char *remote_prefix)
{
	char c;
	int current = 0;
	int color;
	struct strbuf out = STRBUF_INIT, name = STRBUF_INIT;
	const char *prefix = "";
	const char *desc = item->refname;
	char *to_free = NULL;

	switch (item->kind) {
	case FILTER_REFS_BRANCHES:
		skip_prefix(desc, "refs/heads/", &desc);
		if (!filter->detached && !strcmp(desc, head))
			current = 1;
		else
			color = BRANCH_COLOR_LOCAL;
		break;
	case FILTER_REFS_REMOTES:
		skip_prefix(desc, "refs/remotes/", &desc);
		color = BRANCH_COLOR_REMOTE;
		prefix = remote_prefix;
		break;
	case FILTER_REFS_DETACHED_HEAD:
		desc = to_free = get_head_description();
		current = 1;
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

	strbuf_addf(&name, "%s%s", prefix, desc);
	if (filter->verbose) {
		int utf8_compensation = strlen(name.buf) - utf8_strwidth(name.buf);
		strbuf_addf(&out, "%c %s%-*s%s", c, branch_get_color(color),
			    maxwidth + utf8_compensation, name.buf,
			    branch_get_color(BRANCH_COLOR_RESET));
	} else
		strbuf_addf(&out, "%c %s%s%s", c, branch_get_color(color),
			    name.buf, branch_get_color(BRANCH_COLOR_RESET));

	if (item->symref) {
		skip_prefix(item->symref, "refs/remotes/", &desc);
		strbuf_addf(&out, " -> %s", desc);
	}
	else if (filter->verbose)
		/* " f7c0c00 [ahead 58, behind 197] vcs-svn: drop obj_pool.h" */
		add_verbose_info(&out, item, filter, desc);
	if (column_active(colopts)) {
		assert(!filter->verbose && "--column and --verbose are incompatible");
		string_list_append(&output, out.buf);
	} else {
		printf("%s\n", out.buf);
	}
	strbuf_release(&name);
	strbuf_release(&out);
	free(to_free);
}

static int calc_maxwidth(struct ref_array *refs, int remote_bonus)
{
	int i, max = 0;
	for (i = 0; i < refs->nr; i++) {
		struct ref_array_item *it = refs->items[i];
		const char *desc = it->refname;
		int w;

		skip_prefix(it->refname, "refs/heads/", &desc);
		skip_prefix(it->refname, "refs/remotes/", &desc);
		w = utf8_strwidth(desc);

		if (it->kind == FILTER_REFS_REMOTES)
			w += remote_bonus;
		if (w > max)
			max = w;
	}
	return max;
}

static void print_ref_list(struct ref_filter *filter, struct ref_sorting *sorting)
{
	int i;
	struct ref_array array;
	int maxwidth = 0;
	const char *remote_prefix = "";

	/*
	 * If we are listing more than just remote branches,
	 * then remote branches will have a "remotes/" prefix.
	 * We need to account for this in the width.
	 */
	if (filter->kind != FILTER_REFS_REMOTES)
		remote_prefix = "remotes/";

	memset(&array, 0, sizeof(array));

	verify_ref_format("%(refname)%(symref)");
	filter_refs(&array, filter, filter->kind | FILTER_REFS_INCLUDE_BROKEN);

	if (filter->verbose)
		maxwidth = calc_maxwidth(&array, strlen(remote_prefix));

	/*
	 * If no sorting parameter is given then we default to sorting
	 * by 'refname'. This would give us an alphabetically sorted
	 * array with the 'HEAD' ref at the beginning followed by
	 * local branches 'refs/heads/...' and finally remote-tacking
	 * branches 'refs/remotes/...'.
	 */
	if (!sorting)
		sorting = ref_default_sorting();
	ref_array_sort(sorting, &array);

	for (i = 0; i < array.nr; i++)
		format_and_print_ref_item(array.items[i], maxwidth, filter, remote_prefix);

	ref_array_clear(&array);
}

static void rename_branch(const char *oldname, const char *newname, int force)
{
	struct strbuf oldref = STRBUF_INIT, newref = STRBUF_INIT, logmsg = STRBUF_INIT;
	struct strbuf oldsection = STRBUF_INIT, newsection = STRBUF_INIT;
