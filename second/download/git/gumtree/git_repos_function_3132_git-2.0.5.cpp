int grep_config(const char *var, const char *value, void *cb)
{
	struct grep_opt *opt = &grep_defaults;
	char *color = NULL;

	if (userdiff_config(var, value) < 0)
		return -1;

	if (!strcmp(var, "grep.extendedregexp")) {
		if (git_config_bool(var, value))
			opt->extended_regexp_option = 1;
		else
			opt->extended_regexp_option = 0;
		return 0;
	}

	if (!strcmp(var, "grep.patterntype")) {
		opt->pattern_type_option = parse_pattern_type_arg(var, value);
		return 0;
	}

	if (!strcmp(var, "grep.linenumber")) {
		opt->linenum = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "color.grep"))
		opt->color = git_config_colorbool(var, value);
	else if (!strcmp(var, "color.grep.context"))
		color = opt->color_context;
	else if (!strcmp(var, "color.grep.filename"))
		color = opt->color_filename;
	else if (!strcmp(var, "color.grep.function"))
		color = opt->color_function;
	else if (!strcmp(var, "color.grep.linenumber"))
		color = opt->color_lineno;
	else if (!strcmp(var, "color.grep.match"))
		color = opt->color_match;
	else if (!strcmp(var, "color.grep.selected"))
		color = opt->color_selected;
	else if (!strcmp(var, "color.grep.separator"))
		color = opt->color_sep;

	if (color) {
		if (!value)
			return config_error_nonbool(var);
		color_parse(value, var, color);
	}
	return 0;
}