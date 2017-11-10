int grep_source(struct grep_opt *opt, struct grep_source *gs)
{
	/*
	 * we do not have to do the two-pass grep when we do not check
	 * buffer-wide "all-match".
	 */
	if (!opt->all_match)
		return grep_source_1(opt, gs, 0);

	/* Otherwise the toplevel "or" terms hit a bit differently.
	 * We first clear hit markers from them.
	 */
	clr_hit_marker(opt->pattern_expression);
	grep_source_1(opt, gs, 1);

	if (!chk_hit_marker(opt->pattern_expression))
		return 0;

	return grep_source_1(opt, gs, 0);
}