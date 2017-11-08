static int match_line(struct grep_opt *opt, char *bol, char *eol,
		      enum grep_context ctx, int collect_hits)
{
	struct grep_pat *p;
	regmatch_t match;

	if (opt->extended)
		return match_expr(opt, bol, eol, ctx, collect_hits);

	/* we do not call with collect_hits without being extended */
	for (p = opt->pattern_list; p; p = p->next) {
		if (match_one_pattern(p, bol, eol, ctx, &match, 0))
			return 1;
	}
	return 0;
}