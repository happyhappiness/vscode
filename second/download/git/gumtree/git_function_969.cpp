static void format_and_print_ref_item(struct ref_array_item *item, int maxwidth,
				      struct ref_filter *filter, const char *remote_prefix)
{
	char c;
	int current = 0;
	int color;
	struct strbuf out = STRBUF_INIT, name = STRBUF_INIT;
	const char *prefix_to_show = "";
	const char *prefix_to_skip = NULL;
	const char *desc = item->refname;
	char *to_free = NULL;

	switch (item->kind) {
	case FILTER_REFS_BRANCHES:
		prefix_to_skip = "refs/heads/";
		skip_prefix(desc, prefix_to_skip, &desc);
		if (!filter->detached && !strcmp(desc, head))
			current = 1;
		else
			color = BRANCH_COLOR_LOCAL;
		break;
	case FILTER_REFS_REMOTES:
		prefix_to_skip = "refs/remotes/";
		skip_prefix(desc, prefix_to_skip, &desc);
		color = BRANCH_COLOR_REMOTE;
		prefix_to_show = remote_prefix;
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

	strbuf_addf(&name, "%s%s", prefix_to_show, desc);
	if (filter->verbose) {
		int utf8_compensation = strlen(name.buf) - utf8_strwidth(name.buf);
		strbuf_addf(&out, "%c %s%-*s%s", c, branch_get_color(color),
			    maxwidth + utf8_compensation, name.buf,
			    branch_get_color(BRANCH_COLOR_RESET));
	} else
		strbuf_addf(&out, "%c %s%s%s", c, branch_get_color(color),
			    name.buf, branch_get_color(BRANCH_COLOR_RESET));

	if (item->symref) {
		const char *symref = item->symref;
		if (prefix_to_skip)
			skip_prefix(symref, prefix_to_skip, &symref);
		strbuf_addf(&out, " -> %s", symref);
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