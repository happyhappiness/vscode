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