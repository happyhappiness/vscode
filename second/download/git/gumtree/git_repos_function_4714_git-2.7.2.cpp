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