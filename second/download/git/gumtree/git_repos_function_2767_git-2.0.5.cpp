int parse_merge_opt(struct merge_options *o, const char *s)
{
	if (!s || !*s)
		return -1;
	if (!strcmp(s, "ours"))
		o->recursive_variant = MERGE_RECURSIVE_OURS;
	else if (!strcmp(s, "theirs"))
		o->recursive_variant = MERGE_RECURSIVE_THEIRS;
	else if (!strcmp(s, "subtree"))
		o->subtree_shift = "";
	else if (starts_with(s, "subtree="))
		o->subtree_shift = s + strlen("subtree=");
	else if (!strcmp(s, "patience"))
		o->xdl_opts = DIFF_WITH_ALG(o, PATIENCE_DIFF);
	else if (!strcmp(s, "histogram"))
		o->xdl_opts = DIFF_WITH_ALG(o, HISTOGRAM_DIFF);
	else if (starts_with(s, "diff-algorithm=")) {
		long value = parse_algorithm_value(s + strlen("diff-algorithm="));
		if (value < 0)
			return -1;
		/* clear out previous settings */
		DIFF_XDL_CLR(o, NEED_MINIMAL);
		o->xdl_opts &= ~XDF_DIFF_ALGORITHM_MASK;
		o->xdl_opts |= value;
	}
	else if (!strcmp(s, "ignore-space-change"))
		o->xdl_opts |= XDF_IGNORE_WHITESPACE_CHANGE;
	else if (!strcmp(s, "ignore-all-space"))
		o->xdl_opts |= XDF_IGNORE_WHITESPACE;
	else if (!strcmp(s, "ignore-space-at-eol"))
		o->xdl_opts |= XDF_IGNORE_WHITESPACE_AT_EOL;
	else if (!strcmp(s, "renormalize"))
		o->renormalize = 1;
	else if (!strcmp(s, "no-renormalize"))
		o->renormalize = 0;
	else if (starts_with(s, "rename-threshold=")) {
		const char *score = s + strlen("rename-threshold=");
		if ((o->rename_score = parse_rename_score(&score)) == -1 || *score != 0)
			return -1;
	}
	else
		return -1;
	return 0;
}