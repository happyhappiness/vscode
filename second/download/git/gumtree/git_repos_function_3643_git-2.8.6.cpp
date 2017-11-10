static int match_expr(struct grep_opt *opt, char *bol, char *eol,
		      enum grep_context ctx, int collect_hits)
{
	struct grep_expr *x = opt->pattern_expression;
	return match_expr_eval(x, bol, eol, ctx, collect_hits);
}