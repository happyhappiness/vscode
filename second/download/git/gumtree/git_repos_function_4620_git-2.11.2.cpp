static int git_help_config(const char *var, const char *value, void *cb)
{
	if (starts_with(var, "column."))
		return git_column_config(var, value, "help", &colopts);
	if (!strcmp(var, "help.format")) {
		if (!value)
			return config_error_nonbool(var);
		help_format = parse_help_format(value);
		return 0;
	}
	if (!strcmp(var, "help.htmlpath")) {
		if (!value)
			return config_error_nonbool(var);
		html_path = xstrdup(value);
		return 0;
	}
	if (!strcmp(var, "man.viewer")) {
		if (!value)
			return config_error_nonbool(var);
		add_man_viewer(value);
		return 0;
	}
	if (starts_with(var, "man."))
		return add_man_viewer_info(var, value);

	return git_default_config(var, value, cb);
}