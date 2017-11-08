static int git_blame_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "blame.showroot")) {
		show_root = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "blame.blankboundary")) {
		blank_boundary = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "blame.date")) {
		if (!value)
			return config_error_nonbool(var);
		blame_date_mode = parse_date_format(value);
		return 0;
	}

	if (userdiff_config(var, value) < 0)
		return -1;

	return git_default_config(var, value, cb);
}