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

	if (!strcmp(var, "grep.fullname")) {
		opt->relative = !git_config_bool(var, value);
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
	else if (!strcmp(var, "color.grep.matchcontext"))
		color = opt->color_match_context;
	else if (!strcmp(var, "color.grep.matchselected"))
		color = opt->color_match_selected;
	else if (!strcmp(var, "color.grep.selected"))
		color = opt->color_selected;
	else if (!strcmp(var, "color.grep.separator"))
		color = opt->color_sep;
	else if (!strcmp(var, "color.grep.match")) {
		int rc = 0;
		if (!value)
			return config_error_nonbool(var);
		rc |= color_parse(value, opt->color_match_context);
		rc |= color_parse(value, opt->color_match_selected);
		return rc;
	}

	if (color) {
		if (!value)
			return config_error_nonbool(var);
		return color_parse(value, color);
	}
	return 0;
}