int cmd_whatchanged(int argc, const char **argv, const char *prefix)
{
	struct rev_info rev;
	struct setup_revision_opt opt;

	init_log_defaults();
	git_config(git_log_config, NULL);

	init_revisions(&rev, prefix);
	rev.diff = 1;
	rev.simplify_history = 0;
	memset(&opt, 0, sizeof(opt));
	opt.def = "HEAD";
	opt.revarg_opt = REVARG_COMMITTISH;
	cmd_log_init(argc, argv, prefix, &rev, &opt);
	if (!rev.diffopt.output_format)
		rev.diffopt.output_format = DIFF_FORMAT_RAW;
	return cmd_log_walk(&rev);
}