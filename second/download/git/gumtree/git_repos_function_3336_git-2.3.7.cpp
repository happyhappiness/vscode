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
	opt->regflags = def->regflags;
	opt->relative = def->relative;

	strcpy(opt->color_context, def->color_context);
	strcpy(opt->color_filename, def->color_filename);
	strcpy(opt->color_function, def->color_function);
	strcpy(opt->color_lineno, def->color_lineno);
	strcpy(opt->color_match_context, def->color_match_context);
	strcpy(opt->color_match_selected, def->color_match_selected);
	strcpy(opt->color_selected, def->color_selected);
	strcpy(opt->color_sep, def->color_sep);
}