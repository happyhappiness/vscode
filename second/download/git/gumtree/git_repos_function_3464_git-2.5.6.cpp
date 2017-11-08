static void compile_grep_patterns_real(struct grep_opt *opt)
{
	struct grep_pat *p;
	struct grep_expr *header_expr = prep_header_patterns(opt);

	for (p = opt->pattern_list; p; p = p->next) {
		switch (p->token) {
		case GREP_PATTERN: /* atom */
		case GREP_PATTERN_HEAD:
		case GREP_PATTERN_BODY:
			compile_regexp(p, opt);
			break;
		default:
			opt->extended = 1;
			break;
		}
	}

	if (opt->all_match || header_expr)
		opt->extended = 1;
	else if (!opt->extended && !opt->debug)
		return;

	p = opt->pattern_list;
	if (p)
		opt->pattern_expression = compile_pattern_expr(&p);
	if (p)
		die("incomplete pattern expression: %s", p->pattern);

	if (!header_expr)
		return;

	if (!opt->pattern_expression)
		opt->pattern_expression = header_expr;
	else if (opt->all_match)
		opt->pattern_expression = grep_splice_or(header_expr,
							 opt->pattern_expression);
	else
		opt->pattern_expression = grep_or_expr(opt->pattern_expression,
						       header_expr);
	opt->all_match = 1;
}