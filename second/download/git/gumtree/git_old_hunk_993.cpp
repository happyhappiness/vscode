}

int git_config_pathname(const char **dest, const char *var, const char *value)
{
	if (!value)
		return config_error_nonbool(var);
	*dest = expand_user_path(value);
	if (!*dest)
		die(_("failed to expand user dir in: '%s'"), value);
	return 0;
}

static int git_default_core_config(const char *var, const char *value)
