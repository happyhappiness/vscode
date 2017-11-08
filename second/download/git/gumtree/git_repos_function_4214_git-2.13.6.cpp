static void dump_grep_expression(struct grep_opt *opt)
{
	struct grep_expr *x = opt->pattern_expression;

	if (opt->all_match)
		fprintf(stderr, "[all-match]\n");
	dump_grep_expression_1(x, 0);
	fflush(NULL);
}