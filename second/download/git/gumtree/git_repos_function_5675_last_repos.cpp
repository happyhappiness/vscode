static void cmd_log_init(int argc, const char **argv, const char *prefix,
			 struct rev_info *rev, struct setup_revision_opt *opt)
{
	cmd_log_init_defaults(rev);
	cmd_log_init_finish(argc, argv, prefix, rev, opt);
}