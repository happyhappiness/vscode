int git_column_config(const char *var, const char *value,
		      const char *command, unsigned int *colopts)
{
	const char *it;

	if (!skip_prefix(var, "column.", &it))
		return 0;

	if (!strcmp(it, "ui"))
		return column_config(var, value, "ui", colopts);

	if (command && !strcmp(it, command))
		return column_config(var, value, it, colopts);

	return 0;
}