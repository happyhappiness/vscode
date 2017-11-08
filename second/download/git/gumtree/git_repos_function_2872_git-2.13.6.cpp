static int git_config_string_dup(char **dest,
				 const char *var, const char *value)
{
	if (!value)
		return config_error_nonbool(var);
	free(*dest);
	*dest = xstrdup(value);
	return 0;
}