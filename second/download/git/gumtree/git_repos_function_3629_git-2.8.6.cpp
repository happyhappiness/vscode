void compile_grep_patterns(struct grep_opt *opt)
{
	compile_grep_patterns_real(opt);
	if (opt->debug)
		dump_grep_expression(opt);
}