void grep_init(struct grep_opt *opt, const char *prefix)
{
	struct grep_opt *def = &grep_defaults;

	memset(opt, 0, sizeof(*opt));
	opt->prefix = prefix;
	opt->prefix_length = (prefix && *prefix) ? strlen(prefix) : 0;
	opt->pattern_tail = &opt->pattern_list;
	opt->header_tail = &opt->header_list;

	opt->color = def->color;
	opt->extended_regexp_option = def->extended_regexp_option;
	opt->pattern_type_option = def->pattern_type_option;
	opt->linenum = def->linenum;
	opt->max_depth = def->max_depth;
	opt->pathname = def->pathname;
	opt->relative = def->relative;
	opt->output = def->output;

	color_set(opt->color_context, def->color_context);
	color_set(opt->color_filename, def->color_filename);
	color_set(opt->color_function, def->color_function);
	color_set(opt->color_lineno, def->color_lineno);
	color_set(opt->color_match_context, def->color_match_context);
	color_set(opt->color_match_selected, def->color_match_selected);
	color_set(opt->color_selected, def->color_selected);
	color_set(opt->color_sep, def->color_sep);
}