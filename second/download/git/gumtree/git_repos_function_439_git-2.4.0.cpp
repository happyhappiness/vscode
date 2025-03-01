int git_config_bool_or_int(const char *name, const char *value, int *is_bool)
{
	int v = git_config_maybe_bool_text(name, value);
	if (0 <= v) {
		*is_bool = 1;
		return v;
	}
	*is_bool = 0;
	return git_config_int(name, value);
}