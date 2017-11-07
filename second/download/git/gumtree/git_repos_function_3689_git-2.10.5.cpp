void init_grep_defaults(void)
{
	struct grep_opt *opt = &grep_defaults;
	static int run_once;

	if (run_once)
		return;
	run_once++;

	memset(opt, 0, sizeof(*opt));
	opt->relative = 1;
	opt->pathname = 1;
	opt->regflags = REG_NEWLINE;
	opt->max_depth = -1;
	opt->pattern_type_option = GREP_PATTERN_TYPE_UNSPECIFIED;
	opt->extended_regexp_option = 0;
	color_set(opt->color_context, "");
	color_set(opt->color_filename, "");
	color_set(opt->color_function, "");
	color_set(opt->color_lineno, "");
	color_set(opt->color_match_context, GIT_COLOR_BOLD_RED);
	color_set(opt->color_match_selected, GIT_COLOR_BOLD_RED);
	color_set(opt->color_selected, "");
	color_set(opt->color_sep, GIT_COLOR_CYAN);
	opt->color = -1;
}