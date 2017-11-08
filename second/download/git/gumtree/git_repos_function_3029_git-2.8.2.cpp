static void show_diff_tree(const char *prefix, struct commit *commit)
{
	struct rev_info opt;

	/* diff-tree init */
	init_revisions(&opt, prefix);
	git_config(git_diff_basic_config, NULL); /* no "diff" UI options */
	opt.abbrev = 0;
	opt.diff = 1;

	/* This is what "--pretty" does */
	opt.verbose_header = 1;
	opt.use_terminator = 0;
	opt.commit_format = CMIT_FMT_DEFAULT;

	/* diff-tree init */
	if (!opt.diffopt.output_format)
		opt.diffopt.output_format = DIFF_FORMAT_RAW;

	log_tree_commit(&opt, commit);
}