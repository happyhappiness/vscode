int diff_can_quit_early(struct diff_options *opt)
{
	return (DIFF_OPT_TST(opt, QUICK) &&
		!opt->filter &&
		DIFF_OPT_TST(opt, HAS_CHANGES));
}