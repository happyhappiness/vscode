static void fill_tracking_info(struct strbuf *stat, const char *branch_name,
		int show_upstream_ref)
{
	int ours, theirs;
	char *ref = NULL;
	struct branch *branch = branch_get(branch_name);
	const char *upstream;
	struct strbuf fancy = STRBUF_INIT;
	int upstream_is_gone = 0;
	int added_decoration = 1;

	if (stat_tracking_info(branch, &ours, &theirs, &upstream) < 0) {
		if (!upstream)
			return;
		upstream_is_gone = 1;
	}

	if (show_upstream_ref) {
		ref = shorten_unambiguous_ref(upstream, 0);
		if (want_color(branch_use_color))
			strbuf_addf(&fancy, "%s%s%s",
					branch_get_color(BRANCH_COLOR_UPSTREAM),
					ref, branch_get_color(BRANCH_COLOR_RESET));
		else
			strbuf_addstr(&fancy, ref);
	}

	if (upstream_is_gone) {
		if (show_upstream_ref)
			strbuf_addf(stat, _("[%s: gone]"), fancy.buf);
		else
			added_decoration = 0;
	} else if (!ours && !theirs) {
		if (show_upstream_ref)
			strbuf_addf(stat, _("[%s]"), fancy.buf);
		else
			added_decoration = 0;
	} else if (!ours) {
		if (show_upstream_ref)
			strbuf_addf(stat, _("[%s: behind %d]"), fancy.buf, theirs);
		else
			strbuf_addf(stat, _("[behind %d]"), theirs);

	} else if (!theirs) {
		if (show_upstream_ref)
			strbuf_addf(stat, _("[%s: ahead %d]"), fancy.buf, ours);
		else
			strbuf_addf(stat, _("[ahead %d]"), ours);
	} else {
		if (show_upstream_ref)
			strbuf_addf(stat, _("[%s: ahead %d, behind %d]"),
				    fancy.buf, ours, theirs);
		else
			strbuf_addf(stat, _("[ahead %d, behind %d]"),
				    ours, theirs);
	}
	strbuf_release(&fancy);
	if (added_decoration)
		strbuf_addch(stat, ' ');
	free(ref);
}